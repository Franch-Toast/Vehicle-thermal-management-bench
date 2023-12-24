/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may
 * only be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */
/*!
 * @file interrupt_manager.c
 */

#include "interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Counter to manage the nested callings of global disable/enable interrupt.
 */
static int32_t g_interruptDisableCount = 0;

/*!
 * @brief Declaration of vector table.
 * FEATURE_INTERRUPT_IRQ_MAX is the highest interrupt request number.
 * 16 is the maximum number of exceptions
 */
#if defined(__ARMCC_VERSION)
    extern uint32_t __VECTOR_RAM;
    extern uint32_t __VECTOR_TABLE;
    extern uint32_t __DATA_ROM;
    extern uint32_t __RAM_START;
#else
    extern uint32_t __VECTOR_RAM[((uint32_t)(FEATURE_INTERRUPT_IRQ_MAX)) + 16U + 1U];
    extern uint32_t __VECTOR_TABLE[((uint32_t)(FEATURE_INTERRUPT_IRQ_MAX)) + 16U + 1U];
    extern uint32_t __DATA_ROM[];
    extern uint32_t __DATA_END[];
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_InstallHandler
 * Description   : Install an interrupt handler routine for a given IRQ number
 * This function will let application register/replace the interrupt
 * handler for specified IRQ number. IRQ number is different than Vector
 * number. IRQ 0 will start from Vector 16 address. Refer to reference
 * manual for details. Also refer to startup_<CPU>.s file for each chip
 * family to find out the default interrupt handler for each device. This
 * function will convert the IRQ number to vector number by adding 16 to
 * it.
 *
 * Note          : This method is applicable only if interrupt vector is
 *                 copied in RAM, __flash_vector_table__ symbol is used to
 *                 control this from linker options.
 * Implements INT_SYS_InstallHandler_Activity
 *
 *END**************************************************************************/
