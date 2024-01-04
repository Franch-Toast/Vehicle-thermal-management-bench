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
 * @file etmr_hw_access.h
 */

#ifndef eTMR_HW_ACCESS_H
#define eTMR_HW_ACCESS_H

#include <stdbool.h>
#include <stddef.h>
#include "status.h"
#include "device_registers.h"
#include "etmr_common.h"

/*!
 * @defgroup etmr_hw_access eTMR HW ACCESS
 * @brief eTMR Module Hardware Abstraction Level.
 * eTMR HW ACCESS provides low level APIs for reading and writing to all hardware features
 * of the eTMR module.
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************** CTRL Register **************************************************/

/*!
 * @brief Enable capture test
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_EnableCaptureTest(eTMR_Type *const etmrBase)
{
    etmrBase->CTRL |= eTMR_CTRL_CAPTST_MASK;
}

/*!
 * @brief Disable capture test
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_DisableCaptureTest(eTMR_Type *const etmrBase)
{
    etmrBase->CTRL &= ~eTMR_CTRL_CAPTST_MASK;
}

#if FEATURE_eTMR_HAS_DEAD_TIME_PRESCALER
/*!
 * @brief Set the eTMR deadtime prescaler
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] prs Deadtime prescaler
 */
static inline void eTMR_SetDeadtimePrs(eTMR_Type *const etmrBase, uint8_t prs)
{
    etmrBase->CTRL &= ~eTMR_CTRL_DTPRS_MASK;
    etmrBase->CTRL |= prs << eTMR_CTRL_DTPRS_SHIFT;
}

/*!
 * @brief Get the eTMR deadtime prescaler
 *
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline uint8_t eTMR_GetDeadtimePrs(eTMR_Type *const etmrBase)
{
    return (etmrBase->CTRL & eTMR_CTRL_DTPRS_MASK) >> eTMR_CTRL_DTPRS_SHIFT;
}
#endif

/*!
 * @brief Sets the eTMR clock source.
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] clock The eTMR peripheral clock selection
 *            - 00: Internal clock
 *            - 01: External clock
 */
static inline void eTMR_SetClkSrc(eTMR_Type *const etmrBase, etmr_clock_source_t clock)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_CLKSRC_MASK) | eTMR_CTRL_CLKSRC(clock);
}

/*!
 * @brief Reads the eTMR clock source.
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return The eTMR clock source selection
 *            - 00: Internal clock
 *            - 01: External clock
 */
static inline uint8_t eTMR_GetClkSrc(const eTMR_Type *etmrBase)
{
    return (uint8_t)((((etmrBase)->CTRL) & eTMR_CTRL_CLKSRC_MASK) >> eTMR_CTRL_CLKSRC_SHIFT);
}

/*!
 * @brief Sets the eTMR clock divider.
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] prs      The eTMR peripheral clock divider(divider = prs + 1).
 */
static inline void eTMR_SetClkPrs(eTMR_Type *const etmrBase, uint8_t prs)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_CLKPRS_MASK) | eTMR_CTRL_CLKPRS(prs);
}

/*!
 * @brief Reads the eTMR clock divider.
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return The eTMR clock pre-scale divider
 */
static inline uint8_t eTMR_GetClkPrs(const eTMR_Type *etmrBase)
{
    return (uint8_t)((((etmrBase)->CTRL) & eTMR_CTRL_CLKPRS_MASK) >> eTMR_CTRL_CLKPRS_SHIFT);
}

/*!
 * @brief Set eTMR channel 0-1 complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] pwmMode  The eTMR channel pwm mode
 */
static inline void eTMR_SetCh01CompMode(eTMR_Type *etmrBase, etmr_pwm_mode_t pwmMode)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMPL01_MASK) | eTMR_CTRL_COMPL01(pwmMode);
}

/*!
 * @brief Set eTMR channel 2-3 complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] pwmMode  The eTMR channel pwm mode
 */
static inline void eTMR_SetCh23CompMode(eTMR_Type *etmrBase, etmr_pwm_mode_t pwmMode)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMPL23_MASK) | eTMR_CTRL_COMPL23(pwmMode);
}

/*!
 * @brief Set eTMR channel 4-5 complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] pwmMode  The eTMR channel pwm mode
 */
static inline void eTMR_SetCh45CompMode(eTMR_Type *etmrBase, etmr_pwm_mode_t pwmMode)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMPL45_MASK) | eTMR_CTRL_COMPL45(pwmMode);
}

/*!
 * @brief Set eTMR channel 6-7 complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] pwmMode  The eTMR channel pwm mode
 */
static inline void eTMR_SetCh67CompMode(eTMR_Type *etmrBase, etmr_pwm_mode_t pwmMode)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMPL67_MASK) | eTMR_CTRL_COMPL67(pwmMode);
}

#if FEATURE_eTMR_HAS_DOUBLE_SWITCH
/*!
 * @brief Channel 6&7 is used to generate double switch or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh67DoubleSwitch(eTMR_Type *etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DBSW67_MASK) | eTMR_CTRL_DBSW67(enable);
}

/*!
 * @brief Channel 4&5 is used to generate double switch or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh45DoubleSwitch(eTMR_Type *etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DBSW45_MASK) | eTMR_CTRL_DBSW45(enable);
}

/*!
 * @brief Channel 2&3 is used to generate double switch or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh23DoubleSwitch(eTMR_Type *etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DBSW23_MASK) | eTMR_CTRL_DBSW23(enable);
}

/*!
 * @brief Channel 0&1 is used to generate double switch or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh01DoubleSwitch(eTMR_Type *etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DBSW01_MASK) | eTMR_CTRL_DBSW01(enable);
}
#endif

#if FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
/*!
 * @brief Set eTMR channel 0-1 combination capture mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] en enable combination capture mode or not
 */
static inline void eTMR_SetCh01CombMode(eTMR_Type *etmrBase, bool en)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMB01_MASK) | eTMR_CTRL_COMB01(en);
}

/*!
 * @brief Set eTMR channel 2-3 combination capture mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] en enable combination capture mode or not
 */
static inline void eTMR_SetCh23CombMode(eTMR_Type *etmrBase, bool en)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMB23_MASK) | eTMR_CTRL_COMB23(en);
}

/*!
 * @brief Set eTMR channel 4-5 combination capture mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] en enable combination capture mode or not
 */
static inline void eTMR_SetCh45CombMode(eTMR_Type *etmrBase, bool en)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMB45_MASK) | eTMR_CTRL_COMB45(en);
}

