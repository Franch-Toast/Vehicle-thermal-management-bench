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

#ifndef SCU_HW_ACCESS_H
#define SCU_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file scu_hw_access.h
 */

/*!
 * @ingroup scu_hw_access
 * @defgroup scu_hw_access
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Set system clock divider.
 *
 * This function set the divider for system clock.
 *
 * @param[in] base         Base address for current SCU instance.
 * @param[in] sysClkDiv    system clock divider.
 */
static inline void SCU_SetSysClkDiv(SCU_Type* const base, uint8_t sysClkDiv)
{
    uint32_t regValue = base->DIV;
    regValue &= ~(SCU_DIV_CPDIVS_MASK);
    regValue |= SCU_DIV_CPDIVS(sysClkDiv);
    base->DIV = regValue;
}
/*!
 * @brief Get system clock divider.
 *
 * This function get the divider for system clock.
 *
 * @param[in] base         Base address for current SCU instance.
 * @return    sysClkDiv    system clock divider.
 */
static inline uint8_t SCU_GetSysClkDiv(SCU_Type* const base)
{
    return (uint8_t)((base->DIVSTS & SCU_DIVSTS_CPDIVST_MASK) >> SCU_DIVSTS_CPDIVST_SHIFT);
}

/*!
 * @brief Fast bus clock divider.
 *
 * This function set the divider for fast bus clock.
 *
 * @param[in] base       Base address for current SCU instance.
 * @param[in] fastBusClkDiv    Fast bus clock divider.
 */
static inline void SCU_SetFastBusClkDiv(SCU_Type* const base, uint16_t fastBusClkDiv)
{
    uint32_t regValue = base->DIV;
    regValue &= ~(SCU_DIV_FBDIVS_MASK);
    regValue |= SCU_DIV_FBDIVS(fastBusClkDiv);
    base->DIV  = regValue;
}
/*!
 * @brief Get fast bus clock divider.
 *
 * This function get the divider for fast bus clock.
 *
 * @param[in] base         Base address for current SCU instance.
 * @return    fastBusClkDiv    fast bus clock divider.
 */
static inline uint8_t SCU_GetFastBusClkDiv(SCU_Type* const base)
{
    return (uint8_t)((base->DIVSTS & SCU_DIVSTS_FBDIVST_MASK) >> SCU_DIVSTS_FBDIVST_SHIFT);
}

/*!
 * @brief Slow bus clock divider.
 *
 * This function set the divider for slow bus clock.
 *
 * @param[in] base       Base address for current SCU instance.
 * @param[in] slowBusClkDiv    Slow bus clock divider.
 */
static inline void SCU_SetSlowBusClkDiv(SCU_Type* const base, uint16_t slowBusClkDiv)
{
    uint32_t regValue = base->DIV;
    regValue &= ~(SCU_DIV_SBDIVS_MASK);
    regValue |= SCU_DIV_SBDIVS(slowBusClkDiv);
    base->DIV  = regValue;
}

/*!
 * @brief Get slow bus clock divider.
 *
 * This function get the divider for slow bus clock.
 *
 * @param[in] base         Base address for current SCU instance.
 * @return    slowBusClkDiv    slow bus clock divider.
 */
static inline uint8_t SCU_GetSlowBusClkDiv(SCU_Type* const base)
{
    return (uint8_t)((base->DIVSTS & SCU_DIVSTS_SBDIVST_MASK) >> SCU_DIVSTS_SBDIVST_SHIFT);
}

/*!
 * @brief Set system clock selection.
 *
 * This function set the system clock source.
 *
 * @param[in] base       Base address for current SCU instance.
 * @param[in] clkSrc    system clock source.
 *            0 : FIRC
 *            1 : PLL
 *            2 : FXOSC
 *            3 : SIRC
 */
static inline void SCU_SetSysClkSrc(SCU_Type* const base, uint8_t clkSrc)
{
    uint32_t regValue = base->CLKS;
    regValue &= ~(SCU_CLKS_CLKSRCSEL_MASK);
    regValue |= SCU_CLKS_CLKSRCSEL(clkSrc);
    base->CLKS = regValue;
}