void INT_SYS_InstallHandler(IRQn_Type irqNumber,
                            const isr_t newHandler,
                            isr_t* const oldHandler)
{

#if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))

    /* Check IRQ number - dev_irqNumber is used to avoid compiler warning */
    int32_t dev_irqNumber = (int32_t)irqNumber;
    DEV_ASSERT(FEATURE_INTERRUPT_IRQ_MIN <= irqNumber);
    DEV_ASSERT(dev_irqNumber <= (int32_t)FEATURE_INTERRUPT_IRQ_MAX);

#endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */

    const uint32_t * aVectorRam = (uint32_t *)__VECTOR_RAM;
    const uint32_t * aVectorTable = (uint32_t *)__VECTOR_TABLE;

    /* Check whether there is vector table in RAM */
#if defined(__ARMCC_VERSION)
    if ((aVectorRam != aVectorTable) || (__DATA_ROM > __RAM_START))
#elif (defined(__ICCARM__))
    if ((aVectorRam != aVectorTable) || (__VECTOR_RAM != 0))
#else
    const uint32_t * aDataRom = (uint32_t *)__DATA_ROM;
    const uint32_t * aDataRam = (uint32_t *)__DATA_END;
    if ((aVectorRam != aVectorTable) || (aDataRom == aDataRam))
#endif
    {
        uint32_t * pVectorRam = (uint32_t *)__VECTOR_RAM;

        /* Save the former handler pointer */
        if (oldHandler != (isr_t *) 0)
        {
            *oldHandler = (isr_t)pVectorRam[((int32_t)irqNumber) + 16];
        }

        /* Set handler into vector table */
        pVectorRam[((int32_t)irqNumber) + 16] = (uint32_t)newHandler;
    }
    else
    {
        #if (defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT))
            const uint32_t * pVectorRam = (uint32_t *)__VECTOR_RAM;
            /* Check if the existing handler is the same as the one already present in the vector */
            DEV_ASSERT(pVectorRam[((int32_t)irqNumber) + 16] == (uint32_t)newHandler);

        #endif /*(defined(DEV_ERROR_DETECT) || defined(CUSTOM_DEVASSERT)) */
    }

#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
    if (SCB->CCR & SCB_CCR_DC_Msk)
    {
        SCB_CleanDCache();
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQ
 * Description   : Enables an interrupt for a given IRQ number.
 * It calls the system NVIC API to access the interrupt control
 * register and interrupt routing.
 * The input IRQ number does not include the core interrupt, only
 * the peripheral interrupt, from 0 to a maximum supported IRQ.
 * Implements INT_SYS_EnableIRQ_Activity
 *END**************************************************************************/
void INT_SYS_EnableIRQ(IRQn_Type irqNumber)
{
    NVIC_EnableIRQ(irqNumber);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQ
 * Description   : Disable individual interrupt for a specified IRQ
 * It  calls the system NVIC API to access the interrupt control register
 * and interrupt routing.
 * Implements INT_SYS_DisableIRQ_Activity
 *
 *END**************************************************************************/
void INT_SYS_DisableIRQ(IRQn_Type irqNumber)
{
    NVIC_DisableIRQ(irqNumber);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQGlobal
 * Description   : Enable system interrupt
 * This function will enable the global interrupt by calling the core API
 * Implements INT_SYS_EnableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_EnableIRQGlobal(void)
{
    /* Check and update */
    if (g_interruptDisableCount > 0)
    {
        g_interruptDisableCount--;

        if (g_interruptDisableCount <= 0)
        {
            /* Enable the global interrupt */
            __enable_irq();
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQGlobal
 * Description   : Disable system interrupt
 * This function will disable the global interrupt by calling the core API
 * Implements INT_SYS_DisableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_DisableIRQGlobal(void)
{
    /* Disable the global interrupt */
    __disable_irq();

    /* Update counter*/
    g_interruptDisableCount++;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_SetPriority
 * Description   : Set the priority of an interrupt
 * This function will set the priority of an interrupt.
 * Note: The priority cannot be set for every core interrupt.
 * Implements INT_SYS_SetPriority_Activity
 *
 *END**************************************************************************/
void INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority)
{
    NVIC_SetPriority(irqNumber, priority);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetPriority
 * Description   : Get the priority of an interrupt
 * This function will get the priority of an interrupt.
 * Note: The priority cannot be obtained for every core interrupt.
 * Implements INT_SYS_GetPriority_Activity
 *
 *END**************************************************************************/
uint8_t INT_SYS_GetPriority(IRQn_Type irqNumber)
{
    return (uint8_t)NVIC_GetPriority(irqNumber);
}

#if FEATURE_INTERRUPT_HAS_PENDING_STATE
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_ClearPending
 * Description   : Clear Pending Interrupt
 * This function clears the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 * Implements INT_SYS_ClearPending_Activity
 *
 *END**************************************************************************/
void INT_SYS_ClearPending(IRQn_Type irqNumber)
{
    NVIC_ClearPendingIRQ(irqNumber);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_SetPending
 * Description   : Set Pending Interrupt
 * This function configures the pending bit of a peripheral interrupt.
 * Implements INT_SYS_SetPending_Activity
 *
 *END**************************************************************************/
void INT_SYS_SetPending(IRQn_Type irqNumber)
{
    NVIC_SetPendingIRQ(irqNumber);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetPending
 * Description   : Get Pending Interrupt
 * This function gets the pending bit of a peripheral interrupt or a directed
 * interrupt to this CPU (if available).
 * Implements INT_SYS_GetPending_Activity
 *
 *END**************************************************************************/
uint32_t INT_SYS_GetPending(IRQn_Type irqNumber)
{
    return NVIC_GetPendingIRQ(irqNumber);
}
#endif /* FEATURE_INTERRUPT_HAS_PENDING_STATE */

#if FEATURE_INTERRUPT_HAS_ACTIVE_STATE
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_GetActive
 * Description   : Get active state of a peripheral interrupt
 * This function gets the active state of a peripheral interrupt.
 * Implements INT_SYS_GetActive_Activity
 *
 *END**************************************************************************/
uint32_t INT_SYS_GetActive(IRQn_Type irqNumber)
{
    return NVIC_GetActive(irqNumber);
}
#endif /* FEATURE_INTERRUPT_HAS_ACTIVE_STATE */

/*******************************************************************************
 * EOF
 ******************************************************************************/