/*!
 * @brief Set eTMR channel 6-7 combination capture mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] en enable combination capture mode or not
 */
static inline void eTMR_SetCh67CombMode(eTMR_Type *etmrBase, bool en)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMB67_MASK) | eTMR_CTRL_COMB67(en);
}

/*!
 * @brief Set eTMR channel 0-1 combination capture source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] src     The eTMR channel combination capture source
 *            0 -- Channel 0
 *            1 -- Channel 1
 */
static inline void eTMR_SetCh01CombSrc(eTMR_Type *etmrBase, uint8_t src)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMBSRC01_MASK) | eTMR_CTRL_COMBSRC01(src);
}

/*!
 * @brief Set eTMR channel 2-3 combination capture source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] src     The eTMR channel combination capture source
 *            0 -- Channel 2
 *            1 -- Channel 3
 */
static inline void eTMR_SetCh23CombSrc(eTMR_Type *etmrBase, uint8_t src)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMBSRC23_MASK) | eTMR_CTRL_COMBSRC23(src);
}

/*!
 * @brief Set eTMR channel 4-5 combination capture source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] src     The eTMR channel combination capture source
 *            0 -- Channel 4
 *            1 -- Channel 5
 */
static inline void eTMR_SetCh45CombSrc(eTMR_Type *etmrBase, uint8_t src)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMBSRC45_MASK) | eTMR_CTRL_COMBSRC45(src);
}

/*!
 * @brief Set eTMR channel 6-7 combination capture source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] src     The eTMR channel combination capture source
 *            0 -- Channel 6
 *            1 -- Channel 7
 */
static inline void eTMR_SetCh67CombSrc(eTMR_Type *etmrBase, uint8_t src)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_COMBSRC67_MASK) | eTMR_CTRL_COMBSRC67(src);
}
#endif

/*!
 * @brief Disable debug mode or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- disable debug mode, counter will count normally
 *                     false -- counter will stop when debugging
 */
static inline void eTMR_SetDebugModeDisable(eTMR_Type *etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DBGDIS_MASK) | eTMR_CTRL_DBGDIS(enable);
}

#if FEATURE_eTMR_HAS_DITHERING
/*!
 * @brief Select dither mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] mode     00 -- Disable dither mode
 *                     01 -- Simulate fine edge control for the PWM period
 *                     10 -- Simulate fine edge control for the PWM duty cycle
 *                     11 -- Simulate fine edge control for the PWM period and the PWM duty cycle
 */
static inline void eTMR_SetDitherMode(eTMR_Type *const etmrBase, uint8_t mode)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_DITHMD_MASK) | eTMR_CTRL_DITHMD(mode);
}
#endif

/*!
 * @brief eTMR counter synchronization mechanisms
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- Global logic is enabled
 *                     false -- Global logic is disabled
 */
static inline void eTMR_SetGloablEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->CTRL = ((etmrBase->CTRL) & ~eTMR_CTRL_GLOBEN_MASK) | eTMR_CTRL_GLOBEN(enable);
}

/*!
 * @brief Enables the eTMR instance
 *
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_Enable(eTMR_Type *const etmrBase)
{
    etmrBase->CTRL = (etmrBase->CTRL & ~eTMR_CTRL_EN_MASK) | eTMR_CTRL_EN_MASK;
}

/*!
 * @brief Disable eTMR instance
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_Disable(eTMR_Type *const etmrBase)
{
    etmrBase->CTRL &= ~eTMR_CTRL_EN_MASK;
}

/******************************************** CNT Register **************************************************/
/*!
 * @brief Initialize the eTMR counter value.
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      The eTMR timer counter value to be set
 */
static inline void eTMR_SetCntVal(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->CNT &= ~(eTMR_CNT_CNT_MASK);
    etmrBase->CNT |= eTMR_CNT_CNT(val);
}

/*!
 * @brief Get the eTMR counter value when etmr enable.
 *
 * @param[in] etmrBase The eTMR base address pointer
 * 
 * @return    retVal   The eTMR current timer counter value
 */
static inline uint32_t eTMR_GetCntVal(eTMR_Type *const etmrBase)
{
    uint32_t retVal = 0;

    retVal = (uint32_t)((etmrBase->CNT & eTMR_CNT_CNT_MASK) >> eTMR_CNT_CNT_SHIFT);

    return retVal;
}

/******************************************** QDCNT Register **************************************************/

/*!
 * @brief Get the eTMR quadrature decoder counter value when etmr quadrature decoder enable.
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return             The eTMR current quadrature decoder counter value
 */
static inline uint32_t eTMR_GetQuadDecodeCounterValue(eTMR_Type *const etmrBase)
{
    return (uint32_t)(((etmrBase->QDCNT) & eTMR_QDCNT_QDCNT_MASK) >> eTMR_QDCNT_QDCNT_SHIFT);
}

/******************************************** SYNC Register **************************************************/
/*!
 * @brief Generate global signal to synchronize with other eTMRs when GLOBEN is enable
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- generate global signal
 *                     false -- not generate global signal
 */
static inline void eTMR_GenGlobalSignal(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->SYNC &= ~eTMR_SYNC_GLOB_MASK;
    etmrBase->SYNC |= eTMR_SYNC_GLOB(enable);
}

/*!
 * @brief Register loading frequency
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Select reloading frequency
 */
static inline void eTMR_SetRegLoadFreq(eTMR_Type *const etmrBase, uint8_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_LDFRQ_MASK;
    etmrBase->SYNC |= eTMR_SYNC_LDFRQ(sel);
}

/*!
 * @brief Enable hardware trigger from pad
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_SetHwTrig2Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIG2EN_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIG2EN(enable);
}

/*!
 * @brief Enable hardware trigger from CIM
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_SetHwTrig1Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIG1EN_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIG1EN(enable);
}

/*!
 * @brief Enable hardware trigger from TMU
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_SetHwTrig0Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIG0EN_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIG0EN(enable);
}

/*!
 * @brief Generate one bus clock cycle pulse trigger.(write-only)
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_GenSoftwareTrigger(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->SYNC &= ~eTMR_SYNC_SWTRIG_MASK;
    etmrBase->SYNC |= eTMR_SYNC_SWTRIG(enable);
}

/*!
 * @brief Select register CHMASK loading opportunity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Register CHMASK loading opportunity selection
 */
