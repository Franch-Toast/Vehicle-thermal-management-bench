/*
 * Copyright 2020-2021 YTMicro
 * All rights reserved.
 *
 * YTMicro Confidential. This software is owned or controlled by YTMicro and may
 * only be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

/*!
 * @file osif_baremetal.c
 *
 */

#include "osif.h"
#include <stddef.h>

#include "device_registers.h"

#include "devassert.h"

#if defined (USING_OS_FREERTOS)
#error "Wrong OSIF selected. Please define symbol USING_OS_BAREMETAL (or no OS define) in project settings or change the OSIF variant"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/*! @cond DRIVER_INTERNAL_USE_ONLY */

/*! @brief Converts milliseconds to ticks - in this case, one tick = one millisecond */
#define MSEC_TO_TICK(msec) (msec)

#if (FEATURE_OSIF_USE_SYSTICK)
/* Only include headers for configurations that need them. */
#include "interrupt_manager.h"
#include "clock_manager.h"

static volatile uint32_t s_osif_tick_cnt = 0u;

static inline void osif_Tick(void)
{
    s_osif_tick_cnt++;
}

static inline uint32_t osif_GetCurrentTickCount(void)
{
    return s_osif_tick_cnt;
}

#endif /* (FEATURE_OSIF_USE_SYSTICK */

#if FEATURE_OSIF_USE_SYSTICK

void SysTick_Handler(void);

void SysTick_Handler(void)
{
    osif_Tick();
}

static inline void osif_UpdateTickConfig(void)
{
    uint32_t core_freq = 0u;
    static bool first_init = true;
    /* Get the correct name of the core clock */
    clock_names_t coreclk = CORE_CLK;
    status_t clk_status = CLOCK_SYS_GetFreq(coreclk, &core_freq);
    DEV_ASSERT(clk_status == STATUS_SUCCESS);
    DEV_ASSERT(core_freq > 0u);
    (void)clk_status;

    /* For Cortex-M0 devices the systick counter is initialized with an undefined
     value, so make sure to initialize it to 0 before starting */
    SysTick->CTRL = 0;
    /* Reload value */
    SysTick->LOAD = core_freq / 1000u;
    if (first_init)
    {
        /* only initialize CVR on the first entry, to not cause time drift */
        SysTick->VAL = 0U;
        first_init = false;
    }
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
}

static inline void osif_DisableIrqGlobal(void)
{
    INT_SYS_DisableIRQGlobal();
}

static inline void osif_EnableIrqGlobal(void)
{
    INT_SYS_EnableIRQGlobal();
}

#else /* FEATURE_OSIF_USE_SYSTICK == 0 */

static inline uint32_t osif_GetCurrentTickCount(void)
{
    return 0u;
}

static inline void osif_UpdateTickConfig(void)
{
    /* do not update tick */
}

#define osif_DisableIrqGlobal() (void)0;

#define osif_EnableIrqGlobal() (void)0;

#endif /* FEATURE_OSIF_USE_SYSTICK */

/*! @endcond */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_TimeDelay
 * Description   : This function blocks execution for a number of milliseconds.
 *
 * Implements : OSIF_TimeDelay_baremetal_Activity
 *END**************************************************************************/
