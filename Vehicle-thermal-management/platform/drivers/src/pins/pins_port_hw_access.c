/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may only
 * be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

#include "pins_port_hw_access.h"
#include "pins_gpio_hw_access.h"


#if FEATURE_SOC_PORT_COUNT > 0

/*******************************************************************************
 * Code
 ******************************************************************************/


/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_Init
 * Description   : This function configures the pins with the options provided
 * in the provided structure.
 *
 *END**************************************************************************/
void PINS_Init(const pin_settings_config_t * config)
{
    DEV_ASSERT(config->base != NULL);
    DEV_ASSERT((PCTRL_MUX_AS_GPIO != config->mux) || (config->gpioBase != NULL));
    DEV_ASSERT(config->pinPortIdx < PCTRL_PCR_COUNT);
    uint32_t regValue = config->base->PCR[config->pinPortIdx];
    uint32_t directions;

#if FEATURE_PINS_HAS_PULL_SELECTION
    switch (config->pullConfig)
    {
        case PCTRL_INTERNAL_PULL_NOT_ENABLED:
            {
                regValue &= ~(PCTRL_PCR_PE_MASK);
            }
            break;
        case PCTRL_INTERNAL_PULL_DOWN_ENABLED:
            {
                regValue &= ~(PCTRL_PCR_PS_MASK);
                regValue |= PCTRL_PCR_PE(1U);
            }
            break;
        case PCTRL_INTERNAL_PULL_UP_ENABLED:
            {
                regValue |= PCTRL_PCR_PE(1U);
                regValue |= PCTRL_PCR_PS(1U);
            }
            break;
        default:
            /* invalid command */
            DEV_ASSERT(false);
            break;
    }
#endif /* FEATURE_PINS_HAS_PULL_SELECTION */
#if FEATURE_PINS_HAS_SLEW_RATE
    regValue &= ~(PCTRL_PCR_SRE_MASK);
    regValue |= PCTRL_PCR_SRE(config->rateSelect);
#endif
#if FEATURE_PINS_HAS_PASSIVE_FILTER
    regValue &= ~(PCTRL_PCR_PFE_MASK);
    regValue |= PCTRL_PCR_PFE(config->passiveFilter);
#endif
#if FEATURE_PINS_HAS_OPEN_DRAIN
    regValue &= ~(PCTRL_PCR_ODE_MASK);
    regValue |= PCTRL_PCR_ODE(config->openDrain);
#endif
#if FEATURE_PINS_HAS_DRIVE_STRENGTH
    regValue &= ~(PCTRL_PCR_DSE_MASK);
    regValue |= PCTRL_PCR_DSE(config->driveSelect);
#endif
    regValue &= ~(PCTRL_PCR_MUX_MASK);
    regValue |= PCTRL_PCR_MUX(config->mux);
#if FEATURE_PCTRL_HAS_PIN_CONTROL_LOCK
    regValue &= ~(PCTRL_PCR_LOCK_MASK);
    regValue |= PCTRL_PCR_LOCK(config->pinLock);
#endif

    config->base->PCR[config->pinPortIdx] = regValue;

    /* config irq register */

    config->gpioBase->PCR[config->pinPortIdx] &= ~(GPIO_PCR_IRQC_MASK);
    config->gpioBase->PCR[config->pinPortIdx] |= GPIO_PCR_IRQC(config->intConfig);
    if (config->clearIntFlag)
    {
        config->gpioBase->PIFR = 0x01 << config->pinPortIdx;
    }
#if FEATURE_PINS_HAS_DIGITAL_FILTER
    if (config->digitalFilter){
        PINS_ConfigDigitalFilter(config->gpioBase, &config->filterConfig, config->pinPortIdx);
        config->gpioBase->PCR[config->pinPortIdx] |= GPIO_PCR_DFE_MASK;
    } else {
        config->gpioBase->PCR[config->pinPortIdx] &= ~GPIO_PCR_DFE_MASK;
    }
#endif /* FEATURE_PINS_HAS_DIGITAL_FILTER */
#if FEATURE_PCTRL_HAS_DIGITAL_FILTER
    if (config->digitalFilter){
        PINS_ConfigDigitalFilter(config->base, &config->filterConfig, config->pinPortIdx);
        config->base->PCR[config->pinPortIdx] |= PCTRL_PCR_DFE_MASK;
    } else {
        config->base->PCR[config->pinPortIdx] &= ~PCTRL_PCR_DFE_MASK;
    }
#endif /* FEATURE_PCTRL_HAS_DIGITAL_FILTER */
    /* If gpioBase address not null setup the direction of pin */
    if (PCTRL_MUX_AS_GPIO == config->mux)
    {
        /* Read current direction */
        directions = (uint32_t)(config->gpioBase->POER);
        switch (config->direction)
        {
            case GPIO_INPUT_DIRECTION:
                directions &= ~(1UL << config->pinPortIdx);
                break;
            case GPIO_OUTPUT_DIRECTION:
                directions |= (1UL << config->pinPortIdx);
                break;
            case GPIO_UNSPECIFIED_DIRECTION:
            /* pass-through */
            default:
                /* nothing to configure */
                DEV_ASSERT(false);
                break;
        }

        /* Configure initial value for output */
        if (config->direction == GPIO_OUTPUT_DIRECTION)
        {
            PINS_GPIO_WritePin(config->gpioBase, config->pinPortIdx, config->initValue);
        }

        /* Configure direction */
        config->gpioBase->POER = GPIO_POER_POE(directions);
        //config->gpioBase->PIER = GPIO_PIER_PIE(~directions);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_SetMuxModeSel
 * Description   : This function configures the pin muxing and support configuring
 * for the pins that have ADC interleaved channel as well.
 *
 *END**************************************************************************/
void PINS_SetMuxModeSel(PCTRL_Type * const base,
                        uint32_t pin,
                        port_mux_t mux)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];

    regValue &= ~(PCTRL_PCR_MUX_MASK);
    regValue |= PCTRL_PCR_MUX(mux);
    base->PCR[pin] = regValue;
}



#endif /* FEATURE_SOC_PCTRL_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/