static inline void eTMR_SetMaskLoadOpportunity(eTMR_Type *const etmrBase, uint8_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_MASKLD_MASK;
    etmrBase->SYNC |= eTMR_SYNC_MASKLD(sel);
}

/*!
 * @brief Select register CHMASK loading trigger source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Register CHMASK loading trigger source
 * @param[in] 
 */
static inline void eTMR_SetMaskLoadTrigSrc(eTMR_Type *const etmrBase, etmr_sync_trig_src_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIGS2_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIGS2(sel);
}

/*!
 * @brief Select counter initial loading opportunity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Counter initial loading opportunity selection
 */
static inline void eTMR_SetCounterLoadOpportunity(eTMR_Type *const etmrBase, uint8_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_CNTLD_MASK;
    etmrBase->SYNC |= eTMR_SYNC_CNTLD(sel);
}

/*!
 * @brief Select counter initial trigger source.
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Counter initial loading trigger source
 */
static inline void eTMR_SetCounterLoadTrigSrc(eTMR_Type *const etmrBase, etmr_sync_trig_src_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIGS1_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIGS1(sel);
}

/*!
 * @brief Select registers(INIT, MOD, MID, CHxVAL0, CHxVAL1) loading opportunity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Registers loading opportunity selection
 */
static inline void eTMR_SetRegLoadOpportunity(eTMR_Type *const etmrBase, uint8_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_REGLD_MASK;
    etmrBase->SYNC |= eTMR_SYNC_REGLD(sel);
}

/*!
 * @brief Select registers(INIT, MOD, MID, CHxVAL0, CHxVAL1) loading trigger source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      Registers loading trigger source selection
 */
static inline void eTMR_SetRegLoadTrigSrc(eTMR_Type *const etmrBase, etmr_sync_trig_src_t sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_TRIGS0_MASK;
    etmrBase->SYNC |= eTMR_SYNC_TRIGS0(sel);
}

#if FEATURE_eTMR_HAS_CNT_INIT_SRC
/*!
 * @brief Set counter initial value source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      0 -- counter initial value is from register CNT
 *                     1 -- counter initial value is from register INIT
 */
static inline void eTMR_SetCounterInitValSrc(eTMR_Type *const etmrBase, bool sel)
{
    etmrBase->SYNC &= ~eTMR_SYNC_CNTINIT_MASK;
    etmrBase->SYNC |= eTMR_SYNC_CNTINIT(sel);
}

/*!
 * @brief Get sync register counter initial value source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline uint8_t eTMR_GetCntInitSrc(eTMR_Type *const etmrBase)
{
    uint8_t retVal = 0;

    retVal = (uint8_t)(((etmrBase->SYNC) & eTMR_SYNC_CNTINIT_MASK) >> eTMR_SYNC_CNTINIT_SHIFT);

    return retVal;
}
#endif

/*!
 * @brief Clear bit LDOK
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_ClearLdok(eTMR_Type *const etmrBase)
{
    etmrBase->SYNC |= eTMR_SYNC_CLDOK_MASK;
}

/*!
 * @brief Set bit LDOK
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_SetLdok(eTMR_Type *const etmrBase)
{
    etmrBase->SYNC |= eTMR_SYNC_LDOK_MASK;
}

/******************************************** OTRIG Register **************************************************/
#if FEATURE_eTMR_HAS_OUTPUT_TRIGGER_WIDTH
/*!
 * @brief Set output trigger width
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] width    Trigger output width
 */
static inline void eTMR_SetOutputTrigWidth(eTMR_Type *const etmrBase, uint8_t width)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_TWD_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_TWD(width);
}
#endif

/*!
 * @brief Set output trigger frequency
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] freq     trigger output frequency
 */
static inline void eTMR_SetOutputTrigFreq(eTMR_Type *const etmrBase, uint8_t freq)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_TFRQ_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_TFRQ(freq);
}

/*!
 * @brief Select which channel to generate PWM output as trigger.
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  Channel index
 */
static inline void eTMR_SetPulseOutSrc(eTMR_Type *const etmrBase, etmr_channel_index_t channel)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_PULSESRC_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_PULSESRC(channel);
}

/*!
 * @brief Set output trigger source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      0 -- Select trigger generated from matching event
 *                     1 -- Select PWM generated from PWM mode
 */
static inline void eTMR_SetOutTrigSrc(eTMR_Type *const etmrBase, etmr_trig_src_t sel)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_TSRC_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_TSRC(sel);
}

/*!
 * @brief Generate trigger when counter matches with MOD value or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_SetModMatchTrigEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_MODTEN_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_MODTEN(enable);
}

#if FEATURE_eTMR_HAS_MID
/*!
 * @brief Generate trigger when counter matches with MID value or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true or false
 */
static inline void eTMR_SetMidMatchTrigEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_MIDTEN_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_MIDTEN(enable);
}
#endif

#if FEATURE_eTMR_HAS_INIT_REG
/*!
 * @brief Generate trigger when counter matches with INIT value or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- generate trigger when counter matches with INIT
 *                     false -- not generate
 */
static inline void eTMR_SetInitMatchTrigEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->OTRIG &= ~eTMR_OTRIG_INITTEN_MASK;
    etmrBase->OTRIG |= eTMR_OTRIG_INITTEN(enable);
}
#endif
/******************************************** INTE Register **************************************************/
/*!
 * @brief Enable quadrature decoder timer overflow interrupt or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetQdTofIntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_QDTOIE_MASK;
    etmrBase->INTE |= eTMR_INTE_QDTOIE(enable);
}

/*!
 * @brief Enable timer overflow interrupt or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetTofIntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_TOIE_MASK;
    etmrBase->INTE |= eTMR_INTE_TOIE(enable);
}

/*!
 * @brief Enable fault interrupt or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetFaultIntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_FIE_MASK;
    etmrBase->INTE |= eTMR_INTE_FIE(enable);
}

/*!
 * @brief Enable channel 7 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh7IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH7IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH7IE(enable);
}

/*!
 * @brief Enable channel 6 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh6IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH6IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH6IE(enable);
}

/*!
 * @brief Enable channel 5 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh5IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH5IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH5IE(enable);
}

/*!
 * @brief Enable channel 4 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh4IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH4IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH4IE(enable);
}

/*!
 * @brief Enable channel 3 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh3IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH3IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH3IE(enable);
}

/*!
 * @brief Enable channel 2 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh2IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH2IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH2IE(enable);
}

/*!
 * @brief Enable channel 1 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh1IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH1IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH1IE(enable);
}

/*!
 * @brief Enable channel 0 interrupt or not
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_SetCh0IntEnable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->INTE &= ~eTMR_INTE_CH0IE_MASK;
    etmrBase->INTE |= eTMR_INTE_CH0IE(enable);
}

/******************************************** CHINITV Register **************************************************/