/*!
 * @brief Get system clock selection.
 *
 * This function get the system clock source.
 *
 * @param[in] base       Base address for current SCU instance.
 * @return clkSrc    system clock source.
 *            0 : FIRC
 *            1 : PLL
 *            2 : FXOSC
 *            3 : SIRC
 */
static inline uint8_t SCU_GetSysClkSrc(SCU_Type* const base)
{
    return (uint8_t)((base->STS & SCU_STS_CLKST_MASK) >> SCU_STS_CLKST_SHIFT);
}

/*!
 * @brief Select clock out source.
 *
 * This function select the clock out source.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] clkoutSrc  clockout source.
 *            0 : Disable clock output
 *            1 : FIRC
 *            2 : SIRC
 *            3 : FXOSC
 *            4 : SXOSC
 *            5 : PLL
 */
static inline void SCU_SetClkOutSrc(SCU_Type* const base, const uint8_t src)
{
    uint32_t regValue = base->CLKO;
    regValue &= ~(SCU_CLKO_CLKOSEL_MASK);
    regValue |= SCU_CLKO_CLKOSEL(src);
    base->CLKO = regValue;
}

/*!
 * @brief Set SCU clock output divider
 *
 * This function set SCU clock output divider.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] clkSrc Clock output divider.
 */
static inline void SCU_SetClkOutDiv(SCU_Type *base, const uint8_t clkDiv)
{
    uint32_t regValue = base->CLKO;
    regValue &= (uint32_t)(~SCU_CLKO_CLKODIV_MASK);
    regValue |= (uint32_t)SCU_CLKO_CLKODIV(clkDiv + 1);
    base->CLKO = regValue;
}

/*!
 * @brief Enables/Disables the fast external oscillator(FXOSC).
 *
 * This function enables/disables the fast external Oscillator(FXOSC).
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the fast external Oscillator(FXOSC).
 *            true - enable
 *            false - disable
 */
static inline void SCU_EnableFxosc(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_FXOSC_EN_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_FXOSC_EN(enable ? 1U : 0U);
    base->FXOSC_CTRL = regValue;
}

/*!
 * @brief Get the value of fast osc enable bit.
 *
 * This function gets the value of fast osc bit.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return value        FXOSC enablement.
 *            0 -       fast osc is not enabled
 *            1 -       fast osc is enabled 
 */
static inline uint8_t SCU_GetFxoscEnableFlag(SCU_Type* const base)
{
    return (((base->FXOSC_CTRL) & SCU_FXOSC_CTRL_FXOSC_EN_MASK) >> SCU_FXOSC_CTRL_FXOSC_EN_SHIFT);
}

/*!
 * @brief Enables/Disables the external fast oscillator(FXOSC) bypass mode.
 *
 * This function enables/disables the external fast oscillator(FXOSC) bypass mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the external fast oscillator(FXOSC) bypass mode.
 *            true - external clock input enabled
 *            false - external oscillator input enabled
 */
static inline void SCU_SetFxoscBypassMode(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_FXOSC_MODE_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_FXOSC_MODE(enable ? 0U : 1U);
    base->FXOSC_CTRL = regValue;
}
#if defined(SCU_FXOSC_CTRL_COMPEN_MASK)
/*!
 * @brief Enables/Disables the external fast oscillator(FXOSC) comp enable mode.
 *
 * This function enables/disables the external fast oscillator(FXOSC) comp enable mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the external fast oscillator(FXOSC) comp.
 *            true - comp enabled
 *            false - comp enabled
 */
static inline void SCU_SetFxoscComp(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_COMPEN_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_COMPEN(enable ? 0U : 1U);
    base->FXOSC_CTRL = regValue;
}
#endif /* SCU_FXOSC_CTRL_COMPEN_MASK */

#if defined(SCU_FXOSC_CTRL_HYSTDIS_MASK)