void OSIF_TimeDelay(const uint32_t delay)
{
    osif_UpdateTickConfig();
    uint32_t start = osif_GetCurrentTickCount();
    uint32_t crt_ticks = osif_GetCurrentTickCount();
    uint32_t delta = crt_ticks - start;
    uint32_t delay_ticks = MSEC_TO_TICK(delay);
    while (delta < delay_ticks)
    {
        crt_ticks = osif_GetCurrentTickCount();
        delta = crt_ticks - start;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_GetMilliseconds
 * Description   : This function returns the number of miliseconds elapsed since
 *                  starting the internal timer. To initialize the internal timer
 *                  (Systick) in bare-metal, call either OSIF_TimeDelay or
 *                  OSIF_SemaWait functions. Calling OSIF_TimeDelay(0) will initialize
 *                  the timer without any side-effects (no delay).
 *
 * Implements : OSIF_GetMilliseconds_baremetal_Activity
 *END**************************************************************************/
uint32_t OSIF_GetMilliseconds(void)
{
    /*
     * Please make sure the timer is initialized before calling this function.
     * For example, calling OSIF_TimeDelay(0) ensures that the timer is initialized
     * without any other side effects. If OSIF_TimeDelay or OSIF_SemaWait functions
     * have been called, the timer is already initialized.
     */
    return osif_GetCurrentTickCount(); /* This assumes that 1 tick = 1 millisecond */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_MutexLock
 * Description   : This function locks a mutex (mock operation in baremetal case).
 *
 * Implements : OSIF_MutexLock_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_MutexLock(const mutex_t * const pMutex,
                        const uint32_t timeout)
{
    (void)pMutex;
    (void)timeout;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_MutexUnlock
 * Description   : This function unlocks a mutex (mock operation in baremetal case).
 *
 * Implements : OSIF_MutexUnlock_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_MutexUnlock(const mutex_t * const pMutex)
{
    (void)pMutex;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_MutexCreate
 * Description   : This function creates a mutex (mock operation in baremetal case).
 *
 * Implements : OSIF_MutexCreate_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_MutexCreate(mutex_t * const pMutex)
{
    (void)pMutex;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_MutexDestroy
 * Description   : This function destroys a mutex (mock operation in baremetal case).
 *
 * Implements : OSIF_MutexDestroy_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_MutexDestroy(const mutex_t * const pMutex)
{
    (void)pMutex;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_SemaWait
 * Description   : This function performs the 'wait' (decrement) operation on a semaphore.
 *      When timeout value is 0, it's the equivalent of TryWait - try to decrement but return
 *      immediately if it fails (counter is 0).
 *
 * Implements : OSIF_SemaWait_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_SemaWait(semaphore_t * const pSem,
                       const uint32_t timeout)
{
    DEV_ASSERT(pSem != NULL);

    status_t osif_ret_code = STATUS_SUCCESS;

    osif_UpdateTickConfig();
    if ((timeout == 0u))
    {
        /* when the timeout is 0 the wait operation is the equivalent of try_wait,
            meaning that if the semaphore is 0 return immediately with an error code
        */
        if (*pSem == 0u)
        {
            osif_ret_code = STATUS_TIMEOUT;
        }
    }
    else
    {
        /* timeout is not 0 */
        uint32_t timeoutTicks;
        if (timeout == OSIF_WAIT_FOREVER)
        {
            timeoutTicks = OSIF_WAIT_FOREVER;
        }
        else
        {
            /* Convert timeout from milliseconds to ticks. */
            timeoutTicks = MSEC_TO_TICK(timeout);
        }
        uint32_t start = osif_GetCurrentTickCount();
        uint32_t end = (uint32_t)(start + timeoutTicks);
        uint32_t max = end - start;
        while (*pSem == 0u)
        {
            uint32_t crt_ticks = osif_GetCurrentTickCount();
            uint32_t delta = crt_ticks - start;
            if ((timeoutTicks != OSIF_WAIT_FOREVER) && (delta > max))
            {
                /* Timeout occured, stop waiting and return fail code */
                osif_ret_code = STATUS_TIMEOUT;
                break;
            }
        }
    }

    if (osif_ret_code == STATUS_SUCCESS)
    {
        osif_DisableIrqGlobal();
        --(*pSem);
        osif_EnableIrqGlobal();
    }

    return osif_ret_code;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_SemaPost
 * Description   : This function performs the 'post' (increment) operation on a semaphore.
 *
 * Implements : OSIF_SemaPost_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_SemaPost(semaphore_t * const pSem)
{
    DEV_ASSERT(pSem != NULL);

    status_t osif_ret_code = STATUS_SUCCESS;
    osif_DisableIrqGlobal();
    if (*pSem != 255u)
    {
        ++(*pSem);
    }
    else
    {
        osif_ret_code = STATUS_ERROR;
    }

    osif_EnableIrqGlobal();

    return osif_ret_code;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_SemaCreate
 * Description   : This function creates (initializes) a semaphore.
 *
 * Implements : OSIF_SemaCreate_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_SemaCreate(semaphore_t * const pSem,
                         const uint8_t initValue)
{
    DEV_ASSERT(pSem != NULL);
    osif_DisableIrqGlobal();
    *pSem = initValue;
    osif_EnableIrqGlobal();

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSIF_SemaDestroy
 * Description   : This function destroys a semaphore object (mock operation in baremetal case).
 *
 * Implements : OSIF_SemaDestroy_baremetal_Activity
 *END**************************************************************************/
status_t OSIF_SemaDestroy(const semaphore_t * const pSem)
{
    DEV_ASSERT(pSem != NULL);

    (void)pSem;

    return STATUS_SUCCESS;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