#if FEATURE_eTMR_HAS_HW_CENTER_ALIGN_CALCULATION
/*!
 * @brief Set all channels output initial value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      8 channels initial value
 */
static inline void eTMR_InitChannelOutput(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->CHINIT |= val;
}

/*!
 * @brief Set all channels output initial value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      8 channels initial value
 */
static inline void eTMR_SetChnOutInitVal(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->CHINIT = val << 16;
}
#else
/*!
 * @brief Set all channels output initial value
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      8 channels initial value
 */
static inline void eTMR_SetChnOutInitVal(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->CHINIT = val;
}
#endif

/******************************************** CHSWV Register **************************************************/

/*!
 * @brief 8 channels output value are forced as 0/1 by software
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      8 channels output force value by software
 */
static inline void eTMR_SetChnOutSwVal(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->CHSWV &= 0x0U;
    etmrBase->CHSWV |= val;
}

/******************************************** CHMASK Register **************************************************/

/*!
 * @brief Mask 8 channels output value (shadow register)
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] maskVal  8 channels output mask value
 *            maskVal = ch0MaskVal | ch1MaskVal | ch2MaskVal | ch3MaskVal |
 *                      ch4MaskVal | ch5MaskVal | ch6MaskVal | ch7MaskVal
 *            chnMaskVal
 *            00b -- output mask value forced to 0
 *            01b -- output mask value forced to 1
 *            10b -- output mask value forced to tristate
 *            11b -- output mask value forced to tristate
 * @param[in] maskEn   8 channels output mask enablement
 *            maskEn = ch0MaskEn | ch1MaskEn | ch2MaskEn | ch3MaskEn |
 *                     ch4MaskEn | ch5MaskEn | ch6MaskEn | ch7MaskEn
 *            chnMaskEn
 *            0 -- normal pwm
 *            1 -- output value forced to chnMaskVal
 */
static inline void eTMR_SetChnOutMask(eTMR_Type *const etmrBase, uint16_t maskVal, uint8_t maskEn)
{
    etmrBase->CHMASK = (maskVal << 16U) | (maskEn);
}

/******************************************** CHFV Register **************************************************/

/*!
 * @brief Set channels fault output value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      8 channels output fault value
 *            val = ch0FaultVal | ch1FaultVal | ch2FaultVal | ch3FaultVal |
 *                  ch4FaultVal | ch5FaultVal | ch6FaultVal | ch7FaultVal
 *            ch0FaultVal
 *            00b -- output fault value forced to 0
 *            01b -- output fault value forced to 1
 *            10b -- output fault value forced to tristate
 *            11b -- output fault value forced to tristate
 */
static inline void eTMR_SetChnOutFaultVal(eTMR_Type *const etmrBase, uint16_t val)
{
    etmrBase->CHFV &= ~(eTMR_CHFV_CH7FV_MASK | eTMR_CHFV_CH6FV_MASK | eTMR_CHFV_CH5FV_MASK | eTMR_CHFV_CH4FV_MASK |
                        eTMR_CHFV_CH3FV_MASK | eTMR_CHFV_CH2FV_MASK | eTMR_CHFV_CH1FV_MASK | eTMR_CHFV_CH0FV_MASK);
    etmrBase->CHFV |= val;
}

/******************************************** INIT Register **************************************************/
#if FEATURE_eTMR_HAS_INIT_REG
/*!
 * @brief Set counter initial value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      counter initial value
 */
static inline void eTMR_SetInitVal(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->INIT = eTMR_INIT_INIT(val);
}
#endif
/******************************************** DITHMOD Register **************************************************/

#if FEATURE_eTMR_HAS_DITHERING
/*!
 * @brief Set Dither MOD integer and fraction
 *
 * @param[in] etmrBase the eTMR peripheral instance
 * @param[in] integer  the mod integer
 * @param[in] frac     the mod fraction
 */
static inline void eTMR_SetDithMod(eTMR_Type *const etmrBase, uint8_t integer, uint8_t frac)
{
    etmrBase->DITHMOD = eTMR_DITHMOD_MODINT(integer) | eTMR_DITHMOD_MODFRAC(frac);
}

/*!
 * @brief Get Dither MOD Integer
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return    retVal   Dither mod integer
 */
static inline uint8_t eTMR_GetDithModInteger(eTMR_Type *const etmrBase)
{
    uint8_t retVal = 0;

    retVal = (uint8_t)(((etmrBase->DITHMOD) & eTMR_DITHMOD_MODINT_MASK) >> eTMR_DITHMOD_MODINT_SHIFT);

    return retVal;
}

/*!
 * @brief Get Dither MOD Fraction
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return    retval   Dither mod fraction
 */
static inline uint8_t eTMR_GetDithModFrac(eTMR_Type *const etmrBase)
{
    uint8_t retVal = 0;

    retVal = (uint8_t)(((etmrBase->DITHMOD) & eTMR_DITHMOD_MODFRAC_MASK) >> eTMR_DITHMOD_MODFRAC_SHIFT);

    return retVal;
}
#endif

/*!
 * @brief Set counter modulus value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Modulus value
 */
static inline void eTMR_SetMod(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->MOD = eTMR_MOD_MOD(val);
}

/*!
 * @brief Get modulus value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @return    retval   eTMR MOD value
 */
static inline uint32_t eTMR_GetMod(eTMR_Type *const etmrBase)
{
    return (uint32_t)(etmrBase->MOD);
}

/******************************************** MID Register **************************************************/
#if FEATURE_eTMR_HAS_MID
/*!
 * @brief Set counter middle value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Middle value
 */
static inline void eTMR_SetMid(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->MID = val;
}

/*!
 * @brief Get middle value
 *
 * @param[in] etmrBase The eTMR base address pointer
 *
 * @retval    eTMR MID value
 */
static inline uint32_t eTMR_GetMid(eTMR_Type *const etmrBase)
{
    uint32_t retVal = 0;

    retVal = (uint32_t)(((etmrBase->MID) & eTMR_MID_MID_MASK) >> eTMR_MID_MID_SHIFT);

    return retVal;
}
#endif
/******************************************** QDCTRL Register **************************************************/