/*!
 * @brief Enables/Disables the external fast oscillator(FXOSC) hysteresis mode.
 *
 * This function enables/disables the external fast oscillator(FXOSC) hysteresis mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the external fast oscillator(FXOSC) hysteresis mode.
 *            true - OSC Hysteresis is enabled
 *            false - OSC Hysteresis is disabled
 */
static inline void SCU_SetFxoscHysteresis(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_HYSTDIS_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_HYSTDIS(enable ? 0U : 1U);
    base->FXOSC_CTRL = regValue;
}
#endif /* SCU_FXOSC_CTRL_HYSTDIS_MASK */

#if defined(SCU_FXOSC_CTRL_GMSEL_MASK)
/*!
 * @brief External fast oscillator(FXOSC) gain selection.
 *
 * This function set the external fast oscillator(FXOSC) gain selection.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] gain  OSC gain selection value
 */
static inline void SCU_SetFxoscGain(SCU_Type* const base, const uint8_t gain)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_GMSEL_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_GMSEL(gain);
    base->FXOSC_CTRL = regValue;
}
/*!
 * @brief Enables/Disables the external fast oscillator(FXOSC) ALC mode.
 *
 * This function enables/disables the external fast oscillator(FXOSC) ALC mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the external fast oscillator(FXOSC) ALC mode.
 *            true - OSC ALC is enabled
 *            false - OSC ALC is disabled
 */
static inline void SCU_SetFxoscALC(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->FXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_FXOSC_CTRL_ALCDIS_MASK));
    regValue |= (uint32_t)SCU_FXOSC_CTRL_ALCDIS(enable ? 0U : 1U);
    base->FXOSC_CTRL = regValue;
}
#endif /* SCU_FXOSC_CTRL_GMSEL_MASK */

#if FEATURE_SCU_SUPPORT_SXOSC
/*!
 * @brief Enables/Disables the slow external oscillator(SXOSC).
 *
 * This function enables/disables the slow external Oscillator(SXOSC).
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the slow external Oscillator(SXOSC).
 *            true - enable
 *            false - disable
 */
static inline void SCU_EnableSxosc(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_SXOSC_EN_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_SXOSC_EN(enable ? 1U : 0U);
    base->SXOSC_CTRL = regValue;
}
/*!
 * @brief Enables/Disables the slow external oscillator(SXOSC) under deepsleep mode.
 *
 * This function enables/disables the slow external Oscillator(SXOSC) under deepsleep mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the slow external Oscillator(SXOSC).
 *            true - enable
 *            false - disable
 */
static inline void SCU_SxoscDeepSleepEnable(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_SXOSC_DS_EN_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_SXOSC_DS_EN(enable ? 1U : 0U);
    base->SXOSC_CTRL = regValue;
}
/*!
 * @brief Enables/Disables the slow external oscillator(SXOSC) under standby mode.
 *
 * This function enables/disables the slow external Oscillator(SXOSC) under standby mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the slow external Oscillator(SXOSC).
 *            true - enable
 *            false - disable
 */
static inline void SCU_SxoscStandbyEnable(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_SXOSC_STB_EN_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_SXOSC_STB_EN(enable ? 1U : 0U);
    base->SXOSC_CTRL = regValue;
}
/*!
 * @brief Enables/Disables the slow external oscillator(SXOSC) under power down mode.
 *
 * This function enables/disables the slow external Oscillator(SXOSC) under power down mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the slow external Oscillator(SXOSC).
 *            true - enable
 *            false - disable
 */
static inline void SCU_SxoscPowerDownEnable(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_SXOSC_PD_EN_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_SXOSC_PD_EN(enable ? 1U : 0U);
    base->SXOSC_CTRL = regValue;
}

/*!
 * @brief Get the value of slow osc enable bit.
 *
 * This function gets the value of slow osc bit.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return value        SXOSC enablement.
 *            0 -       slow osc is not enabled
 *            1 -       slow osc is enabled 
 */