/*!
 * @brief Set quadrature decoder phase A and B input filter sample counter
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      sample counter value
 */
static inline void eTMR_SetQuadDecoderFilterSampleCount(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDFCNT_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_QDFCNT(val);
}

/*!
 * @brief Set quadrature decoder phase A and B input filter sample period
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      sample period value
 */
static inline void eTMR_SetQuadDecoderFilterSamplePeriod(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDFPER_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_QDFPER(val);
}

/*!
 * @brief Invert phase B polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- Invert
 *                     false -- Not invert
 */
static inline void eTMR_SetQuadDecoderPhaseBPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_PHBPOL_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_PHBPOL(enable);
}

/*!
 * @brief Invert phase A polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- Invert
 *                     false -- Not invert
 */
static inline void eTMR_SetQuadDecoderPhaseAPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_PHAPOL_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_PHAPOL(enable);
}

/*!
 * @brief Set quadrature decoder clock prescaler
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      clock prescaler
 */
static inline void eTMR_SetQuadDecoderClkPrs(eTMR_Type *const etmrBase, etmr_qd_clock_prs_t prs)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDCLKPRS_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_QDCLKPRS(prs);
}

/*!
 * @brief Select quadrature decoder mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] mode     00 -- Phase A and Phase B mode, when B changes follow A, counter increase
 *                                                     when A changes follow B, counter decrease
 *                     01 -- Phase A and Phase B mode, when B changes follow A, counter decrease
 *                                                     when A changes follow B, counter increase
 *                     10 -- Counting and direction mode, phase B input controls direction
 *                     11 -- Counting and direction mode, phase A input controls direction
 */
static inline void eTMR_SetQuadDecoderMode(eTMR_Type *const etmrBase, etmr_qd_mode_t mode)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDMODE_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_QDMODE(mode);
}

/*!
 * @brief Enable quadrature decoder
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_EnableQuadDecoder(eTMR_Type *const etmrBase)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDEN_MASK;
    etmrBase->QDCTRL |= eTMR_QDCTRL_QDEN_MASK;
}

/*!
 * @brief Disable quadrature decoder
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_DisableQuadDecoder(eTMR_Type *const etmrBase)
{
    etmrBase->QDCTRL &= ~eTMR_QDCTRL_QDEN_MASK;
}

/******************************************** QDINIT Register **************************************************/
#if FEATURE_eTMR_HAS_INIT_REG
/*!
 * @brief Set quadrature decoder counter initial value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Quadrature decoder counter initial value
 */
static inline void eTMR_SetQuadDecoderCounterInitVal(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->QDINIT &= ~eTMR_QDINIT_QDINIT_MASK;
    etmrBase->QDINIT |= eTMR_QDINIT_QDINIT(val);
}
#endif

/******************************************** QDMOD Register **************************************************/
#if FEATURE_eTMR_HAS_QUAD_DECODER_MOD
/*!
 * @brief Set quadrature decoder modulus value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Quadrature decoder counter modulus value
 */
static inline void eTMR_SetQuadDecoderMod(eTMR_Type *const etmrBase, uint32_t val)
{
    etmrBase->QDMOD &= ~eTMR_QDMOD_QDMOD_MASK;
    etmrBase->QDMOD |= eTMR_QDMOD_QDMOD(val);
}
#endif
/******************************************** FAULT Register **************************************************/

/*!
 * @brief Set fault filter sample counter
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Fault input filter sample counter
 */
static inline void eTMR_SetFaultFilterSampleCnt(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->FAULT &= ~eTMR_FAULT_FFCNT_MASK;
    etmrBase->FAULT |= eTMR_FAULT_FFCNT(val);
}

/*!
 * @brief Set fault filter sample period
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      Fault filter sample period
 * @param[in] 
 */
static inline void eTMR_SetFaultFilterSamplePeriod(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->FAULT &= ~eTMR_FAULT_FFPER_MASK;
    etmrBase->FAULT |= eTMR_FAULT_FFPER(val);
}

/*!
 * @brief Fault input stretch to 2 bus clock cycle widths at least
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] val      1 -- 2 bus clock cycle widths at least
 */
static inline void eTMR_SetFaultInputStrentch(eTMR_Type *const etmrBase, uint8_t val)
{
    etmrBase->FAULT &= ~eTMR_FAULT_STRETCH_MASK;
    etmrBase->FAULT |= eTMR_FAULT_STRETCH(val);
}

/*!
 * @brief Enable fault combinational logic
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_EnableFaultCombLogic(eTMR_Type *const etmrBase)
{
    etmrBase->FAULT &= ~eTMR_FAULT_FCOMB_MASK;
    etmrBase->FAULT |= eTMR_FAULT_FCOMB_MASK;
}

/*!
 * @brief Disable fault combinational logic
 * 
 * @param[in] etmrBase The eTMR base address pointer
 */
static inline void eTMR_DisableFaultCombLogic(eTMR_Type *const etmrBase)
{
    etmrBase->FAULT &= ~eTMR_FAULT_FCOMB_MASK;
}

/*!
 * @brief PWM recovery
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] sel      PWM recovery opportunity when fault event occurs
 *                     00 -- PWM recovery is disabled
 *                     01 -- PWM recovery when counter matches with MID
 *                     10 -- PWM recovery when counter matches with MOD
 *                     11 -- PWM recovery immediately
 */
static inline void eTMR_SetPwmRecoveryOpportunity(eTMR_Type *const etmrBase, uint8_t sel)
{
    etmrBase->FAULT &= ~eTMR_FAULT_RCVRY_MASK;
    etmrBase->FAULT |= eTMR_FAULT_RCVRY(sel);
}

/*!
 * @brief PWM automatically recovery mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] mode     PWM automatic recovery mode after fault event occurs
 *                     00 -- Clear STS[FxF] manually and recovery automatically
 *                     01 -- Automatic recovery when fault input returns to normal, not care STS[FxF]
 *                     10 -- Automatic recovery and STS[FxF] clear automatically when fault input returns to noraml
 *                     11 -- reserved
 */
static inline void eTMR_SetPwmAutoRecoveryMode(eTMR_Type *const etmrBase, uint8_t mode)
{
    etmrBase->FAULT &= ~eTMR_FAULT_FAUTO_MASK;
    etmrBase->FAULT |= eTMR_FAULT_FAUTO(mode);
}

/*!
 * @brief Invert fault 3 input polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true -- Invert fault 3 input polarity
 */