static inline uint8_t SCU_GetSxoscEnableFlag(SCU_Type* const base)
{
    return (((base->SXOSC_CTRL) & SCU_SXOSC_CTRL_SXOSC_EN_MASK) >> SCU_SXOSC_CTRL_SXOSC_EN_SHIFT);
}

/*!
 * @brief Enables/Disables the external slow oscillator(SXOSC) bypass mode.
 *
 * This function enables/disables the external slow oscillator(SXOSC) bypass mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the external slow oscillator(SXOSC) bypass mode.
 *            true - external clock input enabled
 *            false - external oscillator input enabled
 */
static inline void SCU_SetSxoscBypassMode(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_SXOSC_MODE_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_SXOSC_MODE(enable ? 0U : 1U);
    base->SXOSC_CTRL = regValue;
}
#if defined(SCU_SXOSC_CTRL_GMSEL_MASK)
/*!
 * @brief External slow oscillator(SXOSC) gain selection.
 *
 * This function set the external slow oscillator(SXOSC) gain selection.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] gain  OSC gain selection value
 */
static inline void SCU_SetSxoscGain(SCU_Type* const base, const uint8_t gain)
{
    uint32_t regValue = base->SXOSC_CTRL;
    regValue &= (uint32_t)(~(SCU_SXOSC_CTRL_GMSEL_MASK));
    regValue |= (uint32_t)SCU_SXOSC_CTRL_GMSEL(gain);
    base->SXOSC_CTRL = regValue;
}
#endif /* SCU_SXOSC_CTRL_GMSEL_MASK */
#endif /* FEATURE_SCU_SUPPORT_SXOSC */

#if defined(FEATURE_SCU_SUPPORT_PLL) && (FEATURE_SCU_SUPPORT_PLL == 1U)
/*!
 * @brief PLL reference clock selection.
 *
 * This function set PLL reference clock source selection.
 *
 * @param[in] base      Base address for current SCU instance.
 * @param[in] pllRefClk PLL reference clock
 */
static inline void SCU_SetPllRefClk(SCU_Type* const base, const uint8_t pllRefClk)
{
    uint32_t regValue = base->PLL_CTRL;
    regValue &= (uint32_t)(~(SCU_PLL_CTRL_REFCLKSRCSEL_MASK));
    regValue |= (uint32_t)SCU_PLL_CTRL_REFCLKSRCSEL(pllRefClk);
    base->PLL_CTRL = regValue;
}
/*!
 * @brief PLL get reference clock selection.
 *
 * This function get PLL reference clock source selection.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return              pllRefClk PLL reference clock
 */
static inline uint8_t SCU_GetPllRefClk(SCU_Type* const base)
{
    return (uint8_t)((base->PLL_CTRL & SCU_PLL_CTRL_REFCLKSRCSEL_MASK) >> SCU_PLL_CTRL_REFCLKSRCSEL_SHIFT);
}
/*!
 * @brief PLL feedback clock divider selection.
 *
 * This function set PLL feedback clock divider.
 *
 * @param[in] base      Base address for current SCU instance.
 * @param[in] pllRefClk PLL feedback clock divider
 */
static inline void SCU_SetPllFeedBackDiv(SCU_Type* const base, const uint8_t pllFeedBackDiv)
{
    uint32_t regValue = base->PLL_CTRL;
    regValue &= (uint32_t)(~(SCU_PLL_CTRL_FBDIV_MASK));
    regValue |= (uint32_t)SCU_PLL_CTRL_FBDIV(pllFeedBackDiv - 1);
    base->PLL_CTRL = regValue;
}
/*!
 * @brief PLL get feedback clock divider selection.
 *
 * This function get PLL feedback clock divider.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return    pllRefClk PLL feedback clock divider
 */