static inline void eTMR_IsInvertFault3InputPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F3POL_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F3POL(enable);
}

/*!
 * @brief Invert fault 2 input polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true -- Invert fault 2 input polarity
 */
static inline void eTMR_IsInvertFault2InputPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F2POL_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F2POL(enable);
}

/*!
 * @brief Invert fault 1 input polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true -- Invert fault 1 input polarity
 */
static inline void eTMR_IsInvertFault1InputPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F1POL_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F1POL(enable);
}

/*!
 * @brief Invert fault 0 input polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true -- Invert fault 0 input polarity
 */
static inline void eTMR_IsInvertFault0InputPol(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F0POL_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F0POL(enable);
}

/*!
 * @brief Set fault 3 enable or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_IsFault3Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F3EN_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F3EN(enable);
}

/*!
 * @brief Set fault 2 enable or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_IsFault2Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F2EN_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F2EN(enable);
}

/*!
 * @brief Set fault 1 enable or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_IsFault1Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F1EN_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F1EN(enable);
}

/*!
 * @brief Set fault 0 enable or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] enable   true  -- enable
 *                     false -- disable
 */
static inline void eTMR_IsFault0Enable(eTMR_Type *const etmrBase, bool enable)
{
    etmrBase->FAULT &= ~eTMR_FAULT_F0EN_MASK;
    etmrBase->FAULT |= eTMR_FAULT_F0EN(enable);
}

/******************************************** CH_CTRL Register **************************************************/

/*!
 * @brief Set channel x DMA enable
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- enable DMA
 *                     false -- disable DMA
 */
static inline void eTMR_SetChnDmaEnable(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_DMAEN_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_DMAEN(enable);
}

/*!
 * @brief Set channel x registers loading enable
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- enable registers loading
 *                     false -- disable registers loading
 */
static inline void eTMR_SetChnLdEnable(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_LDEN_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_LDEN(enable);
}

#if FEATURE_eTMR_HAS_CAPTURE_HOLD
/*!
 * @brief Set channel x input capture hold enable
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- enable interrupt
 *                     false -- disable interrupt
 */
static inline void eTMR_SetChnCapHoldEnable(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CAPHOLD_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CAPHOLD(enable);
}
#endif

/*!
 * @brief Select capture edge
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] sel      00 -- not select any edge
 *                     01 -- posedge
 *                     10 -- negedge
 *                     11 -- dual edge
 */
static inline void eTMR_SetChnCapEdge(eTMR_Type *const etmrBase, uint8_t channel, uint8_t sel)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CAPEDGE_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CAPEDGE(sel);
}

/*!
 * @brief Get capture edge
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @return    retVal   Channel input capture mode
 */
static inline uint8_t eTMR_GetChnCapEdge(eTMR_Type *const etmrBase, uint8_t channel)
{
    uint8_t retVal = 0;

    retVal = (etmrBase->CH[channel].CTRL & eTMR_CH_CTRL_CAPEDGE_MASK) >> eTMR_CH_CTRL_CAPEDGE_SHIFT;

    return retVal;
}

/*!
 * @brief Set channel x capture input filter sample counter
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channle
 * @param[in] cnt      Capture input filter sample counter
 */
static inline void eTMR_SetChnCapFilterSampleCounter(eTMR_Type *const etmrBase, uint8_t channel, uint8_t count)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CFCNT_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CFCNT(count);
}

/*!
 * @brief Set channel x capture input filter sample period
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] period   Capture input filter sample period
 */
static inline void eTMR_SetChnCapFilterSamplePeriod(eTMR_Type *const etmrBase, uint8_t channel, uint8_t period)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CFPER_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CFPER(period);
}

/*!
 * @brief Set channel x val1 matching output value in compare mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] val      00 -- output value 0
 *                     01 -- output value 1
 *                     10 & 11 -- output toggle
 */
static inline void eTMR_SelChnVal1MatchingOutputVal(eTMR_Type *const etmrBase, uint8_t channel, uint8_t val)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_VAL1CMP_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_VAL1CMP(val);
}

/*!
 * @brief Set channel x val0 matching output value in compare mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] val      00 -- output value 0
 *                     01 -- output value 1
 *                     10 & 11 -- output toggle
 */
static inline void eTMR_SelChnVal0MatchingOutputVal(eTMR_Type *const etmrBase, uint8_t channel, uint8_t val)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_VAL0CMP_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_VAL0CMP(val);
}

/*!
 * @brief Set channel x pwm source
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] src      00 -- Normal mode, generate pwm by configuring related registers
 *                     01 -- Invert pwm generated in normal mode
 *                     10 -- Generate pwm by configuring CHSWV
 *                     11 -- reserved
 */
static inline void eTMR_SetChnPwmSrc(eTMR_Type *const etmrBase, uint32_t channel, uint32_t src)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_PWMSRC_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_PWMSRC(src);
}

/*!
 * @brief Enable channel x val1 matching trigger or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- Generate trigger when counter matches with VAL1
 *                     false -- not Generate
 */
static inline void eTMR_IsChnVal1MatchTrigEnable(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_VAL1TEN_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_VAL1TEN(enable);
}

/*!
 * @brief Enable channel x val0 matching trigger or not
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- Generate trigger when counter matches with VAL0
 *                     false -- not Generate
 */
static inline void eTMR_IsChnVal0MatchTrigEnable(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_VAL0TEN_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_VAL0TEN(enable);
}

/*!
 * @brief Invert channel x output polarity
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   true  -- Invert channel output polarity
 *                     false -- not Invert
 */
static inline void eTMR_IsInvertChnOutputPol(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CHPOL_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CHPOL(enable);
}

#if !FEATURE_eTMR_HAS_HW_CENTER_ALIGN_CALCULATION && FEATURE_eTMR_HAS_CHINIT_BIT
/*!
 * @brief Initialize channel x output with CHINIT[CHxINIT]
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   
 */
static inline void eTMR_InitChnOutput(eTMR_Type *const etmrBase, uint8_t channel)
{
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CHINIT_MASK;
}
#endif

#if FEATURE_eTMR_HW_CONFIG_CENTER_ALIGN
/*!
 * @brief Set channel center align mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] enable   
 */
static inline void eTMR_SetChannelCenterAlignMode(eTMR_Type *const etmrBase, uint8_t channel, bool enable)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CENTER_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CENTER(enable);
}
#endif