static inline uint8_t SCU_GetPllFeedBackDiv(SCU_Type* const base)
{
    return (uint8_t)(((base->PLL_CTRL & SCU_PLL_CTRL_FBDIV_MASK) >> SCU_PLL_CTRL_FBDIV_SHIFT) + 1);
}
/*!
 * @brief PLL reference clock divider selection.
 *
 * This function set PLL reference clock divider.
 *
 * @param[in] base      Base address for current SCU instance.
 * @param[in] pllRefClk PLL reference clock divider
 */
static inline void SCU_SetPllRefClkDiv(SCU_Type* const base, const uint8_t pllRefClkDiv)
{
    uint32_t regValue = base->PLL_CTRL;
    regValue &= (uint32_t)(~(SCU_PLL_CTRL_REFDIV_MASK));
    regValue |= (uint32_t)SCU_PLL_CTRL_REFDIV(pllRefClkDiv - 1);
    base->PLL_CTRL = regValue;
}
/*!
 * @brief PLL get reference clock divider selection.
 *
 * This function get PLL reference clock divider.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return    pllRefClk PLL reference clock divider
 */
static inline uint8_t SCU_GetPllRefClkDiv(SCU_Type* const base)
{
    return (uint8_t)(((base->PLL_CTRL & SCU_PLL_CTRL_REFDIV_MASK) >> SCU_PLL_CTRL_REFDIV_SHIFT) + 1);
}
/*!
 * @brief Enables/Disables the PLL clock.
 *
 * This function enables/disables PLL clock.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    enable/disable the PLL clock.
 *            true - enable
 *            false - disable
 */
static inline void SCU_EnablePll(SCU_Type* const base, const bool enable)
{
    uint32_t regValue = base->PLL_CTRL;
    regValue &= (uint32_t)(~(SCU_PLL_CTRL_PLL_EN_MASK));
    regValue |= (uint32_t)SCU_PLL_CTRL_PLL_EN(enable ? 1U : 0U);
    base->PLL_CTRL = regValue;
}
/*!
 * @brief Get the PLL lock status.
 *
 * This function get pll clock status.
 *
 * @param[in] base  Base address for current SCU instance.
 * @return bool the PLL clock clock status.
 */
static inline bool SCU_GetPllLock(SCU_Type* const base)
{
    return (bool)((base->STS & SCU_STS_PLL_LOCK_MASK) >> SCU_STS_PLL_LOCK_SHIFT);
}
#endif /* FEATURE_SCU_SUPPORT_PLL */

/*!
 * @brief Force SIRC enable during low power mode.
 *
 * This function force SIRC enable during deepsleep mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    Force SIRC enable during deepsleep mode.
 *            true - Force SIRC enable during deepsleep mode
 *            false - Do not force SIRC enable during deepsleep mode
 */
static inline void SCU_SircDeepSleepEnable(SCU_Type *base, const bool enable)
{
    uint32_t regValue = base->SIRC_CTRL;
    regValue &= (uint32_t)(~SCU_SIRC_CTRL_SIRC_DS_EN_MASK);
    regValue |= (uint32_t)SCU_SIRC_CTRL_SIRC_DS_EN(enable ? 1U : 0U);
    base->SIRC_CTRL = regValue;
}

/*!
 * @brief Force SIRC enable during standby mode.
 *
 * This function force SIRC enable during standby mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    Force SIRC enable during standby mode.
 *            true - Force SIRC enable during standby mode
 *            false - Do not force SIRC enable during standby mode
 */
static inline void SCU_SircStandbyEnable(SCU_Type *base, const bool enable)
{
    uint32_t regValue = base->SIRC_CTRL;
    regValue &= (uint32_t)(~SCU_SIRC_CTRL_SIRC_STB_EN_MASK);
    regValue |= (uint32_t)SCU_SIRC_CTRL_SIRC_STB_EN(enable ? 1U : 0U);
    base->SIRC_CTRL = regValue;
}
#if defined(FEATURE_SOC_SUPPORT_POWERDOWN_MODE) && (FEATURE_SOC_SUPPORT_POWERDOWN_MODE == 1)
/*!
 * @brief Force SIRC enable during power down mode.
 *
 * This function force SIRC enable during power down mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    Force SIRC enable during power down mode.
 *            true - Force SIRC enable during deepsleep mode
 *            false - Do not force SIRC enable during deepsleep mode
 */