/*!
 * @brief Set channel x mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] mode     00 -- Channel disable
 *                     01 -- PWM mode
 *                     10 -- Compare mode
 *                     11 -- Capture mode
 */
static inline void eTMR_SetChnMode(eTMR_Type *const etmrBase, uint8_t channel, etmr_channel_mode_t mode)
{
    etmrBase->CH[channel].CTRL &= ~eTMR_CH_CTRL_CHMODE_MASK;
    etmrBase->CH[channel].CTRL |= eTMR_CH_CTRL_CHMODE(mode);
}

/******************************************** CH_VAL0 Register **************************************************/

/*!
 * @brief Set channel x val0
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] val      VAL0 value
 */
static inline void eTMR_SetChnVal0(eTMR_Type *const etmrBase, uint8_t channel, uint32_t val)
{
    etmrBase->CH[channel].VAL0 = val;
}

static inline uint32_t eTMR_GetChnVal0(const eTMR_Type *etmrBase, uint8_t channel)
{
    return (uint32_t)(etmrBase->CH[channel].VAL0);
}

/******************************************** CH_VAL1 Register **************************************************/

/*!
 * @brief Set channel x val1
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] val      VAL1 value
 */
static inline void eTMR_SetChnVal1(eTMR_Type *const etmrBase, uint8_t channel, uint32_t val)
{
    etmrBase->CH[channel].VAL1 = val;
}

/******************************************** CH_DITHVAL1 Register **************************************************/
#if FEATURE_eTMR_HAS_DITHERING
static inline void eTMR_SetChnDithVal1(eTMR_Type *const etmrBase, uint8_t channel, uint8_t integer, uint8_t frac)
{
    etmrBase->CH[channel].DITHVAL1 = eTMR_CH_DITHVAL1_VAL1INT(integer) | eTMR_CH_DITHVAL1_VAL1FRAC(frac);
}
#endif
/******************************************** CH_DT Register **************************************************/
#if FEATURE_eTMR_DEADTIME_CONFIG_EACH_CHANNEL
/*!
 * @brief Set deadtime value which is used in complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * @param[in] val      Deadtime value
 */
static inline void eTMR_SetChnDeadtime(eTMR_Type *const etmrBase, uint8_t channel, uint16_t val)
{
    etmrBase->CH[channel].DT &= ~eTMR_CH_DT_DTVAL_MASK;
    etmrBase->CH[channel].DT |= eTMR_CH_DT_DTVAL(val);
}
#else
/*!
 * @brief Set odd channel deadtime value which is used in complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] odd      Odd channel deadtime value
 */
static inline void eTMR_SetOddDeadtime(eTMR_Type *const etmrBase, uint16_t odd)
{
    etmrBase->DT &= ~eTMR_DT_DTODD_MASK;
    etmrBase->DT |= odd << eTMR_DT_DTODD_SHIFT;
}

/*!
 * @brief Set even channel deadtime value which is used in complementary mode
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] even     Even channel deadtime value
 */
static inline void eTMR_SetEvenDeadtime(eTMR_Type *const etmrBase, uint16_t even)
{
    etmrBase->DT &= ~eTMR_DT_DTEVEN_MASK;
    etmrBase->DT |= even << eTMR_DT_DTEVEN_SHIFT;
}
#endif
/******************************************** CH_CVAL Register **************************************************/

/*!
 * @brief Get channel x capture input value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 *
 * @return channel x capture input value
 */
static inline uint32_t eTMR_GetChnCapVal(eTMR_Type *const etmrBase, uint8_t channel)
{
    return (uint32_t)(etmrBase->CH[channel].CVAL);
}

/******************************************** CH_PPW Register **************************************************/
#if !FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
/*!
 * @brief Get channel x positive pulse counter periods number
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * 
 * @return    channel x positive pulse counter periods number
 */
static inline uint8_t eTMR_GetChnPosPulseCntPeriodNum(const eTMR_Type *etmrBase, uint8_t channel)
{
    uint8_t retVal;

    retVal = (uint8_t)(etmrBase->CH[channel].PPCNTN);

    return retVal;
}

/*!
 * @brief Get channel x positive pulse width capture value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * 
 * @return    channel x positive pulse width capture value
 */
static inline uint32_t eTMR_GetChnPosPulseWidthCapVal(const eTMR_Type *etmrBase, uint8_t channel)
{
    uint32_t retVal;

    retVal = (uint32_t)(etmrBase->CH[channel].PPCNTV);

    return retVal;
}

/******************************************** CH_NPW Register **************************************************/

/*!
 * @brief Get channel x negative pulse counter periods number
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * 
 * @return    channel x negative pulse counter periods number
 */
static inline uint8_t eTMR_GetChnNegPulseCntPeriodNum(const eTMR_Type *etmrBase, uint8_t channel)
{
    uint8_t retVal;

    retVal = (uint8_t)(etmrBase->CH[channel].NPCNTN);

    return retVal;
}

/*!
 * @brief Get channel x negative pulse width capture value
 * 
 * @param[in] etmrBase The eTMR base address pointer
 * @param[in] channel  The eTMR channel
 * 
 * @return    channel x negative pulse width capture value
 */
static inline uint32_t eTMR_GetChnNegPulseWidthCapVal(const eTMR_Type *etmrBase, uint8_t channel)
{
    uint32_t retVal;

    retVal = (uint32_t)(etmrBase->CH[channel].NPCNTV);

    return retVal;
}
#endif

/*!
 * @brief Reset eTMR all of registers
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_Reset(uint32_t instance);

/******************************************** STS Register **************************************************/

/*!
 * @brief Get channel negative pulse ready flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetChnNegPulseRdyFlag(uint32_t instance, uint8_t channel);

/*!
 * @brief Get channel positive pulse ready flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetChnPosPulseRdyFlag(uint32_t instance, uint8_t channel);

/*!
 * @brief Get quadrature decoder direction
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetQuadDecodeDir(uint32_t instance);

/*!
 * @brief Get quadrature decoder overflow flag
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetQuadDecodeTofFlag(uint32_t instance);

/*!
 * @brief Get counter overflow flag
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetTofFlag(uint32_t instance);

/*!
 * @brief Get reload flag
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetReloadFlag(uint32_t instance);

/*!
 * @brief Get fault flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] fltChannel the eTMR fault channel
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetFaultFlag(uint32_t instance, uint8_t fltChannel);

/*!
 * @brief Get channel interrupt flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 *
 * @retval    true/false
 */
bool eTMR_DRV_GetChnFlag(uint32_t instance, uint8_t channel);