static inline void SCU_SircPowerDownEnable(SCU_Type *base, const bool enable)
{
    uint32_t regValue = base->SIRC_CTRL;
    regValue &= (uint32_t)(~SCU_SIRC_CTRL_SIRC_PD_EN_MASK);
    regValue |= (uint32_t)SCU_SIRC_CTRL_SIRC_PD_EN(enable ? 1U : 0U);
    base->SIRC_CTRL = regValue;
}

#endif /* FEATURE_SOC_SUPPORT_POWERDOWN_MODE */


/*!
 * @brief Enable FIRC.
 *
 * This function enable FIRC.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    Enable FIRC.
 *            true -    Force FIRC to enable
 *            false -   Don't force FIRC to enable
 */
static inline void SCU_EnableFirc(SCU_Type *base, const bool enable)
{
    uint32_t regValue = base->FIRC_CTRL;
    regValue &= (uint32_t)(~SCU_FIRC_CTRL_FIRC_EN_MASK);
    regValue |= (uint32_t)SCU_FIRC_CTRL_FIRC_EN(enable ? 1U : 0U);
    base->FIRC_CTRL = regValue;
}
/*!
 * @brief Force FIRC enable during low power mode.
 *
 * This function force FIRC enable during deepsleep mode.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] enable    Force FIRC enable during deepsleep mode.
 *            true - Force FIRC enable during deepsleep mode
 *            false - Do not force FIRC enable during deepsleep mode
 */
static inline void SCU_FircDeepSleepEnable(SCU_Type *base, const bool enable)
{
    uint32_t regValue = base->FIRC_CTRL;
    regValue &= (uint32_t)(~SCU_FIRC_CTRL_FIRC_DS_EN_MASK);
    regValue |= (uint32_t)SCU_FIRC_CTRL_FIRC_DS_EN(enable ? 1U : 0U);
    base->FIRC_CTRL = regValue;
}

/*!
 * @brief Get the FIRC valid status.
 *
 * This function get FIRC valid status.
 *
 * @param[in] base  Base address for current SCU instance.
 * @return bool the FIRC clock valid status.
 */
static inline bool SCU_GetFIRCValid(SCU_Type* const base)
{
    return (bool)((base->STS & SCU_STS_FIRC_VALID_MASK) >> SCU_STS_FIRC_VALID_SHIFT);
}
/*!
 * @brief Get the value of FIRCEN bit.
 *
 * This function gets the value of FIRCEN bit.
 *
 * @param[in] base      Base address for current SCU instance.
 * @return value        FIRC enablement.
 *            0 -       not set FIRCEN bit
 *            1 -       set FIRCEN bit
 */
static inline uint8_t SCU_GetFircEnableFlag(SCU_Type* const base)
{
    return (((base->FIRC_CTRL) & SCU_FIRC_CTRL_FIRC_EN_MASK) >> SCU_FIRC_CTRL_FIRC_EN_SHIFT);
}


/*!
 * @brief Get the FXOSC valid status.
 *
 * This function get FXOSC valid status.
 *
 * @param[in] base  Base address for current SCU instance.
 * @return bool the FXOSC clock valid status.
 */
static inline bool SCU_GetFXOSCValid(SCU_Type* const base)
{
    return (bool)((base->STS & SCU_STS_FXOSC_VALID_MASK) >> SCU_STS_FXOSC_VALID_SHIFT);
}

#if FEATURE_SCU_SUPPORT_SXOSC
/*!
 * @brief Get the SXOSC valid status.
 *
 * This function get SXOSC valid status.
 *
 * @param[in] base  Base address for current SCU instance.
 * @return bool the SXOSC clock valid status.
 */
static inline bool SCU_GetSXOSCValid(SCU_Type* const base)
{
    return (bool)((base->STS & SCU_STS_SXOSC_VALID_MASK) >> SCU_STS_SXOSC_VALID_SHIFT);
}
#endif /* FEATURE_SCU_SUPPORT_SXOSC */

/*!
 * @brief Get system, fast and slow bus clock divider stable state.
 *
 * This function gets if clock divider is stable
 *
 * @param[in] base      Base address for current SCU instance.
 * @return value        clock divider status
 *         false -      Not stable 
 *         true  -      Stable
 */
static inline bool SCU_GetDividerStable(SCU_Type* const base)
{
    uint32_t regValue = base->DIVSTS;
    return (regValue == base->DIV);
}
/*!
 * @brief Enable CMU channel monitor enable or not.
 *
 * This function enable/disable CMU channel monitor.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] ch    CMU channel monitor channel
 * @param[in] enable    CMU channel monitor enable or disable
 *            true - CMU channel monitor enabled
 *            false - CMU channel monitor disabled
 */
static inline void SCU_SetCmuChEnable(SCU_Type *base, const uint8_t ch, const bool enable)
{
    uint32_t regValue = base->CMU_CTRL;
    regValue &= (uint32_t)(~(0x01 << (SCU_CMU_CTRL_CMU0_EN_SHIFT + ch)));
    base->CMU_CTRL = regValue | (enable << (SCU_CMU_CTRL_CMU0_EN_SHIFT + ch));
}
/*!
 * @brief Enable CMU channel monitor reset enable or not.
 *
 * This function enable/disable CMU channel monitor reset function.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] ch    CMU channel monitor channel
 * @param[in] enable    CMU channel monitor enable or disable
 *            true - CMU channel monitor will reset MCU
 *            false - CMU channel monitor won't reset MCU
 */
static inline void SCU_SetCmuChResetEnable(SCU_Type *base, const uint8_t ch, const bool enable)
{
    uint32_t regValue = base->CMU_CTRL;
    regValue &= (uint32_t)(~(0x01 << (SCU_CMU_CTRL_CMU0_RE_SHIFT + ch)));
    base->CMU_CTRL = regValue | (enable << (SCU_CMU_CTRL_CMU0_RE_SHIFT + ch));
}
#if defined(FEATURE_SCU_SUPPORT_CMU_REFCLK_SEL) && (FEATURE_SCU_SUPPORT_CMU_REFCLK_SEL)
/*!
 * @brief Select CMU channel reference clock
 *
 * This function set CMU channel reference clock
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] ch    CMU channel monitor channel
 * @param[in] refClock CMU channel monitor reference clock
 *            0 - SIRC as reference clock
 *            1 - FXOSC as reference clock
 */
static inline void SCU_SetCmuChRefClock(SCU_Type *base, const uint8_t ch, const uint8_t refClock)
{
    uint32_t regValue = base->CMU_CTRL;
    regValue &= (uint32_t)(~(0x01 << (SCU_CMU_CTRL_CMU0_REFS_SHIFT + ch)));
    base->CMU_CTRL = regValue | (refClock << (SCU_CMU_CTRL_CMU0_REFS_SHIFT + ch));
}
#endif /* FEATURE_SCU_SUPPORT_CMU_REFCLK_SEL */
/*!
 * @brief Set CMU channel compare high value
 *
 * This function set CMU channel compare high value.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] ch    CMU channel monitor channel
 * @param[in] value CMU channel compare high value
 */
static inline void SCU_SetCmuChCompHigh(SCU_Type *base, const uint8_t ch, const uint16_t value)
{
    base->CMUCMP[ch].HIGH = value;
}
/*!
 * @brief Set CMU channel compare low value
 *
 * This function set CMU channel compare low value.
 *
 * @param[in] base  Base address for current SCU instance.
 * @param[in] ch    CMU channel monitor channel
 * @param[in] value CMU channel compare low value
 */
static inline void SCU_SetCmuChCompLow(SCU_Type *base, const uint8_t ch, const uint16_t value)
{
    base->CMUCMP[ch].LOW = value;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* SCU_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