/*!
 * @brief Clear channel negative pulse ready flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 */
void eTMR_DRV_ClearChnNegPulseRdyFlag(uint32_t instance, uint8_t channel);

/*!
 * @brief Clear channel positive pulse ready flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 */
void eTMR_DRV_ClearChnPosPulseRdyFlag(uint32_t instance, uint8_t channel);

/*!
 * @brief Clear quadrature decoder counter overflow flag
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_ClearQuadDecodeTofFlag(uint32_t instance);

/*!
 * @brief Clear counter overflow flag
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_ClearTofFlag(uint32_t instance);

/*!
 * @brief Clear counter reload flag
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_ClearReloadFlag(uint32_t instance);

/*!
 * @brief Clear fault channel flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] fltChannel the eTMR fault channel
 */
void eTMR_DRV_ClearFaultFlag(uint32_t instance, uint8_t fltChannel);

/*!
 * @brief Clear channel interrupt flag
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channelSet the eTMR channel set
 */
void eTMR_DRV_ClearChnFlag(uint32_t instance, uint8_t channelSet);

/******************************************** IOSTS Register **************************************************/

/*!
 * @brief Get phase B input status in Quadrature Decoder
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    0 or 1
 */
uint8_t eTMR_DRV_GetPhaseBStatus(uint32_t instance);

/*!
 * @brief Get phase A input status in Quadrature Decoder
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @retval    0 or 1
 */
uint8_t eTMR_DRV_GetPhaseAStatus(uint32_t instance);

/*!
 * @brief Get fault channel input status(polarity)
 *
 * @param[in] instance   the eTMR peripheral instance
 * @param[in] fltChannel the eTMR fault channel
 *
 * @return    status of fault input
 */
uint8_t eTMR_DRV_GetFaultInputStatus(uint32_t instance, uint8_t fltChannel);

/*!
 * @brief Get channel IO status in pwm, output compare and input capture mode.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 *
 * @return    status of channel IO
 */
uint8_t eTMR_DRV_GetChnIoStatus(uint32_t instance, uint8_t channel);

/******************************************** CTRL Register **************************************************/

/*!
 * @brief Set complementary mode for channels
 *
 * @param[in] instance    the eTMR peripheral instance
 * @param[in] channelPair the eTMR channel pair
 * @param[in] mode        pwm mode, see #etmr_pwm_mode_t struct
 */
void eTMR_DRV_SetChnCompMode(uint32_t instance, uint8_t channelPair, etmr_pwm_mode_t mode);

#if FEATURE_eTMR_HAS_DOUBLE_SWITCH
/*!
 * @brief Set double switch for channels
 *
 * @param[in] instance    the eTMR peripheral instance
 * @param[in] channelPair the eTMR channel pair
 * @param[in] en          enable/disable double switch
 */
void eTMR_DRV_SetChnDoubleSwitch(uint32_t instance, uint8_t channelPair, bool en);
#endif

#if FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
/*!
 * @brief Set combine mode for channels
 *
 * @param[in] instance    the eTMR peripheral instance
 * @param[in] channelPair the eTMR channel pair
 * @param[in] en          enable/disable combine mode
 */
void eTMR_DRV_SetChnCombMode(uint32_t instance, uint8_t channelPair, bool en);

/*!
 * @brief Set channel combine source
 *
 * @param[in] instance    the eTMR peripheral instance
 * @param[in] channelPair the eTMR channel pair
 * @param[in] src         the combine source
 */
void eTMR_DRV_SetChnCombSrc(uint32_t instance, uint8_t channelPair, uint8_t src);
#endif
/******************************************** FAULT Register **************************************************/

/*!
 * @brief Set channel fault input polarity
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 * @param[in] pol the fault input polarity
 */
void eTMR_DRV_SetFaultChnPol(uint32_t instance, uint8_t fltChannel, bool pol);

/*!
 * @brief Set channel fault interrupt enable or disable
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 */
void eTMR_DRV_SetFaultChnEnable(uint32_t instance, uint8_t fltChannel, bool enable);

/******************************************** INTE Register **************************************************/

/*!
 * @brief Enable quadrature decoder counter overflow interrupt
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_EnableQuadDecodeTofInt(uint32_t instance);

/*!
 * @brief Disable quadrature decoder counter overflow interrupt
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_DisableQuadDecodeTofInt(uint32_t instance);

/*!
 * @brief Enable eTMR overflow interrupt
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_EnableTofInt(uint32_t instance);

/*!
 * @brief Disable eTMR overflow interrupt
 *
 * @param[in] instance the eTMR peripheral instance
 */
void eTMR_DRV_DisableTofInt(uint32_t instance);

/*!
 * @brief Enable specified channel interrupt.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 */
void eTMR_DRV_EnableChnInt(uint32_t instance, uint8_t channel);

/*!
 * @brief Enable channel set interrupt.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channelSet the eTMR channel set
 */
void eTMR_DRV_SetChnsetIntEnable(uint32_t instance, uint8_t channelSet);

/*!
 * @brief Disable specified channel interrupt.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel
 */
void eTMR_DRV_DisableChnInt(uint32_t instance, uint8_t channel);

/*!
 * @brief Disable channel set interrupt.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channelSet the eTMR channel set
 */
void eTMR_DRV_SetChnsetIntDisable(uint32_t instance, uint8_t channelSet);

/*!
 * @brief Get if counter overflow interrupt is enabled or not
 *
 * @param[in] instance the eTMR peripheral instance
 */
bool eTMR_DRV_IsTofIntEnabled(uint32_t instance);

/*!
 * @brief Get if quadrature decoder overflow interrupt is enabled or not
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @return    true/false
 */
bool eTMR_DRV_IsQuadDecodeTofIntEnabled(uint32_t instance);

/*!
 * @brief Get if fault interrupt is enabled or not
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @return    true/false
 */
bool eTMR_DRV_IsFaultIntEnabled(uint32_t instance);

/*!
 * @brief Get if the channel interrupt is enabled or not.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] channel the eTMR channel that needs to get
 *
 * @return    true/false
 */
bool eTMR_DRV_IsChnIntEnabled(uint32_t instance, uint8_t channel);

/*!
 * @brief Get eTMR current counter value.
 *
 * @param[in] instance the eTMR peripheral instance
 *
 * @return    current counter value
 */
uint32_t eTMR_DRV_GetCntVal(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* eTMR_HW_ACCESS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
