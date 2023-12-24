/*
** ###################################################################
**     Processor:           YTM32B1ME0
**     Version:             rev. 1.4, Wed Oct 25 17:09:10 2023
**
**     Abstract:
**         Peripheral Access Layer for YTM32B1ME0
**
**     Copyright (c) YTMicro Semiconductor, Inc.
**     Copyright 2016-2020 YTM
**     All rights reserved.
**
** ###################################################################
*/

/*!
 * @file YTM32B1ME0.h
 * @version 1.4
 * @date Wed Oct 25 17:09:10 2023
 * @brief Peripheral Access Layer for YTM32B1ME0
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(YTM32B1ME0_H_)  /* Check if memory map has not been already included */
#define YTM32B1ME0_H_
#define MCU_YTM32B1ME0

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error YTM32B1ME0 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0003u

#include <stdint.h>

/* ----------------------------------------------------------------------------
   -- Generic macros
   ---------------------------------------------------------------------------- */

/* IO definitions (access restrictions to peripheral registers) */
/**
*   IO Type Qualifiers are used
*   \li to specify the access to peripheral variables.
*   \li for automatic generation of peripheral register debug information.
*/
#ifndef __IO
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#endif


/**
* @brief 32 bits memory read macro.
*/
#if !defined(REG_READ32)
  #define REG_READ32(address)               (*(volatile uint32_t*)(address))
#endif

/**
* @brief 32 bits memory write macro.
*/
#if !defined(REG_WRITE32)
  #define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/**
* @brief 32 bits bits setting macro.
*/
#if !defined(REG_BIT_SET32)
  #define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address))|= (uint32_t)(mask))
#endif

/**
* @brief 32 bits bits clearing macro.
*/
#if !defined(REG_BIT_CLEAR32)
  #define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address))&= ((uint32_t)~((uint32_t)(mask))))
#endif

/**
* @brief 32 bit clear bits and set with new value
* @note It is user's responsability to make sure that value has only "mask" bits set - (value&~mask)==0
*/
#if !defined(REG_RMW32)
  #define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32_t)~((uint32_t)(mask))))| ((uint32_t)(value)))))
#endif
/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers for YTM32B1ME0
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers_YTM32B1L Interrupt vector numbers for YTM32B1L
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 208u          /**< Number of interrupts in the Vector table */

/**
 * @brief Defines the Interrupt Numbers definitions
 *
 * This enumeration is used to configure the interrupts.
 *
 * Implements : IRQn_Type_Class
 */
typedef enum
{
  /* Auxiliary constants */
  NotAvail_IRQn     = -128,                /**< Not available device specific interrupt */

  /* Core interrupts */
  NMI_IRQn                    =  -14,                /**< NMI Interrupt */ 
  HardFault_IRQn              =  -13,                /**< HardFault Interrupt */ 
  MemManage_IRQn              =  -12,                /**< MemManage Interrupt */ 
  BusFault_IRQn               =  -11,                /**< BusFault Interrupt */ 
  UsageFault_IRQn             =  -10,                /**< UsageFault Interrupt */ 
  SVC_IRQn                    =   -5,                /**< SVC Interrupt */ 
  DebugMon_IRQn               =   -4,                /**< DebugMon Interrupt */ 
  PendSV_IRQn                 =   -2,                /**< PendSV Interrupt */ 
  SysTick_IRQn                =   -1,                /**< SysTick Interrupt */ 
  /* Device specific interrupts */
  DMA0_IRQn                   =    0,                /**< DMA0 Interrupt */ 
  DMA1_IRQn                   =    1,                /**< DMA1 Interrupt */ 
  DMA2_IRQn                   =    2,                /**< DMA2 Interrupt */ 
  DMA3_IRQn                   =    3,                /**< DMA3 Interrupt */ 
  DMA4_IRQn                   =    4,                /**< DMA4 Interrupt */ 
  DMA5_IRQn                   =    5,                /**< DMA5 Interrupt */ 
  DMA6_IRQn                   =    6,                /**< DMA6 Interrupt */ 
  DMA7_IRQn                   =    7,                /**< DMA7 Interrupt */ 
  DMA8_IRQn                   =    8,                /**< DMA8 Interrupt */ 
  DMA9_IRQn                   =    9,                /**< DMA9 Interrupt */ 
  DMA10_IRQn                  =   10,                /**< DMA10 Interrupt */ 
  DMA11_IRQn                  =   11,                /**< DMA11 Interrupt */ 
  DMA12_IRQn                  =   12,                /**< DMA12 Interrupt */ 
  DMA13_IRQn                  =   13,                /**< DMA13 Interrupt */ 
  DMA14_IRQn                  =   14,                /**< DMA14 Interrupt */ 
  DMA15_IRQn                  =   15,                /**< DMA15 Interrupt */ 
  DMA_Error_IRQn              =   16,                /**< DMA_Error Interrupt */ 
  FPU_IRQn                    =   17,                /**< FPU Interrupt */ 
  EFM_IRQn                    =   18,                /**< EFM Interrupt */ 
  EFM_Error_IRQn              =   19,                /**< EFM_Error Interrupt */ 
  PCU_IRQn                    =   20,                /**< PCU Interrupt */ 
  EFM_Ecc_IRQn                =   21,                /**< EFM_Ecc Interrupt */ 
  WDG_IRQn                    =   22,                /**< WDG Interrupt */ 
  RCU_IRQn                    =   23,                /**< RCU Interrupt */ 
  I2C0_Master_IRQn            =   24,                /**< I2C0_Master Interrupt */ 
  I2C0_Slave_IRQn             =   25,                /**< I2C0_Slave Interrupt */ 
  SPI0_IRQn                   =   26,                /**< SPI0 Interrupt */ 
  SPI1_IRQn                   =   27,                /**< SPI1 Interrupt */ 
  SPI2_IRQn                   =   28,                /**< SPI2 Interrupt */ 
  I2C1_Master_IRQn            =   29,                /**< I2C1_Master Interrupt */ 
  I2C1_Slave_IRQn             =   30,                /**< I2C1_Slave Interrupt */ 
  LINFlexD0_IRQn              =   31,                /**< LINFlexD0 Interrupt */ 
  Reserved5_IRQn              =   32,                /**< Reserved5 Interrupt */ 
  LINFlexD1_IRQn              =   33,                /**< LINFlexD1 Interrupt */ 
  Reserved6_IRQn              =   34,                /**< Reserved6 Interrupt */ 
  LINFlexD2_IRQn              =   35,                /**< LINFlexD2 Interrupt */ 
  Reserved7_IRQn              =   36,                /**< Reserved7 Interrupt */ 
  Reserved8_IRQn              =   37,                /**< Reserved8 Interrupt */ 
  Reserved9_IRQn              =   38,                /**< Reserved9 Interrupt */ 
  ADC0_IRQn                   =   39,                /**< ADC0 Interrupt */ 
  ADC1_IRQn                   =   40,                /**< ADC1 Interrupt */ 
  ACMP0_IRQn                  =   41,                /**< ACMP0 Interrupt */ 
  Reserved10_IRQn             =   42,                /**< Reserved10 Interrupt */ 
  Reserved11_IRQn             =   43,                /**< Reserved11 Interrupt */ 
  EMU_IRQn                    =   44,                /**< EMU Interrupt */ 
  Reserved12_IRQn             =   45,                /**< Reserved12 Interrupt */ 
  RTC_IRQn                    =   46,                /**< RTC Interrupt */ 
  RTC_Seconds_IRQn            =   47,                /**< RTC_Seconds Interrupt */ 
  pTMR_Ch0_IRQn               =   48,                /**< pTMR_Ch0 Interrupt */ 
  pTMR_Ch1_IRQn               =   49,                /**< pTMR_Ch1 Interrupt */ 
  pTMR_Ch2_IRQn               =   50,                /**< pTMR_Ch2 Interrupt */ 
  pTMR_Ch3_IRQn               =   51,                /**< pTMR_Ch3 Interrupt */ 
  PTU0_IRQn                   =   52,                /**< PTU0 Interrupt */ 
  Reserved13_IRQn             =   53,                /**< Reserved13 Interrupt */ 
  Reserved14_IRQn             =   54,                /**< Reserved14 Interrupt */ 
  Reserved15_IRQn             =   55,                /**< Reserved15 Interrupt */ 
  Reserved16_IRQn             =   56,                /**< Reserved16 Interrupt */ 
  SCU_IRQn                    =   57,                /**< SCU Interrupt */ 
  lpTMR0_IRQn                 =   58,                /**< lpTMR0 Interrupt */ 
  GPIOA_IRQn                  =   59,                /**< GPIOA Interrupt */ 
  GPIOB_IRQn                  =   60,                /**< GPIOB Interrupt */ 
  GPIOC_IRQn                  =   61,                /**< GPIOC Interrupt */ 
  GPIOD_IRQn                  =   62,                /**< GPIOD Interrupt */ 
  GPIOE_IRQn                  =   63,                /**< GPIOE Interrupt */ 
  Reserved17_IRQn             =   64,                /**< Reserved17 Interrupt */ 
  Reserved18_IRQn             =   65,                /**< Reserved18 Interrupt */ 
  Reserved19_IRQn             =   66,                /**< Reserved19 Interrupt */ 
  Reserved20_IRQn             =   67,                /**< Reserved20 Interrupt */ 
  PTU1_IRQn                   =   68,                /**< PTU1 Interrupt */ 
  Reserved21_IRQn             =   69,                /**< Reserved21 Interrupt */ 
  Reserved22_IRQn             =   70,                /**< Reserved22 Interrupt */ 
  Reserved23_IRQn             =   71,                /**< Reserved23 Interrupt */ 
  Reserved24_IRQn             =   72,                /**< Reserved24 Interrupt */ 
  Reserved25_IRQn             =   73,                /**< Reserved25 Interrupt */ 
  Reserved26_IRQn             =   74,                /**< Reserved26 Interrupt */ 
  Reserved27_IRQn             =   75,                /**< Reserved27 Interrupt */ 
  Reserved28_IRQn             =   76,                /**< Reserved28 Interrupt */ 
  Reserved29_IRQn             =   77,                /**< Reserved29 Interrupt */ 
  CAN0_ORed_IRQn              =   78,                /**< CAN0_ORed Interrupt */ 
  CAN0_Error_IRQn             =   79,                /**< CAN0_Error Interrupt */ 
  CAN0_Wake_Up_IRQn           =   80,                /**< CAN0_Wake_Up Interrupt */ 
  CAN0_ORed_0_15_MB_IRQn      =   81,                /**< CAN0_ORed_0_15_MB Interrupt */ 
  CAN0_ORed_16_31_MB_IRQn     =   82,                /**< CAN0_ORed_16_31_MB Interrupt */ 
  CAN0_ORed_32_47_MB_IRQn     =   83,                /**< CAN0_ORed_32_47_MB Interrupt */ 
  CAN0_ORed_48_63_MB_IRQn     =   84,                /**< CAN0_ORed_48_63_MB Interrupt */ 
  CAN1_ORed_IRQn              =   85,                /**< CAN1_ORed Interrupt */ 
  CAN1_Error_IRQn             =   86,                /**< CAN1_Error Interrupt */ 
  CAN1_Wake_Up_IRQn           =   87,                /**< CAN1_Wake_Up Interrupt */ 
  CAN1_ORed_0_15_MB_IRQn      =   88,                /**< CAN1_ORed_0_15_MB Interrupt */ 
  CAN1_ORed_16_31_MB_IRQn     =   89,                /**< CAN1_ORed_16_31_MB Interrupt */ 
  CAN1_ORed_32_47_MB_IRQn     =   90,                /**< CAN1_ORed_32_47_MB Interrupt */ 
  CAN1_ORed_48_63_MB_IRQn     =   91,                /**< CAN1_ORed_48_63_MB Interrupt */ 
  CAN2_ORed_IRQn              =   92,                /**< CAN2_ORed Interrupt */ 
  CAN2_Error_IRQn             =   93,                /**< CAN2_Error Interrupt */ 
  CAN2_Wake_Up_IRQn           =   94,                /**< CAN2_Wake_Up Interrupt */ 
  CAN2_ORed_0_15_MB_IRQn      =   95,                /**< CAN2_ORed_0_15_MB Interrupt */ 
  CAN2_ORed_16_31_MB_IRQn     =   96,                /**< CAN2_ORed_16_31_MB Interrupt */ 
  CAN2_ORed_32_47_MB_IRQn     =   97,                /**< CAN2_ORed_32_47_MB Interrupt */ 
  CAN2_ORed_48_63_MB_IRQn     =   98,                /**< CAN2_ORed_48_63_MB Interrupt */ 
  eTMR0_Ch0_Ch1_IRQn          =   99,                /**< eTMR0_Ch0_Ch1 Interrupt */ 
  eTMR0_Ch2_Ch3_IRQn          =  100,                /**< eTMR0_Ch2_Ch3 Interrupt */ 
  eTMR0_Ch4_Ch5_IRQn          =  101,                /**< eTMR0_Ch4_Ch5 Interrupt */ 
  eTMR0_Ch6_Ch7_IRQn          =  102,                /**< eTMR0_Ch6_Ch7 Interrupt */ 
  eTMR0_Fault_IRQn            =  103,                /**< eTMR0_Fault Interrupt */ 
  eTMR0_Ovf_IRQn              =  104,                /**< eTMR0_Ovf Interrupt */ 
  eTMR1_Ch0_Ch1_IRQn          =  105,                /**< eTMR1_Ch0_Ch1 Interrupt */ 
  eTMR1_Ch2_Ch3_IRQn          =  106,                /**< eTMR1_Ch2_Ch3 Interrupt */ 
  eTMR1_Ch4_Ch5_IRQn          =  107,                /**< eTMR1_Ch4_Ch5 Interrupt */ 
  eTMR1_Ch6_Ch7_IRQn          =  108,                /**< eTMR1_Ch6_Ch7 Interrupt */ 
  eTMR1_Fault_IRQn            =  109,                /**< eTMR1_Fault Interrupt */ 
  eTMR1_Ovf_IRQn              =  110,                /**< eTMR1_Ovf Interrupt */ 
  eTMR2_Ch0_Ch1_IRQn          =  111,                /**< eTMR2_Ch0_Ch1 Interrupt */ 
  eTMR2_Ch2_Ch3_IRQn          =  112,                /**< eTMR2_Ch2_Ch3 Interrupt */ 
  eTMR2_Ch4_Ch5_IRQn          =  113,                /**< eTMR2_Ch4_Ch5 Interrupt */ 
  eTMR2_Ch6_Ch7_IRQn          =  114,                /**< eTMR2_Ch6_Ch7 Interrupt */ 
  eTMR2_Fault_IRQn            =  115,                /**< eTMR2_Fault Interrupt */ 
  eTMR2_Ovf_IRQn              =  116,                /**< eTMR2_Ovf Interrupt */ 
  eTMR3_Ch0_Ch1_IRQn          =  117,                /**< eTMR3_Ch0_Ch1 Interrupt */ 
  eTMR3_Ch2_Ch3_IRQn          =  118,                /**< eTMR3_Ch2_Ch3 Interrupt */ 
  eTMR3_Ch4_Ch5_IRQn          =  119,                /**< eTMR3_Ch4_Ch5 Interrupt */ 
  eTMR3_Ch6_Ch7_IRQn          =  120,                /**< eTMR3_Ch6_Ch7 Interrupt */ 
  eTMR3_Fault_IRQn            =  121,                /**< eTMR3_Fault Interrupt */ 
  eTMR3_Ovf_IRQn              =  122,                /**< eTMR3_Ovf Interrupt */ 
  eTMR4_Ch0_Ch1_IRQn          =  123,                /**< eTMR4_Ch0_Ch1 Interrupt */ 
  eTMR4_Ch2_Ch3_IRQn          =  124,                /**< eTMR4_Ch2_Ch3 Interrupt */ 
  eTMR4_Ch4_Ch5_IRQn          =  125,                /**< eTMR4_Ch4_Ch5 Interrupt */ 
  eTMR4_Ch6_Ch7_IRQn          =  126,                /**< eTMR4_Ch6_Ch7 Interrupt */ 
  eTMR4_Fault_IRQn            =  127,                /**< eTMR4_Fault Interrupt */ 
  eTMR4_Ovf_IRQn              =  128,                /**< eTMR4_Ovf Interrupt */ 
  eTMR5_Ch0_Ch1_IRQn          =  129,                /**< eTMR5_Ch0_Ch1 Interrupt */ 
  eTMR5_Ch2_Ch3_IRQn          =  130,                /**< eTMR5_Ch2_Ch3 Interrupt */ 
  eTMR5_Ch4_Ch5_IRQn          =  131,                /**< eTMR5_Ch4_Ch5 Interrupt */ 
  eTMR5_Ch6_Ch7_IRQn          =  132,                /**< eTMR5_Ch6_Ch7 Interrupt */ 
  eTMR5_Fault_IRQn            =  133,                /**< eTMR5_Fault Interrupt */ 
  eTMR5_Ovf_IRQn              =  134,                /**< eTMR5_Ovf Interrupt */ 
  Reserved30_IRQn             =  135,                /**< Reserved30 Interrupt */ 
  Reserved31_IRQn             =  136,                /**< Reserved31 Interrupt */ 
  Reserved32_IRQn             =  137,                /**< Reserved32 Interrupt */ 
  Reserved33_IRQn             =  138,                /**< Reserved33 Interrupt */ 
  Reserved34_IRQn             =  139,                /**< Reserved34 Interrupt */ 
  Reserved35_IRQn             =  140,                /**< Reserved35 Interrupt */ 
  Reserved36_IRQn             =  141,                /**< Reserved36 Interrupt */ 
  Reserved37_IRQn             =  142,                /**< Reserved37 Interrupt */ 
  Reserved38_IRQn             =  143,                /**< Reserved38 Interrupt */ 
  Reserved39_IRQn             =  144,                /**< Reserved39 Interrupt */ 
  Reserved40_IRQn             =  145,                /**< Reserved40 Interrupt */ 
  Reserved41_IRQn             =  146,                /**< Reserved41 Interrupt */ 
  Reserved42_IRQn             =  147,                /**< Reserved42 Interrupt */ 
  Reserved43_IRQn             =  148,                /**< Reserved43 Interrupt */ 
  Reserved44_IRQn             =  149,                /**< Reserved44 Interrupt */ 
  Reserved45_IRQn             =  150,                /**< Reserved45 Interrupt */ 
  Reserved46_IRQn             =  151,                /**< Reserved46 Interrupt */ 
  Reserved47_IRQn             =  152,                /**< Reserved47 Interrupt */ 
  Reserved48_IRQn             =  153,                /**< Reserved48 Interrupt */ 
  Reserved49_IRQn             =  154,                /**< Reserved49 Interrupt */ 
  Reserved50_IRQn             =  155,                /**< Reserved50 Interrupt */ 
  TRNG_IRQn                   =  156,                /**< TRNG Interrupt */ 
  HCU_IRQn                    =  157,                /**< HCU Interrupt */ 
  INTM_IRQn                   =  158,                /**< INTM Interrupt */ 
  TMR0_Ch0_IRQn               =  159,                /**< TMR0_Ch0 Interrupt */ 
  TMR0_Ch1_IRQn               =  160,                /**< TMR0_Ch1 Interrupt */ 
  TMR0_Ch2_IRQn               =  161,                /**< TMR0_Ch2 Interrupt */ 
  TMR0_Ch3_IRQn               =  162,                /**< TMR0_Ch3 Interrupt */ 
  LINFlexD3_IRQn              =  163,                /**< LINFlexD3 Interrupt */ 
  LINFlexD4_IRQn              =  164,                /**< LINFlexD4 Interrupt */ 
  LINFlexD5_IRQn              =  165,                /**< LINFlexD5 Interrupt */ 
  I2C2_Master_IRQn            =  166,                /**< I2C2_Master Interrupt */ 
  I2C2_Slave_IRQn             =  167,                /**< I2C2_Slave Interrupt */ 
  SPI3_IRQn                   =  168,                /**< SPI3 Interrupt */ 
  SPI4_IRQn                   =  169,                /**< SPI4 Interrupt */ 
  SPI5_IRQn                   =  170,                /**< SPI5 Interrupt */ 
  CAN3_ORed_IRQn              =  171,                /**< CAN3_ORed Interrupt */ 
  CAN3_Error_IRQn             =  172,                /**< CAN3_Error Interrupt */ 
  CAN3_Wake_Up_IRQn           =  173,                /**< CAN3_Wake_Up Interrupt */ 
  CAN3_ORed_0_15_MB_IRQn      =  174,                /**< CAN3_ORed_0_15_MB Interrupt */ 
  CAN3_ORed_16_31_MB_IRQn     =  175,                /**< CAN3_ORed_16_31_MB Interrupt */ 
  Reserved51_IRQn             =  176,                /**< Reserved51 Interrupt */ 
  Reserved52_IRQn             =  177,                /**< Reserved52 Interrupt */ 
  CAN4_ORed_IRQn              =  178,                /**< CAN4_ORed Interrupt */ 
  CAN4_Error_IRQn             =  179,                /**< CAN4_Error Interrupt */ 
  CAN4_Wake_Up_IRQn           =  180,                /**< CAN4_Wake_Up Interrupt */ 
  CAN4_ORed_0_15_MB_IRQn      =  181,                /**< CAN4_ORed_0_15_MB Interrupt */ 
  CAN4_ORed_16_31_MB_IRQn     =  182,                /**< CAN4_ORed_16_31_MB Interrupt */ 
  Reserved53_IRQn             =  183,                /**< Reserved53 Interrupt */ 
  Reserved54_IRQn             =  184,                /**< Reserved54 Interrupt */ 
  CAN5_ORed_IRQn              =  185,                /**< CAN5_ORed Interrupt */ 
  CAN5_Error_IRQn             =  186,                /**< CAN5_Error Interrupt */ 
  CAN5_Wake_Up_IRQn           =  187,                /**< CAN5_Wake_Up Interrupt */ 
  CAN5_ORed_0_15_MB_IRQn      =  188,                /**< CAN5_ORed_0_15_MB Interrupt */ 
  CAN5_ORed_16_31_MB_IRQn     =  189,                /**< CAN5_ORed_16_31_MB Interrupt */ 
  WKU_IRQn                    =  190,                /**< WKU Interrupt */ 
  ALIGN_0_IRQn                =  191,                /**< ALIGN_0 Interrupt */ 
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers YTM32B1ME0 */

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM33_REV                0x0004U    // Core revision r0p4 */   /* Core revision r0p1 */
#define __SAUREGION_PRESENT       0U        // SAU regions present */   /* SAU regions present */
#define __MPU_PRESENT             1U        // MPU present */   /* MPU present */
#define __VTOR_PRESENT            1U        // VTOR present */   /* VTOR present */
#define __NVIC_PRIO_BITS          3U        // Number of Bits used for Priority Levels */   /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        // Set to 1 if different SysTick Config is used */   /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        // FPU present */   /* FPU present */
#define __DSP_PRESENT             1U        // DSP extension present */   /* DSP extension present */

#include "core_cm33.h"                      /* Processor and core peripherals */
#include "core_common.h"                      /* Processor common */
#include "system_YTM32B1ME0.h"                 /* System Header */


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer for YTM32B1ME0
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer_YTM32B1ME0 Device Peripheral Access Layer for YTM32B1ME0
 * @{
 */

/* @brief This module covers memory mapped registers available on SoC */

/* -------------------------------------------------------------
   -- EFM Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup EFM_Peripheral_Access_Layer EFM Peripheral Access Layer
 * @{
 */


/** EFM - Size of Registers Arrays */
#define EFM_NVR_DATA_COUNT                     (2)
#define EFM_ADDR_PROT_COUNT                     (3)

/* EFM Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t STS;                                /**< Status Register, offset: 0x0004 */
    __IO uint32_t CMD;                                /**< Command Register, offset: 0x0008 */
    __IO uint32_t RESERVED0[ 1];                      /**< RESERVED0, offset: 0x000C */
    __IO uint32_t TIMING1;                            /**< Timing 1 Control Register, offset: 0x0010 */
    __IO uint32_t TIMING2;                            /**< Timing 2 Control Register, offset: 0x0014 */
    __IO uint32_t NVR_ADDR;                           /**< NVR Access Address, offset: 0x0018 */
    __IO uint32_t NVR_DATA[ 2];                       /**< NVR Access Address, offset: 0x001C */
    __IO uint32_t ADDR_PROT[ 3];                      /**< Address Protect, offset: 0x0024 */
    __IO uint32_t ERR_ADDR;                           /**< EFM Unrecovery ECC Error Address, offset: 0x0030 */
    __IO uint32_t RESERVED1[115];                      /**< RESERVED1, offset: 0x0034 */
    __IO uint32_t CMD_UNLOCK;                         /**< EFM Command Unlock, offset: 0x0200 */
    __IO uint32_t CUS_KEY;                            /**< EFM Customer Key, offset: 0x0204 */
    __IO uint32_t RESERVED2[62];                      /**< RESERVED2, offset: 0x0208 */
    __IO uint32_t CTRL_OVRD;                          /**< Override Control Register, offset: 0x0300 */
    __IO uint32_t RESERVED_15;                        /**< RESERVED_15, offset: 0x0304 */
    __IO uint32_t CFG_KEY;                            /**< EFM Config Key, offset: 0x0308 */

} EFM_Type, *EFM_MemMapPtr;

/** Number of instances of the EFM module. */
#define EFM_INSTANCE_COUNT                             (1u)

/* EFM base address */
#define EFM_BASE                                          (0x40010000)
#define EFM                                               ((EFM_Type *)(EFM_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define EFM_MIRROR_BASE                                   (0x40010800)
#define EFM_MIRROR                                        ((EFM_Type *)(EFM_MIRROR_BASE))

#define EFM_PPU_BASE                                      (0x40010000)
#define EFM_PPU                                           ((PPU_Type *)(EFM_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of EFM peripheral base addresses */
#define EFM_BASE_ADDRS                                     { EFM_BASE }
/** Array initializer of EFM peripheral base pointers */
#define EFM_BASE_PTRS                                      { EFM }
/** Number of interrupt vector arrays for the EFM module. */
#define EFM_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the EFM. */
#define EFM_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the EFM peripheral type */
#define EFM_IRQS                                  { EFM_IRQn }
/** Number of interrupt channels for the Read Collision type of EFM. */
#define EFM_READ_COLLISION_IRQS_CH_COUNT          (1u)
#define EFM_READ_COLLISION_IRQS                   { EFM_IRQn }

/* EFM Register Mask */
/* EFM_CTRL Register */
#define EFM_CTRL_DPD_EN_MASK                               (0x80000000U)
#define EFM_CTRL_DPD_EN_SHIFT                              (31U)
#define EFM_CTRL_DPD_EN(x)                                 (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_DPD_EN_SHIFT)) & EFM_CTRL_DPD_EN_MASK)
#define EFM_CTRL_AES_KEY_SEL_MASK                          (0x1F000000U)
#define EFM_CTRL_AES_KEY_SEL_SHIFT                         (24U)
#define EFM_CTRL_AES_KEY_SEL(x)                            (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_AES_KEY_SEL_SHIFT)) & EFM_CTRL_AES_KEY_SEL_MASK)
#define EFM_CTRL_PRESCALER_MASK                            (0xFF0000U)
#define EFM_CTRL_PRESCALER_SHIFT                           (16U)
#define EFM_CTRL_PRESCALER(x)                              (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_PRESCALER_SHIFT)) & EFM_CTRL_PRESCALER_MASK)
#define EFM_CTRL_PREFETCH_EN_MASK                          (0x8000U)
#define EFM_CTRL_PREFETCH_EN_SHIFT                         (15U)
#define EFM_CTRL_PREFETCH_EN(x)                            (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_PREFETCH_EN_SHIFT)) & EFM_CTRL_PREFETCH_EN_MASK)
#define EFM_CTRL_RWS_MASK                                  (0xF00U)
#define EFM_CTRL_RWS_SHIFT                                 (8U)
#define EFM_CTRL_RWS(x)                                    (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_RWS_SHIFT)) & EFM_CTRL_RWS_MASK)
#define EFM_CTRL_ACCERRIE_MASK                             (0x8U)
#define EFM_CTRL_ACCERRIE_SHIFT                            (3U)
#define EFM_CTRL_ACCERRIE(x)                               (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_ACCERRIE_SHIFT)) & EFM_CTRL_ACCERRIE_MASK)
#define EFM_CTRL_UNRECOVERRIE_MASK                         (0x4U)
#define EFM_CTRL_UNRECOVERRIE_SHIFT                        (2U)
#define EFM_CTRL_UNRECOVERRIE(x)                           (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_UNRECOVERRIE_SHIFT)) & EFM_CTRL_UNRECOVERRIE_MASK)
#define EFM_CTRL_RECOVERRIE_MASK                           (0x2U)
#define EFM_CTRL_RECOVERRIE_SHIFT                          (1U)
#define EFM_CTRL_RECOVERRIE(x)                             (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_RECOVERRIE_SHIFT)) & EFM_CTRL_RECOVERRIE_MASK)
#define EFM_CTRL_DONEIE_MASK                               (0x1U)
#define EFM_CTRL_DONEIE_SHIFT                              (0U)
#define EFM_CTRL_DONEIE(x)                                 (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_DONEIE_SHIFT)) & EFM_CTRL_DONEIE_MASK)
/* EFM_STS Register */
#define EFM_STS_BOOT_INFO_MASK                             (0x8000U)
#define EFM_STS_BOOT_INFO_SHIFT                            (15U)
#define EFM_STS_BOOT_INFO(x)                               (((uint32_t)(((uint32_t)(x)) << EFM_STS_BOOT_INFO_SHIFT)) & EFM_STS_BOOT_INFO_MASK)
#define EFM_STS_CUS_KEY_MATCH_MASK                         (0x2000U)
#define EFM_STS_CUS_KEY_MATCH_SHIFT                        (13U)
#define EFM_STS_CUS_KEY_MATCH(x)                           (((uint32_t)(((uint32_t)(x)) << EFM_STS_CUS_KEY_MATCH_SHIFT)) & EFM_STS_CUS_KEY_MATCH_MASK)
#define EFM_STS_IDLE_MASK                                  (0x80U)
#define EFM_STS_IDLE_SHIFT                                 (7U)
#define EFM_STS_IDLE(x)                                    (((uint32_t)(((uint32_t)(x)) << EFM_STS_IDLE_SHIFT)) & EFM_STS_IDLE_MASK)
#define EFM_STS_FAIL_MASK                                  (0x40U)
#define EFM_STS_FAIL_SHIFT                                 (6U)
#define EFM_STS_FAIL(x)                                    (((uint32_t)(((uint32_t)(x)) << EFM_STS_FAIL_SHIFT)) & EFM_STS_FAIL_MASK)
#define EFM_STS_ACCERR_MASK                                (0x8U)
#define EFM_STS_ACCERR_SHIFT                               (3U)
#define EFM_STS_ACCERR(x)                                  (((uint32_t)(((uint32_t)(x)) << EFM_STS_ACCERR_SHIFT)) & EFM_STS_ACCERR_MASK)
#define EFM_STS_UNRECOVERR_MASK                            (0x4U)
#define EFM_STS_UNRECOVERR_SHIFT                           (2U)
#define EFM_STS_UNRECOVERR(x)                              (((uint32_t)(((uint32_t)(x)) << EFM_STS_UNRECOVERR_SHIFT)) & EFM_STS_UNRECOVERR_MASK)
#define EFM_STS_RECOVERR_MASK                              (0x2U)
#define EFM_STS_RECOVERR_SHIFT                             (1U)
#define EFM_STS_RECOVERR(x)                                (((uint32_t)(((uint32_t)(x)) << EFM_STS_RECOVERR_SHIFT)) & EFM_STS_RECOVERR_MASK)
#define EFM_STS_DONE_MASK                                  (0x1U)
#define EFM_STS_DONE_SHIFT                                 (0U)
#define EFM_STS_DONE(x)                                    (((uint32_t)(((uint32_t)(x)) << EFM_STS_DONE_SHIFT)) & EFM_STS_DONE_MASK)
/* EFM_CMD Register */
#define EFM_CMD_CMD_MASK                                   (0xFFU)
#define EFM_CMD_CMD_SHIFT                                  (0U)
#define EFM_CMD_CMD(x)                                     (((uint32_t)(((uint32_t)(x)) << EFM_CMD_CMD_SHIFT)) & EFM_CMD_CMD_MASK)
/* EFM_TIMING1 Register */
#define EFM_TIMING1_TPREPROG_MASK                          (0xFFFF0000U)
#define EFM_TIMING1_TPREPROG_SHIFT                         (16U)
#define EFM_TIMING1_TPREPROG(x)                            (((uint32_t)(((uint32_t)(x)) << EFM_TIMING1_TPREPROG_SHIFT)) & EFM_TIMING1_TPREPROG_MASK)
#define EFM_TIMING1_TPROG_MASK                             (0xFFFFU)
#define EFM_TIMING1_TPROG_SHIFT                            (0U)
#define EFM_TIMING1_TPROG(x)                               (((uint32_t)(((uint32_t)(x)) << EFM_TIMING1_TPROG_SHIFT)) & EFM_TIMING1_TPROG_MASK)
/* EFM_TIMING2 Register */
#define EFM_TIMING2_TERASE_RETRY_MASK                      (0xFFFF0000U)
#define EFM_TIMING2_TERASE_RETRY_SHIFT                     (16U)
#define EFM_TIMING2_TERASE_RETRY(x)                        (((uint32_t)(((uint32_t)(x)) << EFM_TIMING2_TERASE_RETRY_SHIFT)) & EFM_TIMING2_TERASE_RETRY_MASK)
#define EFM_TIMING2_TERASE_MASK                            (0xFFFFU)
#define EFM_TIMING2_TERASE_SHIFT                           (0U)
#define EFM_TIMING2_TERASE(x)                              (((uint32_t)(((uint32_t)(x)) << EFM_TIMING2_TERASE_SHIFT)) & EFM_TIMING2_TERASE_MASK)
/* EFM_NVR_ADDR Register */
#define EFM_NVR_ADDR_NVR_ADDR_MASK                         (0xFFFFFFFFU)
#define EFM_NVR_ADDR_NVR_ADDR_SHIFT                        (0U)
#define EFM_NVR_ADDR_NVR_ADDR(x)                           (((uint32_t)(((uint32_t)(x)) << EFM_NVR_ADDR_NVR_ADDR_SHIFT)) & EFM_NVR_ADDR_NVR_ADDR_MASK)
/* EFM_NVR_DATA Register */
#define EFM_NVR_DATA_EFM_NVR_DATA_MASK                     (0xFFFFFFFFU)
#define EFM_NVR_DATA_EFM_NVR_DATA_SHIFT                    (0U)
#define EFM_NVR_DATA_EFM_NVR_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << EFM_NVR_DATA_EFM_NVR_DATA_SHIFT)) & EFM_NVR_DATA_EFM_NVR_DATA_MASK)
/* EFM_ADDR_PROT Register */
#define EFM_ADDR_PROT_ADDR_PROT_MASK                       (0xFFFFFFFFU)
#define EFM_ADDR_PROT_ADDR_PROT_SHIFT                      (0U)
#define EFM_ADDR_PROT_ADDR_PROT(x)                         (((uint32_t)(((uint32_t)(x)) << EFM_ADDR_PROT_ADDR_PROT_SHIFT)) & EFM_ADDR_PROT_ADDR_PROT_MASK)
/* EFM_ERR_ADDR Register */
#define EFM_ERR_ADDR_ECC_ERR_ADDR_MASK                     (0xFFFFFFFFU)
#define EFM_ERR_ADDR_ECC_ERR_ADDR_SHIFT                    (0U)
#define EFM_ERR_ADDR_ECC_ERR_ADDR(x)                       (((uint32_t)(((uint32_t)(x)) << EFM_ERR_ADDR_ECC_ERR_ADDR_SHIFT)) & EFM_ERR_ADDR_ECC_ERR_ADDR_MASK)
/* EFM_CMD_UNLOCK Register */
#define EFM_CMD_UNLOCK_CMD_UNLOCK_KEY_MASK                 (0xFFFFFFFFU)
#define EFM_CMD_UNLOCK_CMD_UNLOCK_KEY_SHIFT                (0U)
#define EFM_CMD_UNLOCK_CMD_UNLOCK_KEY(x)                   (((uint32_t)(((uint32_t)(x)) << EFM_CMD_UNLOCK_CMD_UNLOCK_KEY_SHIFT)) & EFM_CMD_UNLOCK_CMD_UNLOCK_KEY_MASK)
/* EFM_CUS_KEY Register */
#define EFM_CUS_KEY_CUS_KEY_MASK                           (0xFFFFFFU)
#define EFM_CUS_KEY_CUS_KEY_SHIFT                          (0U)
#define EFM_CUS_KEY_CUS_KEY(x)                             (((uint32_t)(((uint32_t)(x)) << EFM_CUS_KEY_CUS_KEY_SHIFT)) & EFM_CUS_KEY_CUS_KEY_MASK)
/* EFM_CTRL_OVRD Register */
#define EFM_CTRL_OVRD_SWD_DISABLE_MASK                     (0x2U)
#define EFM_CTRL_OVRD_SWD_DISABLE_SHIFT                    (1U)
#define EFM_CTRL_OVRD_SWD_DISABLE(x)                       (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_OVRD_SWD_DISABLE_SHIFT)) & EFM_CTRL_OVRD_SWD_DISABLE_MASK)
#define EFM_CTRL_OVRD_ECC_DISABLE_MASK                     (0x1U)
#define EFM_CTRL_OVRD_ECC_DISABLE_SHIFT                    (0U)
#define EFM_CTRL_OVRD_ECC_DISABLE(x)                       (((uint32_t)(((uint32_t)(x)) << EFM_CTRL_OVRD_ECC_DISABLE_SHIFT)) & EFM_CTRL_OVRD_ECC_DISABLE_MASK)
/* EFM_CFG_KEY Register */
#define EFM_CFG_KEY_CFG_KEY_MASK                           (0xFFFFFFU)
#define EFM_CFG_KEY_CFG_KEY_SHIFT                          (0U)
#define EFM_CFG_KEY_CFG_KEY(x)                             (((uint32_t)(((uint32_t)(x)) << EFM_CFG_KEY_CFG_KEY_SHIFT)) & EFM_CFG_KEY_CFG_KEY_MASK)


/*!
 * @}
 */ /* end of group EFM_Register_Masks */


/*!
 * @}
 */ /* end of group EFM_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- REGFILE Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup REGFILE_Peripheral_Access_Layer REGFILE Peripheral Access Layer
 * @{
 */


/** REGFILE - Size of Registers Arrays */
#define REGFILE_DR_COUNT                     (8)

/* REGFILE Register Layout Typedef */
typedef struct {
    __IO uint32_t DR[ 8];                             /**< DATA Register, offset: 0x0000 */

} REGFILE_Type, *REGFILE_MemMapPtr;

/** Number of instances of the REGFILE module. */
#define REGFILE_INSTANCE_COUNT                         (1u)

/* REGFILE base address */
#define REGFILE_BASE                                      (0x40061000)
#define REGFILE                                           ((REGFILE_Type *)(REGFILE_BASE))

/** Array initializer of REGFILE peripheral base addresses */
#define REGFILE_BASE_ADDRS                                 { REGFILE_BASE }
/** Array initializer of REGFILE peripheral base pointers */
#define REGFILE_BASE_PTRS                                  { REGFILE }

/* REGFILE Register Mask */
/* REGFILE_DR Register */
#define REGFILE_DR_DATA_MASK                                   (0xFFFFFFFFU)
#define REGFILE_DR_DATA_SHIFT                                  (0U)
#define REGFILE_DR_DATA(x)                                     (((uint32_t)(((uint32_t)(x)) << REGFILE_DR_DATA_SHIFT)) & REGFILE_DR_DATA_MASK)


/*!
 * @}
 */ /* end of group REGFILE_Register_Masks */


/*!
 * @}
 */ /* end of group REGFILE_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */


/** GPIO - Size of Registers Arrays */
#define GPIO_PCR_COUNT                     (32)

/* GPIO Register Layout Typedef */
typedef struct {
    __IO uint32_t PDOR;                               /**< Port Data Output Register, offset: 0x0000 */
    __O  uint32_t PSOR;                               /**< Port Set Output Register, offset: 0x0004 */
    __O  uint32_t PCOR;                               /**< Port Clear Output Register, offset: 0x0008 */
    __O  uint32_t PTOR;                               /**< Port Toggle Output Register, offset: 0x000C */
    __I  uint32_t PDIR;                               /**< Port Data Input Register, offset: 0x0010 */
    __IO uint32_t POER;                               /**< Port Output Enable Register, offset: 0x0014 */
    __IO uint32_t PIER;                               /**< Port Input Enable Register, offset: 0x0018 */
    __IO uint32_t PIFR;                               /**< Port Interrupt Status Flag Register, offset: 0x001C */
    __IO uint32_t RESERVED0[24];                      /**< RESERVED0, offset: 0x0020 */
    __IO uint32_t PCR[32];                            /**< Port Control Register, offset: 0x0080 */

} GPIO_Type, *GPIO_MemMapPtr;

/** Number of instances of the GPIO module. */
#define GPIO_INSTANCE_COUNT                            (5u)

/* GPIOA  base address */
#define GPIOA_BASE                                         (0x40011000)
#define GPIOA                                              ((GPIO_Type *)(GPIOA_BASE))
/* GPIOB  base address */
#define GPIOB_BASE                                         (0x40011100)
#define GPIOB                                              ((GPIO_Type *)(GPIOB_BASE))
/* GPIOC  base address */
#define GPIOC_BASE                                         (0x40011200)
#define GPIOC                                              ((GPIO_Type *)(GPIOC_BASE))
/* GPIOD  base address */
#define GPIOD_BASE                                         (0x40011300)
#define GPIOD                                              ((GPIO_Type *)(GPIOD_BASE))
/* GPIOE  base address */
#define GPIOE_BASE                                         (0x40011400)
#define GPIOE                                              ((GPIO_Type *)(GPIOE_BASE))

/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                                    { GPIOA_BASE,  GPIOB_BASE,  GPIOC_BASE,  GPIOD_BASE,  GPIOE_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                                     { GPIOA,  GPIOB,  GPIOC,  GPIOD,  GPIOE }
/** Number of interrupt vector arrays for the GPIO module. */
#define GPIO_IRQS_ARR_COUNT                                (1u)
/** Number of interrupt channels for the GPIO. */
#define GPIO_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the GPIO peripheral type */
#define GPIO_IRQS                                 { GPIOA_IRQn, GPIOB_IRQn, GPIOC_IRQn, GPIOD_IRQn, GPIOE_IRQn }

/* GPIO Register Mask */
/* GPIO_PDOR Register */
#define GPIO_PDOR_PDO_MASK                                  (0xFFFFFFFFU)
#define GPIO_PDOR_PDO_SHIFT                                 (0U)
#define GPIO_PDOR_PDO(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PDOR_PDO_SHIFT)) & GPIO_PDOR_PDO_MASK)
/* GPIO_PSOR Register */
#define GPIO_PSOR_PSO_MASK                                  (0xFFFFFFFFU)
#define GPIO_PSOR_PSO_SHIFT                                 (0U)
#define GPIO_PSOR_PSO(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PSOR_PSO_SHIFT)) & GPIO_PSOR_PSO_MASK)
/* GPIO_PCOR Register */
#define GPIO_PCOR_PCO_MASK                                  (0xFFFFFFFFU)
#define GPIO_PCOR_PCO_SHIFT                                 (0U)
#define GPIO_PCOR_PCO(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PCOR_PCO_SHIFT)) & GPIO_PCOR_PCO_MASK)
/* GPIO_PTOR Register */
#define GPIO_PTOR_PTO_MASK                                  (0xFFFFFFFFU)
#define GPIO_PTOR_PTO_SHIFT                                 (0U)
#define GPIO_PTOR_PTO(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PTOR_PTO_SHIFT)) & GPIO_PTOR_PTO_MASK)
/* GPIO_PDIR Register */
#define GPIO_PDIR_PDI_MASK                                  (0xFFFFFFFFU)
#define GPIO_PDIR_PDI_SHIFT                                 (0U)
#define GPIO_PDIR_PDI(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PDIR_PDI_SHIFT)) & GPIO_PDIR_PDI_MASK)
/* GPIO_POER Register */
#define GPIO_POER_POE_MASK                                  (0xFFFFFFFFU)
#define GPIO_POER_POE_SHIFT                                 (0U)
#define GPIO_POER_POE(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_POER_POE_SHIFT)) & GPIO_POER_POE_MASK)
/* GPIO_PIER Register */
#define GPIO_PIER_PIE_MASK                                  (0xFFFFFFFFU)
#define GPIO_PIER_PIE_SHIFT                                 (0U)
#define GPIO_PIER_PIE(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PIER_PIE_SHIFT)) & GPIO_PIER_PIE_MASK)
/* GPIO_PIFR Register */
#define GPIO_PIFR_PIF_MASK                                  (0xFFFFFFFFU)
#define GPIO_PIFR_PIF_SHIFT                                 (0U)
#define GPIO_PIFR_PIF(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PIFR_PIF_SHIFT)) & GPIO_PIFR_PIF_MASK)
/* GPIO_PCR Register */
#define GPIO_PCR_DFW_WIDTH                                  (5)
#define GPIO_PCR_DFW_MASK                                   (0x1F000000U)
#define GPIO_PCR_DFW_SHIFT                                  (24U)
#define GPIO_PCR_DFW(x)                                     (((uint32_t)(((uint32_t)(x)) << GPIO_PCR_DFW_SHIFT)) & GPIO_PCR_DFW_MASK)
#define GPIO_PCR_DFE_MASK                                   (0x10000U)
#define GPIO_PCR_DFE_SHIFT                                  (16U)
#define GPIO_PCR_DFE(x)                                     (((uint32_t)(((uint32_t)(x)) << GPIO_PCR_DFE_SHIFT)) & GPIO_PCR_DFE_MASK)
#define GPIO_PCR_INVE_MASK                                  (0x10U)
#define GPIO_PCR_INVE_SHIFT                                 (4U)
#define GPIO_PCR_INVE(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PCR_INVE_SHIFT)) & GPIO_PCR_INVE_MASK)
#define GPIO_PCR_IRQC_MASK                                  (0xFU)
#define GPIO_PCR_IRQC_SHIFT                                 (0U)
#define GPIO_PCR_IRQC(x)                                    (((uint32_t)(((uint32_t)(x)) << GPIO_PCR_IRQC_SHIFT)) & GPIO_PCR_IRQC_MASK)


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- PCTRL Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup PCTRL_Peripheral_Access_Layer PCTRL Peripheral Access Layer
 * @{
 */


/** PCTRL - Size of Registers Arrays */
#define PCTRL_PCR_COUNT                     (32)

/* PCTRL Register Layout Typedef */
typedef struct {
    __IO uint32_t PCR[32];                            /**< Port Control Register, offset: 0x0000 */

} PCTRL_Type, *PCTRL_MemMapPtr;

/** Number of instances of the PCTRL module. */
#define PCTRL_INSTANCE_COUNT                           (5u)

/* PCTRLA  base address */
#define PCTRLA_BASE                                        (0x40012000)
#define PCTRLA                                             ((PCTRL_Type *)(PCTRLA_BASE))
/* PCTRLB  base address */
#define PCTRLB_BASE                                        (0x40013000)
#define PCTRLB                                             ((PCTRL_Type *)(PCTRLB_BASE))
/* PCTRLC  base address */
#define PCTRLC_BASE                                        (0x40014000)
#define PCTRLC                                             ((PCTRL_Type *)(PCTRLC_BASE))
/* PCTRLD  base address */
#define PCTRLD_BASE                                        (0x40015000)
#define PCTRLD                                             ((PCTRL_Type *)(PCTRLD_BASE))
/* PCTRLE  base address */
#define PCTRLE_BASE                                        (0x40016000)
#define PCTRLE                                             ((PCTRL_Type *)(PCTRLE_BASE))

/** Array initializer of PCTRL peripheral base addresses */
#define PCTRL_BASE_ADDRS                                   { PCTRLA_BASE,  PCTRLB_BASE,  PCTRLC_BASE,  PCTRLD_BASE,  PCTRLE_BASE }
/** Array initializer of PCTRL peripheral base pointers */
#define PCTRL_BASE_PTRS                                    { PCTRLA,  PCTRLB,  PCTRLC,  PCTRLD,  PCTRLE }

/* PCTRL Register Mask */
/* PCTRL_PCR Register */
#define PCTRL_PCR_MUX_WIDTH                                  (3)
#define PCTRL_PCR_MUX_MASK                                   (0x700U)
#define PCTRL_PCR_MUX_SHIFT                                  (8U)
#define PCTRL_PCR_MUX(x)                                     (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_MUX_SHIFT)) & PCTRL_PCR_MUX_MASK)
#define PCTRL_PCR_DSE_MASK                                   (0x40U)
#define PCTRL_PCR_DSE_SHIFT                                  (6U)
#define PCTRL_PCR_DSE(x)                                     (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_DSE_SHIFT)) & PCTRL_PCR_DSE_MASK)
#define PCTRL_PCR_PFE_MASK                                   (0x10U)
#define PCTRL_PCR_PFE_SHIFT                                  (4U)
#define PCTRL_PCR_PFE(x)                                     (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_PFE_SHIFT)) & PCTRL_PCR_PFE_MASK)
#define PCTRL_PCR_SRE_MASK                                   (0x4U)
#define PCTRL_PCR_SRE_SHIFT                                  (2U)
#define PCTRL_PCR_SRE(x)                                     (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_SRE_SHIFT)) & PCTRL_PCR_SRE_MASK)
#define PCTRL_PCR_PE_MASK                                    (0x2U)
#define PCTRL_PCR_PE_SHIFT                                   (1U)
#define PCTRL_PCR_PE(x)                                      (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_PE_SHIFT)) & PCTRL_PCR_PE_MASK)
#define PCTRL_PCR_PS_MASK                                    (0x1U)
#define PCTRL_PCR_PS_SHIFT                                   (0U)
#define PCTRL_PCR_PS(x)                                      (((uint32_t)(((uint32_t)(x)) << PCTRL_PCR_PS_SHIFT)) & PCTRL_PCR_PS_MASK)


/*!
 * @}
 */ /* end of group PCTRL_Register_Masks */


/*!
 * @}
 */ /* end of group PCTRL_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */


/** DMA - Size of Registers Arrays */
#define DMA_CHMUX_COUNT                     (16)
#define DMA_CTS_COUNT                     (16)

/* DMA Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t CHTLDIF;                            /**< Channel Trigger Loop Done Interrupt Flag Register, offset: 0x0004 */
    __IO uint32_t CHTLHDIF;                           /**< Channel Trigger Loop Half Done Interrupt Flag Register, offset: 0x0008 */
    __IO uint32_t CHEIF;                              /**< DMA Channel Error Interrupt Flag Register, offset: 0x000C */
    __IO uint32_t CHEIE;                              /**< DMA Channel Error Interrupt Enable Register, offset: 0x0010 */
    __IO uint32_t ERS;                                /**< Error Status Register, offset: 0x0014 */
    __IO uint32_t REQEN;                              /**< Hardware Request Enable Register, offset: 0x0018 */
    __IO uint32_t REQS;                               /**< Request Status Register, offset: 0x001C */
    __IO uint32_t START;                              /**< Channel Start Register, offset: 0x0020 */
    __IO uint32_t DONE;                               /**< Channel Done Register, offset: 0x0024 */
    __IO uint32_t RESERVED0[ 6];                      /**< RESERVED0, offset: 0x0028 */
    __IO uint8_t CHMUX[16];                          /**< Channel Mux Register, offset: 0x0040 */
    __IO uint32_t RESERVED1[236];                      /**< RESERVED1, offset: 0x0060 */
    struct {
        __IO uint32_t SADDR;                              /**< Source Address Register, offset: 0x0400 */
        __IO uint16_t SOFF;                               /**< Source Address Offset Register, offset: 0x0404 */
        __IO uint16_t TCR;                                /**< Transfer Control Register, offset: 0x0406 */
    union {
        __IO uint32_t BCNT;                               /**< Transfer Loop Byte Count, offset: 0x0408 */
        __IO uint32_t LODIS;                              /**< Transfer Loop Offset Disable Mapping, offset: 0x0408 */
        __IO uint32_t LOEN;                               /**< Transfer Loop Offset Enable Mapping, offset: 0x0408 */

    } BCNT;
        __IO uint32_t STO;                                /**< Source Trigger Loop Offset Register, offset: 0x040C */
        __IO uint32_t DADDR;                              /**< Destination Address Register, offset: 0x0410 */
        __IO uint16_t DOFF;                               /**< Destination Address Offset Register, offset: 0x0414 */
    union {
        __IO uint16_t LKDIS;                              /**< Trigger Count with Link Disable, offset: 0x0416 */
        __IO uint16_t LKEN;                               /**< Trigger Count with Link Enable, offset: 0x0416 */

    } TCNT;
    union {
        __IO uint32_t DTO;                                /**< Destination Trigger Loop Offset Register, offset: 0x0418 */
        __IO uint32_t RLD;                                /**< RAM Reload Address Register, offset: 0x0418 */

    } DTO_RLD;
        __IO uint16_t CSR;                                /**< Control and Status Register, offset: 0x041C */
        __IO uint16_t TCNTRV;                             /**< TCNT Reload Value Register, offset: 0x041E */

    } CTS[16];

} DMA_Type, *DMA_MemMapPtr;

/** Number of instances of the DMA module. */
#define DMA_INSTANCE_COUNT                             (1u)

/* DMA0  base address */
#define DMA0_BASE                                          (0x40008000)
#define DMA0                                               ((DMA_Type *)(DMA0_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define DMA0_MIRROR_BASE                                   (0x40008800)
#define DMA0_MIRROR                                        ((DMA_Type *)(DMA0_MIRROR_BASE))

#define DMA0_PPU_BASE                                      (0x40008000)
#define DMA0_PPU                                           ((PPU_Type *)(DMA0_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                                     { DMA0_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                                      { DMA0 }
/** Number of interrupt vector arrays for the DMA module. */
#define DMA_IRQS_ARR_COUNT                                 (17u)
/** Number of interrupt channels for the channel done interrupt type of DMA. */
#define DMA_CHN_IRQS_CH_COUNT                     (15u)
#define DMA_CHN_IRQS                              { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn, DMA4_IRQn, DMA5_IRQn, DMA6_IRQn, DMA7_IRQn, DMA8_IRQn, DMA9_IRQn, DMA10_IRQn, DMA11_IRQn, DMA12_IRQn, DMA13_IRQn, DMA14_IRQn, DMA15_IRQn }
/** Number of interrupt channels for the channel error type of DMA. */
#define DMA_ERROR_IRQS_CH_COUNT                   (1u)
#define DMA_ERROR_IRQS                            { DMA_Error_IRQn }

/* DMA Register Mask */
/* DMA_CTRL Register */
#define DMA_CTRL_ACTIVE_MASK                               (0x80000000U)
#define DMA_CTRL_ACTIVE_SHIFT                              (31U)
#define DMA_CTRL_ACTIVE(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ACTIVE_SHIFT)) & DMA_CTRL_ACTIVE_MASK)
#define DMA_CTRL_ACTCH_MASK                                (0xF000000U)
#define DMA_CTRL_ACTCH_SHIFT                               (24U)
#define DMA_CTRL_ACTCH(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ACTCH_SHIFT)) & DMA_CTRL_ACTCH_MASK)
#define DMA_CTRL_CX_MASK                                   (0x80000U)
#define DMA_CTRL_CX_SHIFT                                  (19U)
#define DMA_CTRL_CX(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_CX_SHIFT)) & DMA_CTRL_CX_MASK)
#define DMA_CTRL_ECX_MASK                                  (0x40000U)
#define DMA_CTRL_ECX_SHIFT                                 (18U)
#define DMA_CTRL_ECX(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ECX_SHIFT)) & DMA_CTRL_ECX_MASK)
#define DMA_CTRL_POE_MASK                                  (0x10000U)
#define DMA_CTRL_POE_SHIFT                                 (16U)
#define DMA_CTRL_POE(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_POE_SHIFT)) & DMA_CTRL_POE_MASK)
#define DMA_CTRL_LOEN_MASK                                 (0x400U)
#define DMA_CTRL_LOEN_SHIFT                                (10U)
#define DMA_CTRL_LOEN(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_LOEN_SHIFT)) & DMA_CTRL_LOEN_MASK)
#define DMA_CTRL_CLM_MASK                                  (0x200U)
#define DMA_CTRL_CLM_SHIFT                                 (9U)
#define DMA_CTRL_CLM(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_CLM_SHIFT)) & DMA_CTRL_CLM_MASK)
#define DMA_CTRL_DBGDIS_MASK                               (0x4U)
#define DMA_CTRL_DBGDIS_SHIFT                              (2U)
#define DMA_CTRL_DBGDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_DBGDIS_SHIFT)) & DMA_CTRL_DBGDIS_MASK)
#define DMA_CTRL_CLRAD_MASK                                (0x2U)
#define DMA_CTRL_CLRAD_SHIFT                               (1U)
#define DMA_CTRL_CLRAD(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_CLRAD_SHIFT)) & DMA_CTRL_CLRAD_MASK)
#define DMA_CTRL_STACH_MASK                                (0x1U)
#define DMA_CTRL_STACH_SHIFT                               (0U)
#define DMA_CTRL_STACH(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_STACH_SHIFT)) & DMA_CTRL_STACH_MASK)
/* DMA_CHTLDIF Register */
#define DMA_CHTLDIF_CH_MASK                                (0xFFFFU)
#define DMA_CHTLDIF_CH_SHIFT                               (0U)
#define DMA_CHTLDIF_CH(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CHTLDIF_CH_SHIFT)) & DMA_CHTLDIF_CH_MASK)
/* DMA_CHTLHDIF Register */
#define DMA_CHTLHDIF_CH_MASK                               (0xFFFFU)
#define DMA_CHTLHDIF_CH_SHIFT                              (0U)
#define DMA_CHTLHDIF_CH(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CHTLHDIF_CH_SHIFT)) & DMA_CHTLHDIF_CH_MASK)
/* DMA_CHEIF Register */
#define DMA_CHEIF_CH_MASK                                  (0xFFFFU)
#define DMA_CHEIF_CH_SHIFT                                 (0U)
#define DMA_CHEIF_CH(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CHEIF_CH_SHIFT)) & DMA_CHEIF_CH_MASK)
/* DMA_CHEIE Register */
#define DMA_CHEIE_CH_MASK                                  (0xFFFFU)
#define DMA_CHEIE_CH_SHIFT                                 (0U)
#define DMA_CHEIE_CH(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CHEIE_CH_SHIFT)) & DMA_CHEIE_CH_MASK)
/* DMA_ERS Register */
#define DMA_ERS_VALID_MASK                                 (0x80000000U)
#define DMA_ERS_VALID_SHIFT                                (31U)
#define DMA_ERS_VALID(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_ERS_VALID_SHIFT)) & DMA_ERS_VALID_MASK)
#define DMA_ERS_ECX_MASK                                   (0x40000U)
#define DMA_ERS_ECX_SHIFT                                  (18U)
#define DMA_ERS_ECX(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_ECX_SHIFT)) & DMA_ERS_ECX_MASK)
#define DMA_ERS_SAE_MASK                                   (0x8000U)
#define DMA_ERS_SAE_SHIFT                                  (15U)
#define DMA_ERS_SAE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_SAE_SHIFT)) & DMA_ERS_SAE_MASK)
#define DMA_ERS_SOE_MASK                                   (0x4000U)
#define DMA_ERS_SOE_SHIFT                                  (14U)
#define DMA_ERS_SOE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_SOE_SHIFT)) & DMA_ERS_SOE_MASK)
#define DMA_ERS_DAE_MASK                                   (0x2000U)
#define DMA_ERS_DAE_SHIFT                                  (13U)
#define DMA_ERS_DAE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_DAE_SHIFT)) & DMA_ERS_DAE_MASK)
#define DMA_ERS_DOE_MASK                                   (0x1000U)
#define DMA_ERS_DOE_SHIFT                                  (12U)
#define DMA_ERS_DOE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_DOE_SHIFT)) & DMA_ERS_DOE_MASK)
#define DMA_ERS_BTCE_MASK                                  (0x800U)
#define DMA_ERS_BTCE_SHIFT                                 (11U)
#define DMA_ERS_BTCE(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_ERS_BTCE_SHIFT)) & DMA_ERS_BTCE_MASK)
#define DMA_ERS_RLDE_MASK                                  (0x400U)
#define DMA_ERS_RLDE_SHIFT                                 (10U)
#define DMA_ERS_RLDE(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_ERS_RLDE_SHIFT)) & DMA_ERS_RLDE_MASK)
#define DMA_ERS_SBE_MASK                                   (0x200U)
#define DMA_ERS_SBE_SHIFT                                  (9U)
#define DMA_ERS_SBE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_SBE_SHIFT)) & DMA_ERS_SBE_MASK)
#define DMA_ERS_DBE_MASK                                   (0x100U)
#define DMA_ERS_DBE_SHIFT                                  (8U)
#define DMA_ERS_DBE(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_DBE_SHIFT)) & DMA_ERS_DBE_MASK)
#define DMA_ERS_ECH_WIDTH                                  (4)
#define DMA_ERS_ECH_MASK                                   (0xFU)
#define DMA_ERS_ECH_SHIFT                                  (0U)
#define DMA_ERS_ECH(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_ERS_ECH_SHIFT)) & DMA_ERS_ECH_MASK)
/* DMA_REQEN Register */
#define DMA_REQEN_CH_WIDTH                                 (16)
#define DMA_REQEN_CH_MASK                                  (0xFFFFU)
#define DMA_REQEN_CH_SHIFT                                 (0U)
#define DMA_REQEN_CH(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_REQEN_CH_SHIFT)) & DMA_REQEN_CH_MASK)
/* DMA_REQS Register */
#define DMA_REQS_CH_WIDTH                                  (16)
#define DMA_REQS_CH_MASK                                   (0xFFFFU)
#define DMA_REQS_CH_SHIFT                                  (0U)
#define DMA_REQS_CH(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_REQS_CH_SHIFT)) & DMA_REQS_CH_MASK)
/* DMA_START Register */
#define DMA_START_CH_WIDTH                                 (16)
#define DMA_START_CH_MASK                                  (0xFFFFU)
#define DMA_START_CH_SHIFT                                 (0U)
#define DMA_START_CH(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_START_CH_SHIFT)) & DMA_START_CH_MASK)
/* DMA_DONE Register */
#define DMA_DONE_CH_WIDTH                                  (16)
#define DMA_DONE_CH_MASK                                   (0xFFFFU)
#define DMA_DONE_CH_SHIFT                                  (0U)
#define DMA_DONE_CH(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_DONE_CH_SHIFT)) & DMA_DONE_CH_MASK)
/* DMA_CHMUX Register */
#define DMA_CHMUX_CH_WIDTH                                 (7)
#define DMA_CHMUX_CH_MASK                                  (0x7FU)
#define DMA_CHMUX_CH_SHIFT                                 (0U)
#define DMA_CHMUX_CH(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CHMUX_CH_SHIFT)) & DMA_CHMUX_CH_MASK)
/* DMA_CTS_SADDR Register */
#define DMA_CTS_SADDR_SADDR_WIDTH                              (32)
#define DMA_CTS_SADDR_SADDR_MASK                               (0xFFFFFFFFU)
#define DMA_CTS_SADDR_SADDR_SHIFT                              (0U)
#define DMA_CTS_SADDR_SADDR(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTS_SADDR_SADDR_SHIFT)) & DMA_CTS_SADDR_SADDR_MASK)
/* DMA_CTS_SOFF Register */
#define DMA_CTS_SOFF_SOFF_WIDTH                                (32)
#define DMA_CTS_SOFF_SOFF_MASK                                 (0xFFFFU)
#define DMA_CTS_SOFF_SOFF_SHIFT                                (0U)
#define DMA_CTS_SOFF_SOFF(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_SOFF_SOFF_SHIFT)) & DMA_CTS_SOFF_SOFF_MASK)
/* DMA_CTS_TCR Register */
#define DMA_CTS_TCR_SMOD_WIDTH                                 (5)
#define DMA_CTS_TCR_SMOD_MASK                                  (0xF800U)
#define DMA_CTS_TCR_SMOD_SHIFT                                 (11U)
#define DMA_CTS_TCR_SMOD(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCR_SMOD_SHIFT)) & DMA_CTS_TCR_SMOD_MASK)
#define DMA_CTS_TCR_SSIZE_WIDTH                                (3)
#define DMA_CTS_TCR_SSIZE_MASK                                 (0x700U)
#define DMA_CTS_TCR_SSIZE_SHIFT                                (8U)
#define DMA_CTS_TCR_SSIZE(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCR_SSIZE_SHIFT)) & DMA_CTS_TCR_SSIZE_MASK)
#define DMA_CTS_TCR_DMOD_WIDTH                                 (5)
#define DMA_CTS_TCR_DMOD_MASK                                  (0xF8U)
#define DMA_CTS_TCR_DMOD_SHIFT                                 (3U)
#define DMA_CTS_TCR_DMOD(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCR_DMOD_SHIFT)) & DMA_CTS_TCR_DMOD_MASK)
#define DMA_CTS_TCR_DSIZE_WIDTH                                (3)
#define DMA_CTS_TCR_DSIZE_MASK                                 (0x7U)
#define DMA_CTS_TCR_DSIZE_SHIFT                                (0U)
#define DMA_CTS_TCR_DSIZE(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCR_DSIZE_SHIFT)) & DMA_CTS_TCR_DSIZE_MASK)
/* DMA_CTS_BCNT_BCNT Register */
#define DMA_CTS_BCNT_BCNT_BCNT_MASK                                 (0xFFFFFFFFU)
#define DMA_CTS_BCNT_BCNT_BCNT_SHIFT                                (0U)
#define DMA_CTS_BCNT_BCNT_BCNT(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_BCNT_BCNT_SHIFT)) & DMA_CTS_BCNT_BCNT_BCNT_MASK)
/* DMA_CTS_BCNT_LODIS Register */
#define DMA_CTS_BCNT_LODIS_SLOE_MASK                                (0x80000000U)
#define DMA_CTS_BCNT_LODIS_SLOE_SHIFT                               (31U)
#define DMA_CTS_BCNT_LODIS_SLOE(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LODIS_SLOE_SHIFT)) & DMA_CTS_BCNT_LODIS_SLOE_MASK)
#define DMA_CTS_BCNT_LODIS_DLOE_MASK                                (0x40000000U)
#define DMA_CTS_BCNT_LODIS_DLOE_SHIFT                               (30U)
#define DMA_CTS_BCNT_LODIS_DLOE(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LODIS_DLOE_SHIFT)) & DMA_CTS_BCNT_LODIS_DLOE_MASK)
#define DMA_CTS_BCNT_LODIS_BCNT_MASK                                (0x3FFFFFFFU)
#define DMA_CTS_BCNT_LODIS_BCNT_SHIFT                               (0U)
#define DMA_CTS_BCNT_LODIS_BCNT(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LODIS_BCNT_SHIFT)) & DMA_CTS_BCNT_LODIS_BCNT_MASK)
/* DMA_CTS_BCNT_LOEN Register */
#define DMA_CTS_BCNT_LOEN_SLOE_MASK                                 (0x80000000U)
#define DMA_CTS_BCNT_LOEN_SLOE_SHIFT                                (31U)
#define DMA_CTS_BCNT_LOEN_SLOE(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LOEN_SLOE_SHIFT)) & DMA_CTS_BCNT_LOEN_SLOE_MASK)
#define DMA_CTS_BCNT_LOEN_DLOE_MASK                                 (0x40000000U)
#define DMA_CTS_BCNT_LOEN_DLOE_SHIFT                                (30U)
#define DMA_CTS_BCNT_LOEN_DLOE(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LOEN_DLOE_SHIFT)) & DMA_CTS_BCNT_LOEN_DLOE_MASK)
#define DMA_CTS_BCNT_LOEN_OFFSET_MASK                               (0x3FFFFC00U)
#define DMA_CTS_BCNT_LOEN_OFFSET_SHIFT                              (10U)
#define DMA_CTS_BCNT_LOEN_OFFSET(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LOEN_OFFSET_SHIFT)) & DMA_CTS_BCNT_LOEN_OFFSET_MASK)
#define DMA_CTS_BCNT_LOEN_BCNT_MASK                                 (0x3FFU)
#define DMA_CTS_BCNT_LOEN_BCNT_SHIFT                                (0U)
#define DMA_CTS_BCNT_LOEN_BCNT(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_BCNT_LOEN_BCNT_SHIFT)) & DMA_CTS_BCNT_LOEN_BCNT_MASK)

/* DMA_CTS_STO Register */
#define DMA_CTS_STO_STLOFF_WIDTH                               (31)
#define DMA_CTS_STO_STLOFF_MASK                                (0xFFFFFFFFU)
#define DMA_CTS_STO_STLOFF_SHIFT                               (0U)
#define DMA_CTS_STO_STLOFF(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_STO_STLOFF_SHIFT)) & DMA_CTS_STO_STLOFF_MASK)
/* DMA_CTS_DADDR Register */
#define DMA_CTS_DADDR_DADDR_WIDTH                              (31)
#define DMA_CTS_DADDR_DADDR_MASK                               (0xFFFFFFFFU)
#define DMA_CTS_DADDR_DADDR_SHIFT                              (0U)
#define DMA_CTS_DADDR_DADDR(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTS_DADDR_DADDR_SHIFT)) & DMA_CTS_DADDR_DADDR_MASK)
/* DMA_CTS_DOFF Register */
#define DMA_CTS_DOFF_DOFF_WIDTH                                (16)
#define DMA_CTS_DOFF_DOFF_MASK                                 (0xFFFFU)
#define DMA_CTS_DOFF_DOFF_SHIFT                                (0U)
#define DMA_CTS_DOFF_DOFF(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_DOFF_DOFF_SHIFT)) & DMA_CTS_DOFF_DOFF_MASK)
/* DMA_CTS_TCNT_LKDIS Register */
#define DMA_CTS_TCNT_LKDIS_LKEN_MASK                                (0x8000U)
#define DMA_CTS_TCNT_LKDIS_LKEN_SHIFT                               (15U)
#define DMA_CTS_TCNT_LKDIS_LKEN(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNT_LKDIS_LKEN_SHIFT)) & DMA_CTS_TCNT_LKDIS_LKEN_MASK)
#define DMA_CTS_TCNT_LKDIS_TCNT_MASK                                (0x7FFFU)
#define DMA_CTS_TCNT_LKDIS_TCNT_SHIFT                               (0U)
#define DMA_CTS_TCNT_LKDIS_TCNT(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNT_LKDIS_TCNT_SHIFT)) & DMA_CTS_TCNT_LKDIS_TCNT_MASK)
/* DMA_CTS_TCNT_LKEN Register */
#define DMA_CTS_TCNT_LKEN_LKEN_MASK                                 (0x8000U)
#define DMA_CTS_TCNT_LKEN_LKEN_SHIFT                                (15U)
#define DMA_CTS_TCNT_LKEN_LKEN(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNT_LKEN_LKEN_SHIFT)) & DMA_CTS_TCNT_LKEN_LKEN_MASK)
#define DMA_CTS_TCNT_LKEN_LKCH_MASK                                 (0x1E00U)
#define DMA_CTS_TCNT_LKEN_LKCH_SHIFT                                (9U)
#define DMA_CTS_TCNT_LKEN_LKCH(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNT_LKEN_LKCH_SHIFT)) & DMA_CTS_TCNT_LKEN_LKCH_MASK)
#define DMA_CTS_TCNT_LKEN_TCNT_MASK                                 (0x1FFU)
#define DMA_CTS_TCNT_LKEN_TCNT_SHIFT                                (0U)
#define DMA_CTS_TCNT_LKEN_TCNT(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNT_LKEN_TCNT_SHIFT)) & DMA_CTS_TCNT_LKEN_TCNT_MASK)

/* DMA_CTS_DTO_RLD_DTO Register */
#define DMA_CTS_DTO_RLD_DTO_OFFSET_MASK                                (0xFFFFFFFFU)
#define DMA_CTS_DTO_RLD_DTO_OFFSET_SHIFT                               (0U)
#define DMA_CTS_DTO_RLD_DTO_OFFSET(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_DTO_RLD_DTO_OFFSET_SHIFT)) & DMA_CTS_DTO_RLD_DTO_OFFSET_MASK)
/* DMA_CTS_DTO_RLD_RLD Register */
#define DMA_CTS_DTO_RLD_RLD_ADDR_MASK                                  (0xFFFFFFFFU)
#define DMA_CTS_DTO_RLD_RLD_ADDR_SHIFT                                 (0U)
#define DMA_CTS_DTO_RLD_RLD_ADDR(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTS_DTO_RLD_RLD_ADDR_SHIFT)) & DMA_CTS_DTO_RLD_RLD_ADDR_MASK)

/* DMA_CTS_CSR Register */
#define DMA_CTS_CSR_TDINT_MASK                                 (0x8000U)
#define DMA_CTS_CSR_TDINT_SHIFT                                (15U)
#define DMA_CTS_CSR_TDINT(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_TDINT_SHIFT)) & DMA_CTS_CSR_TDINT_MASK)
#define DMA_CTS_CSR_THDINT_MASK                                (0x4000U)
#define DMA_CTS_CSR_THDINT_SHIFT                               (14U)
#define DMA_CTS_CSR_THDINT(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_THDINT_SHIFT)) & DMA_CTS_CSR_THDINT_MASK)
#define DMA_CTS_CSR_LOOPINT_MASK                               (0x2000U)
#define DMA_CTS_CSR_LOOPINT_SHIFT                              (13U)
#define DMA_CTS_CSR_LOOPINT(x)                                 (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_LOOPINT_SHIFT)) & DMA_CTS_CSR_LOOPINT_MASK)
#define DMA_CTS_CSR_TLKCH_MASK                                 (0xF00U)
#define DMA_CTS_CSR_TLKCH_SHIFT                                (8U)
#define DMA_CTS_CSR_TLKCH(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_TLKCH_SHIFT)) & DMA_CTS_CSR_TLKCH_MASK)
#define DMA_CTS_CSR_TLKEN_MASK                                 (0x80U)
#define DMA_CTS_CSR_TLKEN_SHIFT                                (7U)
#define DMA_CTS_CSR_TLKEN(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_TLKEN_SHIFT)) & DMA_CTS_CSR_TLKEN_MASK)
#define DMA_CTS_CSR_RLDEN_MASK                                 (0x40U)
#define DMA_CTS_CSR_RLDEN_SHIFT                                (6U)
#define DMA_CTS_CSR_RLDEN(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_RLDEN_SHIFT)) & DMA_CTS_CSR_RLDEN_MASK)
#define DMA_CTS_CSR_BWC_MASK                                   (0x30U)
#define DMA_CTS_CSR_BWC_SHIFT                                  (4U)
#define DMA_CTS_CSR_BWC(x)                                     (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_BWC_SHIFT)) & DMA_CTS_CSR_BWC_MASK)
#define DMA_CTS_CSR_DREQ_MASK                                  (0x8U)
#define DMA_CTS_CSR_DREQ_SHIFT                                 (3U)
#define DMA_CTS_CSR_DREQ(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_DREQ_SHIFT)) & DMA_CTS_CSR_DREQ_MASK)
#define DMA_CTS_CSR_ACTIVE_MASK                                (0x4U)
#define DMA_CTS_CSR_ACTIVE_SHIFT                               (2U)
#define DMA_CTS_CSR_ACTIVE(x)                                  (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_ACTIVE_SHIFT)) & DMA_CTS_CSR_ACTIVE_MASK)
#define DMA_CTS_CSR_DONE_MASK                                  (0x2U)
#define DMA_CTS_CSR_DONE_SHIFT                                 (1U)
#define DMA_CTS_CSR_DONE(x)                                    (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_DONE_SHIFT)) & DMA_CTS_CSR_DONE_MASK)
#define DMA_CTS_CSR_START_MASK                                 (0x1U)
#define DMA_CTS_CSR_START_SHIFT                                (0U)
#define DMA_CTS_CSR_START(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_CSR_START_SHIFT)) & DMA_CTS_CSR_START_MASK)
/* DMA_CTS_TCNTRV Register */
#define DMA_CTS_TCNTRV_RV_MASK                                 (0xFFFFU)
#define DMA_CTS_TCNTRV_RV_SHIFT                                (0U)
#define DMA_CTS_TCNTRV_RV(x)                                   (((uint32_t)(((uint32_t)(x)) << DMA_CTS_TCNTRV_RV_SHIFT)) & DMA_CTS_TCNTRV_RV_MASK)



/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- CIM Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup CIM_Peripheral_Access_Layer CIM Peripheral Access Layer
 * @{
 */


/** CIM - Size of Registers Arrays */

/* CIM Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< CIM Control Register, offset: 0x0000 */
    __IO uint32_t RESERVED0[ 3];                      /**< RESERVED0, offset: 0x0004 */
    __IO uint32_t FPUIE;                              /**< FPU Interrupt Enable Register, offset: 0x0010 */
    __IO uint32_t SWTRIG;                             /**< Software Trigger Register, offset: 0x0014 */
    __IO uint32_t ETMROPT0;                           /**< eTMR Option Register 0, offset: 0x0018 */
    __IO uint32_t ETMROPT1;                           /**< eTMR Option register 1, offset: 0x001C */
    __IO uint32_t RESERVED1[ 8];                      /**< RESERVED1, offset: 0x0020 */
    __I  uint32_t DIEINFO;                            /**< Die Information Register, offset: 0x0040 */
    __I  uint32_t CHIPINFO;                           /**< Chip Information Register, offset: 0x0044 */
    __I  uint32_t UID0;                               /**< CIM Unique Identification Register 0, offset: 0x0048 */
    __I  uint32_t UID1;                               /**< CIM Unique Identification Register 1, offset: 0x004C */
    __I  uint32_t UID2;                               /**< CIM Unique Identification Register 2, offset: 0x0050 */
    __I  uint32_t UID3;                               /**< CIM Unique Identification Register 3, offset: 0x0054 */

} CIM_Type, *CIM_MemMapPtr;

/** Number of instances of the CIM module. */
#define CIM_INSTANCE_COUNT                             (1u)

/* CIM base address */
#define CIM_BASE                                          (0x4007B000)
#define CIM                                               ((CIM_Type *)(CIM_BASE))

/** Array initializer of CIM peripheral base addresses */
#define CIM_BASE_ADDRS                                     { CIM_BASE }
/** Array initializer of CIM peripheral base pointers */
#define CIM_BASE_PTRS                                      { CIM }

/* CIM Register Mask */
/* CIM_CTRL Register */
#define CIM_CTRL_ADC1_TRIG_SEL_MASK                        (0xC0000U)
#define CIM_CTRL_ADC1_TRIG_SEL_SHIFT                       (18U)
#define CIM_CTRL_ADC1_TRIG_SEL(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_ADC1_TRIG_SEL_SHIFT)) & CIM_CTRL_ADC1_TRIG_SEL_MASK)
#define CIM_CTRL_ADC0_TRIG_SEL_MASK                        (0x30000U)
#define CIM_CTRL_ADC0_TRIG_SEL_SHIFT                       (16U)
#define CIM_CTRL_ADC0_TRIG_SEL(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_ADC0_TRIG_SEL_SHIFT)) & CIM_CTRL_ADC0_TRIG_SEL_MASK)
#define CIM_CTRL_ACMP0_TRIG_SEL_MASK                       (0x300U)
#define CIM_CTRL_ACMP0_TRIG_SEL_SHIFT                      (8U)
#define CIM_CTRL_ACMP0_TRIG_SEL(x)                         (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_ACMP0_TRIG_SEL_SHIFT)) & CIM_CTRL_ACMP0_TRIG_SEL_MASK)
#define CIM_CTRL_LOCKUPEN_MASK                             (0x4U)
#define CIM_CTRL_LOCKUPEN_SHIFT                            (2U)
#define CIM_CTRL_LOCKUPEN(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_LOCKUPEN_SHIFT)) & CIM_CTRL_LOCKUPEN_MASK)
#define CIM_CTRL_NMIEN_MASK                                (0x2U)
#define CIM_CTRL_NMIEN_SHIFT                               (1U)
#define CIM_CTRL_NMIEN(x)                                  (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_NMIEN_SHIFT)) & CIM_CTRL_NMIEN_MASK)
#define CIM_CTRL_WICENREQ_MASK                             (0x1U)
#define CIM_CTRL_WICENREQ_SHIFT                            (0U)
#define CIM_CTRL_WICENREQ(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_CTRL_WICENREQ_SHIFT)) & CIM_CTRL_WICENREQ_MASK)
/* CIM_FPUIE Register */
#define CIM_FPUIE_FPIXCIE_MASK                             (0x20U)
#define CIM_FPUIE_FPIXCIE_SHIFT                            (5U)
#define CIM_FPUIE_FPIXCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPIXCIE_SHIFT)) & CIM_FPUIE_FPIXCIE_MASK)
#define CIM_FPUIE_FPIDCIE_MASK                             (0x10U)
#define CIM_FPUIE_FPIDCIE_SHIFT                            (4U)
#define CIM_FPUIE_FPIDCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPIDCIE_SHIFT)) & CIM_FPUIE_FPIDCIE_MASK)
#define CIM_FPUIE_FPOFCIE_MASK                             (0x8U)
#define CIM_FPUIE_FPOFCIE_SHIFT                            (3U)
#define CIM_FPUIE_FPOFCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPOFCIE_SHIFT)) & CIM_FPUIE_FPOFCIE_MASK)
#define CIM_FPUIE_FPUFCIE_MASK                             (0x4U)
#define CIM_FPUIE_FPUFCIE_SHIFT                            (2U)
#define CIM_FPUIE_FPUFCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPUFCIE_SHIFT)) & CIM_FPUIE_FPUFCIE_MASK)
#define CIM_FPUIE_FPDZCIE_MASK                             (0x2U)
#define CIM_FPUIE_FPDZCIE_SHIFT                            (1U)
#define CIM_FPUIE_FPDZCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPDZCIE_SHIFT)) & CIM_FPUIE_FPDZCIE_MASK)
#define CIM_FPUIE_FPIOCIE_MASK                             (0x1U)
#define CIM_FPUIE_FPIOCIE_SHIFT                            (0U)
#define CIM_FPUIE_FPIOCIE(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_FPUIE_FPIOCIE_SHIFT)) & CIM_FPUIE_FPIOCIE_MASK)
/* CIM_SWTRIG Register */
#define CIM_SWTRIG_SWTCNT_MASK                             (0xFEU)
#define CIM_SWTRIG_SWTCNT_SHIFT                            (1U)
#define CIM_SWTRIG_SWTCNT(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_SWTRIG_SWTCNT_SHIFT)) & CIM_SWTRIG_SWTCNT_MASK)
#define CIM_SWTRIG_SWT_MASK                                (0x1U)
#define CIM_SWTRIG_SWT_SHIFT                               (0U)
#define CIM_SWTRIG_SWT(x)                                  (((uint32_t)(((uint32_t)(x)) << CIM_SWTRIG_SWT_SHIFT)) & CIM_SWTRIG_SWT_MASK)
/* CIM_ETMROPT0 Register */
#define CIM_ETMROPT0_ETMR3_FAULT_SEL_MASK                  (0x70000000U)
#define CIM_ETMROPT0_ETMR3_FAULT_SEL_SHIFT                 (28U)
#define CIM_ETMROPT0_ETMR3_FAULT_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR3_FAULT_SEL_SHIFT)) & CIM_ETMROPT0_ETMR3_FAULT_SEL_MASK)
#define CIM_ETMROPT0_ETMR2_FAULT_SEL_MASK                  (0x7000000U)
#define CIM_ETMROPT0_ETMR2_FAULT_SEL_SHIFT                 (24U)
#define CIM_ETMROPT0_ETMR2_FAULT_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR2_FAULT_SEL_SHIFT)) & CIM_ETMROPT0_ETMR2_FAULT_SEL_MASK)
#define CIM_ETMROPT0_ETMR1_FAULT_SEL_MASK                  (0x700000U)
#define CIM_ETMROPT0_ETMR1_FAULT_SEL_SHIFT                 (20U)
#define CIM_ETMROPT0_ETMR1_FAULT_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR1_FAULT_SEL_SHIFT)) & CIM_ETMROPT0_ETMR1_FAULT_SEL_MASK)
#define CIM_ETMROPT0_ETMR0_FAULT_SEL_MASK                  (0x70000U)
#define CIM_ETMROPT0_ETMR0_FAULT_SEL_SHIFT                 (16U)
#define CIM_ETMROPT0_ETMR0_FAULT_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR0_FAULT_SEL_SHIFT)) & CIM_ETMROPT0_ETMR0_FAULT_SEL_MASK)
#define CIM_ETMROPT0_ETMR5_EXTCLK_SEL_MASK                  (0xC00U)
#define CIM_ETMROPT0_ETMR5_EXTCLK_SEL_SHIFT                 (10U)
#define CIM_ETMROPT0_ETMR5_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR5_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_ETMR5_EXTCLK_SEL_MASK)
#define CIM_ETMROPT0_ETMR4_EXTCLK_SEL_MASK                  (0x300U)
#define CIM_ETMROPT0_ETMR4_EXTCLK_SEL_SHIFT                 (8U)
#define CIM_ETMROPT0_ETMR4_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR4_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_ETMR4_EXTCLK_SEL_MASK)
#define CIM_ETMROPT0_ETMR3_EXTCLK_SEL_MASK                  (0xC0U)
#define CIM_ETMROPT0_ETMR3_EXTCLK_SEL_SHIFT                 (6U)
#define CIM_ETMROPT0_ETMR3_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR3_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_ETMR3_EXTCLK_SEL_MASK)
#define CIM_ETMROPT0_eTMR2_EXTCLK_SEL_MASK                  (0x30U)
#define CIM_ETMROPT0_eTMR2_EXTCLK_SEL_SHIFT                 (4U)
#define CIM_ETMROPT0_eTMR2_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_eTMR2_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_eTMR2_EXTCLK_SEL_MASK)
#define CIM_ETMROPT0_ETMR1_EXTCLK_SEL_MASK                  (0xCU)
#define CIM_ETMROPT0_ETMR1_EXTCLK_SEL_SHIFT                 (2U)
#define CIM_ETMROPT0_ETMR1_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR1_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_ETMR1_EXTCLK_SEL_MASK)
#define CIM_ETMROPT0_ETMR0_EXTCLK_SEL_MASK                  (0x3U)
#define CIM_ETMROPT0_ETMR0_EXTCLK_SEL_SHIFT                 (0U)
#define CIM_ETMROPT0_ETMR0_EXTCLK_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT0_ETMR0_EXTCLK_SEL_SHIFT)) & CIM_ETMROPT0_ETMR0_EXTCLK_SEL_MASK)
/* CIM_ETMROPT1 Register */
#define CIM_ETMROPT1_ETMR3_CH7OUTSEL_MASK                  (0x80000000U)
#define CIM_ETMROPT1_ETMR3_CH7OUTSEL_SHIFT                 (31U)
#define CIM_ETMROPT1_ETMR3_CH7OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH7OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH7OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH6OUTSEL_MASK                  (0x40000000U)
#define CIM_ETMROPT1_ETMR3_CH6OUTSEL_SHIFT                 (30U)
#define CIM_ETMROPT1_ETMR3_CH6OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH6OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH6OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH5OUTSEL_MASK                  (0x20000000U)
#define CIM_ETMROPT1_ETMR3_CH5OUTSEL_SHIFT                 (29U)
#define CIM_ETMROPT1_ETMR3_CH5OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH5OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH5OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH4OUTSEL_MASK                  (0x10000000U)
#define CIM_ETMROPT1_ETMR3_CH4OUTSEL_SHIFT                 (28U)
#define CIM_ETMROPT1_ETMR3_CH4OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH4OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH4OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH3OUTSEL_MASK                  (0x8000000U)
#define CIM_ETMROPT1_ETMR3_CH3OUTSEL_SHIFT                 (27U)
#define CIM_ETMROPT1_ETMR3_CH3OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH3OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH3OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH2OUTSEL_MASK                  (0x4000000U)
#define CIM_ETMROPT1_ETMR3_CH2OUTSEL_SHIFT                 (26U)
#define CIM_ETMROPT1_ETMR3_CH2OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH2OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH2OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH1OUTSEL_MASK                  (0x2000000U)
#define CIM_ETMROPT1_ETMR3_CH1OUTSEL_SHIFT                 (25U)
#define CIM_ETMROPT1_ETMR3_CH1OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH1OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH1OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR3_CH0OUTSEL_MASK                  (0x1000000U)
#define CIM_ETMROPT1_ETMR3_CH0OUTSEL_SHIFT                 (24U)
#define CIM_ETMROPT1_ETMR3_CH0OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3_CH0OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR3_CH0OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH7OUTSEL_MASK                  (0x800000U)
#define CIM_ETMROPT1_ETMR0_CH7OUTSEL_SHIFT                 (23U)
#define CIM_ETMROPT1_ETMR0_CH7OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH7OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH7OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH6OUTSEL_MASK                  (0x400000U)
#define CIM_ETMROPT1_ETMR0_CH6OUTSEL_SHIFT                 (22U)
#define CIM_ETMROPT1_ETMR0_CH6OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH6OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH6OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH5OUTSEL_MASK                  (0x200000U)
#define CIM_ETMROPT1_ETMR0_CH5OUTSEL_SHIFT                 (21U)
#define CIM_ETMROPT1_ETMR0_CH5OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH5OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH5OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH4OUTSEL_MASK                  (0x100000U)
#define CIM_ETMROPT1_ETMR0_CH4OUTSEL_SHIFT                 (20U)
#define CIM_ETMROPT1_ETMR0_CH4OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH4OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH4OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH3OUTSEL_MASK                  (0x80000U)
#define CIM_ETMROPT1_ETMR0_CH3OUTSEL_SHIFT                 (19U)
#define CIM_ETMROPT1_ETMR0_CH3OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH3OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH3OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH2OUTSEL_MASK                  (0x40000U)
#define CIM_ETMROPT1_ETMR0_CH2OUTSEL_SHIFT                 (18U)
#define CIM_ETMROPT1_ETMR0_CH2OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH2OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH2OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH1OUTSEL_MASK                  (0x20000U)
#define CIM_ETMROPT1_ETMR0_CH1OUTSEL_SHIFT                 (17U)
#define CIM_ETMROPT1_ETMR0_CH1OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH1OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH1OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR0_CH0OUTSEL_MASK                  (0x10000U)
#define CIM_ETMROPT1_ETMR0_CH0OUTSEL_SHIFT                 (16U)
#define CIM_ETMROPT1_ETMR0_CH0OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0_CH0OUTSEL_SHIFT)) & CIM_ETMROPT1_ETMR0_CH0OUTSEL_MASK)
#define CIM_ETMROPT1_ETMR_GTBE_SEL_MASK                    (0x4000U)
#define CIM_ETMROPT1_ETMR_GTBE_SEL_SHIFT                   (14U)
#define CIM_ETMROPT1_ETMR_GTBE_SEL(x)                      (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR_GTBE_SEL_SHIFT)) & CIM_ETMROPT1_ETMR_GTBE_SEL_MASK)
#define CIM_ETMROPT1_ETMR2CH1SEL_MASK                      (0x1000U)
#define CIM_ETMROPT1_ETMR2CH1SEL_SHIFT                     (12U)
#define CIM_ETMROPT1_ETMR2CH1SEL(x)                        (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR2CH1SEL_SHIFT)) & CIM_ETMROPT1_ETMR2CH1SEL_MASK)
#define CIM_ETMROPT1_ETMR2CH0SEL_MASK                      (0x400U)
#define CIM_ETMROPT1_ETMR2CH0SEL_SHIFT                     (10U)
#define CIM_ETMROPT1_ETMR2CH0SEL(x)                        (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR2CH0SEL_SHIFT)) & CIM_ETMROPT1_ETMR2CH0SEL_MASK)
#define CIM_ETMROPT1_ETMR1CH0SEL_MASK                      (0x100U)
#define CIM_ETMROPT1_ETMR1CH0SEL_SHIFT                     (8U)
#define CIM_ETMROPT1_ETMR1CH0SEL(x)                        (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR1CH0SEL_SHIFT)) & CIM_ETMROPT1_ETMR1CH0SEL_MASK)
#define CIM_ETMROPT1_ETMR5SS1C_MASK                        (0x20U)
#define CIM_ETMROPT1_ETMR5SS1C_SHIFT                       (5U)
#define CIM_ETMROPT1_ETMR5SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR5SS1C_SHIFT)) & CIM_ETMROPT1_ETMR5SS1C_MASK)
#define CIM_ETMROPT1_ETMR4SS1C_MASK                        (0x10U)
#define CIM_ETMROPT1_ETMR4SS1C_SHIFT                       (4U)
#define CIM_ETMROPT1_ETMR4SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR4SS1C_SHIFT)) & CIM_ETMROPT1_ETMR4SS1C_MASK)
#define CIM_ETMROPT1_ETMR3SS1C_MASK                        (0x8U)
#define CIM_ETMROPT1_ETMR3SS1C_SHIFT                       (3U)
#define CIM_ETMROPT1_ETMR3SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR3SS1C_SHIFT)) & CIM_ETMROPT1_ETMR3SS1C_MASK)
#define CIM_ETMROPT1_ETMR2SS1C_MASK                        (0x4U)
#define CIM_ETMROPT1_ETMR2SS1C_SHIFT                       (2U)
#define CIM_ETMROPT1_ETMR2SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR2SS1C_SHIFT)) & CIM_ETMROPT1_ETMR2SS1C_MASK)
#define CIM_ETMROPT1_ETMR1SS1C_MASK                        (0x2U)
#define CIM_ETMROPT1_ETMR1SS1C_SHIFT                       (1U)
#define CIM_ETMROPT1_ETMR1SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR1SS1C_SHIFT)) & CIM_ETMROPT1_ETMR1SS1C_MASK)
#define CIM_ETMROPT1_ETMR0SS1C_MASK                        (0x1U)
#define CIM_ETMROPT1_ETMR0SS1C_SHIFT                       (0U)
#define CIM_ETMROPT1_ETMR0SS1C(x)                          (((uint32_t)(((uint32_t)(x)) << CIM_ETMROPT1_ETMR0SS1C_SHIFT)) & CIM_ETMROPT1_ETMR0SS1C_MASK)
/* CIM_DIEINFO Register */
#define CIM_DIEINFO_FAMID_MASK                             (0xF0000000U)
#define CIM_DIEINFO_FAMID_SHIFT                            (28U)
#define CIM_DIEINFO_FAMID(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_FAMID_SHIFT)) & CIM_DIEINFO_FAMID_MASK)
#define CIM_DIEINFO_GENID_MASK                             (0xF000000U)
#define CIM_DIEINFO_GENID_SHIFT                            (24U)
#define CIM_DIEINFO_GENID(x)                               (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_GENID_SHIFT)) & CIM_DIEINFO_GENID_MASK)
#define CIM_DIEINFO_SUBFAMIDH_MASK                         (0xF00000U)
#define CIM_DIEINFO_SUBFAMIDH_SHIFT                        (20U)
#define CIM_DIEINFO_SUBFAMIDH(x)                           (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_SUBFAMIDH_SHIFT)) & CIM_DIEINFO_SUBFAMIDH_MASK)
#define CIM_DIEINFO_SUBFAMIDL_MASK                         (0xF0000U)
#define CIM_DIEINFO_SUBFAMIDL_SHIFT                        (16U)
#define CIM_DIEINFO_SUBFAMIDL(x)                           (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_SUBFAMIDL_SHIFT)) & CIM_DIEINFO_SUBFAMIDL_MASK)
#define CIM_DIEINFO_MAJVER_MASK                            (0xF0U)
#define CIM_DIEINFO_MAJVER_SHIFT                           (4U)
#define CIM_DIEINFO_MAJVER(x)                              (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_MAJVER_SHIFT)) & CIM_DIEINFO_MAJVER_MASK)
#define CIM_DIEINFO_MINVER_MASK                            (0xFU)
#define CIM_DIEINFO_MINVER_SHIFT                           (0U)
#define CIM_DIEINFO_MINVER(x)                              (((uint32_t)(((uint32_t)(x)) << CIM_DIEINFO_MINVER_SHIFT)) & CIM_DIEINFO_MINVER_MASK)
/* CIM_CHIPINFO Register */
#define CIM_CHIPINFO_FLEXCAN5_FD_EN_MASK                   (0x20000000U)
#define CIM_CHIPINFO_FLEXCAN5_FD_EN_SHIFT                  (29U)
#define CIM_CHIPINFO_FLEXCAN5_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN5_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN5_FD_EN_MASK)
#define CIM_CHIPINFO_FLEXCAN4_FD_EN_MASK                   (0x10000000U)
#define CIM_CHIPINFO_FLEXCAN4_FD_EN_SHIFT                  (28U)
#define CIM_CHIPINFO_FLEXCAN4_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN4_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN4_FD_EN_MASK)
#define CIM_CHIPINFO_FLEXCAN3_FD_EN_MASK                   (0x8000000U)
#define CIM_CHIPINFO_FLEXCAN3_FD_EN_SHIFT                  (27U)
#define CIM_CHIPINFO_FLEXCAN3_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN3_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN3_FD_EN_MASK)
#define CIM_CHIPINFO_FLEXCAN2_FD_EN_MASK                   (0x4000000U)
#define CIM_CHIPINFO_FLEXCAN2_FD_EN_SHIFT                  (26U)
#define CIM_CHIPINFO_FLEXCAN2_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN2_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN2_FD_EN_MASK)
#define CIM_CHIPINFO_FLEXCAN1_FD_EN_MASK                   (0x2000000U)
#define CIM_CHIPINFO_FLEXCAN1_FD_EN_SHIFT                  (25U)
#define CIM_CHIPINFO_FLEXCAN1_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN1_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN1_FD_EN_MASK)
#define CIM_CHIPINFO_FLEXCAN0_FD_EN_MASK                   (0x1000000U)
#define CIM_CHIPINFO_FLEXCAN0_FD_EN_SHIFT                  (24U)
#define CIM_CHIPINFO_FLEXCAN0_FD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_FLEXCAN0_FD_EN_SHIFT)) & CIM_CHIPINFO_FLEXCAN0_FD_EN_MASK)
#define CIM_CHIPINFO_SRAMS_MASK                            (0xF0000U)
#define CIM_CHIPINFO_SRAMS_SHIFT                           (16U)
#define CIM_CHIPINFO_SRAMS(x)                              (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_SRAMS_SHIFT)) & CIM_CHIPINFO_SRAMS_MASK)
#define CIM_CHIPINFO_DFLASHS_MASK                          (0xF000U)
#define CIM_CHIPINFO_DFLASHS_SHIFT                         (12U)
#define CIM_CHIPINFO_DFLASHS(x)                            (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_DFLASHS_SHIFT)) & CIM_CHIPINFO_DFLASHS_MASK)
#define CIM_CHIPINFO_PFLASHS_MASK                          (0xF00U)
#define CIM_CHIPINFO_PFLASHS_SHIFT                         (8U)
#define CIM_CHIPINFO_PFLASHS(x)                            (((uint32_t)(((uint32_t)(x)) << CIM_CHIPINFO_PFLASHS_SHIFT)) & CIM_CHIPINFO_PFLASHS_MASK)
/* CIM_UID0 Register */
#define CIM_UID0_UID0_MASK                                 (0xFFFFFFFFU)
#define CIM_UID0_UID0_SHIFT                                (0U)
#define CIM_UID0_UID0(x)                                   (((uint32_t)(((uint32_t)(x)) << CIM_UID0_UID0_SHIFT)) & CIM_UID0_UID0_MASK)
/* CIM_UID1 Register */
#define CIM_UID1_UID1_MASK                                 (0xFFFFFFFFU)
#define CIM_UID1_UID1_SHIFT                                (0U)
#define CIM_UID1_UID1(x)                                   (((uint32_t)(((uint32_t)(x)) << CIM_UID1_UID1_SHIFT)) & CIM_UID1_UID1_MASK)
/* CIM_UID2 Register */
#define CIM_UID2_UID2_MASK                                 (0xFFFFFFFFU)
#define CIM_UID2_UID2_SHIFT                                (0U)
#define CIM_UID2_UID2(x)                                   (((uint32_t)(((uint32_t)(x)) << CIM_UID2_UID2_SHIFT)) & CIM_UID2_UID2_MASK)
/* CIM_UID3 Register */
#define CIM_UID3_UID3_MASK                                 (0xFFFFFFFFU)
#define CIM_UID3_UID3_SHIFT                                (0U)
#define CIM_UID3_UID3(x)                                   (((uint32_t)(((uint32_t)(x)) << CIM_UID3_UID3_SHIFT)) & CIM_UID3_UID3_MASK)


/*!
 * @}
 */ /* end of group CIM_Register_Masks */


/*!
 * @}
 */ /* end of group CIM_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- TMU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup TMU_Peripheral_Access_Layer TMU Peripheral Access Layer
 * @{
 */


/** TMU - Size of Registers Arrays */
#define TMU_MUX_COUNT                     (32)

/* TMU Register Layout Typedef */
typedef struct {
    __IO uint32_t MUX[32];                            /**< MUX, offset: 0x0000 */

} TMU_Type, *TMU_MemMapPtr;

/** Number of instances of the TMU module. */
#define TMU_INSTANCE_COUNT                             (1u)

/* TMU base address */
#define TMU_BASE                                          (0x40048000)
#define TMU                                               ((TMU_Type *)(TMU_BASE))

/** Array initializer of TMU peripheral base addresses */
#define TMU_BASE_ADDRS                                     { TMU_BASE }
/** Array initializer of TMU peripheral base pointers */
#define TMU_BASE_PTRS                                      { TMU }

/* TMU Register Mask */
/* TMU_MUX Register */
#define TMU_MUX_LOCK_MASK                                  (0x80000000U)
#define TMU_MUX_LOCK_SHIFT                                 (31U)
#define TMU_MUX_LOCK(x)                                    (((uint32_t)(((uint32_t)(x)) << TMU_MUX_LOCK_SHIFT)) & TMU_MUX_LOCK_MASK)
#define TMU_MUX_SEL3_WIDTH                                 (7)
#define TMU_MUX_SEL3_MASK                                  (0x7F000000U)
#define TMU_MUX_SEL3_SHIFT                                 (24U)
#define TMU_MUX_SEL3(x)                                    (((uint32_t)(((uint32_t)(x)) << TMU_MUX_SEL3_SHIFT)) & TMU_MUX_SEL3_MASK)
#define TMU_MUX_SEL2_WIDTH                                 (7)
#define TMU_MUX_SEL2_MASK                                  (0x7F0000U)
#define TMU_MUX_SEL2_SHIFT                                 (16U)
#define TMU_MUX_SEL2(x)                                    (((uint32_t)(((uint32_t)(x)) << TMU_MUX_SEL2_SHIFT)) & TMU_MUX_SEL2_MASK)
#define TMU_MUX_SEL1_WIDTH                                 (7)
#define TMU_MUX_SEL1_MASK                                  (0x7F00U)
#define TMU_MUX_SEL1_SHIFT                                 (8U)
#define TMU_MUX_SEL1(x)                                    (((uint32_t)(((uint32_t)(x)) << TMU_MUX_SEL1_SHIFT)) & TMU_MUX_SEL1_MASK)
#define TMU_MUX_SEL0_WIDTH                                 (7)
#define TMU_MUX_SEL0_MASK                                  (0x7FU)
#define TMU_MUX_SEL0_SHIFT                                 (0U)
#define TMU_MUX_SEL0(x)                                    (((uint32_t)(((uint32_t)(x)) << TMU_MUX_SEL0_SHIFT)) & TMU_MUX_SEL0_MASK)


/*!
 * @}
 */ /* end of group TMU_Register_Masks */


/*!
 * @}
 */ /* end of group TMU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- SCU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup SCU_Peripheral_Access_Layer SCU Peripheral Access Layer
 * @{
 */


/** SCU - Size of Registers Arrays */
#define SCU_CMUCMP_COUNT                     (4)

/* SCU Register Layout Typedef */
typedef struct {
    __IO uint32_t CLKS;                               /**< Clock Selection Register, offset: 0x0000 */
    __IO uint32_t DIV;                                /**< System Clock Divider, offset: 0x0004 */
    __I  uint32_t STS;                                /**< Status Register, offset: 0x0008 */
    __I  uint32_t DIVSTS;                             /**< Clock Divier Status Register, offset: 0x000C */
    __IO uint32_t FIRC_CTRL;                          /**< FIRC Control Register, offset: 0x0010 */
    __IO uint32_t SIRC_CTRL;                          /**< SIRC Control Register, offset: 0x0014 */
    __IO uint32_t FXOSC_CTRL;                         /**< FXOSC Control Register, offset: 0x0018 */
    __IO uint32_t SXOSC_CTRL;                         /**< SXOSC Control Register, offset: 0x001C */
    __IO uint32_t PLL_CTRL;                           /**< PLL Control Register, offset: 0x0020 */
    __IO uint32_t RESERVED0[ 2];                      /**< RESERVED0, offset: 0x0024 */
    __IO uint32_t CLKO;                               /**< Clock Output Control Register, offset: 0x002C */
    __IO uint32_t RESERVED_11;                        /**< RESERVED_11, offset: 0x0030 */
    __IO uint32_t RESERVED_12;                        /**< RESERVED_12, offset: 0x0034 */
    __IO uint32_t RESERVED1[ 2];                      /**< RESERVED1, offset: 0x0038 */
    __IO uint32_t CMU_CTRL;                           /**< Clock Monitor Unit Control Register, offset: 0x0040 */
    __IO uint32_t CMUSTS;                             /**< Clock Monitor Unit Status Register, offset: 0x0044 */
    struct {
        __IO uint32_t HIGH;                               /**< Clock Monitor Unit High Comparison Value Register, offset: 0x0048 */
        __IO uint32_t LOW;                                /**< Clock Monitor Unit Low Comparison Value Register, offset: 0x004C */

    } CMUCMP[4];
    __IO uint32_t RESERVED_17;                        /**< RESERVED_17, offset: 0x0068 */

} SCU_Type, *SCU_MemMapPtr;

/** Number of instances of the SCU module. */
#define SCU_INSTANCE_COUNT                             (1u)

/* SCU base address */
#define SCU_BASE                                          (0x4007C000)
#define SCU                                               ((SCU_Type *)(SCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define SCU_MIRROR_BASE                                   (0x4007C800)
#define SCU_MIRROR                                        ((SCU_Type *)(SCU_MIRROR_BASE))

#define SCU_PPU_BASE                                      (0x4007C000)
#define SCU_PPU                                           ((PPU_Type *)(SCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of SCU peripheral base addresses */
#define SCU_BASE_ADDRS                                     { SCU_BASE }
/** Array initializer of SCU peripheral base pointers */
#define SCU_BASE_PTRS                                      { SCU }

/* SCU Register Mask */
/* SCU_CLKS Register */
#define SCU_CLKS_CLKSRCSEL_MASK                            (0x3U)
#define SCU_CLKS_CLKSRCSEL_SHIFT                           (0U)
#define SCU_CLKS_CLKSRCSEL(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_CLKS_CLKSRCSEL_SHIFT)) & SCU_CLKS_CLKSRCSEL_MASK)
/* SCU_DIV Register */
#define SCU_DIV_CPDIVS_MASK                                (0xF0000U)
#define SCU_DIV_CPDIVS_SHIFT                               (16U)
#define SCU_DIV_CPDIVS(x)                                  (((uint32_t)(((uint32_t)(x)) << SCU_DIV_CPDIVS_SHIFT)) & SCU_DIV_CPDIVS_MASK)
#define SCU_DIV_FBDIVS_MASK                                (0xF00U)
#define SCU_DIV_FBDIVS_SHIFT                               (8U)
#define SCU_DIV_FBDIVS(x)                                  (((uint32_t)(((uint32_t)(x)) << SCU_DIV_FBDIVS_SHIFT)) & SCU_DIV_FBDIVS_MASK)
#define SCU_DIV_SBDIVS_MASK                                (0xFU)
#define SCU_DIV_SBDIVS_SHIFT                               (0U)
#define SCU_DIV_SBDIVS(x)                                  (((uint32_t)(((uint32_t)(x)) << SCU_DIV_SBDIVS_SHIFT)) & SCU_DIV_SBDIVS_MASK)
/* SCU_STS Register */
#define SCU_STS_PLL_LOCK_MASK                              (0x20U)
#define SCU_STS_PLL_LOCK_SHIFT                             (5U)
#define SCU_STS_PLL_LOCK(x)                                (((uint32_t)(((uint32_t)(x)) << SCU_STS_PLL_LOCK_SHIFT)) & SCU_STS_PLL_LOCK_MASK)
#define SCU_STS_SXOSC_VALID_MASK                           (0x10U)
#define SCU_STS_SXOSC_VALID_SHIFT                          (4U)
#define SCU_STS_SXOSC_VALID(x)                             (((uint32_t)(((uint32_t)(x)) << SCU_STS_SXOSC_VALID_SHIFT)) & SCU_STS_SXOSC_VALID_MASK)
#define SCU_STS_FXOSC_VALID_MASK                           (0x8U)
#define SCU_STS_FXOSC_VALID_SHIFT                          (3U)
#define SCU_STS_FXOSC_VALID(x)                             (((uint32_t)(((uint32_t)(x)) << SCU_STS_FXOSC_VALID_SHIFT)) & SCU_STS_FXOSC_VALID_MASK)
#define SCU_STS_FIRC_VALID_MASK                            (0x4U)
#define SCU_STS_FIRC_VALID_SHIFT                           (2U)
#define SCU_STS_FIRC_VALID(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_STS_FIRC_VALID_SHIFT)) & SCU_STS_FIRC_VALID_MASK)
#define SCU_STS_CLKST_MASK                                 (0x3U)
#define SCU_STS_CLKST_SHIFT                                (0U)
#define SCU_STS_CLKST(x)                                   (((uint32_t)(((uint32_t)(x)) << SCU_STS_CLKST_SHIFT)) & SCU_STS_CLKST_MASK)
/* SCU_DIVSTS Register */
#define SCU_DIVSTS_CPDIVST_MASK                            (0xF0000U)
#define SCU_DIVSTS_CPDIVST_SHIFT                           (16U)
#define SCU_DIVSTS_CPDIVST(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_DIVSTS_CPDIVST_SHIFT)) & SCU_DIVSTS_CPDIVST_MASK)
#define SCU_DIVSTS_FBDIVST_MASK                            (0xF00U)
#define SCU_DIVSTS_FBDIVST_SHIFT                           (8U)
#define SCU_DIVSTS_FBDIVST(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_DIVSTS_FBDIVST_SHIFT)) & SCU_DIVSTS_FBDIVST_MASK)
#define SCU_DIVSTS_SBDIVST_MASK                            (0xFU)
#define SCU_DIVSTS_SBDIVST_SHIFT                           (0U)
#define SCU_DIVSTS_SBDIVST(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_DIVSTS_SBDIVST_SHIFT)) & SCU_DIVSTS_SBDIVST_MASK)
/* SCU_FIRC_CTRL Register */
#define SCU_FIRC_CTRL_FIRC_DS_EN_MASK                      (0x2U)
#define SCU_FIRC_CTRL_FIRC_DS_EN_SHIFT                     (1U)
#define SCU_FIRC_CTRL_FIRC_DS_EN(x)                        (((uint32_t)(((uint32_t)(x)) << SCU_FIRC_CTRL_FIRC_DS_EN_SHIFT)) & SCU_FIRC_CTRL_FIRC_DS_EN_MASK)
#define SCU_FIRC_CTRL_FIRC_EN_MASK                         (0x1U)
#define SCU_FIRC_CTRL_FIRC_EN_SHIFT                        (0U)
#define SCU_FIRC_CTRL_FIRC_EN(x)                           (((uint32_t)(((uint32_t)(x)) << SCU_FIRC_CTRL_FIRC_EN_SHIFT)) & SCU_FIRC_CTRL_FIRC_EN_MASK)
/* SCU_SIRC_CTRL Register */
#define SCU_SIRC_CTRL_SIRC_PD_EN_MASK                      (0x8U)
#define SCU_SIRC_CTRL_SIRC_PD_EN_SHIFT                     (3U)
#define SCU_SIRC_CTRL_SIRC_PD_EN(x)                        (((uint32_t)(((uint32_t)(x)) << SCU_SIRC_CTRL_SIRC_PD_EN_SHIFT)) & SCU_SIRC_CTRL_SIRC_PD_EN_MASK)
#define SCU_SIRC_CTRL_SIRC_STB_EN_MASK                     (0x4U)
#define SCU_SIRC_CTRL_SIRC_STB_EN_SHIFT                    (2U)
#define SCU_SIRC_CTRL_SIRC_STB_EN(x)                       (((uint32_t)(((uint32_t)(x)) << SCU_SIRC_CTRL_SIRC_STB_EN_SHIFT)) & SCU_SIRC_CTRL_SIRC_STB_EN_MASK)
#define SCU_SIRC_CTRL_SIRC_DS_EN_MASK                      (0x2U)
#define SCU_SIRC_CTRL_SIRC_DS_EN_SHIFT                     (1U)
#define SCU_SIRC_CTRL_SIRC_DS_EN(x)                        (((uint32_t)(((uint32_t)(x)) << SCU_SIRC_CTRL_SIRC_DS_EN_SHIFT)) & SCU_SIRC_CTRL_SIRC_DS_EN_MASK)
/* SCU_FXOSC_CTRL Register */
#define SCU_FXOSC_CTRL_HYSTDIS_MASK                        (0x4000U)
#define SCU_FXOSC_CTRL_HYSTDIS_SHIFT                       (14U)
#define SCU_FXOSC_CTRL_HYSTDIS(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_HYSTDIS_SHIFT)) & SCU_FXOSC_CTRL_HYSTDIS_MASK)
#define SCU_FXOSC_CTRL_ALCDIS_MASK                         (0x2000U)
#define SCU_FXOSC_CTRL_ALCDIS_SHIFT                        (13U)
#define SCU_FXOSC_CTRL_ALCDIS(x)                           (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_ALCDIS_SHIFT)) & SCU_FXOSC_CTRL_ALCDIS_MASK)
#define SCU_FXOSC_CTRL_COMPEN_MASK                         (0x1000U)
#define SCU_FXOSC_CTRL_COMPEN_SHIFT                        (12U)
#define SCU_FXOSC_CTRL_COMPEN(x)                           (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_COMPEN_SHIFT)) & SCU_FXOSC_CTRL_COMPEN_MASK)
#define SCU_FXOSC_CTRL_GMSEL_MASK                          (0xF00U)
#define SCU_FXOSC_CTRL_GMSEL_SHIFT                         (8U)
#define SCU_FXOSC_CTRL_GMSEL(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_GMSEL_SHIFT)) & SCU_FXOSC_CTRL_GMSEL_MASK)
#define SCU_FXOSC_CTRL_FXOSC_MODE_MASK                     (0x10U)
#define SCU_FXOSC_CTRL_FXOSC_MODE_SHIFT                    (4U)
#define SCU_FXOSC_CTRL_FXOSC_MODE(x)                       (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_FXOSC_MODE_SHIFT)) & SCU_FXOSC_CTRL_FXOSC_MODE_MASK)
#define SCU_FXOSC_CTRL_FXOSC_DS_EN_MASK                    (0x2U)
#define SCU_FXOSC_CTRL_FXOSC_DS_EN_SHIFT                   (1U)
#define SCU_FXOSC_CTRL_FXOSC_DS_EN(x)                      (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_FXOSC_DS_EN_SHIFT)) & SCU_FXOSC_CTRL_FXOSC_DS_EN_MASK)
#define SCU_FXOSC_CTRL_FXOSC_EN_MASK                       (0x1U)
#define SCU_FXOSC_CTRL_FXOSC_EN_SHIFT                      (0U)
#define SCU_FXOSC_CTRL_FXOSC_EN(x)                         (((uint32_t)(((uint32_t)(x)) << SCU_FXOSC_CTRL_FXOSC_EN_SHIFT)) & SCU_FXOSC_CTRL_FXOSC_EN_MASK)
/* SCU_SXOSC_CTRL Register */
#define SCU_SXOSC_CTRL_GMSEL_MASK                          (0x100U)
#define SCU_SXOSC_CTRL_GMSEL_SHIFT                         (8U)
#define SCU_SXOSC_CTRL_GMSEL(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_GMSEL_SHIFT)) & SCU_SXOSC_CTRL_GMSEL_MASK)
#define SCU_SXOSC_CTRL_SXOSC_MODE_MASK                     (0x10U)
#define SCU_SXOSC_CTRL_SXOSC_MODE_SHIFT                    (4U)
#define SCU_SXOSC_CTRL_SXOSC_MODE(x)                       (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_SXOSC_MODE_SHIFT)) & SCU_SXOSC_CTRL_SXOSC_MODE_MASK)
#define SCU_SXOSC_CTRL_SXOSC_PD_EN_MASK                    (0x8U)
#define SCU_SXOSC_CTRL_SXOSC_PD_EN_SHIFT                   (3U)
#define SCU_SXOSC_CTRL_SXOSC_PD_EN(x)                      (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_SXOSC_PD_EN_SHIFT)) & SCU_SXOSC_CTRL_SXOSC_PD_EN_MASK)
#define SCU_SXOSC_CTRL_SXOSC_DS_EN_MASK                    (0x4U)
#define SCU_SXOSC_CTRL_SXOSC_DS_EN_SHIFT                   (2U)
#define SCU_SXOSC_CTRL_SXOSC_DS_EN(x)                      (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_SXOSC_DS_EN_SHIFT)) & SCU_SXOSC_CTRL_SXOSC_DS_EN_MASK)
#define SCU_SXOSC_CTRL_SXOSC_STB_EN_MASK                   (0x2U)
#define SCU_SXOSC_CTRL_SXOSC_STB_EN_SHIFT                  (1U)
#define SCU_SXOSC_CTRL_SXOSC_STB_EN(x)                     (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_SXOSC_STB_EN_SHIFT)) & SCU_SXOSC_CTRL_SXOSC_STB_EN_MASK)
#define SCU_SXOSC_CTRL_SXOSC_EN_MASK                       (0x1U)
#define SCU_SXOSC_CTRL_SXOSC_EN_SHIFT                      (0U)
#define SCU_SXOSC_CTRL_SXOSC_EN(x)                         (((uint32_t)(((uint32_t)(x)) << SCU_SXOSC_CTRL_SXOSC_EN_SHIFT)) & SCU_SXOSC_CTRL_SXOSC_EN_MASK)
/* SCU_PLL_CTRL Register */
#define SCU_PLL_CTRL_FBDIV_MASK                            (0x3F0000U)
#define SCU_PLL_CTRL_FBDIV_SHIFT                           (16U)
#define SCU_PLL_CTRL_FBDIV(x)                              (((uint32_t)(((uint32_t)(x)) << SCU_PLL_CTRL_FBDIV_SHIFT)) & SCU_PLL_CTRL_FBDIV_MASK)
#define SCU_PLL_CTRL_REFDIV_MASK                           (0xF00U)
#define SCU_PLL_CTRL_REFDIV_SHIFT                          (8U)
#define SCU_PLL_CTRL_REFDIV(x)                             (((uint32_t)(((uint32_t)(x)) << SCU_PLL_CTRL_REFDIV_SHIFT)) & SCU_PLL_CTRL_REFDIV_MASK)
#define SCU_PLL_CTRL_REFCLKSRCSEL_MASK                     (0x10U)
#define SCU_PLL_CTRL_REFCLKSRCSEL_SHIFT                    (4U)
#define SCU_PLL_CTRL_REFCLKSRCSEL(x)                       (((uint32_t)(((uint32_t)(x)) << SCU_PLL_CTRL_REFCLKSRCSEL_SHIFT)) & SCU_PLL_CTRL_REFCLKSRCSEL_MASK)
#define SCU_PLL_CTRL_PLL_DS_EN_MASK                        (0x2U)
#define SCU_PLL_CTRL_PLL_DS_EN_SHIFT                       (1U)
#define SCU_PLL_CTRL_PLL_DS_EN(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_PLL_CTRL_PLL_DS_EN_SHIFT)) & SCU_PLL_CTRL_PLL_DS_EN_MASK)
#define SCU_PLL_CTRL_PLL_EN_MASK                           (0x1U)
#define SCU_PLL_CTRL_PLL_EN_SHIFT                          (0U)
#define SCU_PLL_CTRL_PLL_EN(x)                             (((uint32_t)(((uint32_t)(x)) << SCU_PLL_CTRL_PLL_EN_SHIFT)) & SCU_PLL_CTRL_PLL_EN_MASK)
/* SCU_CLKO Register */
#define SCU_CLKO_CLKODIV_MASK                              (0xFF00U)
#define SCU_CLKO_CLKODIV_SHIFT                             (8U)
#define SCU_CLKO_CLKODIV(x)                                (((uint32_t)(((uint32_t)(x)) << SCU_CLKO_CLKODIV_SHIFT)) & SCU_CLKO_CLKODIV_MASK)
#define SCU_CLKO_CLKOSEL_MASK                              (0x7U)
#define SCU_CLKO_CLKOSEL_SHIFT                             (0U)
#define SCU_CLKO_CLKOSEL(x)                                (((uint32_t)(((uint32_t)(x)) << SCU_CLKO_CLKOSEL_SHIFT)) & SCU_CLKO_CLKOSEL_MASK)
/* SCU_CMU_CTRL Register */
#define SCU_CMU_CTRL_CMU2_REFS_MASK                        (0x40000U)
#define SCU_CMU_CTRL_CMU2_REFS_SHIFT                       (18U)
#define SCU_CMU_CTRL_CMU2_REFS(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU2_REFS_SHIFT)) & SCU_CMU_CTRL_CMU2_REFS_MASK)
#define SCU_CMU_CTRL_CMU1_REFS_MASK                        (0x20000U)
#define SCU_CMU_CTRL_CMU1_REFS_SHIFT                       (17U)
#define SCU_CMU_CTRL_CMU1_REFS(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU1_REFS_SHIFT)) & SCU_CMU_CTRL_CMU1_REFS_MASK)
#define SCU_CMU_CTRL_CMU0_REFS_MASK                        (0x10000U)
#define SCU_CMU_CTRL_CMU0_REFS_SHIFT                       (16U)
#define SCU_CMU_CTRL_CMU0_REFS(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU0_REFS_SHIFT)) & SCU_CMU_CTRL_CMU0_REFS_MASK)
#define SCU_CMU_CTRL_CMU3_RE_MASK                          (0x800U)
#define SCU_CMU_CTRL_CMU3_RE_SHIFT                         (11U)
#define SCU_CMU_CTRL_CMU3_RE(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU3_RE_SHIFT)) & SCU_CMU_CTRL_CMU3_RE_MASK)
#define SCU_CMU_CTRL_CMU2_RE_MASK                          (0x400U)
#define SCU_CMU_CTRL_CMU2_RE_SHIFT                         (10U)
#define SCU_CMU_CTRL_CMU2_RE(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU2_RE_SHIFT)) & SCU_CMU_CTRL_CMU2_RE_MASK)
#define SCU_CMU_CTRL_CMU1_RE_MASK                          (0x200U)
#define SCU_CMU_CTRL_CMU1_RE_SHIFT                         (9U)
#define SCU_CMU_CTRL_CMU1_RE(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU1_RE_SHIFT)) & SCU_CMU_CTRL_CMU1_RE_MASK)
#define SCU_CMU_CTRL_CMU0_RE_MASK                          (0x100U)
#define SCU_CMU_CTRL_CMU0_RE_SHIFT                         (8U)
#define SCU_CMU_CTRL_CMU0_RE(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU0_RE_SHIFT)) & SCU_CMU_CTRL_CMU0_RE_MASK)
#define SCU_CMU_CTRL_CMU3_EN_MASK                          (0x8U)
#define SCU_CMU_CTRL_CMU3_EN_SHIFT                         (3U)
#define SCU_CMU_CTRL_CMU3_EN(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU3_EN_SHIFT)) & SCU_CMU_CTRL_CMU3_EN_MASK)
#define SCU_CMU_CTRL_CMU2_EN_MASK                          (0x4U)
#define SCU_CMU_CTRL_CMU2_EN_SHIFT                         (2U)
#define SCU_CMU_CTRL_CMU2_EN(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU2_EN_SHIFT)) & SCU_CMU_CTRL_CMU2_EN_MASK)
#define SCU_CMU_CTRL_CMU1_EN_MASK                          (0x2U)
#define SCU_CMU_CTRL_CMU1_EN_SHIFT                         (1U)
#define SCU_CMU_CTRL_CMU1_EN(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU1_EN_SHIFT)) & SCU_CMU_CTRL_CMU1_EN_MASK)
#define SCU_CMU_CTRL_CMU0_EN_MASK                          (0x1U)
#define SCU_CMU_CTRL_CMU0_EN_SHIFT                         (0U)
#define SCU_CMU_CTRL_CMU0_EN(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMU_CTRL_CMU0_EN_SHIFT)) & SCU_CMU_CTRL_CMU0_EN_MASK)
/* SCU_CMUSTS Register */
#define SCU_CMUSTS_CMU3_LOSC_MASK                          (0x80000U)
#define SCU_CMUSTS_CMU3_LOSC_SHIFT                         (19U)
#define SCU_CMUSTS_CMU3_LOSC(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU3_LOSC_SHIFT)) & SCU_CMUSTS_CMU3_LOSC_MASK)
#define SCU_CMUSTS_CMU2_LOSC_MASK                          (0x40000U)
#define SCU_CMUSTS_CMU2_LOSC_SHIFT                         (18U)
#define SCU_CMUSTS_CMU2_LOSC(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU2_LOSC_SHIFT)) & SCU_CMUSTS_CMU2_LOSC_MASK)
#define SCU_CMUSTS_CMU1_LOSC_MASK                          (0x20000U)
#define SCU_CMUSTS_CMU1_LOSC_SHIFT                         (17U)
#define SCU_CMUSTS_CMU1_LOSC(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU1_LOSC_SHIFT)) & SCU_CMUSTS_CMU1_LOSC_MASK)
#define SCU_CMUSTS_CMU0_LOSC_MASK                          (0x10000U)
#define SCU_CMUSTS_CMU0_LOSC_SHIFT                         (16U)
#define SCU_CMUSTS_CMU0_LOSC(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU0_LOSC_SHIFT)) & SCU_CMUSTS_CMU0_LOSC_MASK)
#define SCU_CMUSTS_CMU3_LOSR_MASK                          (0x800U)
#define SCU_CMUSTS_CMU3_LOSR_SHIFT                         (11U)
#define SCU_CMUSTS_CMU3_LOSR(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU3_LOSR_SHIFT)) & SCU_CMUSTS_CMU3_LOSR_MASK)
#define SCU_CMUSTS_CMU2_LOSR_MASK                          (0x400U)
#define SCU_CMUSTS_CMU2_LOSR_SHIFT                         (10U)
#define SCU_CMUSTS_CMU2_LOSR(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU2_LOSR_SHIFT)) & SCU_CMUSTS_CMU2_LOSR_MASK)
#define SCU_CMUSTS_CMU1_LOSR_MASK                          (0x200U)
#define SCU_CMUSTS_CMU1_LOSR_SHIFT                         (9U)
#define SCU_CMUSTS_CMU1_LOSR(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU1_LOSR_SHIFT)) & SCU_CMUSTS_CMU1_LOSR_MASK)
#define SCU_CMUSTS_CMU0_LOSR_MASK                          (0x100U)
#define SCU_CMUSTS_CMU0_LOSR_SHIFT                         (8U)
#define SCU_CMUSTS_CMU0_LOSR(x)                            (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU0_LOSR_SHIFT)) & SCU_CMUSTS_CMU0_LOSR_MASK)
#define SCU_CMUSTS_CMU3_OUTRNG_MASK                        (0x8U)
#define SCU_CMUSTS_CMU3_OUTRNG_SHIFT                       (3U)
#define SCU_CMUSTS_CMU3_OUTRNG(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU3_OUTRNG_SHIFT)) & SCU_CMUSTS_CMU3_OUTRNG_MASK)
#define SCU_CMUSTS_CMU2_OUTRNG_MASK                        (0x4U)
#define SCU_CMUSTS_CMU2_OUTRNG_SHIFT                       (2U)
#define SCU_CMUSTS_CMU2_OUTRNG(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU2_OUTRNG_SHIFT)) & SCU_CMUSTS_CMU2_OUTRNG_MASK)
#define SCU_CMUSTS_CMU1_OUTRNG_MASK                        (0x2U)
#define SCU_CMUSTS_CMU1_OUTRNG_SHIFT                       (1U)
#define SCU_CMUSTS_CMU1_OUTRNG(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU1_OUTRNG_SHIFT)) & SCU_CMUSTS_CMU1_OUTRNG_MASK)
#define SCU_CMUSTS_CMU0_OUTRNG_MASK                        (0x1U)
#define SCU_CMUSTS_CMU0_OUTRNG_SHIFT                       (0U)
#define SCU_CMUSTS_CMU0_OUTRNG(x)                          (((uint32_t)(((uint32_t)(x)) << SCU_CMUSTS_CMU0_OUTRNG_SHIFT)) & SCU_CMUSTS_CMU0_OUTRNG_MASK)
/* SCU_CMUCMP_HIGH Register */
#define SCU_CMUCMP_HIGH_VAL_MASK                                  (0xFFFFU)
#define SCU_CMUCMP_HIGH_VAL_SHIFT                                 (0U)
#define SCU_CMUCMP_HIGH_VAL(x)                                    (((uint32_t)(((uint32_t)(x)) << SCU_CMUCMP_HIGH_VAL_SHIFT)) & SCU_CMUCMP_HIGH_VAL_MASK)
/* SCU_CMUCMP_LOW Register */
#define SCU_CMUCMP_LOW_VAL_MASK                                   (0xFFFFU)
#define SCU_CMUCMP_LOW_VAL_SHIFT                                  (0U)
#define SCU_CMUCMP_LOW_VAL(x)                                     (((uint32_t)(((uint32_t)(x)) << SCU_CMUCMP_LOW_VAL_SHIFT)) & SCU_CMUCMP_LOW_VAL_MASK)



/*!
 * @}
 */ /* end of group SCU_Register_Masks */


/*!
 * @}
 */ /* end of group SCU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- IPC Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup IPC_Peripheral_Access_Layer IPC Peripheral Access Layer
 * @{
 */


/** IPC - Size of Registers Arrays */
#define IPC_CTRL_COUNT                     (128)

/* IPC Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL[128];                           /**< Control Register, offset: 0x0000 */

} IPC_Type, *IPC_MemMapPtr;

/** Number of instances of the IPC module. */
#define IPC_INSTANCE_COUNT                             (1u)

/* IPC base address */
#define IPC_BASE                                          (0x4007D000)
#define IPC                                               ((IPC_Type *)(IPC_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define IPC_MIRROR_BASE                                   (0x4007D800)
#define IPC_MIRROR                                        ((IPC_Type *)(IPC_MIRROR_BASE))

#define IPC_PPU_BASE                                      (0x4007D000)
#define IPC_PPU                                           ((PPU_Type *)(IPC_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of IPC peripheral base addresses */
#define IPC_BASE_ADDRS                                     { IPC_BASE }
/** Array initializer of IPC peripheral base pointers */
#define IPC_BASE_PTRS                                      { IPC }

/* IPC Register Mask */
/* IPC_CTRL Register */
#define IPC_CTRL_DIV_WIDTH                                 (4)
#define IPC_CTRL_DIV_MASK                                  (0xF0000U)
#define IPC_CTRL_DIV_SHIFT                                 (16U)
#define IPC_CTRL_DIV(x)                                    (((uint32_t)(((uint32_t)(x)) << IPC_CTRL_DIV_SHIFT)) & IPC_CTRL_DIV_MASK)
#define IPC_CTRL_SRCSEL_WIDTH                              (3)
#define IPC_CTRL_SRCSEL_MASK                               (0x700U)
#define IPC_CTRL_SRCSEL_SHIFT                              (8U)
#define IPC_CTRL_SRCSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << IPC_CTRL_SRCSEL_SHIFT)) & IPC_CTRL_SRCSEL_MASK)
#define IPC_CTRL_SWREN_MASK                                (0x2U)
#define IPC_CTRL_SWREN_SHIFT                               (1U)
#define IPC_CTRL_SWREN(x)                                  (((uint32_t)(((uint32_t)(x)) << IPC_CTRL_SWREN_SHIFT)) & IPC_CTRL_SWREN_MASK)
#define IPC_CTRL_CLKEN_MASK                                (0x1U)
#define IPC_CTRL_CLKEN_SHIFT                               (0U)
#define IPC_CTRL_CLKEN(x)                                  (((uint32_t)(((uint32_t)(x)) << IPC_CTRL_CLKEN_SHIFT)) & IPC_CTRL_CLKEN_MASK)


/*!
 * @}
 */ /* end of group IPC_Register_Masks */


/*!
 * @}
 */ /* end of group IPC_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- RCU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup RCU_Peripheral_Access_Layer RCU Peripheral Access Layer
 * @{
 */


/** RCU - Size of Registers Arrays */

/* RCU Register Layout Typedef */
typedef struct {
    __IO uint32_t RSSR;                               /**< Reset Source Status Register, offset: 0x0000 */
    __IO uint32_t RPFR;                               /**< Reset Pin Filter Register, offset: 0x0004 */

} RCU_Type, *RCU_MemMapPtr;

/** Number of instances of the RCU module. */
#define RCU_INSTANCE_COUNT                             (1u)

/* RCU base address */
#define RCU_BASE                                          (0x4007F000)
#define RCU                                               ((RCU_Type *)(RCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define RCU_MIRROR_BASE                                   (0x4007F800)
#define RCU_MIRROR                                        ((RCU_Type *)(RCU_MIRROR_BASE))

#define RCU_PPU_BASE                                      (0x4007F000)
#define RCU_PPU                                           ((PPU_Type *)(RCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of RCU peripheral base addresses */
#define RCU_BASE_ADDRS                                     { RCU_BASE }
/** Array initializer of RCU peripheral base pointers */
#define RCU_BASE_PTRS                                      { RCU }

/* RCU Register Mask */
/* RCU_RSSR Register */
#define RCU_RSSR_HVD_MASK                                  (0x100000U)
#define RCU_RSSR_HVD_SHIFT                                 (20U)
#define RCU_RSSR_HVD(x)                                    (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_HVD_SHIFT)) & RCU_RSSR_HVD_MASK)
#define RCU_RSSR_LPACK_MASK                                (0x80000U)
#define RCU_RSSR_LPACK_SHIFT                               (19U)
#define RCU_RSSR_LPACK(x)                                  (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_LPACK_SHIFT)) & RCU_RSSR_LPACK_MASK)
#define RCU_RSSR_WDG_MASK                                  (0x40000U)
#define RCU_RSSR_WDG_SHIFT                                 (18U)
#define RCU_RSSR_WDG(x)                                    (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_WDG_SHIFT)) & RCU_RSSR_WDG_MASK)
#define RCU_RSSR_CMU_MASK                                  (0x20000U)
#define RCU_RSSR_CMU_SHIFT                                 (17U)
#define RCU_RSSR_CMU(x)                                    (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_CMU_SHIFT)) & RCU_RSSR_CMU_MASK)
#define RCU_RSSR_LOCKUP_MASK                               (0x10000U)
#define RCU_RSSR_LOCKUP_SHIFT                              (16U)
#define RCU_RSSR_LOCKUP(x)                                 (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_LOCKUP_SHIFT)) & RCU_RSSR_LOCKUP_MASK)
#define RCU_RSSR_DBG_MASK                                  (0x200U)
#define RCU_RSSR_DBG_SHIFT                                 (9U)
#define RCU_RSSR_DBG(x)                                    (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_DBG_SHIFT)) & RCU_RSSR_DBG_MASK)
#define RCU_RSSR_SW_MASK                                   (0x100U)
#define RCU_RSSR_SW_SHIFT                                  (8U)
#define RCU_RSSR_SW(x)                                     (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_SW_SHIFT)) & RCU_RSSR_SW_MASK)
#define RCU_RSSR_PIN_MASK                                  (0x2U)
#define RCU_RSSR_PIN_SHIFT                                 (1U)
#define RCU_RSSR_PIN(x)                                    (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_PIN_SHIFT)) & RCU_RSSR_PIN_MASK)
#define RCU_RSSR_POR_LVD_MASK                              (0x1U)
#define RCU_RSSR_POR_LVD_SHIFT                             (0U)
#define RCU_RSSR_POR_LVD(x)                                (((uint32_t)(((uint32_t)(x)) << RCU_RSSR_POR_LVD_SHIFT)) & RCU_RSSR_POR_LVD_MASK)
/* RCU_RPFR Register */
#define RCU_RPFR_RSTPIN_IBE_MASK                           (0x20000U)
#define RCU_RPFR_RSTPIN_IBE_SHIFT                          (17U)
#define RCU_RPFR_RSTPIN_IBE(x)                             (((uint32_t)(((uint32_t)(x)) << RCU_RPFR_RSTPIN_IBE_SHIFT)) & RCU_RPFR_RSTPIN_IBE_MASK)
#define RCU_RPFR_RSTPIN_OBEN_MASK                          (0x10000U)
#define RCU_RPFR_RSTPIN_OBEN_SHIFT                         (16U)
#define RCU_RPFR_RSTPIN_OBEN(x)                            (((uint32_t)(((uint32_t)(x)) << RCU_RPFR_RSTPIN_OBEN_SHIFT)) & RCU_RPFR_RSTPIN_OBEN_MASK)
#define RCU_RPFR_FLTVAL_MASK                               (0xFF00U)
#define RCU_RPFR_FLTVAL_SHIFT                              (8U)
#define RCU_RPFR_FLTVAL(x)                                 (((uint32_t)(((uint32_t)(x)) << RCU_RPFR_FLTVAL_SHIFT)) & RCU_RPFR_FLTVAL_MASK)
#define RCU_RPFR_FLTSTEN_MASK                              (0x2U)
#define RCU_RPFR_FLTSTEN_SHIFT                             (1U)
#define RCU_RPFR_FLTSTEN(x)                                (((uint32_t)(((uint32_t)(x)) << RCU_RPFR_FLTSTEN_SHIFT)) & RCU_RPFR_FLTSTEN_MASK)
#define RCU_RPFR_FLTEN_MASK                                (0x1U)
#define RCU_RPFR_FLTEN_SHIFT                               (0U)
#define RCU_RPFR_FLTEN(x)                                  (((uint32_t)(((uint32_t)(x)) << RCU_RPFR_FLTEN_SHIFT)) & RCU_RPFR_FLTEN_MASK)


/*!
 * @}
 */ /* end of group RCU_Register_Masks */


/*!
 * @}
 */ /* end of group RCU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- PCU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup PCU_Peripheral_Access_Layer PCU Peripheral Access Layer
 * @{
 */


/** PCU - Size of Registers Arrays */

/* PCU Register Layout Typedef */
typedef struct {
    __IO uint32_t SSTS;                               /**< Sticky Status Register, offset: 0x0000 */
    __IO uint32_t STS;                                /**< Status Register, offset: 0x0004 */
    __IO uint32_t INTE;                               /**< Interrupt Register, offset: 0x0008 */
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x000C */
    __IO uint32_t RESERVED_4;                         /**< RESERVED_4, offset: 0x0010 */
    __IO uint32_t RESERVED_5;                         /**< RESERVED_5, offset: 0x0014 */
    __IO uint32_t RESERVED_6;                         /**< RESERVED_6, offset: 0x0018 */
    __IO uint32_t RESERVED_7;                         /**< RESERVED_7, offset: 0x001C */

} PCU_Type, *PCU_MemMapPtr;

/** Number of instances of the PCU module. */
#define PCU_INSTANCE_COUNT                             (1u)

/* PCU base address */
#define PCU_BASE                                          (0x4007E000)
#define PCU                                               ((PCU_Type *)(PCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define PCU_MIRROR_BASE                                   (0x4007E800)
#define PCU_MIRROR                                        ((PCU_Type *)(PCU_MIRROR_BASE))

#define PCU_PPU_BASE                                      (0x4007E000)
#define PCU_PPU                                           ((PPU_Type *)(PCU_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of PCU peripheral base addresses */
#define PCU_BASE_ADDRS                                     { PCU_BASE }
/** Array initializer of PCU peripheral base pointers */
#define PCU_BASE_PTRS                                      { PCU }

/* PCU Register Mask */
/* PCU_SSTS Register */
#define PCU_SSTS_PORF_MASK                                 (0x80000000U)
#define PCU_SSTS_PORF_SHIFT                                (31U)
#define PCU_SSTS_PORF(x)                                   (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_PORF_SHIFT)) & PCU_SSTS_PORF_MASK)
#define PCU_SSTS_GNG11F_MASK                               (0x800000U)
#define PCU_SSTS_GNG11F_SHIFT                              (23U)
#define PCU_SSTS_GNG11F(x)                                 (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_GNG11F_SHIFT)) & PCU_SSTS_GNG11F_MASK)
#define PCU_SSTS_HVD11F_MASK                               (0x80000U)
#define PCU_SSTS_HVD11F_SHIFT                              (19U)
#define PCU_SSTS_HVD11F(x)                                 (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_HVD11F_SHIFT)) & PCU_SSTS_HVD11F_MASK)
#define PCU_SSTS_GNG25F_MASK                               (0x8000U)
#define PCU_SSTS_GNG25F_SHIFT                              (15U)
#define PCU_SSTS_GNG25F(x)                                 (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_GNG25F_SHIFT)) & PCU_SSTS_GNG25F_MASK)
#define PCU_SSTS_HVD25F_MASK                               (0x800U)
#define PCU_SSTS_HVD25F_SHIFT                              (11U)
#define PCU_SSTS_HVD25F(x)                                 (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_HVD25F_SHIFT)) & PCU_SSTS_HVD25F_MASK)
#define PCU_SSTS_HVD50F_MASK                               (0x8U)
#define PCU_SSTS_HVD50F_SHIFT                              (3U)
#define PCU_SSTS_HVD50F(x)                                 (((uint32_t)(((uint32_t)(x)) << PCU_SSTS_HVD50F_SHIFT)) & PCU_SSTS_HVD50F_MASK)
/* PCU_STS Register */
#define PCU_STS_HVD11S_MASK                                (0x80000U)
#define PCU_STS_HVD11S_SHIFT                               (19U)
#define PCU_STS_HVD11S(x)                                  (((uint32_t)(((uint32_t)(x)) << PCU_STS_HVD11S_SHIFT)) & PCU_STS_HVD11S_MASK)
#define PCU_STS_HVD25S_MASK                                (0x800U)
#define PCU_STS_HVD25S_SHIFT                               (11U)
#define PCU_STS_HVD25S(x)                                  (((uint32_t)(((uint32_t)(x)) << PCU_STS_HVD25S_SHIFT)) & PCU_STS_HVD25S_MASK)
#define PCU_STS_HVD50S_MASK                                (0x8U)
#define PCU_STS_HVD50S_SHIFT                               (3U)
#define PCU_STS_HVD50S(x)                                  (((uint32_t)(((uint32_t)(x)) << PCU_STS_HVD50S_SHIFT)) & PCU_STS_HVD50S_MASK)
/* PCU_INTE Register */
#define PCU_INTE_HVD11IE_MASK                              (0x80000U)
#define PCU_INTE_HVD11IE_SHIFT                             (19U)
#define PCU_INTE_HVD11IE(x)                                (((uint32_t)(((uint32_t)(x)) << PCU_INTE_HVD11IE_SHIFT)) & PCU_INTE_HVD11IE_MASK)
#define PCU_INTE_HVD25IE_MASK                              (0x800U)
#define PCU_INTE_HVD25IE_SHIFT                             (11U)
#define PCU_INTE_HVD25IE(x)                                (((uint32_t)(((uint32_t)(x)) << PCU_INTE_HVD25IE_SHIFT)) & PCU_INTE_HVD25IE_MASK)
#define PCU_INTE_HVD50IE_MASK                              (0x8U)
#define PCU_INTE_HVD50IE_SHIFT                             (3U)
#define PCU_INTE_HVD50IE(x)                                (((uint32_t)(((uint32_t)(x)) << PCU_INTE_HVD50IE_SHIFT)) & PCU_INTE_HVD50IE_MASK)
/* PCU_CTRL Register */
#define PCU_CTRL_HVDRE_MASK                                (0x8000U)
#define PCU_CTRL_HVDRE_SHIFT                               (15U)
#define PCU_CTRL_HVDRE(x)                                  (((uint32_t)(((uint32_t)(x)) << PCU_CTRL_HVDRE_SHIFT)) & PCU_CTRL_HVDRE_MASK)
#define PCU_CTRL_FASTREC_MASK                              (0x100U)
#define PCU_CTRL_FASTREC_SHIFT                             (8U)
#define PCU_CTRL_FASTREC(x)                                (((uint32_t)(((uint32_t)(x)) << PCU_CTRL_FASTREC_SHIFT)) & PCU_CTRL_FASTREC_MASK)
#define PCU_CTRL_STANDBYEN_MASK                            (0x2U)
#define PCU_CTRL_STANDBYEN_SHIFT                           (1U)
#define PCU_CTRL_STANDBYEN(x)                              (((uint32_t)(((uint32_t)(x)) << PCU_CTRL_STANDBYEN_SHIFT)) & PCU_CTRL_STANDBYEN_MASK)
#define PCU_CTRL_RPMEN_MASK                                (0x1U)
#define PCU_CTRL_RPMEN_SHIFT                               (0U)
#define PCU_CTRL_RPMEN(x)                                  (((uint32_t)(((uint32_t)(x)) << PCU_CTRL_RPMEN_SHIFT)) & PCU_CTRL_RPMEN_MASK)


/*!
 * @}
 */ /* end of group PCU_Register_Masks */


/*!
 * @}
 */ /* end of group PCU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- WKU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup WKU_Peripheral_Access_Layer WKU Peripheral Access Layer
 * @{
 */


/** WKU - Size of Registers Arrays */
#define WKU_PCR_COUNT                     (32)
#define WKU_PFR_COUNT                     (1)

/* WKU Register Layout Typedef */
typedef struct {
    __IO uint8_t PCR[32];                            /**< Pin Control Register, offset: 0x0000 */
    __IO uint32_t PFR[ 1];                            /**< Pin Flag Register, offset: 0x0020 */
    __IO uint32_t RPCR;                               /**< Reset Pin Control Register, offset: 0x0024 */
    __IO uint32_t MER;                                /**< Module Enable Register, offset: 0x0028 */

} WKU_Type, *WKU_MemMapPtr;

/** Number of instances of the WKU module. */
#define WKU_INSTANCE_COUNT                             (1u)

/* WKU base address */
#define WKU_BASE                                          (0x40062000)
#define WKU                                               ((WKU_Type *)(WKU_BASE))

/** Array initializer of WKU peripheral base addresses */
#define WKU_BASE_ADDRS                                     { WKU_BASE }
/** Array initializer of WKU peripheral base pointers */
#define WKU_BASE_PTRS                                      { WKU }

/* WKU Register Mask */
/* WKU_PCR Register */
#define WKU_PCR_WUPIE_MASK                                 (0x10U)
#define WKU_PCR_WUPIE_SHIFT                                (4U)
#define WKU_PCR_WUPIE(x)                                   (((uint32_t)(((uint32_t)(x)) << WKU_PCR_WUPIE_SHIFT)) & WKU_PCR_WUPIE_MASK)
#define WKU_PCR_WUPFS_MASK                                 (0x8U)
#define WKU_PCR_WUPFS_SHIFT                                (3U)
#define WKU_PCR_WUPFS(x)                                   (((uint32_t)(((uint32_t)(x)) << WKU_PCR_WUPFS_SHIFT)) & WKU_PCR_WUPFS_MASK)
#define WKU_PCR_WUPFE_MASK                                 (0x4U)
#define WKU_PCR_WUPFE_SHIFT                                (2U)
#define WKU_PCR_WUPFE(x)                                   (((uint32_t)(((uint32_t)(x)) << WKU_PCR_WUPFE_SHIFT)) & WKU_PCR_WUPFE_MASK)
#define WKU_PCR_WUPE_MASK                                  (0x3U)
#define WKU_PCR_WUPE_SHIFT                                 (0U)
#define WKU_PCR_WUPE(x)                                    (((uint32_t)(((uint32_t)(x)) << WKU_PCR_WUPE_SHIFT)) & WKU_PCR_WUPE_MASK)
/* WKU_PFR Register */
#define WKU_PFR_WUF_WIDTH                                  (32)
#define WKU_PFR_WUF_MASK                                   (0xFFFFFFFFU)
#define WKU_PFR_WUF_SHIFT                                  (0U)
#define WKU_PFR_WUF(x)                                     (((uint32_t)(((uint32_t)(x)) << WKU_PFR_WUF_SHIFT)) & WKU_PFR_WUF_MASK)
/* WKU_RPCR Register */
#define WKU_RPCR_WURPFS_MASK                               (0x8U)
#define WKU_RPCR_WURPFS_SHIFT                              (3U)
#define WKU_RPCR_WURPFS(x)                                 (((uint32_t)(((uint32_t)(x)) << WKU_RPCR_WURPFS_SHIFT)) & WKU_RPCR_WURPFS_MASK)
#define WKU_RPCR_WURPFE_MASK                               (0x4U)
#define WKU_RPCR_WURPFE_SHIFT                              (2U)
#define WKU_RPCR_WURPFE(x)                                 (((uint32_t)(((uint32_t)(x)) << WKU_RPCR_WURPFE_SHIFT)) & WKU_RPCR_WURPFE_MASK)
#define WKU_RPCR_WURPE_MASK                                (0x1U)
#define WKU_RPCR_WURPE_SHIFT                               (0U)
#define WKU_RPCR_WURPE(x)                                  (((uint32_t)(((uint32_t)(x)) << WKU_RPCR_WURPE_SHIFT)) & WKU_RPCR_WURPE_MASK)
/* WKU_MER Register */
#define WKU_MER_WUME_WIDTH                                 (4)
#define WKU_MER_WUME_MASK                                  (0xFU)
#define WKU_MER_WUME_SHIFT                                 (0U)
#define WKU_MER_WUME(x)                                    (((uint32_t)(((uint32_t)(x)) << WKU_MER_WUME_SHIFT)) & WKU_MER_WUME_MASK)


/*!
 * @}
 */ /* end of group WKU_Register_Masks */


/*!
 * @}
 */ /* end of group WKU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- CAN Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 * @{
 */


/** CAN - Size of Registers Arrays */
#define CAN_RAM_COUNT                     (256)
#define CAN_RXIMR_COUNT                     (64)
#define CAN_WMB_COUNT                     (4)
#define CAN_HR_TIME_STAMPn_COUNT                     (128)
#define CAN_ERFFELn_COUNT                     (128)

/* CAN Register Layout Typedef */
typedef struct {
    __IO uint32_t MCR;                                /**< Module Configuration Register, offset: 0x0000 */
    __IO uint32_t CTRL1;                              /**< Countrol 1 Register, offset: 0x0004 */
    __IO uint32_t TIMER;                              /**< Free Running Timer Register, offset: 0x0008 */
    __IO uint32_t RESERVED0[ 1];                      /**< RESERVED0, offset: 0x000C */
    __IO uint32_t RXMGMASK;                           /**< Rx Mailboxes Global Mask Register, offset: 0x0010 */
    __IO uint32_t RX14MASK;                           /**< Rx 14 Mask Register, offset: 0x0014 */
    __IO uint32_t RX15MASK;                           /**< Rx 15 Mask Register, offset: 0x0018 */
    __IO uint32_t ECR;                                /**< Error Counter Register, offset: 0x001C */
    __IO uint32_t ESR1;                               /**< Error and Status Register, offset: 0x0020 */
    __IO uint32_t IMASK2;                             /**< Interrupt Mask 2 Register, offset: 0x0024 */
    __IO uint32_t IMASK1;                             /**< Interrupt Mask 1 Register, offset: 0x0028 */
    __IO uint32_t IFLAG2;                             /**< Interrupt Flag 2 Register, offset: 0x002C */
    __IO uint32_t IFLAG1;                             /**< Interrupt Flag 1 Register, offset: 0x0030 */
    __IO uint32_t CTRL2;                              /**< Control 2 Register, offset: 0x0034 */
    __IO uint32_t ESR2;                               /**< Error and Status 2 Register, offset: 0x0038 */
    __IO uint32_t RESERVED1[ 2];                      /**< RESERVED1, offset: 0x003C */
    __IO uint32_t CRCR;                               /**< CRC Register, offset: 0x0044 */
    __IO uint32_t RXFGMASK;                           /**< Legacy Rx FIFO Global Mask Register, offset: 0x0048 */
    __IO uint32_t RXFIR;                              /**< Legacy Rx FIFO Information Register, offset: 0x004C */
    __IO uint32_t CBT;                                /**< Bit Timing Register, offset: 0x0050 */
    __IO uint32_t RESERVED2[ 5];                      /**< RESERVED2, offset: 0x0054 */
    __IO uint32_t IMASK4;                             /**< Interrupt Mask 4 Register, offset: 0x0068 */
    __IO uint32_t IMASK3;                             /**< Interrupt Mask 3 Register, offset: 0x006C */
    __IO uint32_t IFLAG4;                             /**< Interrupt Flags 4 Register, offset: 0x0070 */
    __IO uint32_t IFLAG3;                             /**< Interrupt Flags 3 Register, offset: 0x0074 */
    __IO uint32_t RESERVED3[ 2];                      /**< RESERVED3, offset: 0x0078 */
    __IO uint32_t RAM[256];                            /**< Embeded RAM, offset: 0x0080 */
    __IO uint32_t RESERVED4[256];                      /**< RESERVED4, offset: 0x0480 */
    __IO uint32_t RXIMR[64];                          /**< RX Individual Mask Register, offset: 0x0880 */
    __IO uint32_t RESERVED5[88];                      /**< RESERVED5, offset: 0x0980 */
    __IO uint32_t MECR;                               /**< Memory Error Control Register, offset: 0x0AE0 */
    __IO uint32_t ERRIAR;                             /**< Error Injection Address Register, offset: 0x0AE4 */
    __IO uint32_t ERRIDPR;                            /**< Error Injection Data Pattern Register, offset: 0x0AE8 */
    __IO uint32_t ERRIPPR;                            /**< Error Injection Parity Pattern Register, offset: 0x0AEC */
    __IO uint32_t RERRAR;                             /**< Error Report Address Register, offset: 0x0AF0 */
    __IO uint32_t RERRDR;                             /**< Error Report Data Register, offset: 0x0AF4 */
    __IO uint32_t RERRSYNR;                           /**< Error Report Syndrome Register, offset: 0x0AF8 */
    __IO uint32_t ERRSR;                              /**< Error Status Register, offset: 0x0AFC */
    __IO uint32_t CTRL1_PN;                           /**< Pretended Networking Control 1 Register, offset: 0x0B00 */
    __IO uint32_t CTRL2_PN;                           /**< Pretended Networking Control 2 Register, offset: 0x0B04 */
    __IO uint32_t WU_MTC;                             /**< Pretended Networking Wake Up Match Register, offset: 0x0B08 */
    __IO uint32_t FLT_ID1;                            /**< Pretended Networking ID Filter 1 Register, offset: 0x0B0C */
    __IO uint32_t FLT_DLC;                            /**< Pretended Networking DLC Filter Register, offset: 0x0B10 */
    __IO uint32_t PL1_LO;                             /**< Pretended Networking Payload Low Filter 1 Register, offset: 0x0B14 */
    __IO uint32_t PL1_HI;                             /**< Pretended Networking Payload High Filter 1 Register, offset: 0x0B18 */
    __IO uint32_t FLT_ID2_IDMASK;                     /**< Pretended Networking ID Filter 2 Register, offset: 0x0B1C */
    __IO uint32_t PL2_PLMASK_LO;                      /**< Pretended Networking Payload Low Filter 2 Register, offset: 0x0B20 */
    __IO uint32_t PL2_PLMASK_HI;                      /**< Pretended Networking Payload High Filter 2 Register, offset: 0x0B24 */
    __IO uint32_t RESERVED6[ 6];                      /**< RESERVED6, offset: 0x0B28 */
    struct {
        __IO uint32_t WMBn_CS;                            /**< , offset: 0x0B40 */
        __IO uint32_t WMBn_ID;                            /**< , offset: 0x0B44 */
        __IO uint32_t WMBn_D03;                           /**< , offset: 0x0B48 */
        __IO uint32_t WMBn_D47;                           /**< , offset: 0x0B4C */

    } WMB[4];
    __IO uint32_t RESERVED7[28];                      /**< RESERVED7, offset: 0x0B80 */
    __IO uint32_t EPRS;                               /**< Enhanced CAN Bit Timing Prescalers Register, offset: 0x0BF0 */
    __IO uint32_t ENCBT;                              /**< Enhanced Nominal CAN Bit Timing Register, offset: 0x0BF4 */
    __IO uint32_t EDCBT;                              /**< Enhanced Data Phase CAN Bit Timing Register, offset: 0x0BF8 */
    __IO uint32_t ETDC;                               /**< Enhanced Transceiver Delay Compensation Register, offset: 0x0BFC */
    __IO uint32_t FDCTRL;                             /**< FD Control Register, offset: 0x0C00 */
    __IO uint32_t FDCBT;                              /**< FD Bit Timing Register, offset: 0x0C04 */
    __IO uint32_t FDCRC;                              /**< FD CRC Register, offset: 0x0C08 */
    __IO uint32_t ERFCR;                              /**< Enhanced Rx FIFO Control Register, offset: 0x0C0C */
    __IO uint32_t ERFIER;                             /**< Enhanced Rx FIFO Interrupt Enable Register, offset: 0x0C10 */
    __IO uint32_t ERFSR;                              /**< Enhanced Rx FIFO Status Register, offset: 0x0C14 */
    __IO uint32_t RESERVED8[ 6];                      /**< RESERVED8, offset: 0x0C18 */
    __IO uint32_t HR_TIME_STAMPn[128];                 /**< High Resolution Time Stamp Registers, offset: 0x0C30 */
    __IO uint32_t RESERVED9[2164];                      /**< RESERVED9, offset: 0x0E30 */
    __IO uint32_t ERFFELn[128];                        /**< Enhanced Rx FIFO Filter Element Registers, offset: 0x3000 */

} CAN_Type, *CAN_MemMapPtr;

/** Number of instances of the CAN module. */
#define CAN_INSTANCE_COUNT                             (6u)

/* CAN0  base address */
#define CAN0_BASE                                          (0x40030000)
#define CAN0                                               ((CAN_Type *)(CAN0_BASE))
/* CAN1  base address */
#define CAN1_BASE                                          (0x40034000)
#define CAN1                                               ((CAN_Type *)(CAN1_BASE))
/* CAN2  base address */
#define CAN2_BASE                                          (0x40038000)
#define CAN2                                               ((CAN_Type *)(CAN2_BASE))
/* CAN3  base address */
#define CAN3_BASE                                          (0x4003C000)
#define CAN3                                               ((CAN_Type *)(CAN3_BASE))
/* CAN4  base address */
#define CAN4_BASE                                          (0x4003D000)
#define CAN4                                               ((CAN_Type *)(CAN4_BASE))
/* CAN5  base address */
#define CAN5_BASE                                          (0x4003E000)
#define CAN5                                               ((CAN_Type *)(CAN5_BASE))

/** Array initializer of CAN peripheral base addresses */
#define CAN_BASE_ADDRS                                     { CAN0_BASE,  CAN1_BASE,  CAN2_BASE,  CAN3_BASE,  CAN4_BASE,  CAN5_BASE }
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                                      { CAN0,  CAN1,  CAN2,  CAN3,  CAN4,  CAN5 }
/** Number of interrupt vector arrays for the CAN module. */
#define CAN_IRQS_ARR_COUNT                                 (7u)
/** Number of interrupt channels for the Rx Waring IRQS type of CAN. */
#define CAN_RX_Warning_IRQS_CH_COUNT              (6u)
#define CAN_RX_Warning_IRQS                       { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn, CAN3_ORed_IRQn, CAN4_ORed_IRQn, CAN5_ORed_IRQn }
/** Number of interrupt channels for the Tx Waring IRQS type of CAN. */
#define CAN_TX_Warning_IRQS_CH_COUNT              (6u)
#define CAN_TX_Warning_IRQS                       { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn, CAN3_ORed_IRQn, CAN4_ORed_IRQn, CAN5_ORed_IRQn }
/** Number of interrupt channels for the Error IRQS type of CAN. */
#define CAN_Error_IRQS_CH_COUNT                   (6u)
#define CAN_Error_IRQS                            { CAN0_Error_IRQn, CAN1_Error_IRQn, CAN2_Error_IRQn, CAN3_Error_IRQn, CAN4_Error_IRQn, CAN5_Error_IRQn }
/** Number of interrupt channels for the Bus Off IRQS type of CAN. */
#define CAN_Bus_Off_IRQS_CH_COUNT                 (6u)
#define CAN_Bus_Off_IRQS                          { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn, CAN3_ORed_IRQn, CAN4_ORed_IRQn, CAN5_ORed_IRQn }
/** Number of interrupt channels for the Wake Up IRQS type of CAN. */
#define CAN_Wake_Up_IRQS_CH_COUNT                 (6u)
#define CAN_Wake_Up_IRQS                          { CAN0_Wake_Up_IRQn, CAN1_Wake_Up_IRQn, CAN2_Wake_Up_IRQn, CAN3_Wake_Up_IRQn, CAN4_Wake_Up_IRQn, CAN5_Wake_Up_IRQn }
/** Number of interrupt channels for the Mailbox buffer 0 - 15 type of CAN. */
#define CAN_ORed_0_15_MB_IRQS_CH_COUNT            (6u)
#define CAN_ORed_0_15_MB_IRQS                     { CAN0_ORed_0_15_MB_IRQn, CAN1_ORed_0_15_MB_IRQn, CAN2_ORed_0_15_MB_IRQn, CAN3_ORed_0_15_MB_IRQn, CAN4_ORed_0_15_MB_IRQn, CAN5_ORed_0_15_MB_IRQn }
/** Number of interrupt channels for the Mailbox buffer 16 - 31 type of CAN. */
#define CAN_ORed_16_31_MB_IRQS_CH_COUNT           (6u)
#define CAN_ORed_16_31_MB_IRQS                    { CAN0_ORed_16_31_MB_IRQn, CAN1_ORed_16_31_MB_IRQn, CAN2_ORed_16_31_MB_IRQn, CAN3_ORed_16_31_MB_IRQn, CAN4_ORed_16_31_MB_IRQn, CAN5_ORed_16_31_MB_IRQn }
/** Number of interrupt channels for the Mailbox buffer 32 - 47 type of CAN. */
#define CAN_ORed_32_47_MB_IRQS_CH_COUNT           (3u)
#define CAN_ORed_32_47_MB_IRQS                    { CAN0_ORed_32_47_MB_IRQn, CAN1_ORed_32_47_MB_IRQn, CAN2_ORed_32_47_MB_IRQn }
/** Number of interrupt channels for the Mailbox buffer 48 - 64 type of CAN. */
#define CAN_ORed_48_63_MB_IRQS_CH_COUNT           (3u)
#define CAN_ORed_48_63_MB_IRQS                    { CAN0_ORed_48_63_MB_IRQn, CAN1_ORed_48_63_MB_IRQn, CAN2_ORed_48_63_MB_IRQn }

/* CAN Register Mask */
/* CAN_MCR Register */
#define CAN_MCR_MDIS_MASK                                  (0x80000000U)
#define CAN_MCR_MDIS_SHIFT                                 (31U)
#define CAN_MCR_MDIS(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_MDIS_SHIFT)) & CAN_MCR_MDIS_MASK)
#define CAN_MCR_FRZ_MASK                                   (0x40000000U)
#define CAN_MCR_FRZ_SHIFT                                  (30U)
#define CAN_MCR_FRZ(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_MCR_FRZ_SHIFT)) & CAN_MCR_FRZ_MASK)
#define CAN_MCR_RFEN_MASK                                  (0x20000000U)
#define CAN_MCR_RFEN_SHIFT                                 (29U)
#define CAN_MCR_RFEN(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_RFEN_SHIFT)) & CAN_MCR_RFEN_MASK)
#define CAN_MCR_HALT_MASK                                  (0x10000000U)
#define CAN_MCR_HALT_SHIFT                                 (28U)
#define CAN_MCR_HALT(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_HALT_SHIFT)) & CAN_MCR_HALT_MASK)
#define CAN_MCR_NOTRDY_MASK                                (0x8000000U)
#define CAN_MCR_NOTRDY_SHIFT                               (27U)
#define CAN_MCR_NOTRDY(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_NOTRDY_SHIFT)) & CAN_MCR_NOTRDY_MASK)
#define CAN_MCR_WAKMSK_MASK                                (0x4000000U)
#define CAN_MCR_WAKMSK_SHIFT                               (26U)
#define CAN_MCR_WAKMSK(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WAKMSK_SHIFT)) & CAN_MCR_WAKMSK_MASK)
#define CAN_MCR_SOFTRST_MASK                               (0x2000000U)
#define CAN_MCR_SOFTRST_SHIFT                              (25U)
#define CAN_MCR_SOFTRST(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SOFTRST_SHIFT)) & CAN_MCR_SOFTRST_MASK)
#define CAN_MCR_FRZACK_MASK                                (0x1000000U)
#define CAN_MCR_FRZACK_SHIFT                               (24U)
#define CAN_MCR_FRZACK(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_FRZACK_SHIFT)) & CAN_MCR_FRZACK_MASK)
#define CAN_MCR_SUPV_MASK                                  (0x800000U)
#define CAN_MCR_SUPV_SHIFT                                 (23U)
#define CAN_MCR_SUPV(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SUPV_SHIFT)) & CAN_MCR_SUPV_MASK)
#define CAN_MCR_SLFWAK_MASK                                (0x400000U)
#define CAN_MCR_SLFWAK_SHIFT                               (22U)
#define CAN_MCR_SLFWAK(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SLFWAK_SHIFT)) & CAN_MCR_SLFWAK_MASK)
#define CAN_MCR_WRNEN_MASK                                 (0x200000U)
#define CAN_MCR_WRNEN_SHIFT                                (21U)
#define CAN_MCR_WRNEN(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WRNEN_SHIFT)) & CAN_MCR_WRNEN_MASK)
#define CAN_MCR_LPMACK_MASK                                (0x100000U)
#define CAN_MCR_LPMACK_SHIFT                               (20U)
#define CAN_MCR_LPMACK(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_LPMACK_SHIFT)) & CAN_MCR_LPMACK_MASK)
#define CAN_MCR_WAKSRC_MASK                                (0x80000U)
#define CAN_MCR_WAKSRC_SHIFT                               (19U)
#define CAN_MCR_WAKSRC(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_WAKSRC_SHIFT)) & CAN_MCR_WAKSRC_MASK)
#define CAN_MCR_DOZE_MASK                                  (0x40000U)
#define CAN_MCR_DOZE_SHIFT                                 (18U)
#define CAN_MCR_DOZE(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_DOZE_SHIFT)) & CAN_MCR_DOZE_MASK)
#define CAN_MCR_SRXDIS_MASK                                (0x20000U)
#define CAN_MCR_SRXDIS_SHIFT                               (17U)
#define CAN_MCR_SRXDIS(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_MCR_SRXDIS_SHIFT)) & CAN_MCR_SRXDIS_MASK)
#define CAN_MCR_IRMQ_MASK                                  (0x10000U)
#define CAN_MCR_IRMQ_SHIFT                                 (16U)
#define CAN_MCR_IRMQ(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_IRMQ_SHIFT)) & CAN_MCR_IRMQ_MASK)
#define CAN_MCR_DMA_MASK                                   (0x8000U)
#define CAN_MCR_DMA_SHIFT                                  (15U)
#define CAN_MCR_DMA(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_MCR_DMA_SHIFT)) & CAN_MCR_DMA_MASK)
#define CAN_MCR_PNET_EN_MASK                               (0x4000U)
#define CAN_MCR_PNET_EN_SHIFT                              (14U)
#define CAN_MCR_PNET_EN(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_MCR_PNET_EN_SHIFT)) & CAN_MCR_PNET_EN_MASK)
#define CAN_MCR_LPRIOEN_MASK                               (0x2000U)
#define CAN_MCR_LPRIOEN_SHIFT                              (13U)
#define CAN_MCR_LPRIOEN(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_MCR_LPRIOEN_SHIFT)) & CAN_MCR_LPRIOEN_MASK)
#define CAN_MCR_AEN_MASK                                   (0x1000U)
#define CAN_MCR_AEN_SHIFT                                  (12U)
#define CAN_MCR_AEN(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_MCR_AEN_SHIFT)) & CAN_MCR_AEN_MASK)
#define CAN_MCR_FDEN_MASK                                  (0x800U)
#define CAN_MCR_FDEN_SHIFT                                 (11U)
#define CAN_MCR_FDEN(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_FDEN_SHIFT)) & CAN_MCR_FDEN_MASK)
#define CAN_MCR_IDAM_MASK                                  (0x300U)
#define CAN_MCR_IDAM_SHIFT                                 (8U)
#define CAN_MCR_IDAM(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_MCR_IDAM_SHIFT)) & CAN_MCR_IDAM_MASK)
#define CAN_MCR_MAXMB_MASK                                 (0x7FU)
#define CAN_MCR_MAXMB_SHIFT                                (0U)
#define CAN_MCR_MAXMB(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_MCR_MAXMB_SHIFT)) & CAN_MCR_MAXMB_MASK)
/* CAN_CTRL1 Register */
#define CAN_CTRL1_PRESDIV_MASK                             (0xFF000000U)
#define CAN_CTRL1_PRESDIV_SHIFT                            (24U)
#define CAN_CTRL1_PRESDIV(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PRESDIV_SHIFT)) & CAN_CTRL1_PRESDIV_MASK)
#define CAN_CTRL1_RJW_MASK                                 (0xC00000U)
#define CAN_CTRL1_RJW_SHIFT                                (22U)
#define CAN_CTRL1_RJW(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_RJW_SHIFT)) & CAN_CTRL1_RJW_MASK)
#define CAN_CTRL1_PSEG1_MASK                               (0x380000U)
#define CAN_CTRL1_PSEG1_SHIFT                              (19U)
#define CAN_CTRL1_PSEG1(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PSEG1_SHIFT)) & CAN_CTRL1_PSEG1_MASK)
#define CAN_CTRL1_PSEG2_MASK                               (0x70000U)
#define CAN_CTRL1_PSEG2_SHIFT                              (16U)
#define CAN_CTRL1_PSEG2(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PSEG2_SHIFT)) & CAN_CTRL1_PSEG2_MASK)
#define CAN_CTRL1_BOFFMSK_MASK                             (0x8000U)
#define CAN_CTRL1_BOFFMSK_SHIFT                            (15U)
#define CAN_CTRL1_BOFFMSK(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_BOFFMSK_SHIFT)) & CAN_CTRL1_BOFFMSK_MASK)
#define CAN_CTRL1_ERRMSK_MASK                              (0x4000U)
#define CAN_CTRL1_ERRMSK_SHIFT                             (14U)
#define CAN_CTRL1_ERRMSK(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_ERRMSK_SHIFT)) & CAN_CTRL1_ERRMSK_MASK)
#define CAN_CTRL1_CLKSRC_MASK                              (0x2000U)
#define CAN_CTRL1_CLKSRC_SHIFT                             (13U)
#define CAN_CTRL1_CLKSRC(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_CLKSRC_SHIFT)) & CAN_CTRL1_CLKSRC_MASK)
#define CAN_CTRL1_LPB_MASK                                 (0x1000U)
#define CAN_CTRL1_LPB_SHIFT                                (12U)
#define CAN_CTRL1_LPB(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LPB_SHIFT)) & CAN_CTRL1_LPB_MASK)
#define CAN_CTRL1_TWRNMSK_MASK                             (0x800U)
#define CAN_CTRL1_TWRNMSK_SHIFT                            (11U)
#define CAN_CTRL1_TWRNMSK(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_TWRNMSK_SHIFT)) & CAN_CTRL1_TWRNMSK_MASK)
#define CAN_CTRL1_RWRNMSK_MASK                             (0x400U)
#define CAN_CTRL1_RWRNMSK_SHIFT                            (10U)
#define CAN_CTRL1_RWRNMSK(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_RWRNMSK_SHIFT)) & CAN_CTRL1_RWRNMSK_MASK)
#define CAN_CTRL1_SMP_MASK                                 (0x80U)
#define CAN_CTRL1_SMP_SHIFT                                (7U)
#define CAN_CTRL1_SMP(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_SMP_SHIFT)) & CAN_CTRL1_SMP_MASK)
#define CAN_CTRL1_BOFFREC_MASK                             (0x40U)
#define CAN_CTRL1_BOFFREC_SHIFT                            (6U)
#define CAN_CTRL1_BOFFREC(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_BOFFREC_SHIFT)) & CAN_CTRL1_BOFFREC_MASK)
#define CAN_CTRL1_TSYN_MASK                                (0x20U)
#define CAN_CTRL1_TSYN_SHIFT                               (5U)
#define CAN_CTRL1_TSYN(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_TSYN_SHIFT)) & CAN_CTRL1_TSYN_MASK)
#define CAN_CTRL1_LBUF_MASK                                (0x10U)
#define CAN_CTRL1_LBUF_SHIFT                               (4U)
#define CAN_CTRL1_LBUF(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LBUF_SHIFT)) & CAN_CTRL1_LBUF_MASK)
#define CAN_CTRL1_LOM_MASK                                 (0x8U)
#define CAN_CTRL1_LOM_SHIFT                                (3U)
#define CAN_CTRL1_LOM(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_LOM_SHIFT)) & CAN_CTRL1_LOM_MASK)
#define CAN_CTRL1_PROPSEG_MASK                             (0x7U)
#define CAN_CTRL1_PROPSEG_SHIFT                            (0U)
#define CAN_CTRL1_PROPSEG(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PROPSEG_SHIFT)) & CAN_CTRL1_PROPSEG_MASK)
/* CAN_TIMER Register */
#define CAN_TIMER_TIMER_MASK                               (0xFFFFU)
#define CAN_TIMER_TIMER_SHIFT                              (0U)
#define CAN_TIMER_TIMER(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_TIMER_TIMER_SHIFT)) & CAN_TIMER_TIMER_MASK)
/* CAN_RXMGMASK Register */
#define CAN_RXMGMASK_MG_MASK                               (0xFFFFFFFFU)
#define CAN_RXMGMASK_MG_SHIFT                              (0U)
#define CAN_RXMGMASK_MG(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_RXMGMASK_MG_SHIFT)) & CAN_RXMGMASK_MG_MASK)
/* CAN_RX14MASK Register */
#define CAN_RX14MASK_RX14M_MASK                            (0xFFFFFFFFU)
#define CAN_RX14MASK_RX14M_SHIFT                           (0U)
#define CAN_RX14MASK_RX14M(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RX14MASK_RX14M_SHIFT)) & CAN_RX14MASK_RX14M_MASK)
/* CAN_RX15MASK Register */
#define CAN_RX15MASK_RX15M_MASK                            (0xFFFFFFFFU)
#define CAN_RX15MASK_RX15M_SHIFT                           (0U)
#define CAN_RX15MASK_RX15M(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RX15MASK_RX15M_SHIFT)) & CAN_RX15MASK_RX15M_MASK)
/* CAN_ECR Register */
#define CAN_ECR_RXERRCNT_FAST_MASK                         (0xFF000000U)
#define CAN_ECR_RXERRCNT_FAST_SHIFT                        (24U)
#define CAN_ECR_RXERRCNT_FAST(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_RXERRCNT_FAST_SHIFT)) & CAN_ECR_RXERRCNT_FAST_MASK)
#define CAN_ECR_TXERRCNT_FAST_MASK                         (0xFF0000U)
#define CAN_ECR_TXERRCNT_FAST_SHIFT                        (16U)
#define CAN_ECR_TXERRCNT_FAST(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ECR_TXERRCNT_FAST_SHIFT)) & CAN_ECR_TXERRCNT_FAST_MASK)
#define CAN_ECR_RXERRCNT_MASK                              (0xFF00U)
#define CAN_ECR_RXERRCNT_SHIFT                             (8U)
#define CAN_ECR_RXERRCNT(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ECR_RXERRCNT_SHIFT)) & CAN_ECR_RXERRCNT_MASK)
#define CAN_ECR_TXERRCNT_MASK                              (0xFFU)
#define CAN_ECR_TXERRCNT_SHIFT                             (0U)
#define CAN_ECR_TXERRCNT(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ECR_TXERRCNT_SHIFT)) & CAN_ECR_TXERRCNT_MASK)
/* CAN_ESR1 Register */
#define CAN_ESR1_BIT1ERR_FAST_MASK                         (0x80000000U)
#define CAN_ESR1_BIT1ERR_FAST_SHIFT                        (31U)
#define CAN_ESR1_BIT1ERR_FAST(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT1ERR_FAST_SHIFT)) & CAN_ESR1_BIT1ERR_FAST_MASK)
#define CAN_ESR1_BIT0ERR_FAST_MASK                         (0x40000000U)
#define CAN_ESR1_BIT0ERR_FAST_SHIFT                        (30U)
#define CAN_ESR1_BIT0ERR_FAST(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT0ERR_FAST_SHIFT)) & CAN_ESR1_BIT0ERR_FAST_MASK)
#define CAN_ESR1_CRCERR_FAST_MASK                          (0x10000000U)
#define CAN_ESR1_CRCERR_FAST_SHIFT                         (28U)
#define CAN_ESR1_CRCERR_FAST(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_CRCERR_FAST_SHIFT)) & CAN_ESR1_CRCERR_FAST_MASK)
#define CAN_ESR1_FRMERR_FAST_MASK                          (0x8000000U)
#define CAN_ESR1_FRMERR_FAST_SHIFT                         (27U)
#define CAN_ESR1_FRMERR_FAST(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_FRMERR_FAST_SHIFT)) & CAN_ESR1_FRMERR_FAST_MASK)
#define CAN_ESR1_STFERR_FAST_MASK                          (0x4000000U)
#define CAN_ESR1_STFERR_FAST_SHIFT                         (26U)
#define CAN_ESR1_STFERR_FAST(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_STFERR_FAST_SHIFT)) & CAN_ESR1_STFERR_FAST_MASK)
#define CAN_ESR1_ERROVR_MASK                               (0x200000U)
#define CAN_ESR1_ERROVR_SHIFT                              (21U)
#define CAN_ESR1_ERROVR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ERROVR_SHIFT)) & CAN_ESR1_ERROVR_MASK)
#define CAN_ESR1_ERRINT_FAST_MASK                          (0x100000U)
#define CAN_ESR1_ERRINT_FAST_SHIFT                         (20U)
#define CAN_ESR1_ERRINT_FAST(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ERRINT_FAST_SHIFT)) & CAN_ESR1_ERRINT_FAST_MASK)
#define CAN_ESR1_BOFFDONEINT_MASK                          (0x80000U)
#define CAN_ESR1_BOFFDONEINT_SHIFT                         (19U)
#define CAN_ESR1_BOFFDONEINT(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BOFFDONEINT_SHIFT)) & CAN_ESR1_BOFFDONEINT_MASK)
#define CAN_ESR1_SYNCH_MASK                                (0x40000U)
#define CAN_ESR1_SYNCH_SHIFT                               (18U)
#define CAN_ESR1_SYNCH(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_SYNCH_SHIFT)) & CAN_ESR1_SYNCH_MASK)
#define CAN_ESR1_TWRNINT_MASK                              (0x20000U)
#define CAN_ESR1_TWRNINT_SHIFT                             (17U)
#define CAN_ESR1_TWRNINT(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TWRNINT_SHIFT)) & CAN_ESR1_TWRNINT_MASK)
#define CAN_ESR1_RWRNINT_MASK                              (0x10000U)
#define CAN_ESR1_RWRNINT_SHIFT                             (16U)
#define CAN_ESR1_RWRNINT(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RWRNINT_SHIFT)) & CAN_ESR1_RWRNINT_MASK)
#define CAN_ESR1_BIT1ERR_MASK                              (0x8000U)
#define CAN_ESR1_BIT1ERR_SHIFT                             (15U)
#define CAN_ESR1_BIT1ERR(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT1ERR_SHIFT)) & CAN_ESR1_BIT1ERR_MASK)
#define CAN_ESR1_BIT0ERR_MASK                              (0x4000U)
#define CAN_ESR1_BIT0ERR_SHIFT                             (14U)
#define CAN_ESR1_BIT0ERR(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BIT0ERR_SHIFT)) & CAN_ESR1_BIT0ERR_MASK)
#define CAN_ESR1_ACKERR_MASK                               (0x2000U)
#define CAN_ESR1_ACKERR_SHIFT                              (13U)
#define CAN_ESR1_ACKERR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ACKERR_SHIFT)) & CAN_ESR1_ACKERR_MASK)
#define CAN_ESR1_CRCERR_MASK                               (0x1000U)
#define CAN_ESR1_CRCERR_SHIFT                              (12U)
#define CAN_ESR1_CRCERR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_CRCERR_SHIFT)) & CAN_ESR1_CRCERR_MASK)
#define CAN_ESR1_FRMERR_MASK                               (0x800U)
#define CAN_ESR1_FRMERR_SHIFT                              (11U)
#define CAN_ESR1_FRMERR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_FRMERR_SHIFT)) & CAN_ESR1_FRMERR_MASK)
#define CAN_ESR1_STFERR_MASK                               (0x400U)
#define CAN_ESR1_STFERR_SHIFT                              (10U)
#define CAN_ESR1_STFERR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_STFERR_SHIFT)) & CAN_ESR1_STFERR_MASK)
#define CAN_ESR1_TXWRN_MASK                                (0x200U)
#define CAN_ESR1_TXWRN_SHIFT                               (9U)
#define CAN_ESR1_TXWRN(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TXWRN_SHIFT)) & CAN_ESR1_TXWRN_MASK)
#define CAN_ESR1_RXWRN_MASK                                (0x100U)
#define CAN_ESR1_RXWRN_SHIFT                               (8U)
#define CAN_ESR1_RXWRN(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RXWRN_SHIFT)) & CAN_ESR1_RXWRN_MASK)
#define CAN_ESR1_IDLE_MASK                                 (0x80U)
#define CAN_ESR1_IDLE_SHIFT                                (7U)
#define CAN_ESR1_IDLE(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_IDLE_SHIFT)) & CAN_ESR1_IDLE_MASK)
#define CAN_ESR1_TX_MASK                                   (0x40U)
#define CAN_ESR1_TX_SHIFT                                  (6U)
#define CAN_ESR1_TX(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_TX_SHIFT)) & CAN_ESR1_TX_MASK)
#define CAN_ESR1_FLTCONF_MASK                              (0x30U)
#define CAN_ESR1_FLTCONF_SHIFT                             (4U)
#define CAN_ESR1_FLTCONF(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_FLTCONF_SHIFT)) & CAN_ESR1_FLTCONF_MASK)
#define CAN_ESR1_RX_MASK                                   (0x8U)
#define CAN_ESR1_RX_SHIFT                                  (3U)
#define CAN_ESR1_RX(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_RX_SHIFT)) & CAN_ESR1_RX_MASK)
#define CAN_ESR1_BOFFINT_MASK                              (0x4U)
#define CAN_ESR1_BOFFINT_SHIFT                             (2U)
#define CAN_ESR1_BOFFINT(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_BOFFINT_SHIFT)) & CAN_ESR1_BOFFINT_MASK)
#define CAN_ESR1_ERRINT_MASK                               (0x2U)
#define CAN_ESR1_ERRINT_SHIFT                              (1U)
#define CAN_ESR1_ERRINT(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_ERRINT_SHIFT)) & CAN_ESR1_ERRINT_MASK)
#define CAN_ESR1_WAKINT_MASK                               (0x1U)
#define CAN_ESR1_WAKINT_SHIFT                              (0U)
#define CAN_ESR1_WAKINT(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ESR1_WAKINT_SHIFT)) & CAN_ESR1_WAKINT_MASK)
/* CAN_IMASK2 Register */
#define CAN_IMASK2_BUF63TO32M_MASK                         (0xFFFFFFFFU)
#define CAN_IMASK2_BUF63TO32M_SHIFT                        (0U)
#define CAN_IMASK2_BUF63TO32M(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IMASK2_BUF63TO32M_SHIFT)) & CAN_IMASK2_BUF63TO32M_MASK)
/* CAN_IMASK1 Register */
#define CAN_IMASK1_BUF31TO0M_MASK                          (0xFFFFFFFFU)
#define CAN_IMASK1_BUF31TO0M_SHIFT                         (0U)
#define CAN_IMASK1_BUF31TO0M(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IMASK1_BUF31TO0M_SHIFT)) & CAN_IMASK1_BUF31TO0M_MASK)
/* CAN_IFLAG2 Register */
#define CAN_IFLAG2_BUF63TO32I_MASK                         (0xFFFFFFFFU)
#define CAN_IFLAG2_BUF63TO32I_SHIFT                        (0U)
#define CAN_IFLAG2_BUF63TO32I(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG2_BUF63TO32I_SHIFT)) & CAN_IFLAG2_BUF63TO32I_MASK)
/* CAN_IFLAG1 Register */
#define CAN_IFLAG1_BUF31TO8I_MASK                          (0xFFFFFF00U)
#define CAN_IFLAG1_BUF31TO8I_SHIFT                         (8U)
#define CAN_IFLAG1_BUF31TO8I(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF31TO8I_SHIFT)) & CAN_IFLAG1_BUF31TO8I_MASK)
#define CAN_IFLAG1_BUF7I_MASK                              (0x80U)
#define CAN_IFLAG1_BUF7I_SHIFT                             (7U)
#define CAN_IFLAG1_BUF7I(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF7I_SHIFT)) & CAN_IFLAG1_BUF7I_MASK)
#define CAN_IFLAG1_BUF6I_MASK                              (0x40U)
#define CAN_IFLAG1_BUF6I_SHIFT                             (6U)
#define CAN_IFLAG1_BUF6I(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF6I_SHIFT)) & CAN_IFLAG1_BUF6I_MASK)
#define CAN_IFLAG1_BUF5I_MASK                              (0x20U)
#define CAN_IFLAG1_BUF5I_SHIFT                             (5U)
#define CAN_IFLAG1_BUF5I(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF5I_SHIFT)) & CAN_IFLAG1_BUF5I_MASK)
#define CAN_IFLAG1_BUF4TO1I_MASK                           (0x1EU)
#define CAN_IFLAG1_BUF4TO1I_SHIFT                          (1U)
#define CAN_IFLAG1_BUF4TO1I(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF4TO1I_SHIFT)) & CAN_IFLAG1_BUF4TO1I_MASK)
#define CAN_IFLAG1_BUF0I_MASK                              (0x1U)
#define CAN_IFLAG1_BUF0I_SHIFT                             (0U)
#define CAN_IFLAG1_BUF0I(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG1_BUF0I_SHIFT)) & CAN_IFLAG1_BUF0I_MASK)
/* CAN_CTRL2 Register */
#define CAN_CTRL2_ERRMSK_FAST_MASK                         (0x80000000U)
#define CAN_CTRL2_ERRMSK_FAST_SHIFT                        (31U)
#define CAN_CTRL2_ERRMSK_FAST(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_ERRMSK_FAST_SHIFT)) & CAN_CTRL2_ERRMSK_FAST_MASK)
#define CAN_CTRL2_BOFFDONEMSK_MASK                         (0x40000000U)
#define CAN_CTRL2_BOFFDONEMSK_SHIFT                        (30U)
#define CAN_CTRL2_BOFFDONEMSK(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_BOFFDONEMSK_SHIFT)) & CAN_CTRL2_BOFFDONEMSK_MASK)
#define CAN_CTRL2_ECRWRE_MASK                              (0x20000000U)
#define CAN_CTRL2_ECRWRE_SHIFT                             (29U)
#define CAN_CTRL2_ECRWRE(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_ECRWRE_SHIFT)) & CAN_CTRL2_ECRWRE_MASK)
#define CAN_CTRL2_WRMFRZ_MASK                              (0x10000000U)
#define CAN_CTRL2_WRMFRZ_SHIFT                             (28U)
#define CAN_CTRL2_WRMFRZ(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_WRMFRZ_SHIFT)) & CAN_CTRL2_WRMFRZ_MASK)
#define CAN_CTRL2_RFFN_MASK                                (0xF000000U)
#define CAN_CTRL2_RFFN_SHIFT                               (24U)
#define CAN_CTRL2_RFFN(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_RFFN_SHIFT)) & CAN_CTRL2_RFFN_MASK)
#define CAN_CTRL2_TASD_MASK                                (0xF80000U)
#define CAN_CTRL2_TASD_SHIFT                               (19U)
#define CAN_CTRL2_TASD(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_TASD_SHIFT)) & CAN_CTRL2_TASD_MASK)
#define CAN_CTRL2_MRP_MASK                                 (0x40000U)
#define CAN_CTRL2_MRP_SHIFT                                (18U)
#define CAN_CTRL2_MRP(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_MRP_SHIFT)) & CAN_CTRL2_MRP_MASK)
#define CAN_CTRL2_RRS_MASK                                 (0x20000U)
#define CAN_CTRL2_RRS_SHIFT                                (17U)
#define CAN_CTRL2_RRS(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_RRS_SHIFT)) & CAN_CTRL2_RRS_MASK)
#define CAN_CTRL2_EACEN_MASK                               (0x10000U)
#define CAN_CTRL2_EACEN_SHIFT                              (16U)
#define CAN_CTRL2_EACEN(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_EACEN_SHIFT)) & CAN_CTRL2_EACEN_MASK)
#define CAN_CTRL2_TIMER_SRC_MASK                           (0x8000U)
#define CAN_CTRL2_TIMER_SRC_SHIFT                          (15U)
#define CAN_CTRL2_TIMER_SRC(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_TIMER_SRC_SHIFT)) & CAN_CTRL2_TIMER_SRC_MASK)
#define CAN_CTRL2_PREXCEN_MASK                             (0x4000U)
#define CAN_CTRL2_PREXCEN_SHIFT                            (14U)
#define CAN_CTRL2_PREXCEN(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_PREXCEN_SHIFT)) & CAN_CTRL2_PREXCEN_MASK)
#define CAN_CTRL2_BTE_MASK                                 (0x2000U)
#define CAN_CTRL2_BTE_SHIFT                                (13U)
#define CAN_CTRL2_BTE(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_BTE_SHIFT)) & CAN_CTRL2_BTE_MASK)
#define CAN_CTRL2_ISOCANFDEN_MASK                          (0x1000U)
#define CAN_CTRL2_ISOCANFDEN_SHIFT                         (12U)
#define CAN_CTRL2_ISOCANFDEN(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_ISOCANFDEN_SHIFT)) & CAN_CTRL2_ISOCANFDEN_MASK)
#define CAN_CTRL2_EDFLTDIS_MASK                            (0x800U)
#define CAN_CTRL2_EDFLTDIS_SHIFT                           (11U)
#define CAN_CTRL2_EDFLTDIS(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_EDFLTDIS_SHIFT)) & CAN_CTRL2_EDFLTDIS_MASK)
#define CAN_CTRL2_MBTSBASE_MASK                            (0x300U)
#define CAN_CTRL2_MBTSBASE_SHIFT                           (8U)
#define CAN_CTRL2_MBTSBASE(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_MBTSBASE_SHIFT)) & CAN_CTRL2_MBTSBASE_MASK)
#define CAN_CTRL2_TSTAMPCAP_MASK                           (0xC0U)
#define CAN_CTRL2_TSTAMPCAP_SHIFT                          (6U)
#define CAN_CTRL2_TSTAMPCAP(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_TSTAMPCAP_SHIFT)) & CAN_CTRL2_TSTAMPCAP_MASK)
/* CAN_ESR2 Register */
#define CAN_ESR2_LPTM_MASK                                 (0x7F0000U)
#define CAN_ESR2_LPTM_SHIFT                                (16U)
#define CAN_ESR2_LPTM(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_LPTM_SHIFT)) & CAN_ESR2_LPTM_MASK)
#define CAN_ESR2_VPS_MASK                                  (0x4000U)
#define CAN_ESR2_VPS_SHIFT                                 (14U)
#define CAN_ESR2_VPS(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_VPS_SHIFT)) & CAN_ESR2_VPS_MASK)
#define CAN_ESR2_IMB_MASK                                  (0x2000U)
#define CAN_ESR2_IMB_SHIFT                                 (13U)
#define CAN_ESR2_IMB(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_ESR2_IMB_SHIFT)) & CAN_ESR2_IMB_MASK)
/* CAN_CRCR Register */
#define CAN_CRCR_MBCRC_MASK                                (0x7F0000U)
#define CAN_CRCR_MBCRC_SHIFT                               (16U)
#define CAN_CRCR_MBCRC(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CRCR_MBCRC_SHIFT)) & CAN_CRCR_MBCRC_MASK)
#define CAN_CRCR_TXCRC_MASK                                (0x7FFFU)
#define CAN_CRCR_TXCRC_SHIFT                               (0U)
#define CAN_CRCR_TXCRC(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CRCR_TXCRC_SHIFT)) & CAN_CRCR_TXCRC_MASK)
/* CAN_RXFGMASK Register */
#define CAN_RXFGMASK_FGM_MASK                              (0xFFFFFFFFU)
#define CAN_RXFGMASK_FGM_SHIFT                             (0U)
#define CAN_RXFGMASK_FGM(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RXFGMASK_FGM_SHIFT)) & CAN_RXFGMASK_FGM_MASK)
/* CAN_RXFIR Register */
#define CAN_RXFIR_IDHIT_MASK                               (0x1FFU)
#define CAN_RXFIR_IDHIT_SHIFT                              (0U)
#define CAN_RXFIR_IDHIT(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_RXFIR_IDHIT_SHIFT)) & CAN_RXFIR_IDHIT_MASK)
/* CAN_CBT Register */
#define CAN_CBT_BTF_MASK                                   (0x80000000U)
#define CAN_CBT_BTF_SHIFT                                  (31U)
#define CAN_CBT_BTF(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_CBT_BTF_SHIFT)) & CAN_CBT_BTF_MASK)
#define CAN_CBT_EPRESDIV_MASK                              (0x7FE00000U)
#define CAN_CBT_EPRESDIV_SHIFT                             (21U)
#define CAN_CBT_EPRESDIV(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPRESDIV_SHIFT)) & CAN_CBT_EPRESDIV_MASK)
#define CAN_CBT_ERJW_MASK                                  (0x1F0000U)
#define CAN_CBT_ERJW_SHIFT                                 (16U)
#define CAN_CBT_ERJW(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_CBT_ERJW_SHIFT)) & CAN_CBT_ERJW_MASK)
#define CAN_CBT_EPROPSEG_MASK                              (0xFC00U)
#define CAN_CBT_EPROPSEG_SHIFT                             (10U)
#define CAN_CBT_EPROPSEG(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPROPSEG_SHIFT)) & CAN_CBT_EPROPSEG_MASK)
#define CAN_CBT_EPSEG1_MASK                                (0x3E0U)
#define CAN_CBT_EPSEG1_SHIFT                               (5U)
#define CAN_CBT_EPSEG1(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPSEG1_SHIFT)) & CAN_CBT_EPSEG1_MASK)
#define CAN_CBT_EPSEG2_MASK                                (0x1FU)
#define CAN_CBT_EPSEG2_SHIFT                               (0U)
#define CAN_CBT_EPSEG2(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_CBT_EPSEG2_SHIFT)) & CAN_CBT_EPSEG2_MASK)
/* CAN_IMASK4 Register */
#define CAN_IMASK4_BUF127TO96M_MASK                        (0xFFFFFFFFU)
#define CAN_IMASK4_BUF127TO96M_SHIFT                       (0U)
#define CAN_IMASK4_BUF127TO96M(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IMASK4_BUF127TO96M_SHIFT)) & CAN_IMASK4_BUF127TO96M_MASK)
/* CAN_IMASK3 Register */
#define CAN_IMASK3_BUF95TO64M_MASK                         (0xFFFFFFFFU)
#define CAN_IMASK3_BUF95TO64M_SHIFT                        (0U)
#define CAN_IMASK3_BUF95TO64M(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IMASK3_BUF95TO64M_SHIFT)) & CAN_IMASK3_BUF95TO64M_MASK)
/* CAN_IFLAG4 Register */
#define CAN_IFLAG4_BUF127TO96_MASK                         (0xFFFFFFFFU)
#define CAN_IFLAG4_BUF127TO96_SHIFT                        (0U)
#define CAN_IFLAG4_BUF127TO96(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG4_BUF127TO96_SHIFT)) & CAN_IFLAG4_BUF127TO96_MASK)
/* CAN_IFLAG3 Register */
#define CAN_IFLAG3_BUF95TO64_MASK                          (0xFFFFFFFFU)
#define CAN_IFLAG3_BUF95TO64_SHIFT                         (0U)
#define CAN_IFLAG3_BUF95TO64(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IFLAG3_BUF95TO64_SHIFT)) & CAN_IFLAG3_BUF95TO64_MASK)
/* CAN_RAM Register */
#define CAN_RAM_RAM_MASK                                   (0xFFFFFFFFU)
#define CAN_RAM_RAM_SHIFT                                  (0U)
#define CAN_RAM_RAM(x)                                     (((uint32_t)(((uint32_t)(x)) << CAN_RAM_RAM_SHIFT)) & CAN_RAM_RAM_MASK)
/* CAN_RXIMR Register */
#define CAN_RXIMR_MI_MASK                                  (0xFFFFFFFFU)
#define CAN_RXIMR_MI_SHIFT                                 (0U)
#define CAN_RXIMR_MI(x)                                    (((uint32_t)(((uint32_t)(x)) << CAN_RXIMR_MI_SHIFT)) & CAN_RXIMR_MI_MASK)
/* CAN_MECR Register */
#define CAN_MECR_ECRWRDIS_MASK                             (0x80000000U)
#define CAN_MECR_ECRWRDIS_SHIFT                            (31U)
#define CAN_MECR_ECRWRDIS(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_MECR_ECRWRDIS_SHIFT)) & CAN_MECR_ECRWRDIS_MASK)
#define CAN_MECR_HANCEI_MSK_MASK                           (0x80000U)
#define CAN_MECR_HANCEI_MSK_SHIFT                          (19U)
#define CAN_MECR_HANCEI_MSK(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_MECR_HANCEI_MSK_SHIFT)) & CAN_MECR_HANCEI_MSK_MASK)
#define CAN_MECR_FANCEI_MSK_MASK                           (0x40000U)
#define CAN_MECR_FANCEI_MSK_SHIFT                          (18U)
#define CAN_MECR_FANCEI_MSK(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_MECR_FANCEI_MSK_SHIFT)) & CAN_MECR_FANCEI_MSK_MASK)
#define CAN_MECR_CEI_MSK_MASK                              (0x10000U)
#define CAN_MECR_CEI_MSK_SHIFT                             (16U)
#define CAN_MECR_CEI_MSK(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_MECR_CEI_MSK_SHIFT)) & CAN_MECR_CEI_MSK_MASK)
#define CAN_MECR_HAERRIE_MASK                              (0x8000U)
#define CAN_MECR_HAERRIE_SHIFT                             (15U)
#define CAN_MECR_HAERRIE(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_MECR_HAERRIE_SHIFT)) & CAN_MECR_HAERRIE_MASK)
#define CAN_MECR_FAERRIE_MASK                              (0x4000U)
#define CAN_MECR_FAERRIE_SHIFT                             (14U)
#define CAN_MECR_FAERRIE(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_MECR_FAERRIE_SHIFT)) & CAN_MECR_FAERRIE_MASK)
#define CAN_MECR_EXTERRIE_MASK                             (0x2000U)
#define CAN_MECR_EXTERRIE_SHIFT                            (13U)
#define CAN_MECR_EXTERRIE(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_MECR_EXTERRIE_SHIFT)) & CAN_MECR_EXTERRIE_MASK)
#define CAN_MECR_RERRDIS_MASK                              (0x200U)
#define CAN_MECR_RERRDIS_SHIFT                             (9U)
#define CAN_MECR_RERRDIS(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_MECR_RERRDIS_SHIFT)) & CAN_MECR_RERRDIS_MASK)
#define CAN_MECR_ECCDIS_MASK                               (0x100U)
#define CAN_MECR_ECCDIS_SHIFT                              (8U)
#define CAN_MECR_ECCDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_MECR_ECCDIS_SHIFT)) & CAN_MECR_ECCDIS_MASK)
#define CAN_MECR_NCEFAFRZ_MASK                             (0x80U)
#define CAN_MECR_NCEFAFRZ_SHIFT                            (7U)
#define CAN_MECR_NCEFAFRZ(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_MECR_NCEFAFRZ_SHIFT)) & CAN_MECR_NCEFAFRZ_MASK)
/* CAN_ERRIAR Register */
#define CAN_ERRIAR_INJADDR_H_MASK                          (0x3FFCU)
#define CAN_ERRIAR_INJADDR_H_SHIFT                         (2U)
#define CAN_ERRIAR_INJADDR_H(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ERRIAR_INJADDR_H_SHIFT)) & CAN_ERRIAR_INJADDR_H_MASK)
#define CAN_ERRIAR_INJADDR_L_MASK                          (0x3U)
#define CAN_ERRIAR_INJADDR_L_SHIFT                         (0U)
#define CAN_ERRIAR_INJADDR_L(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_ERRIAR_INJADDR_L_SHIFT)) & CAN_ERRIAR_INJADDR_L_MASK)
/* CAN_ERRIDPR Register */
#define CAN_ERRIDPR_DFLIP_MASK                             (0xFFFFFFFFU)
#define CAN_ERRIDPR_DFLIP_SHIFT                            (0U)
#define CAN_ERRIDPR_DFLIP(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_ERRIDPR_DFLIP_SHIFT)) & CAN_ERRIDPR_DFLIP_MASK)
/* CAN_ERRIPPR Register */
#define CAN_ERRIPPR_PFLIP3_MASK                            (0x1F000000U)
#define CAN_ERRIPPR_PFLIP3_SHIFT                           (24U)
#define CAN_ERRIPPR_PFLIP3(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRIPPR_PFLIP3_SHIFT)) & CAN_ERRIPPR_PFLIP3_MASK)
#define CAN_ERRIPPR_PFLIP2_MASK                            (0x1F0000U)
#define CAN_ERRIPPR_PFLIP2_SHIFT                           (16U)
#define CAN_ERRIPPR_PFLIP2(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRIPPR_PFLIP2_SHIFT)) & CAN_ERRIPPR_PFLIP2_MASK)
#define CAN_ERRIPPR_PFLIP1_MASK                            (0x1F00U)
#define CAN_ERRIPPR_PFLIP1_SHIFT                           (8U)
#define CAN_ERRIPPR_PFLIP1(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRIPPR_PFLIP1_SHIFT)) & CAN_ERRIPPR_PFLIP1_MASK)
#define CAN_ERRIPPR_PFLIP0_MASK                            (0x1FU)
#define CAN_ERRIPPR_PFLIP0_SHIFT                           (0U)
#define CAN_ERRIPPR_PFLIP0(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRIPPR_PFLIP0_SHIFT)) & CAN_ERRIPPR_PFLIP0_MASK)
/* CAN_RERRAR Register */
#define CAN_RERRAR_NCE_MASK                                (0x1000000U)
#define CAN_RERRAR_NCE_SHIFT                               (24U)
#define CAN_RERRAR_NCE(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_RERRAR_NCE_SHIFT)) & CAN_RERRAR_NCE_MASK)
#define CAN_RERRAR_SAID_MASK                               (0x70000U)
#define CAN_RERRAR_SAID_SHIFT                              (16U)
#define CAN_RERRAR_SAID(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_RERRAR_SAID_SHIFT)) & CAN_RERRAR_SAID_MASK)
#define CAN_RERRAR_ERRADDR_MASK                            (0x3FFFU)
#define CAN_RERRAR_ERRADDR_SHIFT                           (0U)
#define CAN_RERRAR_ERRADDR(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RERRAR_ERRADDR_SHIFT)) & CAN_RERRAR_ERRADDR_MASK)
/* CAN_RERRDR Register */
#define CAN_RERRDR_RDATA_MASK                              (0xFFFFFFFFU)
#define CAN_RERRDR_RDATA_SHIFT                             (0U)
#define CAN_RERRDR_RDATA(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RERRDR_RDATA_SHIFT)) & CAN_RERRDR_RDATA_MASK)
/* CAN_RERRSYNR Register */
#define CAN_RERRSYNR_BE3_MASK                              (0x80000000U)
#define CAN_RERRSYNR_BE3_SHIFT                             (31U)
#define CAN_RERRSYNR_BE3(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_BE3_SHIFT)) & CAN_RERRSYNR_BE3_MASK)
#define CAN_RERRSYNR_SYND3_MASK                            (0x1F000000U)
#define CAN_RERRSYNR_SYND3_SHIFT                           (24U)
#define CAN_RERRSYNR_SYND3(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_SYND3_SHIFT)) & CAN_RERRSYNR_SYND3_MASK)
#define CAN_RERRSYNR_BE2_MASK                              (0x800000U)
#define CAN_RERRSYNR_BE2_SHIFT                             (23U)
#define CAN_RERRSYNR_BE2(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_BE2_SHIFT)) & CAN_RERRSYNR_BE2_MASK)
#define CAN_RERRSYNR_SYND2_MASK                            (0x1F0000U)
#define CAN_RERRSYNR_SYND2_SHIFT                           (16U)
#define CAN_RERRSYNR_SYND2(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_SYND2_SHIFT)) & CAN_RERRSYNR_SYND2_MASK)
#define CAN_RERRSYNR_BE1_MASK                              (0x8000U)
#define CAN_RERRSYNR_BE1_SHIFT                             (15U)
#define CAN_RERRSYNR_BE1(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_BE1_SHIFT)) & CAN_RERRSYNR_BE1_MASK)
#define CAN_RERRSYNR_SYND1_MASK                            (0x1F00U)
#define CAN_RERRSYNR_SYND1_SHIFT                           (8U)
#define CAN_RERRSYNR_SYND1(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_SYND1_SHIFT)) & CAN_RERRSYNR_SYND1_MASK)
#define CAN_RERRSYNR_BE0_MASK                              (0x80U)
#define CAN_RERRSYNR_BE0_SHIFT                             (7U)
#define CAN_RERRSYNR_BE0(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_BE0_SHIFT)) & CAN_RERRSYNR_BE0_MASK)
#define CAN_RERRSYNR_SYND0_MASK                            (0x1FU)
#define CAN_RERRSYNR_SYND0_SHIFT                           (0U)
#define CAN_RERRSYNR_SYND0(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_RERRSYNR_SYND0_SHIFT)) & CAN_RERRSYNR_SYND0_MASK)
/* CAN_ERRSR Register */
#define CAN_ERRSR_HANCEIF_MASK                             (0x80000U)
#define CAN_ERRSR_HANCEIF_SHIFT                            (19U)
#define CAN_ERRSR_HANCEIF(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_HANCEIF_SHIFT)) & CAN_ERRSR_HANCEIF_MASK)
#define CAN_ERRSR_FANCEIF_MASK                             (0x40000U)
#define CAN_ERRSR_FANCEIF_SHIFT                            (18U)
#define CAN_ERRSR_FANCEIF(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_FANCEIF_SHIFT)) & CAN_ERRSR_FANCEIF_MASK)
#define CAN_ERRSR_CEIF_MASK                                (0x10000U)
#define CAN_ERRSR_CEIF_SHIFT                               (16U)
#define CAN_ERRSR_CEIF(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_CEIF_SHIFT)) & CAN_ERRSR_CEIF_MASK)
#define CAN_ERRSR_HANCEIOF_MASK                            (0x8U)
#define CAN_ERRSR_HANCEIOF_SHIFT                           (3U)
#define CAN_ERRSR_HANCEIOF(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_HANCEIOF_SHIFT)) & CAN_ERRSR_HANCEIOF_MASK)
#define CAN_ERRSR_FANCEIOF_MASK                            (0x4U)
#define CAN_ERRSR_FANCEIOF_SHIFT                           (2U)
#define CAN_ERRSR_FANCEIOF(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_FANCEIOF_SHIFT)) & CAN_ERRSR_FANCEIOF_MASK)
#define CAN_ERRSR_CEIOF_MASK                               (0x1U)
#define CAN_ERRSR_CEIOF_SHIFT                              (0U)
#define CAN_ERRSR_CEIOF(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERRSR_CEIOF_SHIFT)) & CAN_ERRSR_CEIOF_MASK)
/* CAN_CTRL1_PN Register */
#define CAN_CTRL1_PN_WTOF_MSK_MASK                         (0x20000U)
#define CAN_CTRL1_PN_WTOF_MSK_SHIFT                        (17U)
#define CAN_CTRL1_PN_WTOF_MSK(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_WTOF_MSK_SHIFT)) & CAN_CTRL1_PN_WTOF_MSK_MASK)
#define CAN_CTRL1_PN_WUMF_MSK_MASK                         (0x10000U)
#define CAN_CTRL1_PN_WUMF_MSK_SHIFT                        (16U)
#define CAN_CTRL1_PN_WUMF_MSK(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_WUMF_MSK_SHIFT)) & CAN_CTRL1_PN_WUMF_MSK_MASK)
#define CAN_CTRL1_PN_NMATCH_MASK                           (0xFF00U)
#define CAN_CTRL1_PN_NMATCH_SHIFT                          (8U)
#define CAN_CTRL1_PN_NMATCH(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_NMATCH_SHIFT)) & CAN_CTRL1_PN_NMATCH_MASK)
#define CAN_CTRL1_PN_PLFS_MASK                             (0x30U)
#define CAN_CTRL1_PN_PLFS_SHIFT                            (4U)
#define CAN_CTRL1_PN_PLFS(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_PLFS_SHIFT)) & CAN_CTRL1_PN_PLFS_MASK)
#define CAN_CTRL1_PN_IDFS_MASK                             (0xCU)
#define CAN_CTRL1_PN_IDFS_SHIFT                            (2U)
#define CAN_CTRL1_PN_IDFS(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_IDFS_SHIFT)) & CAN_CTRL1_PN_IDFS_MASK)
#define CAN_CTRL1_PN_FCS_MASK                              (0x3U)
#define CAN_CTRL1_PN_FCS_SHIFT                             (0U)
#define CAN_CTRL1_PN_FCS(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_CTRL1_PN_FCS_SHIFT)) & CAN_CTRL1_PN_FCS_MASK)
/* CAN_CTRL2_PN Register */
#define CAN_CTRL2_PN_MATCHTO_MASK                          (0xFFFFU)
#define CAN_CTRL2_PN_MATCHTO_SHIFT                         (0U)
#define CAN_CTRL2_PN_MATCHTO(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CTRL2_PN_MATCHTO_SHIFT)) & CAN_CTRL2_PN_MATCHTO_MASK)
/* CAN_WU_MTC Register */
#define CAN_WU_MTC_WTOF_MASK                               (0x20000U)
#define CAN_WU_MTC_WTOF_SHIFT                              (17U)
#define CAN_WU_MTC_WTOF(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WU_MTC_WTOF_SHIFT)) & CAN_WU_MTC_WTOF_MASK)
#define CAN_WU_MTC_WUMF_MASK                               (0x10000U)
#define CAN_WU_MTC_WUMF_SHIFT                              (16U)
#define CAN_WU_MTC_WUMF(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WU_MTC_WUMF_SHIFT)) & CAN_WU_MTC_WUMF_MASK)
#define CAN_WU_MTC_MCOUNTER_MASK                           (0xFF00U)
#define CAN_WU_MTC_MCOUNTER_SHIFT                          (8U)
#define CAN_WU_MTC_MCOUNTER(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_WU_MTC_MCOUNTER_SHIFT)) & CAN_WU_MTC_MCOUNTER_MASK)
/* CAN_FLT_ID1 Register */
#define CAN_FLT_ID1_FLT_IDE_MASK                           (0x40000000U)
#define CAN_FLT_ID1_FLT_IDE_SHIFT                          (30U)
#define CAN_FLT_ID1_FLT_IDE(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID1_FLT_IDE_SHIFT)) & CAN_FLT_ID1_FLT_IDE_MASK)
#define CAN_FLT_ID1_FLT_RTR_MASK                           (0x20000000U)
#define CAN_FLT_ID1_FLT_RTR_SHIFT                          (29U)
#define CAN_FLT_ID1_FLT_RTR(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID1_FLT_RTR_SHIFT)) & CAN_FLT_ID1_FLT_RTR_MASK)
#define CAN_FLT_ID1_FLT_ID1_MASK                           (0x1FFFFFFFU)
#define CAN_FLT_ID1_FLT_ID1_SHIFT                          (0U)
#define CAN_FLT_ID1_FLT_ID1(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID1_FLT_ID1_SHIFT)) & CAN_FLT_ID1_FLT_ID1_MASK)
/* CAN_FLT_DLC Register */
#define CAN_FLT_DLC_FLT_DLC_LO_MASK                        (0xF0000U)
#define CAN_FLT_DLC_FLT_DLC_LO_SHIFT                       (16U)
#define CAN_FLT_DLC_FLT_DLC_LO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_FLT_DLC_FLT_DLC_LO_SHIFT)) & CAN_FLT_DLC_FLT_DLC_LO_MASK)
#define CAN_FLT_DLC_FLT_DLC_HI_MASK                        (0xFU)
#define CAN_FLT_DLC_FLT_DLC_HI_SHIFT                       (0U)
#define CAN_FLT_DLC_FLT_DLC_HI(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_FLT_DLC_FLT_DLC_HI_SHIFT)) & CAN_FLT_DLC_FLT_DLC_HI_MASK)
/* CAN_PL1_LO Register */
#define CAN_PL1_LO_Data_byte_0_MASK                        (0xFF000000U)
#define CAN_PL1_LO_Data_byte_0_SHIFT                       (24U)
#define CAN_PL1_LO_Data_byte_0(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_LO_Data_byte_0_SHIFT)) & CAN_PL1_LO_Data_byte_0_MASK)
#define CAN_PL1_LO_Data_byte_1_MASK                        (0xFF0000U)
#define CAN_PL1_LO_Data_byte_1_SHIFT                       (16U)
#define CAN_PL1_LO_Data_byte_1(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_LO_Data_byte_1_SHIFT)) & CAN_PL1_LO_Data_byte_1_MASK)
#define CAN_PL1_LO_Data_byte_2_MASK                        (0xFF00U)
#define CAN_PL1_LO_Data_byte_2_SHIFT                       (8U)
#define CAN_PL1_LO_Data_byte_2(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_LO_Data_byte_2_SHIFT)) & CAN_PL1_LO_Data_byte_2_MASK)
#define CAN_PL1_LO_Data_byte_3_MASK                        (0xFFU)
#define CAN_PL1_LO_Data_byte_3_SHIFT                       (0U)
#define CAN_PL1_LO_Data_byte_3(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_LO_Data_byte_3_SHIFT)) & CAN_PL1_LO_Data_byte_3_MASK)
/* CAN_PL1_HI Register */
#define CAN_PL1_HI_Data_byte_4_MASK                        (0xFF000000U)
#define CAN_PL1_HI_Data_byte_4_SHIFT                       (24U)
#define CAN_PL1_HI_Data_byte_4(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_HI_Data_byte_4_SHIFT)) & CAN_PL1_HI_Data_byte_4_MASK)
#define CAN_PL1_HI_Data_byte_5_MASK                        (0xFF0000U)
#define CAN_PL1_HI_Data_byte_5_SHIFT                       (16U)
#define CAN_PL1_HI_Data_byte_5(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_HI_Data_byte_5_SHIFT)) & CAN_PL1_HI_Data_byte_5_MASK)
#define CAN_PL1_HI_Data_byte_6_MASK                        (0xFF00U)
#define CAN_PL1_HI_Data_byte_6_SHIFT                       (8U)
#define CAN_PL1_HI_Data_byte_6(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_HI_Data_byte_6_SHIFT)) & CAN_PL1_HI_Data_byte_6_MASK)
#define CAN_PL1_HI_Data_byte_7_MASK                        (0xFFU)
#define CAN_PL1_HI_Data_byte_7_SHIFT                       (0U)
#define CAN_PL1_HI_Data_byte_7(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_PL1_HI_Data_byte_7_SHIFT)) & CAN_PL1_HI_Data_byte_7_MASK)
/* CAN_FLT_ID2_IDMASK Register */
#define CAN_FLT_ID2_IDMASK_IDE_MSK_MASK                    (0x40000000U)
#define CAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT                   (30U)
#define CAN_FLT_ID2_IDMASK_IDE_MSK(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT)) & CAN_FLT_ID2_IDMASK_IDE_MSK_MASK)
#define CAN_FLT_ID2_IDMASK_RTR_MSK_MASK                    (0x20000000U)
#define CAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT                   (29U)
#define CAN_FLT_ID2_IDMASK_RTR_MSK(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT)) & CAN_FLT_ID2_IDMASK_RTR_MSK_MASK)
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK             (0x1FFFFFFFU)
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT            (0U)
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK(x)               (((uint32_t)(((uint32_t)(x)) << CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT)) & CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK)
/* CAN_PL2_PLMASK_LO Register */
#define CAN_PL2_PLMASK_LO_Data_byte_0_MASK                 (0xFF000000U)
#define CAN_PL2_PLMASK_LO_Data_byte_0_SHIFT                (24U)
#define CAN_PL2_PLMASK_LO_Data_byte_0(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_LO_Data_byte_0_SHIFT)) & CAN_PL2_PLMASK_LO_Data_byte_0_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_1_MASK                 (0xFF0000U)
#define CAN_PL2_PLMASK_LO_Data_byte_1_SHIFT                (16U)
#define CAN_PL2_PLMASK_LO_Data_byte_1(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_LO_Data_byte_1_SHIFT)) & CAN_PL2_PLMASK_LO_Data_byte_1_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_2_MASK                 (0xFF00U)
#define CAN_PL2_PLMASK_LO_Data_byte_2_SHIFT                (8U)
#define CAN_PL2_PLMASK_LO_Data_byte_2(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_LO_Data_byte_2_SHIFT)) & CAN_PL2_PLMASK_LO_Data_byte_2_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_3_MASK                 (0xFFU)
#define CAN_PL2_PLMASK_LO_Data_byte_3_SHIFT                (0U)
#define CAN_PL2_PLMASK_LO_Data_byte_3(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_LO_Data_byte_3_SHIFT)) & CAN_PL2_PLMASK_LO_Data_byte_3_MASK)
/* CAN_PL2_PLMASK_HI Register */
#define CAN_PL2_PLMASK_HI_Data_byte_4_MASK                 (0xFF000000U)
#define CAN_PL2_PLMASK_HI_Data_byte_4_SHIFT                (24U)
#define CAN_PL2_PLMASK_HI_Data_byte_4(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_HI_Data_byte_4_SHIFT)) & CAN_PL2_PLMASK_HI_Data_byte_4_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_5_MASK                 (0xFF0000U)
#define CAN_PL2_PLMASK_HI_Data_byte_5_SHIFT                (16U)
#define CAN_PL2_PLMASK_HI_Data_byte_5(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_HI_Data_byte_5_SHIFT)) & CAN_PL2_PLMASK_HI_Data_byte_5_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_6_MASK                 (0xFF00U)
#define CAN_PL2_PLMASK_HI_Data_byte_6_SHIFT                (8U)
#define CAN_PL2_PLMASK_HI_Data_byte_6(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_HI_Data_byte_6_SHIFT)) & CAN_PL2_PLMASK_HI_Data_byte_6_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_7_MASK                 (0xFFU)
#define CAN_PL2_PLMASK_HI_Data_byte_7_SHIFT                (0U)
#define CAN_PL2_PLMASK_HI_Data_byte_7(x)                   (((uint32_t)(((uint32_t)(x)) << CAN_PL2_PLMASK_HI_Data_byte_7_SHIFT)) & CAN_PL2_PLMASK_HI_Data_byte_7_MASK)
/* CAN_WMB_WMBn_CS Register */
#define CAN_WMB_WMBn_CS_SRR_MASK                               (0x400000U)
#define CAN_WMB_WMBn_CS_SRR_SHIFT                              (22U)
#define CAN_WMB_WMBn_CS_SRR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_CS_SRR_SHIFT)) & CAN_WMB_WMBn_CS_SRR_MASK)
#define CAN_WMB_WMBn_CS_IDE_MASK                               (0x200000U)
#define CAN_WMB_WMBn_CS_IDE_SHIFT                              (21U)
#define CAN_WMB_WMBn_CS_IDE(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_CS_IDE_SHIFT)) & CAN_WMB_WMBn_CS_IDE_MASK)
#define CAN_WMB_WMBn_CS_RTR_MASK                               (0x100000U)
#define CAN_WMB_WMBn_CS_RTR_SHIFT                              (20U)
#define CAN_WMB_WMBn_CS_RTR(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_CS_RTR_SHIFT)) & CAN_WMB_WMBn_CS_RTR_MASK)
#define CAN_WMB_WMBn_CS_DLC_MASK                               (0xF0000U)
#define CAN_WMB_WMBn_CS_DLC_SHIFT                              (16U)
#define CAN_WMB_WMBn_CS_DLC(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_CS_DLC_SHIFT)) & CAN_WMB_WMBn_CS_DLC_MASK)
/* CAN_WMB_WMBn_ID Register */
#define CAN_WMB_WMBn_ID_ID_MASK                                (0x1FFFFFFFU)
#define CAN_WMB_WMBn_ID_ID_SHIFT                               (0U)
#define CAN_WMB_WMBn_ID_ID(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_ID_ID_SHIFT)) & CAN_WMB_WMBn_ID_ID_MASK)
/* CAN_WMB_WMBn_D03 Register */
#define CAN_WMB_WMBn_D03_Data_byte_0_MASK                      (0xFF000000U)
#define CAN_WMB_WMBn_D03_Data_byte_0_SHIFT                     (24U)
#define CAN_WMB_WMBn_D03_Data_byte_0(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D03_Data_byte_0_SHIFT)) & CAN_WMB_WMBn_D03_Data_byte_0_MASK)
#define CAN_WMB_WMBn_D03_Data_byte_1_MASK                      (0xFF0000U)
#define CAN_WMB_WMBn_D03_Data_byte_1_SHIFT                     (16U)
#define CAN_WMB_WMBn_D03_Data_byte_1(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D03_Data_byte_1_SHIFT)) & CAN_WMB_WMBn_D03_Data_byte_1_MASK)
#define CAN_WMB_WMBn_D03_Data_byte_2_MASK                      (0xFF00U)
#define CAN_WMB_WMBn_D03_Data_byte_2_SHIFT                     (8U)
#define CAN_WMB_WMBn_D03_Data_byte_2(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D03_Data_byte_2_SHIFT)) & CAN_WMB_WMBn_D03_Data_byte_2_MASK)
#define CAN_WMB_WMBn_D03_Data_byte_3_MASK                      (0xFFU)
#define CAN_WMB_WMBn_D03_Data_byte_3_SHIFT                     (0U)
#define CAN_WMB_WMBn_D03_Data_byte_3(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D03_Data_byte_3_SHIFT)) & CAN_WMB_WMBn_D03_Data_byte_3_MASK)
/* CAN_WMB_WMBn_D47 Register */
#define CAN_WMB_WMBn_D47_Data_byte_4_MASK                      (0xFF000000U)
#define CAN_WMB_WMBn_D47_Data_byte_4_SHIFT                     (24U)
#define CAN_WMB_WMBn_D47_Data_byte_4(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D47_Data_byte_4_SHIFT)) & CAN_WMB_WMBn_D47_Data_byte_4_MASK)
#define CAN_WMB_WMBn_D47_Data_byte_5_MASK                      (0xFF0000U)
#define CAN_WMB_WMBn_D47_Data_byte_5_SHIFT                     (16U)
#define CAN_WMB_WMBn_D47_Data_byte_5(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D47_Data_byte_5_SHIFT)) & CAN_WMB_WMBn_D47_Data_byte_5_MASK)
#define CAN_WMB_WMBn_D47_Data_byte_6_MASK                      (0xFF00U)
#define CAN_WMB_WMBn_D47_Data_byte_6_SHIFT                     (8U)
#define CAN_WMB_WMBn_D47_Data_byte_6(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D47_Data_byte_6_SHIFT)) & CAN_WMB_WMBn_D47_Data_byte_6_MASK)
#define CAN_WMB_WMBn_D47_Data_byte_7_MASK                      (0xFFU)
#define CAN_WMB_WMBn_D47_Data_byte_7_SHIFT                     (0U)
#define CAN_WMB_WMBn_D47_Data_byte_7(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_WMB_WMBn_D47_Data_byte_7_SHIFT)) & CAN_WMB_WMBn_D47_Data_byte_7_MASK)

/* CAN_EPRS Register */
#define CAN_EPRS_EDPRESDIV_MASK                            (0x3FF0000U)
#define CAN_EPRS_EDPRESDIV_SHIFT                           (16U)
#define CAN_EPRS_EDPRESDIV(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_EPRS_EDPRESDIV_SHIFT)) & CAN_EPRS_EDPRESDIV_MASK)
#define CAN_EPRS_ENPRESDIV_MASK                            (0x3FFU)
#define CAN_EPRS_ENPRESDIV_SHIFT                           (0U)
#define CAN_EPRS_ENPRESDIV(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_EPRS_ENPRESDIV_SHIFT)) & CAN_EPRS_ENPRESDIV_MASK)
/* CAN_ENCBT Register */
#define CAN_ENCBT_NRJW_MASK                                (0x1FC00000U)
#define CAN_ENCBT_NRJW_SHIFT                               (22U)
#define CAN_ENCBT_NRJW(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ENCBT_NRJW_SHIFT)) & CAN_ENCBT_NRJW_MASK)
#define CAN_ENCBT_NTSEG2_MASK                              (0x7F000U)
#define CAN_ENCBT_NTSEG2_SHIFT                             (12U)
#define CAN_ENCBT_NTSEG2(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ENCBT_NTSEG2_SHIFT)) & CAN_ENCBT_NTSEG2_MASK)
#define CAN_ENCBT_NTSEG1_MASK                              (0xFFU)
#define CAN_ENCBT_NTSEG1_SHIFT                             (0U)
#define CAN_ENCBT_NTSEG1(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ENCBT_NTSEG1_SHIFT)) & CAN_ENCBT_NTSEG1_MASK)
/* CAN_EDCBT Register */
#define CAN_EDCBT_DRJW_MASK                                (0x3C00000U)
#define CAN_EDCBT_DRJW_SHIFT                               (22U)
#define CAN_EDCBT_DRJW(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_EDCBT_DRJW_SHIFT)) & CAN_EDCBT_DRJW_MASK)
#define CAN_EDCBT_DTSEG2_MASK                              (0xF000U)
#define CAN_EDCBT_DTSEG2_SHIFT                             (12U)
#define CAN_EDCBT_DTSEG2(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_EDCBT_DTSEG2_SHIFT)) & CAN_EDCBT_DTSEG2_MASK)
#define CAN_EDCBT_DTSEG1_MASK                              (0x1FU)
#define CAN_EDCBT_DTSEG1_SHIFT                             (0U)
#define CAN_EDCBT_DTSEG1(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_EDCBT_DTSEG1_SHIFT)) & CAN_EDCBT_DTSEG1_MASK)
/* CAN_ETDC Register */
#define CAN_ETDC_ETDCEN_MASK                               (0x80000000U)
#define CAN_ETDC_ETDCEN_SHIFT                              (31U)
#define CAN_ETDC_ETDCEN(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ETDC_ETDCEN_SHIFT)) & CAN_ETDC_ETDCEN_MASK)
#define CAN_ETDC_TDMDIS_MASK                               (0x40000000U)
#define CAN_ETDC_TDMDIS_SHIFT                              (30U)
#define CAN_ETDC_TDMDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ETDC_TDMDIS_SHIFT)) & CAN_ETDC_TDMDIS_MASK)
#define CAN_ETDC_ETDCOFF_MASK                              (0x7F0000U)
#define CAN_ETDC_ETDCOFF_SHIFT                             (16U)
#define CAN_ETDC_ETDCOFF(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ETDC_ETDCOFF_SHIFT)) & CAN_ETDC_ETDCOFF_MASK)
#define CAN_ETDC_ETDCFAIL_MASK                             (0x8000U)
#define CAN_ETDC_ETDCFAIL_SHIFT                            (15U)
#define CAN_ETDC_ETDCFAIL(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_ETDC_ETDCFAIL_SHIFT)) & CAN_ETDC_ETDCFAIL_MASK)
#define CAN_ETDC_ETDCVAL_MASK                              (0xFFU)
#define CAN_ETDC_ETDCVAL_SHIFT                             (0U)
#define CAN_ETDC_ETDCVAL(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ETDC_ETDCVAL_SHIFT)) & CAN_ETDC_ETDCVAL_MASK)
/* CAN_FDCTRL Register */
#define CAN_FDCTRL_FDRATE_MASK                             (0x80000000U)
#define CAN_FDCTRL_FDRATE_SHIFT                            (31U)
#define CAN_FDCTRL_FDRATE(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_FDRATE_SHIFT)) & CAN_FDCTRL_FDRATE_MASK)
#define CAN_FDCTRL_MBDSR3_MASK                             (0x6000000U)
#define CAN_FDCTRL_MBDSR3_SHIFT                            (25U)
#define CAN_FDCTRL_MBDSR3(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_MBDSR3_SHIFT)) & CAN_FDCTRL_MBDSR3_MASK)
#define CAN_FDCTRL_MBDSR2_MASK                             (0xC00000U)
#define CAN_FDCTRL_MBDSR2_SHIFT                            (22U)
#define CAN_FDCTRL_MBDSR2(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_MBDSR2_SHIFT)) & CAN_FDCTRL_MBDSR2_MASK)
#define CAN_FDCTRL_MBDSR1_MASK                             (0x180000U)
#define CAN_FDCTRL_MBDSR1_SHIFT                            (19U)
#define CAN_FDCTRL_MBDSR1(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_MBDSR1_SHIFT)) & CAN_FDCTRL_MBDSR1_MASK)
#define CAN_FDCTRL_MBDSR0_MASK                             (0x30000U)
#define CAN_FDCTRL_MBDSR0_SHIFT                            (16U)
#define CAN_FDCTRL_MBDSR0(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_MBDSR0_SHIFT)) & CAN_FDCTRL_MBDSR0_MASK)
#define CAN_FDCTRL_TDCEN_MASK                              (0x8000U)
#define CAN_FDCTRL_TDCEN_SHIFT                             (15U)
#define CAN_FDCTRL_TDCEN(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_TDCEN_SHIFT)) & CAN_FDCTRL_TDCEN_MASK)
#define CAN_FDCTRL_TDCFAIL_MASK                            (0x4000U)
#define CAN_FDCTRL_TDCFAIL_SHIFT                           (14U)
#define CAN_FDCTRL_TDCFAIL(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_TDCFAIL_SHIFT)) & CAN_FDCTRL_TDCFAIL_MASK)
#define CAN_FDCTRL_TDCOFF_MASK                             (0x1F00U)
#define CAN_FDCTRL_TDCOFF_SHIFT                            (8U)
#define CAN_FDCTRL_TDCOFF(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_TDCOFF_SHIFT)) & CAN_FDCTRL_TDCOFF_MASK)
#define CAN_FDCTRL_TDCVAL_MASK                             (0x3FU)
#define CAN_FDCTRL_TDCVAL_SHIFT                            (0U)
#define CAN_FDCTRL_TDCVAL(x)                               (((uint32_t)(((uint32_t)(x)) << CAN_FDCTRL_TDCVAL_SHIFT)) & CAN_FDCTRL_TDCVAL_MASK)
/* CAN_FDCBT Register */
#define CAN_FDCBT_FPRESDIV_MASK                            (0x3FF00000U)
#define CAN_FDCBT_FPRESDIV_SHIFT                           (20U)
#define CAN_FDCBT_FPRESDIV(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_FDCBT_FPRESDIV_SHIFT)) & CAN_FDCBT_FPRESDIV_MASK)
#define CAN_FDCBT_FRJW_MASK                                (0x70000U)
#define CAN_FDCBT_FRJW_SHIFT                               (16U)
#define CAN_FDCBT_FRJW(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_FDCBT_FRJW_SHIFT)) & CAN_FDCBT_FRJW_MASK)
#define CAN_FDCBT_FPROPSEG_MASK                            (0x7C00U)
#define CAN_FDCBT_FPROPSEG_SHIFT                           (10U)
#define CAN_FDCBT_FPROPSEG(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_FDCBT_FPROPSEG_SHIFT)) & CAN_FDCBT_FPROPSEG_MASK)
#define CAN_FDCBT_FPSEG1_MASK                              (0xE0U)
#define CAN_FDCBT_FPSEG1_SHIFT                             (5U)
#define CAN_FDCBT_FPSEG1(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_FDCBT_FPSEG1_SHIFT)) & CAN_FDCBT_FPSEG1_MASK)
#define CAN_FDCBT_FPSEG2_MASK                              (0x7U)
#define CAN_FDCBT_FPSEG2_SHIFT                             (0U)
#define CAN_FDCBT_FPSEG2(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_FDCBT_FPSEG2_SHIFT)) & CAN_FDCBT_FPSEG2_MASK)
/* CAN_FDCRC Register */
#define CAN_FDCRC_FD_MBCRC_MASK                            (0x7F000000U)
#define CAN_FDCRC_FD_MBCRC_SHIFT                           (24U)
#define CAN_FDCRC_FD_MBCRC(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_FDCRC_FD_MBCRC_SHIFT)) & CAN_FDCRC_FD_MBCRC_MASK)
#define CAN_FDCRC_FD_TXCRC_MASK                            (0x1FFFFFU)
#define CAN_FDCRC_FD_TXCRC_SHIFT                           (0U)
#define CAN_FDCRC_FD_TXCRC(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_FDCRC_FD_TXCRC_SHIFT)) & CAN_FDCRC_FD_TXCRC_MASK)
/* CAN_ERFCR Register */
#define CAN_ERFCR_ERFEN_MASK                               (0x80000000U)
#define CAN_ERFCR_ERFEN_SHIFT                              (31U)
#define CAN_ERFCR_ERFEN(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFCR_ERFEN_SHIFT)) & CAN_ERFCR_ERFEN_MASK)
#define CAN_ERFCR_DMALW_MASK                               (0x7C000000U)
#define CAN_ERFCR_DMALW_SHIFT                              (26U)
#define CAN_ERFCR_DMALW(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFCR_DMALW_SHIFT)) & CAN_ERFCR_DMALW_MASK)
#define CAN_ERFCR_NEXIF_MASK                               (0x7F0000U)
#define CAN_ERFCR_NEXIF_SHIFT                              (16U)
#define CAN_ERFCR_NEXIF(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFCR_NEXIF_SHIFT)) & CAN_ERFCR_NEXIF_MASK)
#define CAN_ERFCR_NFE_MASK                                 (0x3F00U)
#define CAN_ERFCR_NFE_SHIFT                                (8U)
#define CAN_ERFCR_NFE(x)                                   (((uint32_t)(((uint32_t)(x)) << CAN_ERFCR_NFE_SHIFT)) & CAN_ERFCR_NFE_MASK)
#define CAN_ERFCR_ERFWM_MASK                               (0x1FU)
#define CAN_ERFCR_ERFWM_SHIFT                              (0U)
#define CAN_ERFCR_ERFWM(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFCR_ERFWM_SHIFT)) & CAN_ERFCR_ERFWM_MASK)
/* CAN_ERFIER Register */
#define CAN_ERFIER_ERFUFWIE_MASK                           (0x80000000U)
#define CAN_ERFIER_ERFUFWIE_SHIFT                          (31U)
#define CAN_ERFIER_ERFUFWIE(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_ERFIER_ERFUFWIE_SHIFT)) & CAN_ERFIER_ERFUFWIE_MASK)
#define CAN_ERFIER_ERFOVFIE_MASK                           (0x40000000U)
#define CAN_ERFIER_ERFOVFIE_SHIFT                          (30U)
#define CAN_ERFIER_ERFOVFIE(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_ERFIER_ERFOVFIE_SHIFT)) & CAN_ERFIER_ERFOVFIE_MASK)
#define CAN_ERFIER_ERFWMIIE_MASK                           (0x20000000U)
#define CAN_ERFIER_ERFWMIIE_SHIFT                          (29U)
#define CAN_ERFIER_ERFWMIIE(x)                             (((uint32_t)(((uint32_t)(x)) << CAN_ERFIER_ERFWMIIE_SHIFT)) & CAN_ERFIER_ERFWMIIE_MASK)
#define CAN_ERFIER_ERFDAIE_MASK                            (0x10000000U)
#define CAN_ERFIER_ERFDAIE_SHIFT                           (28U)
#define CAN_ERFIER_ERFDAIE(x)                              (((uint32_t)(((uint32_t)(x)) << CAN_ERFIER_ERFDAIE_SHIFT)) & CAN_ERFIER_ERFDAIE_MASK)
/* CAN_ERFSR Register */
#define CAN_ERFSR_ERFUFW_MASK                              (0x80000000U)
#define CAN_ERFSR_ERFUFW_SHIFT                             (31U)
#define CAN_ERFSR_ERFUFW(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFUFW_SHIFT)) & CAN_ERFSR_ERFUFW_MASK)
#define CAN_ERFSR_ERFOVF_MASK                              (0x40000000U)
#define CAN_ERFSR_ERFOVF_SHIFT                             (30U)
#define CAN_ERFSR_ERFOVF(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFOVF_SHIFT)) & CAN_ERFSR_ERFOVF_MASK)
#define CAN_ERFSR_ERFWMI_MASK                              (0x20000000U)
#define CAN_ERFSR_ERFWMI_SHIFT                             (29U)
#define CAN_ERFSR_ERFWMI(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFWMI_SHIFT)) & CAN_ERFSR_ERFWMI_MASK)
#define CAN_ERFSR_ERFDA_MASK                               (0x10000000U)
#define CAN_ERFSR_ERFDA_SHIFT                              (28U)
#define CAN_ERFSR_ERFDA(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFDA_SHIFT)) & CAN_ERFSR_ERFDA_MASK)
#define CAN_ERFSR_ERFCLR_MASK                              (0x8000000U)
#define CAN_ERFSR_ERFCLR_SHIFT                             (27U)
#define CAN_ERFSR_ERFCLR(x)                                (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFCLR_SHIFT)) & CAN_ERFSR_ERFCLR_MASK)
#define CAN_ERFSR_ERFE_MASK                                (0x20000U)
#define CAN_ERFSR_ERFE_SHIFT                               (17U)
#define CAN_ERFSR_ERFE(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFE_SHIFT)) & CAN_ERFSR_ERFE_MASK)
#define CAN_ERFSR_ERFF_MASK                                (0x10000U)
#define CAN_ERFSR_ERFF_SHIFT                               (16U)
#define CAN_ERFSR_ERFF(x)                                  (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFF_SHIFT)) & CAN_ERFSR_ERFF_MASK)
#define CAN_ERFSR_ERFEL_MASK                               (0x3FU)
#define CAN_ERFSR_ERFEL_SHIFT                              (0U)
#define CAN_ERFSR_ERFEL(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFSR_ERFEL_SHIFT)) & CAN_ERFSR_ERFEL_MASK)
/* CAN_HR_TIME_STAMPn Register */
#define CAN_HR_TIME_STAMPn_TS_MASK                         (0xFFFFFFFFU)
#define CAN_HR_TIME_STAMPn_TS_SHIFT                        (0U)
#define CAN_HR_TIME_STAMPn_TS(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_HR_TIME_STAMPn_TS_SHIFT)) & CAN_HR_TIME_STAMPn_TS_MASK)
/* CAN_ERFFELn Register */
#define CAN_ERFFELn_FEL_MASK                               (0xFFFFFFFFU)
#define CAN_ERFFELn_FEL_SHIFT                              (0U)
#define CAN_ERFFELn_FEL(x)                                 (((uint32_t)(((uint32_t)(x)) << CAN_ERFFELn_FEL_SHIFT)) & CAN_ERFFELn_FEL_MASK)


/*!
 * @}
 */ /* end of group CAN_Register_Masks */


/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- LINFlexD Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup LINFlexD_Peripheral_Access_Layer LINFlexD Peripheral Access Layer
 * @{
 */


/** LINFlexD - Size of Registers Arrays */
#define LINFlexD_IFCR_COUNT                     (16)

/* LINFlexD Register Layout Typedef */
typedef struct {
    __IO uint32_t LINCR1;                             /**< LIN Control Register 1, offset: 0x0000 */
    __IO uint32_t LINIER;                             /**< LIN Interrupt Enable Register, offset: 0x0004 */
    __IO uint32_t LINSR;                              /**< LIN Status Register, offset: 0x0008 */
    __IO uint32_t LINESR;                             /**< LIN Error Status Register, offset: 0x000C */
    __IO uint32_t UARTCR;                             /**< UART Mode Control Register, offset: 0x0010 */
    __IO uint32_t UARTSR;                             /**< UART Mode Status Register, offset: 0x0014 */
    __IO uint32_t LINTCSR;                            /**< LIN Timeout Control Status Register, offset: 0x0018 */
    __IO uint32_t LINOCR;                             /**< LIN Output Compare Register, offset: 0x001C */
    __IO uint32_t LINTOCR;                            /**< LIN Timeout Control Register, offset: 0x0020 */
    __IO uint32_t LINFBRR;                            /**< LIN Fractional Baud Rate Register, offset: 0x0024 */
    __IO uint32_t LINIBRR;                            /**< LIN Integer Baud Rate Register, offset: 0x0028 */
    __IO uint32_t LINCFR;                             /**< LIN Checksum Field Register, offset: 0x002C */
    __IO uint32_t LINCR2;                             /**< LIN Control Register 2, offset: 0x0030 */
    __IO uint32_t BIDR;                               /**< Buffer Identifier Register, offset: 0x0034 */
    union {
    __IO uint8_t DATA8[ 8];                          /**< Data in byte, offset: 0x0038 */
    __IO uint16_t DATA16[ 4];                         /**< Data in half-word, offset: 0x0038 */
    __IO uint32_t DATA32[ 2];                         /**< Data in word, offset: 0x0038 */

    } DATA;
    __IO uint32_t IFER;                               /**< Identifier Filter Enable Register, offset: 0x0040 */
    __I  uint32_t IFMI;                               /**< Identifier Filter Match Index, offset: 0x0044 */
    __IO uint32_t IFMR;                               /**< Identifier Filter Mode Register, offset: 0x0048 */
    __IO uint32_t IFCR[16];                           /**< Identifier Filter Control Register, offset: 0x004C */
    __IO uint32_t GCR;                                /**< Global Control Register, offset: 0x008C */
    __IO uint32_t UARTPTO;                            /**< UART Preset Timeout Register, offset: 0x0090 */
    __I  uint32_t UARTCTO;                            /**< UART Current Timeout Register, offset: 0x0094 */
    __IO uint32_t DMATXE;                             /**< DMA Tx Enable Register, offset: 0x0098 */
    __IO uint32_t DMARXE;                             /**< DMA Rx Enable Register, offset: 0x009C */

} LINFlexD_Type, *LINFlexD_MemMapPtr;

/** Number of instances of the LINFlexD module. */
#define LINFlexD_INSTANCE_COUNT                        (6u)

/* LINFlexD0  base address */
#define LINFlexD0_BASE                                     (0x4001B000)
#define LINFlexD0                                          ((LINFlexD_Type *)(LINFlexD0_BASE))
/* LINFlexD1  base address */
#define LINFlexD1_BASE                                     (0x4001C000)
#define LINFlexD1                                          ((LINFlexD_Type *)(LINFlexD1_BASE))
/* LINFlexD2  base address */
#define LINFlexD2_BASE                                     (0x4001D000)
#define LINFlexD2                                          ((LINFlexD_Type *)(LINFlexD2_BASE))
/* LINFlexD3  base address */
#define LINFlexD3_BASE                                     (0x4001E000)
#define LINFlexD3                                          ((LINFlexD_Type *)(LINFlexD3_BASE))
/* LINFlexD4  base address */
#define LINFlexD4_BASE                                     (0x4001F000)
#define LINFlexD4                                          ((LINFlexD_Type *)(LINFlexD4_BASE))
/* LINFlexD5  base address */
#define LINFlexD5_BASE                                     (0x40020000)
#define LINFlexD5                                          ((LINFlexD_Type *)(LINFlexD5_BASE))

/** Array initializer of LINFlexD peripheral base addresses */
#define LINFlexD_BASE_ADDRS                                { LINFlexD0_BASE,  LINFlexD1_BASE,  LINFlexD2_BASE,  LINFlexD3_BASE,  LINFlexD4_BASE,  LINFlexD5_BASE }
/** Array initializer of LINFlexD peripheral base pointers */
#define LINFlexD_BASE_PTRS                                 { LINFlexD0,  LINFlexD1,  LINFlexD2,  LINFlexD3,  LINFlexD4,  LINFlexD5 }
/** Number of interrupt vector arrays for the LINFlexD module. */
#define LINFlexD_IRQS_ARR_COUNT                            (1u)
/** Number of interrupt channels for the LINFlexD. */
#define LINFlexD_IRQS_CH_COUNT                    (1u)
/** Interrupt vectors for the LINFlexD peripheral type */
#define LINFlexD_IRQS                             { LINFlexD0_IRQn, LINFlexD1_IRQn, LINFlexD2_IRQn, LINFlexD3_IRQn, LINFlexD4_IRQn, LINFlexD5_IRQn }

/* LINFlexD Register Mask */
/* LINFlexD_LINCR1 Register */
#define LINFlexD_LINCR1_NLSE_MASK                               (0x10000U)
#define LINFlexD_LINCR1_NLSE_SHIFT                              (16U)
#define LINFlexD_LINCR1_NLSE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_NLSE_SHIFT)) & LINFlexD_LINCR1_NLSE_MASK)
#define LINFlexD_LINCR1_CCD_MASK                                (0x8000U)
#define LINFlexD_LINCR1_CCD_SHIFT                               (15U)
#define LINFlexD_LINCR1_CCD(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_CCD_SHIFT)) & LINFlexD_LINCR1_CCD_MASK)
#define LINFlexD_LINCR1_CFD_MASK                                (0x4000U)
#define LINFlexD_LINCR1_CFD_SHIFT                               (14U)
#define LINFlexD_LINCR1_CFD(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_CFD_SHIFT)) & LINFlexD_LINCR1_CFD_MASK)
#define LINFlexD_LINCR1_LASE_MASK                               (0x2000U)
#define LINFlexD_LINCR1_LASE_SHIFT                              (13U)
#define LINFlexD_LINCR1_LASE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_LASE_SHIFT)) & LINFlexD_LINCR1_LASE_MASK)
#define LINFlexD_LINCR1_AUTOWU_MASK                             (0x1000U)
#define LINFlexD_LINCR1_AUTOWU_SHIFT                            (12U)
#define LINFlexD_LINCR1_AUTOWU(x)                               (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_AUTOWU_SHIFT)) & LINFlexD_LINCR1_AUTOWU_MASK)
#define LINFlexD_LINCR1_MBL_MASK                                (0xF00U)
#define LINFlexD_LINCR1_MBL_SHIFT                               (8U)
#define LINFlexD_LINCR1_MBL(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_MBL_SHIFT)) & LINFlexD_LINCR1_MBL_MASK)
#define LINFlexD_LINCR1_BF_MASK                                 (0x80U)
#define LINFlexD_LINCR1_BF_SHIFT                                (7U)
#define LINFlexD_LINCR1_BF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_BF_SHIFT)) & LINFlexD_LINCR1_BF_MASK)
#define LINFlexD_LINCR1_LBKM_MASK                               (0x20U)
#define LINFlexD_LINCR1_LBKM_SHIFT                              (5U)
#define LINFlexD_LINCR1_LBKM(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_LBKM_SHIFT)) & LINFlexD_LINCR1_LBKM_MASK)
#define LINFlexD_LINCR1_MME_MASK                                (0x10U)
#define LINFlexD_LINCR1_MME_SHIFT                               (4U)
#define LINFlexD_LINCR1_MME(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_MME_SHIFT)) & LINFlexD_LINCR1_MME_MASK)
#define LINFlexD_LINCR1_SSBL_MASK                               (0x8U)
#define LINFlexD_LINCR1_SSBL_SHIFT                              (3U)
#define LINFlexD_LINCR1_SSBL(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_SSBL_SHIFT)) & LINFlexD_LINCR1_SSBL_MASK)
#define LINFlexD_LINCR1_RBLM_MASK                               (0x4U)
#define LINFlexD_LINCR1_RBLM_SHIFT                              (2U)
#define LINFlexD_LINCR1_RBLM(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_RBLM_SHIFT)) & LINFlexD_LINCR1_RBLM_MASK)
#define LINFlexD_LINCR1_SLEEP_MASK                              (0x2U)
#define LINFlexD_LINCR1_SLEEP_SHIFT                             (1U)
#define LINFlexD_LINCR1_SLEEP(x)                                (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_SLEEP_SHIFT)) & LINFlexD_LINCR1_SLEEP_MASK)
#define LINFlexD_LINCR1_INIT_MASK                               (0x1U)
#define LINFlexD_LINCR1_INIT_SHIFT                              (0U)
#define LINFlexD_LINCR1_INIT(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_INIT_SHIFT)) & LINFlexD_LINCR1_INIT_MASK)
/* LINFlexD_LINIER Register */
#define LINFlexD_LINIER_SZIE_MASK                               (0x8000U)
#define LINFlexD_LINIER_SZIE_SHIFT                              (15U)
#define LINFlexD_LINIER_SZIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_SZIE_SHIFT)) & LINFlexD_LINIER_SZIE_MASK)
#define LINFlexD_LINIER_OCIE_MASK                               (0x4000U)
#define LINFlexD_LINIER_OCIE_SHIFT                              (14U)
#define LINFlexD_LINIER_OCIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_OCIE_SHIFT)) & LINFlexD_LINIER_OCIE_MASK)
#define LINFlexD_LINIER_BEIE_MASK                               (0x2000U)
#define LINFlexD_LINIER_BEIE_SHIFT                              (13U)
#define LINFlexD_LINIER_BEIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_BEIE_SHIFT)) & LINFlexD_LINIER_BEIE_MASK)
#define LINFlexD_LINIER_CEIE_MASK                               (0x1000U)
#define LINFlexD_LINIER_CEIE_SHIFT                              (12U)
#define LINFlexD_LINIER_CEIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_CEIE_SHIFT)) & LINFlexD_LINIER_CEIE_MASK)
#define LINFlexD_LINIER_HEIE_MASK                               (0x800U)
#define LINFlexD_LINIER_HEIE_SHIFT                              (11U)
#define LINFlexD_LINIER_HEIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_HEIE_SHIFT)) & LINFlexD_LINIER_HEIE_MASK)
#define LINFlexD_LINIER_FEIE_MASK                               (0x100U)
#define LINFlexD_LINIER_FEIE_SHIFT                              (8U)
#define LINFlexD_LINIER_FEIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_FEIE_SHIFT)) & LINFlexD_LINIER_FEIE_MASK)
#define LINFlexD_LINIER_BOIE_MASK                               (0x80U)
#define LINFlexD_LINIER_BOIE_SHIFT                              (7U)
#define LINFlexD_LINIER_BOIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_BOIE_SHIFT)) & LINFlexD_LINIER_BOIE_MASK)
#define LINFlexD_LINIER_LSIE_MASK                               (0x40U)
#define LINFlexD_LINIER_LSIE_SHIFT                              (6U)
#define LINFlexD_LINIER_LSIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_LSIE_SHIFT)) & LINFlexD_LINIER_LSIE_MASK)
#define LINFlexD_LINIER_WUIE_MASK                               (0x20U)
#define LINFlexD_LINIER_WUIE_SHIFT                              (5U)
#define LINFlexD_LINIER_WUIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_WUIE_SHIFT)) & LINFlexD_LINIER_WUIE_MASK)
#define LINFlexD_LINIER_TOIE_MASK                               (0x8U)
#define LINFlexD_LINIER_TOIE_SHIFT                              (3U)
#define LINFlexD_LINIER_TOIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_TOIE_SHIFT)) & LINFlexD_LINIER_TOIE_MASK)
#define LINFlexD_LINIER_DRIE_MASK                               (0x4U)
#define LINFlexD_LINIER_DRIE_SHIFT                              (2U)
#define LINFlexD_LINIER_DRIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_DRIE_SHIFT)) & LINFlexD_LINIER_DRIE_MASK)
#define LINFlexD_LINIER_DTIE_MASK                               (0x2U)
#define LINFlexD_LINIER_DTIE_SHIFT                              (1U)
#define LINFlexD_LINIER_DTIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_DTIE_SHIFT)) & LINFlexD_LINIER_DTIE_MASK)
#define LINFlexD_LINIER_HRIE_MASK                               (0x1U)
#define LINFlexD_LINIER_HRIE_SHIFT                              (0U)
#define LINFlexD_LINIER_HRIE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIER_HRIE_SHIFT)) & LINFlexD_LINIER_HRIE_MASK)
/* LINFlexD_LINSR Register */
#define LINFlexD_LINSR_AUTOSYNC_COMP_MASK                       (0x80000U)
#define LINFlexD_LINSR_AUTOSYNC_COMP_SHIFT                      (19U)
#define LINFlexD_LINSR_AUTOSYNC_COMP(x)                         (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_AUTOSYNC_COMP_SHIFT)) & LINFlexD_LINSR_AUTOSYNC_COMP_MASK)
#define LINFlexD_LINSR_RDC_MASK                                 (0x70000U)
#define LINFlexD_LINSR_RDC_SHIFT                                (16U)
#define LINFlexD_LINSR_RDC(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_RDC_SHIFT)) & LINFlexD_LINSR_RDC_MASK)
#define LINFlexD_LINSR_LINS_MASK                                (0xF000U)
#define LINFlexD_LINSR_LINS_SHIFT                               (12U)
#define LINFlexD_LINSR_LINS(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_LINS_SHIFT)) & LINFlexD_LINSR_LINS_MASK)
#define LINFlexD_LINSR_RMB_MASK                                 (0x200U)
#define LINFlexD_LINSR_RMB_SHIFT                                (9U)
#define LINFlexD_LINSR_RMB(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_RMB_SHIFT)) & LINFlexD_LINSR_RMB_MASK)
#define LINFlexD_LINSR_DRBNE_MASK                               (0x100U)
#define LINFlexD_LINSR_DRBNE_SHIFT                              (8U)
#define LINFlexD_LINSR_DRBNE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_DRBNE_SHIFT)) & LINFlexD_LINSR_DRBNE_MASK)
#define LINFlexD_LINSR_RXBUSY_MASK                              (0x80U)
#define LINFlexD_LINSR_RXBUSY_SHIFT                             (7U)
#define LINFlexD_LINSR_RXBUSY(x)                                (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_RXBUSY_SHIFT)) & LINFlexD_LINSR_RXBUSY_MASK)
#define LINFlexD_LINSR_RDI_MASK                                 (0x40U)
#define LINFlexD_LINSR_RDI_SHIFT                                (6U)
#define LINFlexD_LINSR_RDI(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_RDI_SHIFT)) & LINFlexD_LINSR_RDI_MASK)
#define LINFlexD_LINSR_WUF_MASK                                 (0x20U)
#define LINFlexD_LINSR_WUF_SHIFT                                (5U)
#define LINFlexD_LINSR_WUF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_WUF_SHIFT)) & LINFlexD_LINSR_WUF_MASK)
#define LINFlexD_LINSR_DRF_MASK                                 (0x4U)
#define LINFlexD_LINSR_DRF_SHIFT                                (2U)
#define LINFlexD_LINSR_DRF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_DRF_SHIFT)) & LINFlexD_LINSR_DRF_MASK)
#define LINFlexD_LINSR_DTF_MASK                                 (0x2U)
#define LINFlexD_LINSR_DTF_SHIFT                                (1U)
#define LINFlexD_LINSR_DTF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_DTF_SHIFT)) & LINFlexD_LINSR_DTF_MASK)
#define LINFlexD_LINSR_HRF_MASK                                 (0x1U)
#define LINFlexD_LINSR_HRF_SHIFT                                (0U)
#define LINFlexD_LINSR_HRF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINSR_HRF_SHIFT)) & LINFlexD_LINSR_HRF_MASK)
/* LINFlexD_LINESR Register */
#define LINFlexD_LINESR_SZF_MASK                                (0x8000U)
#define LINFlexD_LINESR_SZF_SHIFT                               (15U)
#define LINFlexD_LINESR_SZF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_SZF_SHIFT)) & LINFlexD_LINESR_SZF_MASK)
#define LINFlexD_LINESR_OCF_MASK                                (0x4000U)
#define LINFlexD_LINESR_OCF_SHIFT                               (14U)
#define LINFlexD_LINESR_OCF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_OCF_SHIFT)) & LINFlexD_LINESR_OCF_MASK)
#define LINFlexD_LINESR_BEF_MASK                                (0x2000U)
#define LINFlexD_LINESR_BEF_SHIFT                               (13U)
#define LINFlexD_LINESR_BEF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_BEF_SHIFT)) & LINFlexD_LINESR_BEF_MASK)
#define LINFlexD_LINESR_CEF_MASK                                (0x1000U)
#define LINFlexD_LINESR_CEF_SHIFT                               (12U)
#define LINFlexD_LINESR_CEF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_CEF_SHIFT)) & LINFlexD_LINESR_CEF_MASK)
#define LINFlexD_LINESR_SFEF_MASK                               (0x800U)
#define LINFlexD_LINESR_SFEF_SHIFT                              (11U)
#define LINFlexD_LINESR_SFEF(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_SFEF_SHIFT)) & LINFlexD_LINESR_SFEF_MASK)
#define LINFlexD_LINESR_SDEF_MASK                               (0x400U)
#define LINFlexD_LINESR_SDEF_SHIFT                              (10U)
#define LINFlexD_LINESR_SDEF(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_SDEF_SHIFT)) & LINFlexD_LINESR_SDEF_MASK)
#define LINFlexD_LINESR_IDPEF_MASK                              (0x200U)
#define LINFlexD_LINESR_IDPEF_SHIFT                             (9U)
#define LINFlexD_LINESR_IDPEF(x)                                (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_IDPEF_SHIFT)) & LINFlexD_LINESR_IDPEF_MASK)
#define LINFlexD_LINESR_FEF_MASK                                (0x100U)
#define LINFlexD_LINESR_FEF_SHIFT                               (8U)
#define LINFlexD_LINESR_FEF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_FEF_SHIFT)) & LINFlexD_LINESR_FEF_MASK)
#define LINFlexD_LINESR_BOF_MASK                                (0x80U)
#define LINFlexD_LINESR_BOF_SHIFT                               (7U)
#define LINFlexD_LINESR_BOF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_BOF_SHIFT)) & LINFlexD_LINESR_BOF_MASK)
#define LINFlexD_LINESR_NF_MASK                                 (0x1U)
#define LINFlexD_LINESR_NF_SHIFT                                (0U)
#define LINFlexD_LINESR_NF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINESR_NF_SHIFT)) & LINFlexD_LINESR_NF_MASK)
/* LINFlexD_UARTCR Register */
#define LINFlexD_UARTCR_MIS_MASK                                (0x80000000U)
#define LINFlexD_UARTCR_MIS_SHIFT                               (31U)
#define LINFlexD_UARTCR_MIS(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_MIS_SHIFT)) & LINFlexD_UARTCR_MIS_MASK)
#define LINFlexD_UARTCR_CSP_MASK                                (0x70000000U)
#define LINFlexD_UARTCR_CSP_SHIFT                               (28U)
#define LINFlexD_UARTCR_CSP(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_CSP_SHIFT)) & LINFlexD_UARTCR_CSP_MASK)
#define LINFlexD_UARTCR_OSR_MASK                                (0xF000000U)
#define LINFlexD_UARTCR_OSR_SHIFT                               (24U)
#define LINFlexD_UARTCR_OSR(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_OSR_SHIFT)) & LINFlexD_UARTCR_OSR_MASK)
#define LINFlexD_UARTCR_ROSE_MASK                               (0x800000U)
#define LINFlexD_UARTCR_ROSE_SHIFT                              (23U)
#define LINFlexD_UARTCR_ROSE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_ROSE_SHIFT)) & LINFlexD_UARTCR_ROSE_MASK)
#define LINFlexD_UARTCR_NEF_MASK                                (0x700000U)
#define LINFlexD_UARTCR_NEF_SHIFT                               (20U)
#define LINFlexD_UARTCR_NEF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_NEF_SHIFT)) & LINFlexD_UARTCR_NEF_MASK)
#define LINFlexD_UARTCR_DTU_MASK                                (0x80000U)
#define LINFlexD_UARTCR_DTU_SHIFT                               (19U)
#define LINFlexD_UARTCR_DTU(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_DTU_SHIFT)) & LINFlexD_UARTCR_DTU_MASK)
#define LINFlexD_UARTCR_SBUR_MASK                               (0x60000U)
#define LINFlexD_UARTCR_SBUR_SHIFT                              (17U)
#define LINFlexD_UARTCR_SBUR(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_SBUR_SHIFT)) & LINFlexD_UARTCR_SBUR_MASK)
#define LINFlexD_UARTCR_WLS_MASK                                (0x10000U)
#define LINFlexD_UARTCR_WLS_SHIFT                               (16U)
#define LINFlexD_UARTCR_WLS(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_WLS_SHIFT)) & LINFlexD_UARTCR_WLS_MASK)
#define LINFlexD_UARTCR_TDFL_TFC_MASK                           (0xE000U)
#define LINFlexD_UARTCR_TDFL_TFC_SHIFT                          (13U)
#define LINFlexD_UARTCR_TDFL_TFC(x)                             (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TDFL_TFC_SHIFT)) & LINFlexD_UARTCR_TDFL_TFC_MASK)
#define LINFlexD_UARTCR_RDFL_RFC_MASK                           (0x1C00U)
#define LINFlexD_UARTCR_RDFL_RFC_SHIFT                          (10U)
#define LINFlexD_UARTCR_RDFL_RFC(x)                             (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RDFL_RFC_SHIFT)) & LINFlexD_UARTCR_RDFL_RFC_MASK)
#define LINFlexD_UARTCR_RFBM_MASK                               (0x200U)
#define LINFlexD_UARTCR_RFBM_SHIFT                              (9U)
#define LINFlexD_UARTCR_RFBM(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RFBM_SHIFT)) & LINFlexD_UARTCR_RFBM_MASK)
#define LINFlexD_UARTCR_TFBM_MASK                               (0x100U)
#define LINFlexD_UARTCR_TFBM_SHIFT                              (8U)
#define LINFlexD_UARTCR_TFBM(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TFBM_SHIFT)) & LINFlexD_UARTCR_TFBM_MASK)
#define LINFlexD_UARTCR_WL1_MASK                                (0x80U)
#define LINFlexD_UARTCR_WL1_SHIFT                               (7U)
#define LINFlexD_UARTCR_WL1(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_WL1_SHIFT)) & LINFlexD_UARTCR_WL1_MASK)
#define LINFlexD_UARTCR_PC1_MASK                                (0x40U)
#define LINFlexD_UARTCR_PC1_SHIFT                               (6U)
#define LINFlexD_UARTCR_PC1(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_PC1_SHIFT)) & LINFlexD_UARTCR_PC1_MASK)
#define LINFlexD_UARTCR_RxEn_MASK                               (0x20U)
#define LINFlexD_UARTCR_RxEn_SHIFT                              (5U)
#define LINFlexD_UARTCR_RxEn(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RxEn_SHIFT)) & LINFlexD_UARTCR_RxEn_MASK)
#define LINFlexD_UARTCR_TxEn_MASK                               (0x10U)
#define LINFlexD_UARTCR_TxEn_SHIFT                              (4U)
#define LINFlexD_UARTCR_TxEn(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TxEn_SHIFT)) & LINFlexD_UARTCR_TxEn_MASK)
#define LINFlexD_UARTCR_PC0_MASK                                (0x8U)
#define LINFlexD_UARTCR_PC0_SHIFT                               (3U)
#define LINFlexD_UARTCR_PC0(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_PC0_SHIFT)) & LINFlexD_UARTCR_PC0_MASK)
#define LINFlexD_UARTCR_PCE_MASK                                (0x4U)
#define LINFlexD_UARTCR_PCE_SHIFT                               (2U)
#define LINFlexD_UARTCR_PCE(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_PCE_SHIFT)) & LINFlexD_UARTCR_PCE_MASK)
#define LINFlexD_UARTCR_WL0_MASK                                (0x2U)
#define LINFlexD_UARTCR_WL0_SHIFT                               (1U)
#define LINFlexD_UARTCR_WL0(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_WL0_SHIFT)) & LINFlexD_UARTCR_WL0_MASK)
#define LINFlexD_UARTCR_UART_MASK                               (0x1U)
#define LINFlexD_UARTCR_UART_SHIFT                              (0U)
#define LINFlexD_UARTCR_UART(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_UART_SHIFT)) & LINFlexD_UARTCR_UART_MASK)
/* LINFlexD_UARTSR Register */
#define LINFlexD_UARTSR_SZF_MASK                                (0x8000U)
#define LINFlexD_UARTSR_SZF_SHIFT                               (15U)
#define LINFlexD_UARTSR_SZF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_SZF_SHIFT)) & LINFlexD_UARTSR_SZF_MASK)
#define LINFlexD_UARTSR_OCF_MASK                                (0x4000U)
#define LINFlexD_UARTSR_OCF_SHIFT                               (14U)
#define LINFlexD_UARTSR_OCF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_OCF_SHIFT)) & LINFlexD_UARTSR_OCF_MASK)
#define LINFlexD_UARTSR_PE_MASK                                 (0x3C00U)
#define LINFlexD_UARTSR_PE_SHIFT                                (10U)
#define LINFlexD_UARTSR_PE(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_PE_SHIFT)) & LINFlexD_UARTSR_PE_MASK)
#define LINFlexD_UARTSR_RMB_MASK                                (0x200U)
#define LINFlexD_UARTSR_RMB_SHIFT                               (9U)
#define LINFlexD_UARTSR_RMB(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_RMB_SHIFT)) & LINFlexD_UARTSR_RMB_MASK)
#define LINFlexD_UARTSR_FEF_MASK                                (0x100U)
#define LINFlexD_UARTSR_FEF_SHIFT                               (8U)
#define LINFlexD_UARTSR_FEF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_FEF_SHIFT)) & LINFlexD_UARTSR_FEF_MASK)
#define LINFlexD_UARTSR_BOF_MASK                                (0x80U)
#define LINFlexD_UARTSR_BOF_SHIFT                               (7U)
#define LINFlexD_UARTSR_BOF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_BOF_SHIFT)) & LINFlexD_UARTSR_BOF_MASK)
#define LINFlexD_UARTSR_RDI_MASK                                (0x40U)
#define LINFlexD_UARTSR_RDI_SHIFT                               (6U)
#define LINFlexD_UARTSR_RDI(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_RDI_SHIFT)) & LINFlexD_UARTSR_RDI_MASK)
#define LINFlexD_UARTSR_WUF_MASK                                (0x20U)
#define LINFlexD_UARTSR_WUF_SHIFT                               (5U)
#define LINFlexD_UARTSR_WUF(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_WUF_SHIFT)) & LINFlexD_UARTSR_WUF_MASK)
#define LINFlexD_UARTSR_RFNE_MASK                               (0x10U)
#define LINFlexD_UARTSR_RFNE_SHIFT                              (4U)
#define LINFlexD_UARTSR_RFNE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_RFNE_SHIFT)) & LINFlexD_UARTSR_RFNE_MASK)
#define LINFlexD_UARTSR_TO_MASK                                 (0x8U)
#define LINFlexD_UARTSR_TO_SHIFT                                (3U)
#define LINFlexD_UARTSR_TO(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_TO_SHIFT)) & LINFlexD_UARTSR_TO_MASK)
#define LINFlexD_UARTSR_DRF_RFE_MASK                            (0x4U)
#define LINFlexD_UARTSR_DRF_RFE_SHIFT                           (2U)
#define LINFlexD_UARTSR_DRF_RFE(x)                              (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_DRF_RFE_SHIFT)) & LINFlexD_UARTSR_DRF_RFE_MASK)
#define LINFlexD_UARTSR_DTF_TFF_MASK                            (0x2U)
#define LINFlexD_UARTSR_DTF_TFF_SHIFT                           (1U)
#define LINFlexD_UARTSR_DTF_TFF(x)                              (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_DTF_TFF_SHIFT)) & LINFlexD_UARTSR_DTF_TFF_MASK)
#define LINFlexD_UARTSR_NF_MASK                                 (0x1U)
#define LINFlexD_UARTSR_NF_SHIFT                                (0U)
#define LINFlexD_UARTSR_NF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTSR_NF_SHIFT)) & LINFlexD_UARTSR_NF_MASK)
/* LINFlexD_LINTCSR Register */
#define LINFlexD_LINTCSR_MODE_MASK                              (0x400U)
#define LINFlexD_LINTCSR_MODE_SHIFT                             (10U)
#define LINFlexD_LINTCSR_MODE(x)                                (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTCSR_MODE_SHIFT)) & LINFlexD_LINTCSR_MODE_MASK)
#define LINFlexD_LINTCSR_IOT_MASK                               (0x200U)
#define LINFlexD_LINTCSR_IOT_SHIFT                              (9U)
#define LINFlexD_LINTCSR_IOT(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTCSR_IOT_SHIFT)) & LINFlexD_LINTCSR_IOT_MASK)
#define LINFlexD_LINTCSR_TOCE_MASK                              (0x100U)
#define LINFlexD_LINTCSR_TOCE_SHIFT                             (8U)
#define LINFlexD_LINTCSR_TOCE(x)                                (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTCSR_TOCE_SHIFT)) & LINFlexD_LINTCSR_TOCE_MASK)
#define LINFlexD_LINTCSR_CNT_MASK                               (0xFFU)
#define LINFlexD_LINTCSR_CNT_SHIFT                              (0U)
#define LINFlexD_LINTCSR_CNT(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTCSR_CNT_SHIFT)) & LINFlexD_LINTCSR_CNT_MASK)
/* LINFlexD_LINOCR Register */
#define LINFlexD_LINOCR_OC2_MASK                                (0xFF00U)
#define LINFlexD_LINOCR_OC2_SHIFT                               (8U)
#define LINFlexD_LINOCR_OC2(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINOCR_OC2_SHIFT)) & LINFlexD_LINOCR_OC2_MASK)
#define LINFlexD_LINOCR_OC1_MASK                                (0xFFU)
#define LINFlexD_LINOCR_OC1_SHIFT                               (0U)
#define LINFlexD_LINOCR_OC1(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINOCR_OC1_SHIFT)) & LINFlexD_LINOCR_OC1_MASK)
/* LINFlexD_LINTOCR Register */
#define LINFlexD_LINTOCR_RTO_MASK                               (0xF00U)
#define LINFlexD_LINTOCR_RTO_SHIFT                              (8U)
#define LINFlexD_LINTOCR_RTO(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTOCR_RTO_SHIFT)) & LINFlexD_LINTOCR_RTO_MASK)
#define LINFlexD_LINTOCR_HTO_MASK                               (0x7FU)
#define LINFlexD_LINTOCR_HTO_SHIFT                              (0U)
#define LINFlexD_LINTOCR_HTO(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINTOCR_HTO_SHIFT)) & LINFlexD_LINTOCR_HTO_MASK)
/* LINFlexD_LINFBRR Register */
#define LINFlexD_LINFBRR_FBR_WIDTH                              (4)
#define LINFlexD_LINFBRR_FBR_MASK                               (0xFU)
#define LINFlexD_LINFBRR_FBR_SHIFT                              (0U)
#define LINFlexD_LINFBRR_FBR(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINFBRR_FBR_SHIFT)) & LINFlexD_LINFBRR_FBR_MASK)
/* LINFlexD_LINIBRR Register */
#define LINFlexD_LINIBRR_IBR_MASK                               (0xFFFFFU)
#define LINFlexD_LINIBRR_IBR_SHIFT                              (0U)
#define LINFlexD_LINIBRR_IBR(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIBRR_IBR_SHIFT)) & LINFlexD_LINIBRR_IBR_MASK)
/* LINFlexD_LINCFR Register */
#define LINFlexD_LINCFR_CF_MASK                                 (0xFFU)
#define LINFlexD_LINCFR_CF_SHIFT                                (0U)
#define LINFlexD_LINCFR_CF(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCFR_CF_SHIFT)) & LINFlexD_LINCFR_CF_MASK)
/* LINFlexD_LINCR2 Register */
#define LINFlexD_LINCR2_TBDE_MASK                               (0x8000U)
#define LINFlexD_LINCR2_TBDE_SHIFT                              (15U)
#define LINFlexD_LINCR2_TBDE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_TBDE_SHIFT)) & LINFlexD_LINCR2_TBDE_MASK)
#define LINFlexD_LINCR2_IOBE_MASK                               (0x4000U)
#define LINFlexD_LINCR2_IOBE_SHIFT                              (14U)
#define LINFlexD_LINCR2_IOBE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_IOBE_SHIFT)) & LINFlexD_LINCR2_IOBE_MASK)
#define LINFlexD_LINCR2_IOPE_MASK                               (0x2000U)
#define LINFlexD_LINCR2_IOPE_SHIFT                              (13U)
#define LINFlexD_LINCR2_IOPE(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_IOPE_SHIFT)) & LINFlexD_LINCR2_IOPE_MASK)
#define LINFlexD_LINCR2_WURQ_MASK                               (0x1000U)
#define LINFlexD_LINCR2_WURQ_SHIFT                              (12U)
#define LINFlexD_LINCR2_WURQ(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_WURQ_SHIFT)) & LINFlexD_LINCR2_WURQ_MASK)
#define LINFlexD_LINCR2_DDRQ_MASK                               (0x800U)
#define LINFlexD_LINCR2_DDRQ_SHIFT                              (11U)
#define LINFlexD_LINCR2_DDRQ(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_DDRQ_SHIFT)) & LINFlexD_LINCR2_DDRQ_MASK)
#define LINFlexD_LINCR2_DTRQ_MASK                               (0x400U)
#define LINFlexD_LINCR2_DTRQ_SHIFT                              (10U)
#define LINFlexD_LINCR2_DTRQ(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_DTRQ_SHIFT)) & LINFlexD_LINCR2_DTRQ_MASK)
#define LINFlexD_LINCR2_ABRQ_MASK                               (0x200U)
#define LINFlexD_LINCR2_ABRQ_SHIFT                              (9U)
#define LINFlexD_LINCR2_ABRQ(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_ABRQ_SHIFT)) & LINFlexD_LINCR2_ABRQ_MASK)
#define LINFlexD_LINCR2_HTRQ_MASK                               (0x100U)
#define LINFlexD_LINCR2_HTRQ_SHIFT                              (8U)
#define LINFlexD_LINCR2_HTRQ(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR2_HTRQ_SHIFT)) & LINFlexD_LINCR2_HTRQ_MASK)
/* LINFlexD_BIDR Register */
#define LINFlexD_BIDR_DFL_MASK                                  (0x1C00U)
#define LINFlexD_BIDR_DFL_SHIFT                                 (10U)
#define LINFlexD_BIDR_DFL(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_BIDR_DFL_SHIFT)) & LINFlexD_BIDR_DFL_MASK)
#define LINFlexD_BIDR_DIR_MASK                                  (0x200U)
#define LINFlexD_BIDR_DIR_SHIFT                                 (9U)
#define LINFlexD_BIDR_DIR(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_BIDR_DIR_SHIFT)) & LINFlexD_BIDR_DIR_MASK)
#define LINFlexD_BIDR_CCS_MASK                                  (0x100U)
#define LINFlexD_BIDR_CCS_SHIFT                                 (8U)
#define LINFlexD_BIDR_CCS(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_BIDR_CCS_SHIFT)) & LINFlexD_BIDR_CCS_MASK)
#define LINFlexD_BIDR_ID_MASK                                   (0x3FU)
#define LINFlexD_BIDR_ID_SHIFT                                  (0U)
#define LINFlexD_BIDR_ID(x)                                     (((uint32_t)(((uint32_t)(x)) << LINFlexD_BIDR_ID_SHIFT)) & LINFlexD_BIDR_ID_MASK)
/* LINFlexD_DATA_DATA8 Register */
#define LINFlexD_DATA_DATA8_DATA_MASK                                (0xFFU)
#define LINFlexD_DATA_DATA8_DATA_SHIFT                               (0U)
#define LINFlexD_DATA_DATA8_DATA(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_DATA_DATA8_DATA_SHIFT)) & LINFlexD_DATA_DATA8_DATA_MASK)
/* LINFlexD_DATA_DATA16 Register */
#define LINFlexD_DATA_DATA16_DATA_MASK                               (0xFFFFU)
#define LINFlexD_DATA_DATA16_DATA_SHIFT                              (0U)
#define LINFlexD_DATA_DATA16_DATA(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_DATA_DATA16_DATA_SHIFT)) & LINFlexD_DATA_DATA16_DATA_MASK)
/* LINFlexD_DATA_DATA32 Register */
#define LINFlexD_DATA_DATA32_DATA_MASK                               (0xFFFFFFFFU)
#define LINFlexD_DATA_DATA32_DATA_SHIFT                              (0U)
#define LINFlexD_DATA_DATA32_DATA(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_DATA_DATA32_DATA_SHIFT)) & LINFlexD_DATA_DATA32_DATA_MASK)

/* LINFlexD_IFER Register */
#define LINFlexD_IFER_FACT_MASK                                 (0xFFFFU)
#define LINFlexD_IFER_FACT_SHIFT                                (0U)
#define LINFlexD_IFER_FACT(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFER_FACT_SHIFT)) & LINFlexD_IFER_FACT_MASK)
/* LINFlexD_IFMI Register */
#define LINFlexD_IFMI_IFMI_MASK                                 (0x1FU)
#define LINFlexD_IFMI_IFMI_SHIFT                                (0U)
#define LINFlexD_IFMI_IFMI(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFMI_IFMI_SHIFT)) & LINFlexD_IFMI_IFMI_MASK)
/* LINFlexD_IFMR Register */
#define LINFlexD_IFMR_IFM_MASK                                  (0xFFU)
#define LINFlexD_IFMR_IFM_SHIFT                                 (0U)
#define LINFlexD_IFMR_IFM(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFMR_IFM_SHIFT)) & LINFlexD_IFMR_IFM_MASK)
/* LINFlexD_IFCR Register */
#define LINFlexD_IFCR_DFL_MASK                                  (0x1C00U)
#define LINFlexD_IFCR_DFL_SHIFT                                 (10U)
#define LINFlexD_IFCR_DFL(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFCR_DFL_SHIFT)) & LINFlexD_IFCR_DFL_MASK)
#define LINFlexD_IFCR_DIR_MASK                                  (0x200U)
#define LINFlexD_IFCR_DIR_SHIFT                                 (9U)
#define LINFlexD_IFCR_DIR(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFCR_DIR_SHIFT)) & LINFlexD_IFCR_DIR_MASK)
#define LINFlexD_IFCR_CCS_MASK                                  (0x100U)
#define LINFlexD_IFCR_CCS_SHIFT                                 (8U)
#define LINFlexD_IFCR_CCS(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFCR_CCS_SHIFT)) & LINFlexD_IFCR_CCS_MASK)
#define LINFlexD_IFCR_ID_MASK                                   (0x3FU)
#define LINFlexD_IFCR_ID_SHIFT                                  (0U)
#define LINFlexD_IFCR_ID(x)                                     (((uint32_t)(((uint32_t)(x)) << LINFlexD_IFCR_ID_SHIFT)) & LINFlexD_IFCR_ID_MASK)
/* LINFlexD_GCR Register */
#define LINFlexD_GCR_TDFBM_MASK                                 (0x20U)
#define LINFlexD_GCR_TDFBM_SHIFT                                (5U)
#define LINFlexD_GCR_TDFBM(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_TDFBM_SHIFT)) & LINFlexD_GCR_TDFBM_MASK)
#define LINFlexD_GCR_RDFBM_MASK                                 (0x10U)
#define LINFlexD_GCR_RDFBM_SHIFT                                (4U)
#define LINFlexD_GCR_RDFBM(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_RDFBM_SHIFT)) & LINFlexD_GCR_RDFBM_MASK)
#define LINFlexD_GCR_TDLIS_MASK                                 (0x8U)
#define LINFlexD_GCR_TDLIS_SHIFT                                (3U)
#define LINFlexD_GCR_TDLIS(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_TDLIS_SHIFT)) & LINFlexD_GCR_TDLIS_MASK)
#define LINFlexD_GCR_RDLIS_MASK                                 (0x4U)
#define LINFlexD_GCR_RDLIS_SHIFT                                (2U)
#define LINFlexD_GCR_RDLIS(x)                                   (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_RDLIS_SHIFT)) & LINFlexD_GCR_RDLIS_MASK)
#define LINFlexD_GCR_STOP_MASK                                  (0x2U)
#define LINFlexD_GCR_STOP_SHIFT                                 (1U)
#define LINFlexD_GCR_STOP(x)                                    (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_STOP_SHIFT)) & LINFlexD_GCR_STOP_MASK)
#define LINFlexD_GCR_SR_MASK                                    (0x1U)
#define LINFlexD_GCR_SR_SHIFT                                   (0U)
#define LINFlexD_GCR_SR(x)                                      (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_SR_SHIFT)) & LINFlexD_GCR_SR_MASK)
/* LINFlexD_UARTPTO Register */
#define LINFlexD_UARTPTO_PTO_MASK                               (0xFFFU)
#define LINFlexD_UARTPTO_PTO_SHIFT                              (0U)
#define LINFlexD_UARTPTO_PTO(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTPTO_PTO_SHIFT)) & LINFlexD_UARTPTO_PTO_MASK)
/* LINFlexD_UARTCTO Register */
#define LINFlexD_UARTCTO_CTO_MASK                               (0xFFFU)
#define LINFlexD_UARTCTO_CTO_SHIFT                              (0U)
#define LINFlexD_UARTCTO_CTO(x)                                 (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCTO_CTO_SHIFT)) & LINFlexD_UARTCTO_CTO_MASK)
/* LINFlexD_DMATXE Register */
#define LINFlexD_DMATXE_DTE_MASK                                (0xFFFFU)
#define LINFlexD_DMATXE_DTE_SHIFT                               (0U)
#define LINFlexD_DMATXE_DTE(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_DMATXE_DTE_SHIFT)) & LINFlexD_DMATXE_DTE_MASK)
/* LINFlexD_DMARXE Register */
#define LINFlexD_DMARXE_DRE_MASK                                (0xFFFFU)
#define LINFlexD_DMARXE_DRE_SHIFT                               (0U)
#define LINFlexD_DMARXE_DRE(x)                                  (((uint32_t)(((uint32_t)(x)) << LINFlexD_DMARXE_DRE_SHIFT)) & LINFlexD_DMARXE_DRE_MASK)


/*!
 * @}
 */ /* end of group LINFlexD_Register_Masks */


/*!
 * @}
 */ /* end of group LINFlexD_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */


/** SPI - Size of Registers Arrays */

/* SPI Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t TXCFG;                              /**< Transmit Configuration Register, offset: 0x0004 */
    __IO uint32_t CLK;                                /**< Clock Configuration Register, offset: 0x0008 */
    __IO uint32_t STS;                                /**< Status Register, offset: 0x000C */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x0010 */
    __IO uint32_t MATCH0;                             /**< Data Match Register 0, offset: 0x0014 */
    __IO uint32_t MATCH1;                             /**< Data Match Register 1, offset: 0x0018 */
    __IO uint32_t TXFIFO;                             /**< TX FIFO Configuration Register, offset: 0x001C */
    __IO uint32_t RXFIFO;                             /**< RX FIFO Configuration Register, offset: 0x0020 */
    __IO uint32_t DATA;                               /**< Data Register, offset: 0x0024 */

} SPI_Type, *SPI_MemMapPtr;

/** Number of instances of the SPI module. */
#define SPI_INSTANCE_COUNT                             (6u)

/* SPI0  base address */
#define SPI0_BASE                                          (0x4002A000)
#define SPI0                                               ((SPI_Type *)(SPI0_BASE))
/* SPI1  base address */
#define SPI1_BASE                                          (0x4002B000)
#define SPI1                                               ((SPI_Type *)(SPI1_BASE))
/* SPI2  base address */
#define SPI2_BASE                                          (0x4002C000)
#define SPI2                                               ((SPI_Type *)(SPI2_BASE))
/* SPI3  base address */
#define SPI3_BASE                                          (0x4002D000)
#define SPI3                                               ((SPI_Type *)(SPI3_BASE))
/* SPI4  base address */
#define SPI4_BASE                                          (0x4002E000)
#define SPI4                                               ((SPI_Type *)(SPI4_BASE))
/* SPI5  base address */
#define SPI5_BASE                                          (0x4002F000)
#define SPI5                                               ((SPI_Type *)(SPI5_BASE))

/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                                     { SPI0_BASE,  SPI1_BASE,  SPI2_BASE,  SPI3_BASE,  SPI4_BASE,  SPI5_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                                      { SPI0,  SPI1,  SPI2,  SPI3,  SPI4,  SPI5 }
/** Number of interrupt vector arrays for the SPI module. */
#define SPI_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the SPI. */
#define SPI_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                  { SPI0_IRQn, SPI1_IRQn, SPI2_IRQn, SPI3_IRQn, SPI4_IRQn, SPI5_IRQn }

/* SPI Register Mask */
/* SPI_CTRL Register */
#define SPI_CTRL_TXDMAEN_MASK                              (0x20000000U)
#define SPI_CTRL_TXDMAEN_SHIFT                             (29U)
#define SPI_CTRL_TXDMAEN(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_TXDMAEN_SHIFT)) & SPI_CTRL_TXDMAEN_MASK)
#define SPI_CTRL_RXDMAEN_MASK                              (0x10000000U)
#define SPI_CTRL_RXDMAEN_SHIFT                             (28U)
#define SPI_CTRL_RXDMAEN(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_RXDMAEN_SHIFT)) & SPI_CTRL_RXDMAEN_MASK)
#define SPI_CTRL_AUTOPCS_MASK                              (0x2000000U)
#define SPI_CTRL_AUTOPCS_SHIFT                             (25U)
#define SPI_CTRL_AUTOPCS(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_AUTOPCS_SHIFT)) & SPI_CTRL_AUTOPCS_MASK)
#define SPI_CTRL_SPDEN_MASK                                (0x1000000U)
#define SPI_CTRL_SPDEN_SHIFT                               (24U)
#define SPI_CTRL_SPDEN(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_SPDEN_SHIFT)) & SPI_CTRL_SPDEN_MASK)
#define SPI_CTRL_MATCFG_MASK                               (0x70000U)
#define SPI_CTRL_MATCFG_SHIFT                              (16U)
#define SPI_CTRL_MATCFG(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_MATCFG_SHIFT)) & SPI_CTRL_MATCFG_MASK)
#define SPI_CTRL_CSDEN_MASK                                (0x8000U)
#define SPI_CTRL_CSDEN_SHIFT                               (15U)
#define SPI_CTRL_CSDEN(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_CSDEN_SHIFT)) & SPI_CTRL_CSDEN_MASK)
#define SPI_CTRL_DHZEN_MASK                                (0x4000U)
#define SPI_CTRL_DHZEN_SHIFT                               (14U)
#define SPI_CTRL_DHZEN(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_DHZEN_SHIFT)) & SPI_CTRL_DHZEN_MASK)
#define SPI_CTRL_CSPOL_MASK                                (0x3C00U)
#define SPI_CTRL_CSPOL_SHIFT                               (10U)
#define SPI_CTRL_CSPOL(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_CSPOL_SHIFT)) & SPI_CTRL_CSPOL_MASK)
#define SPI_CTRL_PINCFG_MASK                               (0x300U)
#define SPI_CTRL_PINCFG_SHIFT                              (8U)
#define SPI_CTRL_PINCFG(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_PINCFG_SHIFT)) & SPI_CTRL_PINCFG_MASK)
#define SPI_CTRL_RXMO_MASK                                 (0x80U)
#define SPI_CTRL_RXMO_SHIFT                                (7U)
#define SPI_CTRL_RXMO(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_RXMO_SHIFT)) & SPI_CTRL_RXMO_MASK)
#define SPI_CTRL_MODE_MASK                                 (0x4U)
#define SPI_CTRL_MODE_SHIFT                                (2U)
#define SPI_CTRL_MODE(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_MODE_SHIFT)) & SPI_CTRL_MODE_MASK)
#define SPI_CTRL_EN_MASK                                   (0x1U)
#define SPI_CTRL_EN_SHIFT                                  (0U)
#define SPI_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << SPI_CTRL_EN_SHIFT)) & SPI_CTRL_EN_MASK)
/* SPI_TXCFG Register */
#define SPI_TXCFG_CPOL_MASK                                (0x80000000U)
#define SPI_TXCFG_CPOL_SHIFT                               (31U)
#define SPI_TXCFG_CPOL(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_CPOL_SHIFT)) & SPI_TXCFG_CPOL_MASK)
#define SPI_TXCFG_CPHA_MASK                                (0x40000000U)
#define SPI_TXCFG_CPHA_SHIFT                               (30U)
#define SPI_TXCFG_CPHA(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_CPHA_SHIFT)) & SPI_TXCFG_CPHA_MASK)
#define SPI_TXCFG_PRESCALE_MASK                            (0x38000000U)
#define SPI_TXCFG_PRESCALE_SHIFT                           (27U)
#define SPI_TXCFG_PRESCALE(x)                              (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_PRESCALE_SHIFT)) & SPI_TXCFG_PRESCALE_MASK)
#define SPI_TXCFG_PCS_MASK                                 (0x3000000U)
#define SPI_TXCFG_PCS_SHIFT                                (24U)
#define SPI_TXCFG_PCS(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_PCS_SHIFT)) & SPI_TXCFG_PCS_MASK)
#define SPI_TXCFG_LSBF_MASK                                (0x800000U)
#define SPI_TXCFG_LSBF_SHIFT                               (23U)
#define SPI_TXCFG_LSBF(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_LSBF_SHIFT)) & SPI_TXCFG_LSBF_MASK)
#define SPI_TXCFG_BSW_MASK                                 (0x400000U)
#define SPI_TXCFG_BSW_SHIFT                                (22U)
#define SPI_TXCFG_BSW(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_BSW_SHIFT)) & SPI_TXCFG_BSW_MASK)
#define SPI_TXCFG_CONT_MASK                                (0x200000U)
#define SPI_TXCFG_CONT_SHIFT                               (21U)
#define SPI_TXCFG_CONT(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_CONT_SHIFT)) & SPI_TXCFG_CONT_MASK)
#define SPI_TXCFG_CONTC_MASK                               (0x100000U)
#define SPI_TXCFG_CONTC_SHIFT                              (20U)
#define SPI_TXCFG_CONTC(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_CONTC_SHIFT)) & SPI_TXCFG_CONTC_MASK)
#define SPI_TXCFG_MSKRX_MASK                               (0x80000U)
#define SPI_TXCFG_MSKRX_SHIFT                              (19U)
#define SPI_TXCFG_MSKRX(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_MSKRX_SHIFT)) & SPI_TXCFG_MSKRX_MASK)
#define SPI_TXCFG_MSKTX_MASK                               (0x40000U)
#define SPI_TXCFG_MSKTX_SHIFT                              (18U)
#define SPI_TXCFG_MSKTX(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_MSKTX_SHIFT)) & SPI_TXCFG_MSKTX_MASK)
#define SPI_TXCFG_WIDTH_MASK                               (0x30000U)
#define SPI_TXCFG_WIDTH_SHIFT                              (16U)
#define SPI_TXCFG_WIDTH(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_WIDTH_SHIFT)) & SPI_TXCFG_WIDTH_MASK)
#define SPI_TXCFG_FRAMESZ_WIDTH                            (12)
#define SPI_TXCFG_FRAMESZ_MASK                             (0xFFFU)
#define SPI_TXCFG_FRAMESZ_SHIFT                            (0U)
#define SPI_TXCFG_FRAMESZ(x)                               (((uint32_t)(((uint32_t)(x)) << SPI_TXCFG_FRAMESZ_SHIFT)) & SPI_TXCFG_FRAMESZ_MASK)
/* SPI_CLK Register */
#define SPI_CLK_SCKPCS_WIDTH                               (8)
#define SPI_CLK_SCKPCS_MASK                                (0xFF000000U)
#define SPI_CLK_SCKPCS_SHIFT                               (24U)
#define SPI_CLK_SCKPCS(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CLK_SCKPCS_SHIFT)) & SPI_CLK_SCKPCS_MASK)
#define SPI_CLK_PCSSCK_WIDTH                               (8)
#define SPI_CLK_PCSSCK_MASK                                (0xFF0000U)
#define SPI_CLK_PCSSCK_SHIFT                               (16U)
#define SPI_CLK_PCSSCK(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_CLK_PCSSCK_SHIFT)) & SPI_CLK_PCSSCK_MASK)
#define SPI_CLK_FMDLY_WIDTH                                (8)
#define SPI_CLK_FMDLY_MASK                                 (0xFF00U)
#define SPI_CLK_FMDLY_SHIFT                                (8U)
#define SPI_CLK_FMDLY(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_CLK_FMDLY_SHIFT)) & SPI_CLK_FMDLY_MASK)
#define SPI_CLK_DIV_WIDTH                                  (8)
#define SPI_CLK_DIV_MASK                                   (0xFFU)
#define SPI_CLK_DIV_SHIFT                                  (0U)
#define SPI_CLK_DIV(x)                                     (((uint32_t)(((uint32_t)(x)) << SPI_CLK_DIV_SHIFT)) & SPI_CLK_DIV_MASK)
/* SPI_STS Register */
#define SPI_STS_BUSY_MASK                                  (0x40000U)
#define SPI_STS_BUSY_SHIFT                                 (18U)
#define SPI_STS_BUSY(x)                                    (((uint32_t)(((uint32_t)(x)) << SPI_STS_BUSY_SHIFT)) & SPI_STS_BUSY_MASK)
#define SPI_STS_RXEPT_MASK                                 (0x20000U)
#define SPI_STS_RXEPT_SHIFT                                (17U)
#define SPI_STS_RXEPT(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_STS_RXEPT_SHIFT)) & SPI_STS_RXEPT_MASK)
#define SPI_STS_SOF_MASK                                   (0x10000U)
#define SPI_STS_SOF_SHIFT                                  (16U)
#define SPI_STS_SOF(x)                                     (((uint32_t)(((uint32_t)(x)) << SPI_STS_SOF_SHIFT)) & SPI_STS_SOF_MASK)
#define SPI_STS_MATIF_MASK                                 (0x80U)
#define SPI_STS_MATIF_SHIFT                                (7U)
#define SPI_STS_MATIF(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_STS_MATIF_SHIFT)) & SPI_STS_MATIF_MASK)
#define SPI_STS_RXOVIF_MASK                                (0x40U)
#define SPI_STS_RXOVIF_SHIFT                               (6U)
#define SPI_STS_RXOVIF(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_STS_RXOVIF_SHIFT)) & SPI_STS_RXOVIF_MASK)
#define SPI_STS_TXUNIF_MASK                                (0x20U)
#define SPI_STS_TXUNIF_SHIFT                               (5U)
#define SPI_STS_TXUNIF(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_STS_TXUNIF_SHIFT)) & SPI_STS_TXUNIF_MASK)
#define SPI_STS_TCIF_MASK                                  (0x10U)
#define SPI_STS_TCIF_SHIFT                                 (4U)
#define SPI_STS_TCIF(x)                                    (((uint32_t)(((uint32_t)(x)) << SPI_STS_TCIF_SHIFT)) & SPI_STS_TCIF_MASK)
#define SPI_STS_FCIF_MASK                                  (0x8U)
#define SPI_STS_FCIF_SHIFT                                 (3U)
#define SPI_STS_FCIF(x)                                    (((uint32_t)(((uint32_t)(x)) << SPI_STS_FCIF_SHIFT)) & SPI_STS_FCIF_MASK)
#define SPI_STS_TXIF_MASK                                  (0x2U)
#define SPI_STS_TXIF_SHIFT                                 (1U)
#define SPI_STS_TXIF(x)                                    (((uint32_t)(((uint32_t)(x)) << SPI_STS_TXIF_SHIFT)) & SPI_STS_TXIF_MASK)
#define SPI_STS_RXIF_MASK                                  (0x1U)
#define SPI_STS_RXIF_SHIFT                                 (0U)
#define SPI_STS_RXIF(x)                                    (((uint32_t)(((uint32_t)(x)) << SPI_STS_RXIF_SHIFT)) & SPI_STS_RXIF_MASK)
/* SPI_INTE Register */
#define SPI_INTE_MATIE_MASK                                (0x80U)
#define SPI_INTE_MATIE_SHIFT                               (7U)
#define SPI_INTE_MATIE(x)                                  (((uint32_t)(((uint32_t)(x)) << SPI_INTE_MATIE_SHIFT)) & SPI_INTE_MATIE_MASK)
#define SPI_INTE_RXOVIE_MASK                               (0x40U)
#define SPI_INTE_RXOVIE_SHIFT                              (6U)
#define SPI_INTE_RXOVIE(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_INTE_RXOVIE_SHIFT)) & SPI_INTE_RXOVIE_MASK)
#define SPI_INTE_TXUNIE_MASK                               (0x20U)
#define SPI_INTE_TXUNIE_SHIFT                              (5U)
#define SPI_INTE_TXUNIE(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_INTE_TXUNIE_SHIFT)) & SPI_INTE_TXUNIE_MASK)
#define SPI_INTE_TCIE_MASK                                 (0x10U)
#define SPI_INTE_TCIE_SHIFT                                (4U)
#define SPI_INTE_TCIE(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_INTE_TCIE_SHIFT)) & SPI_INTE_TCIE_MASK)
#define SPI_INTE_FCIE_MASK                                 (0x8U)
#define SPI_INTE_FCIE_SHIFT                                (3U)
#define SPI_INTE_FCIE(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_INTE_FCIE_SHIFT)) & SPI_INTE_FCIE_MASK)
#define SPI_INTE_TXIE_MASK                                 (0x2U)
#define SPI_INTE_TXIE_SHIFT                                (1U)
#define SPI_INTE_TXIE(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_INTE_TXIE_SHIFT)) & SPI_INTE_TXIE_MASK)
#define SPI_INTE_RXIE_MASK                                 (0x1U)
#define SPI_INTE_RXIE_SHIFT                                (0U)
#define SPI_INTE_RXIE(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_INTE_RXIE_SHIFT)) & SPI_INTE_RXIE_MASK)
/* SPI_MATCH0 Register */
#define SPI_MATCH0_MATCH0_MASK                             (0xFFFFFFFFU)
#define SPI_MATCH0_MATCH0_SHIFT                            (0U)
#define SPI_MATCH0_MATCH0(x)                               (((uint32_t)(((uint32_t)(x)) << SPI_MATCH0_MATCH0_SHIFT)) & SPI_MATCH0_MATCH0_MASK)
/* SPI_MATCH1 Register */
#define SPI_MATCH1_MATCH1_MASK                             (0xFFFFFFFFU)
#define SPI_MATCH1_MATCH1_SHIFT                            (0U)
#define SPI_MATCH1_MATCH1(x)                               (((uint32_t)(((uint32_t)(x)) << SPI_MATCH1_MATCH1_SHIFT)) & SPI_MATCH1_MATCH1_MASK)
/* SPI_TXFIFO Register */
#define SPI_TXFIFO_SIZE_MASK                               (0x1F000000U)
#define SPI_TXFIFO_SIZE_SHIFT                              (24U)
#define SPI_TXFIFO_SIZE(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_TXFIFO_SIZE_SHIFT)) & SPI_TXFIFO_SIZE_MASK)
#define SPI_TXFIFO_RESET_MASK                              (0x8000U)
#define SPI_TXFIFO_RESET_SHIFT                             (15U)
#define SPI_TXFIFO_RESET(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_TXFIFO_RESET_SHIFT)) & SPI_TXFIFO_RESET_MASK)
#define SPI_TXFIFO_COUNT_MASK                              (0x1F00U)
#define SPI_TXFIFO_COUNT_SHIFT                             (8U)
#define SPI_TXFIFO_COUNT(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_TXFIFO_COUNT_SHIFT)) & SPI_TXFIFO_COUNT_MASK)
#define SPI_TXFIFO_WATER_MASK                              (0xFU)
#define SPI_TXFIFO_WATER_SHIFT                             (0U)
#define SPI_TXFIFO_WATER(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_TXFIFO_WATER_SHIFT)) & SPI_TXFIFO_WATER_MASK)
/* SPI_RXFIFO Register */
#define SPI_RXFIFO_SIZE_MASK                               (0x1F000000U)
#define SPI_RXFIFO_SIZE_SHIFT                              (24U)
#define SPI_RXFIFO_SIZE(x)                                 (((uint32_t)(((uint32_t)(x)) << SPI_RXFIFO_SIZE_SHIFT)) & SPI_RXFIFO_SIZE_MASK)
#define SPI_RXFIFO_RESET_MASK                              (0x8000U)
#define SPI_RXFIFO_RESET_SHIFT                             (15U)
#define SPI_RXFIFO_RESET(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_RXFIFO_RESET_SHIFT)) & SPI_RXFIFO_RESET_MASK)
#define SPI_RXFIFO_COUNT_MASK                              (0x1F00U)
#define SPI_RXFIFO_COUNT_SHIFT                             (8U)
#define SPI_RXFIFO_COUNT(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_RXFIFO_COUNT_SHIFT)) & SPI_RXFIFO_COUNT_MASK)
#define SPI_RXFIFO_WATER_MASK                              (0xFU)
#define SPI_RXFIFO_WATER_SHIFT                             (0U)
#define SPI_RXFIFO_WATER(x)                                (((uint32_t)(((uint32_t)(x)) << SPI_RXFIFO_WATER_SHIFT)) & SPI_RXFIFO_WATER_MASK)
/* SPI_DATA Register */
#define SPI_DATA_DATA_MASK                                 (0xFFFFFFFFU)
#define SPI_DATA_DATA_SHIFT                                (0U)
#define SPI_DATA_DATA(x)                                   (((uint32_t)(((uint32_t)(x)) << SPI_DATA_DATA_SHIFT)) & SPI_DATA_DATA_MASK)


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 * @{
 */


/** I2C - Size of Registers Arrays */

/* I2C Register Layout Typedef */
typedef struct {
    __IO uint32_t MCTRL;                              /**< Master Control Register, offset: 0x0000 */
    __IO uint32_t MCLKCFG;                            /**< Master Clock Configuration Register, offset: 0x0004 */
    __IO uint32_t MFLTCFG;                            /**< Master Clock Filter Configuration and Divider Register, offset: 0x0008 */
    __IO uint32_t MSTS;                               /**< Master Status Register, offset: 0x000C */
    __IO uint32_t MIE;                                /**< Master Interrupt Register, offset: 0x0010 */
    __IO uint32_t TXFIFO;                             /**< Master TX FIFO Control and Status Register, offset: 0x0014 */
    __IO uint32_t RXFIFO;                             /**< Master RX FIFO Control and Status Register, offset: 0x0018 */
    __IO uint32_t MDATA;                              /**< Master Data Register, offset: 0x001C */
    __IO uint32_t MATCH;                              /**< Data Match Register, offset: 0x0020 */
    __IO uint32_t TOCFG;                              /**< Timeout Configure Register, offset: 0x0024 */
    __IO uint32_t HSCLK;                              /**< Master Clock Configuration Under High Speed Mode Register, offset: 0x0028 */
    __IO uint32_t RESERVED0[53];                      /**< RESERVED0, offset: 0x002C */
    __IO uint32_t SCTRL;                              /**< Slave Control Register, offset: 0x0100 */
    __IO uint32_t SCLKCFG;                            /**< Slave Clock Configuration Register, offset: 0x0104 */
    __IO uint32_t SFLTCFG;                            /**< Slave Filter Configuration Register, offset: 0x0108 */
    __IO uint32_t SSTS;                               /**< Slave Status Register, offset: 0x010C */
    __IO uint32_t SIE;                                /**< Slave Interrupt Enable Register, offset: 0x0110 */
    __IO uint32_t SDATA;                              /**< Slave Data Register, offset: 0x0114 */
    __IO uint32_t SACK;                               /**< Slave Ack Register, offset: 0x0118 */
    __IO uint32_t SADDR;                              /**< Slave Address Match Configuration Register, offset: 0x011C */
    __IO uint32_t SRADDR;                             /**< Slave Received Address Register, offset: 0x0120 */

} I2C_Type, *I2C_MemMapPtr;

/** Number of instances of the I2C module. */
#define I2C_INSTANCE_COUNT                             (3u)

/* I2C0  base address */
#define I2C0_BASE                                          (0x40023000)
#define I2C0                                               ((I2C_Type *)(I2C0_BASE))
/* I2C1  base address */
#define I2C1_BASE                                          (0x40024000)
#define I2C1                                               ((I2C_Type *)(I2C1_BASE))
/* I2C2  base address */
#define I2C2_BASE                                          (0x40025000)
#define I2C2                                               ((I2C_Type *)(I2C2_BASE))

/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                                     { I2C0_BASE,  I2C1_BASE,  I2C2_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                                      { I2C0,  I2C1,  I2C2 }
/** Number of interrupt vector arrays for the I2C module. */
#define I2C_IRQS_ARR_COUNT                                 (2u)
/** Number of interrupt channels for the MASTER type of I2C. */
#define I2C_MASTER_IRQS_CH_COUNT                  (3u)
#define I2C_MASTER_IRQS                           { I2C0_Master_IRQn, I2C1_Master_IRQn, I2C2_Master_IRQn }
/** Number of interrupt channels for the SLAVE type of I2C. */
#define I2C_SLAVE_IRQS_CH_COUNT                   (3u)
#define I2C_SLAVE_IRQS                            { I2C0_Slave_IRQn, I2C1_Slave_IRQn, I2C2_Slave_IRQn }

/* I2C Register Mask */
/* I2C_MCTRL Register */
#define I2C_MCTRL_TXDMAEN_MASK                             (0x20000000U)
#define I2C_MCTRL_TXDMAEN_SHIFT                            (29U)
#define I2C_MCTRL_TXDMAEN(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_TXDMAEN_SHIFT)) & I2C_MCTRL_TXDMAEN_MASK)
#define I2C_MCTRL_RXDMAEN_MASK                             (0x10000000U)
#define I2C_MCTRL_RXDMAEN_SHIFT                            (28U)
#define I2C_MCTRL_RXDMAEN(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_RXDMAEN_SHIFT)) & I2C_MCTRL_RXDMAEN_MASK)
#define I2C_MCTRL_RDMO_MASK                                (0x2000000U)
#define I2C_MCTRL_RDMO_SHIFT                               (25U)
#define I2C_MCTRL_RDMO(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_RDMO_SHIFT)) & I2C_MCTRL_RDMO_MASK)
#define I2C_MCTRL_MATCFG_MASK                              (0x70000U)
#define I2C_MCTRL_MATCFG_SHIFT                             (16U)
#define I2C_MCTRL_MATCFG(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_MATCFG_SHIFT)) & I2C_MCTRL_MATCFG_MASK)
#define I2C_MCTRL_IGACK_MASK                               (0x8000U)
#define I2C_MCTRL_IGACK_SHIFT                              (15U)
#define I2C_MCTRL_IGACK(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_IGACK_SHIFT)) & I2C_MCTRL_IGACK_MASK)
#define I2C_MCTRL_ASTOP_MASK                               (0x4000U)
#define I2C_MCTRL_ASTOP_SHIFT                              (14U)
#define I2C_MCTRL_ASTOP(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_ASTOP_SHIFT)) & I2C_MCTRL_ASTOP_MASK)
#define I2C_MCTRL_HSMOD_MASK                               (0x200U)
#define I2C_MCTRL_HSMOD_SHIFT                              (9U)
#define I2C_MCTRL_HSMOD(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_HSMOD_SHIFT)) & I2C_MCTRL_HSMOD_MASK)
#define I2C_MCTRL_PPEN_MASK                                (0x100U)
#define I2C_MCTRL_PPEN_SHIFT                               (8U)
#define I2C_MCTRL_PPEN(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_PPEN_SHIFT)) & I2C_MCTRL_PPEN_MASK)
#define I2C_MCTRL_MEN_MASK                                 (0x1U)
#define I2C_MCTRL_MEN_SHIFT                                (0U)
#define I2C_MCTRL_MEN(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MCTRL_MEN_SHIFT)) & I2C_MCTRL_MEN_MASK)
/* I2C_MCLKCFG Register */
#define I2C_MCLKCFG_HIGH_WIDTH                             (6)
#define I2C_MCLKCFG_HIGH_MASK                              (0x3F000000U)
#define I2C_MCLKCFG_HIGH_SHIFT                             (24U)
#define I2C_MCLKCFG_HIGH(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MCLKCFG_HIGH_SHIFT)) & I2C_MCLKCFG_HIGH_MASK)
#define I2C_MCLKCFG_LOW_WIDTH                              (6)
#define I2C_MCLKCFG_LOW_MASK                               (0x3F0000U)
#define I2C_MCLKCFG_LOW_SHIFT                              (16U)
#define I2C_MCLKCFG_LOW(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MCLKCFG_LOW_SHIFT)) & I2C_MCLKCFG_LOW_MASK)
#define I2C_MCLKCFG_VALID_WIDTH                            (6)
#define I2C_MCLKCFG_VALID_MASK                             (0x3F00U)
#define I2C_MCLKCFG_VALID_SHIFT                            (8U)
#define I2C_MCLKCFG_VALID(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_MCLKCFG_VALID_SHIFT)) & I2C_MCLKCFG_VALID_MASK)
#define I2C_MCLKCFG_STHD_WIDTH                             (6)
#define I2C_MCLKCFG_STHD_MASK                              (0x3FU)
#define I2C_MCLKCFG_STHD_SHIFT                             (0U)
#define I2C_MCLKCFG_STHD(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MCLKCFG_STHD_SHIFT)) & I2C_MCLKCFG_STHD_MASK)
/* I2C_MFLTCFG Register */
#define I2C_MFLTCFG_FLTSCL_WIDTH                           (4)
#define I2C_MFLTCFG_FLTSCL_MASK                            (0xF000000U)
#define I2C_MFLTCFG_FLTSCL_SHIFT                           (24U)
#define I2C_MFLTCFG_FLTSCL(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_MFLTCFG_FLTSCL_SHIFT)) & I2C_MFLTCFG_FLTSCL_MASK)
#define I2C_MFLTCFG_FLTSDA_WIDTH                           (4)
#define I2C_MFLTCFG_FLTSDA_MASK                            (0xF0000U)
#define I2C_MFLTCFG_FLTSDA_SHIFT                           (16U)
#define I2C_MFLTCFG_FLTSDA(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_MFLTCFG_FLTSDA_SHIFT)) & I2C_MFLTCFG_FLTSDA_MASK)
#define I2C_MFLTCFG_DIV_WIDTH                              (3)
#define I2C_MFLTCFG_DIV_MASK                               (0x7U)
#define I2C_MFLTCFG_DIV_SHIFT                              (0U)
#define I2C_MFLTCFG_DIV(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MFLTCFG_DIV_SHIFT)) & I2C_MFLTCFG_DIV_MASK)
/* I2C_MSTS Register */
#define I2C_MSTS_ACTIVE_MASK                               (0x20000U)
#define I2C_MSTS_ACTIVE_SHIFT                              (17U)
#define I2C_MSTS_ACTIVE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_ACTIVE_SHIFT)) & I2C_MSTS_ACTIVE_MASK)
#define I2C_MSTS_BUSY_MASK                                 (0x10000U)
#define I2C_MSTS_BUSY_SHIFT                                (16U)
#define I2C_MSTS_BUSY(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_BUSY_SHIFT)) & I2C_MSTS_BUSY_MASK)
#define I2C_MSTS_OPERRIF_MASK                              (0x800U)
#define I2C_MSTS_OPERRIF_SHIFT                             (11U)
#define I2C_MSTS_OPERRIF(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_OPERRIF_SHIFT)) & I2C_MSTS_OPERRIF_MASK)
#define I2C_MSTS_MATIF_MASK                                (0x200U)
#define I2C_MSTS_MATIF_SHIFT                               (9U)
#define I2C_MSTS_MATIF(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_MATIF_SHIFT)) & I2C_MSTS_MATIF_MASK)
#define I2C_MSTS_TOIF_MASK                                 (0x100U)
#define I2C_MSTS_TOIF_SHIFT                                (8U)
#define I2C_MSTS_TOIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_TOIF_SHIFT)) & I2C_MSTS_TOIF_MASK)
#define I2C_MSTS_ARBIF_MASK                                (0x80U)
#define I2C_MSTS_ARBIF_SHIFT                               (7U)
#define I2C_MSTS_ARBIF(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_ARBIF_SHIFT)) & I2C_MSTS_ARBIF_MASK)
#define I2C_MSTS_NACKIF_MASK                               (0x40U)
#define I2C_MSTS_NACKIF_SHIFT                              (6U)
#define I2C_MSTS_NACKIF(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_NACKIF_SHIFT)) & I2C_MSTS_NACKIF_MASK)
#define I2C_MSTS_STOPIF_MASK                               (0x10U)
#define I2C_MSTS_STOPIF_SHIFT                              (4U)
#define I2C_MSTS_STOPIF(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_STOPIF_SHIFT)) & I2C_MSTS_STOPIF_MASK)
#define I2C_MSTS_TXIF_MASK                                 (0x2U)
#define I2C_MSTS_TXIF_SHIFT                                (1U)
#define I2C_MSTS_TXIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_TXIF_SHIFT)) & I2C_MSTS_TXIF_MASK)
#define I2C_MSTS_RXIF_MASK                                 (0x1U)
#define I2C_MSTS_RXIF_SHIFT                                (0U)
#define I2C_MSTS_RXIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTS_RXIF_SHIFT)) & I2C_MSTS_RXIF_MASK)
/* I2C_MIE Register */
#define I2C_MIE_OPERRIE_MASK                               (0x800U)
#define I2C_MIE_OPERRIE_SHIFT                              (11U)
#define I2C_MIE_OPERRIE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MIE_OPERRIE_SHIFT)) & I2C_MIE_OPERRIE_MASK)
#define I2C_MIE_MATIE_MASK                                 (0x200U)
#define I2C_MIE_MATIE_SHIFT                                (9U)
#define I2C_MIE_MATIE(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MIE_MATIE_SHIFT)) & I2C_MIE_MATIE_MASK)
#define I2C_MIE_TOIE_MASK                                  (0x100U)
#define I2C_MIE_TOIE_SHIFT                                 (8U)
#define I2C_MIE_TOIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_MIE_TOIE_SHIFT)) & I2C_MIE_TOIE_MASK)
#define I2C_MIE_ARBIE_MASK                                 (0x80U)
#define I2C_MIE_ARBIE_SHIFT                                (7U)
#define I2C_MIE_ARBIE(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MIE_ARBIE_SHIFT)) & I2C_MIE_ARBIE_MASK)
#define I2C_MIE_NACKIE_MASK                                (0x40U)
#define I2C_MIE_NACKIE_SHIFT                               (6U)
#define I2C_MIE_NACKIE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MIE_NACKIE_SHIFT)) & I2C_MIE_NACKIE_MASK)
#define I2C_MIE_STOPIE_MASK                                (0x10U)
#define I2C_MIE_STOPIE_SHIFT                               (4U)
#define I2C_MIE_STOPIE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MIE_STOPIE_SHIFT)) & I2C_MIE_STOPIE_MASK)
#define I2C_MIE_TXIE_MASK                                  (0x2U)
#define I2C_MIE_TXIE_SHIFT                                 (1U)
#define I2C_MIE_TXIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_MIE_TXIE_SHIFT)) & I2C_MIE_TXIE_MASK)
#define I2C_MIE_RXIE_MASK                                  (0x1U)
#define I2C_MIE_RXIE_SHIFT                                 (0U)
#define I2C_MIE_RXIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_MIE_RXIE_SHIFT)) & I2C_MIE_RXIE_MASK)
/* I2C_TXFIFO Register */
#define I2C_TXFIFO_SIZE_MASK                               (0x7000000U)
#define I2C_TXFIFO_SIZE_SHIFT                              (24U)
#define I2C_TXFIFO_SIZE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_TXFIFO_SIZE_SHIFT)) & I2C_TXFIFO_SIZE_MASK)
#define I2C_TXFIFO_RESET_MASK                              (0x8000U)
#define I2C_TXFIFO_RESET_SHIFT                             (15U)
#define I2C_TXFIFO_RESET(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_TXFIFO_RESET_SHIFT)) & I2C_TXFIFO_RESET_MASK)
#define I2C_TXFIFO_COUNT_MASK                              (0x700U)
#define I2C_TXFIFO_COUNT_SHIFT                             (8U)
#define I2C_TXFIFO_COUNT(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_TXFIFO_COUNT_SHIFT)) & I2C_TXFIFO_COUNT_MASK)
#define I2C_TXFIFO_WATER_MASK                              (0x3U)
#define I2C_TXFIFO_WATER_SHIFT                             (0U)
#define I2C_TXFIFO_WATER(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_TXFIFO_WATER_SHIFT)) & I2C_TXFIFO_WATER_MASK)
/* I2C_RXFIFO Register */
#define I2C_RXFIFO_SIZE_MASK                               (0x7000000U)
#define I2C_RXFIFO_SIZE_SHIFT                              (24U)
#define I2C_RXFIFO_SIZE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_RXFIFO_SIZE_SHIFT)) & I2C_RXFIFO_SIZE_MASK)
#define I2C_RXFIFO_RESET_MASK                              (0x8000U)
#define I2C_RXFIFO_RESET_SHIFT                             (15U)
#define I2C_RXFIFO_RESET(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_RXFIFO_RESET_SHIFT)) & I2C_RXFIFO_RESET_MASK)
#define I2C_RXFIFO_COUNT_MASK                              (0x700U)
#define I2C_RXFIFO_COUNT_SHIFT                             (8U)
#define I2C_RXFIFO_COUNT(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_RXFIFO_COUNT_SHIFT)) & I2C_RXFIFO_COUNT_MASK)
#define I2C_RXFIFO_WATER_MASK                              (0x7U)
#define I2C_RXFIFO_WATER_SHIFT                             (0U)
#define I2C_RXFIFO_WATER(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_RXFIFO_WATER_SHIFT)) & I2C_RXFIFO_WATER_MASK)
/* I2C_MDATA Register */
#define I2C_MDATA_EMPTY_MASK                               (0x10000U)
#define I2C_MDATA_EMPTY_SHIFT                              (16U)
#define I2C_MDATA_EMPTY(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_EMPTY_SHIFT)) & I2C_MDATA_EMPTY_MASK)
#define I2C_MDATA_HS_MASK                                  (0x800U)
#define I2C_MDATA_HS_SHIFT                                 (11U)
#define I2C_MDATA_HS(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_HS_SHIFT)) & I2C_MDATA_HS_MASK)
#define I2C_MDATA_REC_MASK                                 (0x400U)
#define I2C_MDATA_REC_SHIFT                                (10U)
#define I2C_MDATA_REC(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_REC_SHIFT)) & I2C_MDATA_REC_MASK)
#define I2C_MDATA_STOP_MASK                                (0x200U)
#define I2C_MDATA_STOP_SHIFT                               (9U)
#define I2C_MDATA_STOP(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_STOP_SHIFT)) & I2C_MDATA_STOP_MASK)
#define I2C_MDATA_START_MASK                               (0x100U)
#define I2C_MDATA_START_SHIFT                              (8U)
#define I2C_MDATA_START(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_START_SHIFT)) & I2C_MDATA_START_MASK)
#define I2C_MDATA_DATA_MASK                                (0xFFU)
#define I2C_MDATA_DATA_SHIFT                               (0U)
#define I2C_MDATA_DATA(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_MDATA_DATA_SHIFT)) & I2C_MDATA_DATA_MASK)
/* I2C_MATCH Register */
#define I2C_MATCH_MATCH1_MASK                              (0xFF0000U)
#define I2C_MATCH_MATCH1_SHIFT                             (16U)
#define I2C_MATCH_MATCH1(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MATCH_MATCH1_SHIFT)) & I2C_MATCH_MATCH1_MASK)
#define I2C_MATCH_MATCH0_MASK                              (0xFFU)
#define I2C_MATCH_MATCH0_SHIFT                             (0U)
#define I2C_MATCH_MATCH0(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_MATCH_MATCH0_SHIFT)) & I2C_MATCH_MATCH0_MASK)
/* I2C_TOCFG Register */
#define I2C_TOCFG_IDLE_MASK                                (0xFFF0000U)
#define I2C_TOCFG_IDLE_SHIFT                               (16U)
#define I2C_TOCFG_IDLE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_TOCFG_IDLE_SHIFT)) & I2C_TOCFG_IDLE_MASK)
#define I2C_TOCFG_SDA_MASK                                 (0x8000U)
#define I2C_TOCFG_SDA_SHIFT                                (15U)
#define I2C_TOCFG_SDA(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_TOCFG_SDA_SHIFT)) & I2C_TOCFG_SDA_MASK)
#define I2C_TOCFG_LOW_MASK                                 (0xFFFU)
#define I2C_TOCFG_LOW_SHIFT                                (0U)
#define I2C_TOCFG_LOW(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_TOCFG_LOW_SHIFT)) & I2C_TOCFG_LOW_MASK)
/* I2C_HSCLK Register */
#define I2C_HSCLK_HIGH_WIDTH                               (6)
#define I2C_HSCLK_HIGH_MASK                                (0x3F000000U)
#define I2C_HSCLK_HIGH_SHIFT                               (24U)
#define I2C_HSCLK_HIGH(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_HSCLK_HIGH_SHIFT)) & I2C_HSCLK_HIGH_MASK)
#define I2C_HSCLK_LOW_WIDTH                                (6)
#define I2C_HSCLK_LOW_MASK                                 (0x3F0000U)
#define I2C_HSCLK_LOW_SHIFT                                (16U)
#define I2C_HSCLK_LOW(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_HSCLK_LOW_SHIFT)) & I2C_HSCLK_LOW_MASK)
#define I2C_HSCLK_VALID_WIDTH                              (6)
#define I2C_HSCLK_VALID_MASK                               (0x3F00U)
#define I2C_HSCLK_VALID_SHIFT                              (8U)
#define I2C_HSCLK_VALID(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_HSCLK_VALID_SHIFT)) & I2C_HSCLK_VALID_MASK)
#define I2C_HSCLK_STHD_WIDTH                               (6)
#define I2C_HSCLK_STHD_MASK                                (0x3FU)
#define I2C_HSCLK_STHD_SHIFT                               (0U)
#define I2C_HSCLK_STHD(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_HSCLK_STHD_SHIFT)) & I2C_HSCLK_STHD_MASK)
/* I2C_SCTRL Register */
#define I2C_SCTRL_ADDRDMAEN_MASK                           (0x40000000U)
#define I2C_SCTRL_ADDRDMAEN_SHIFT                          (30U)
#define I2C_SCTRL_ADDRDMAEN(x)                             (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_ADDRDMAEN_SHIFT)) & I2C_SCTRL_ADDRDMAEN_MASK)
#define I2C_SCTRL_TXDMAEN_MASK                             (0x20000000U)
#define I2C_SCTRL_TXDMAEN_SHIFT                            (29U)
#define I2C_SCTRL_TXDMAEN(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_TXDMAEN_SHIFT)) & I2C_SCTRL_TXDMAEN_MASK)
#define I2C_SCTRL_RXDMAEN_MASK                             (0x10000000U)
#define I2C_SCTRL_RXDMAEN_SHIFT                            (28U)
#define I2C_SCTRL_RXDMAEN(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_RXDMAEN_SHIFT)) & I2C_SCTRL_RXDMAEN_MASK)
#define I2C_SCTRL_STARTDMAEN_MASK                          (0x8000000U)
#define I2C_SCTRL_STARTDMAEN_SHIFT                         (27U)
#define I2C_SCTRL_STARTDMAEN(x)                            (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_STARTDMAEN_SHIFT)) & I2C_SCTRL_STARTDMAEN_MASK)
#define I2C_SCTRL_STOPDMAEN_MASK                           (0x4000000U)
#define I2C_SCTRL_STOPDMAEN_SHIFT                          (26U)
#define I2C_SCTRL_STOPDMAEN(x)                             (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_STOPDMAEN_SHIFT)) & I2C_SCTRL_STOPDMAEN_MASK)
#define I2C_SCTRL_HSEN_MASK                                (0x400000U)
#define I2C_SCTRL_HSEN_SHIFT                               (22U)
#define I2C_SCTRL_HSEN(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_HSEN_SHIFT)) & I2C_SCTRL_HSEN_MASK)
#define I2C_SCTRL_RXCFG_MASK                               (0x100000U)
#define I2C_SCTRL_RXCFG_SHIFT                              (20U)
#define I2C_SCTRL_RXCFG(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_RXCFG_SHIFT)) & I2C_SCTRL_RXCFG_MASK)
#define I2C_SCTRL_TXCFG_MASK                               (0x80000U)
#define I2C_SCTRL_TXCFG_SHIFT                              (19U)
#define I2C_SCTRL_TXCFG(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_TXCFG_SHIFT)) & I2C_SCTRL_TXCFG_MASK)
#define I2C_SCTRL_ADDRCFG_MASK                             (0x70000U)
#define I2C_SCTRL_ADDRCFG_SHIFT                            (16U)
#define I2C_SCTRL_ADDRCFG(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_ADDRCFG_SHIFT)) & I2C_SCTRL_ADDRCFG_MASK)
#define I2C_SCTRL_IGACK_MASK                               (0x8000U)
#define I2C_SCTRL_IGACK_SHIFT                              (15U)
#define I2C_SCTRL_IGACK(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_IGACK_SHIFT)) & I2C_SCTRL_IGACK_MASK)
#define I2C_SCTRL_TXRST_MASK                               (0x2000U)
#define I2C_SCTRL_TXRST_SHIFT                              (13U)
#define I2C_SCTRL_TXRST(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_TXRST_SHIFT)) & I2C_SCTRL_TXRST_MASK)
#define I2C_SCTRL_RXRST_MASK                               (0x1000U)
#define I2C_SCTRL_RXRST_SHIFT                              (12U)
#define I2C_SCTRL_RXRST(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_RXRST_SHIFT)) & I2C_SCTRL_RXRST_MASK)
#define I2C_SCTRL_ALERTEN_MASK                             (0x800U)
#define I2C_SCTRL_ALERTEN_SHIFT                            (11U)
#define I2C_SCTRL_ALERTEN(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_ALERTEN_SHIFT)) & I2C_SCTRL_ALERTEN_MASK)
#define I2C_SCTRL_GCEN_MASK                                (0x400U)
#define I2C_SCTRL_GCEN_SHIFT                               (10U)
#define I2C_SCTRL_GCEN(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_GCEN_SHIFT)) & I2C_SCTRL_GCEN_MASK)
#define I2C_SCTRL_TXSTALL_MASK                             (0x80U)
#define I2C_SCTRL_TXSTALL_SHIFT                            (7U)
#define I2C_SCTRL_TXSTALL(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_TXSTALL_SHIFT)) & I2C_SCTRL_TXSTALL_MASK)
#define I2C_SCTRL_RXSTALL_MASK                             (0x40U)
#define I2C_SCTRL_RXSTALL_SHIFT                            (6U)
#define I2C_SCTRL_RXSTALL(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_RXSTALL_SHIFT)) & I2C_SCTRL_RXSTALL_MASK)
#define I2C_SCTRL_ACKSTALL_MASK                            (0x20U)
#define I2C_SCTRL_ACKSTALL_SHIFT                           (5U)
#define I2C_SCTRL_ACKSTALL(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_ACKSTALL_SHIFT)) & I2C_SCTRL_ACKSTALL_MASK)
#define I2C_SCTRL_ADRSTALL_MASK                            (0x10U)
#define I2C_SCTRL_ADRSTALL_SHIFT                           (4U)
#define I2C_SCTRL_ADRSTALL(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_ADRSTALL_SHIFT)) & I2C_SCTRL_ADRSTALL_MASK)
#define I2C_SCTRL_FILTEN_MASK                              (0x4U)
#define I2C_SCTRL_FILTEN_SHIFT                             (2U)
#define I2C_SCTRL_FILTEN(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_FILTEN_SHIFT)) & I2C_SCTRL_FILTEN_MASK)
#define I2C_SCTRL_SEN_MASK                                 (0x1U)
#define I2C_SCTRL_SEN_SHIFT                                (0U)
#define I2C_SCTRL_SEN(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SCTRL_SEN_SHIFT)) & I2C_SCTRL_SEN_MASK)
/* I2C_SCLKCFG Register */
#define I2C_SCLKCFG_VALID_MASK                             (0x3F00U)
#define I2C_SCLKCFG_VALID_SHIFT                            (8U)
#define I2C_SCLKCFG_VALID(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SCLKCFG_VALID_SHIFT)) & I2C_SCLKCFG_VALID_MASK)
#define I2C_SCLKCFG_HOLD_MASK                              (0xFU)
#define I2C_SCLKCFG_HOLD_SHIFT                             (0U)
#define I2C_SCLKCFG_HOLD(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_SCLKCFG_HOLD_SHIFT)) & I2C_SCLKCFG_HOLD_MASK)
/* I2C_SFLTCFG Register */
#define I2C_SFLTCFG_FLTSCL_MASK                            (0xF000000U)
#define I2C_SFLTCFG_FLTSCL_SHIFT                           (24U)
#define I2C_SFLTCFG_FLTSCL(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_SFLTCFG_FLTSCL_SHIFT)) & I2C_SFLTCFG_FLTSCL_MASK)
#define I2C_SFLTCFG_FLTSDA_MASK                            (0xF0000U)
#define I2C_SFLTCFG_FLTSDA_SHIFT                           (16U)
#define I2C_SFLTCFG_FLTSDA(x)                              (((uint32_t)(((uint32_t)(x)) << I2C_SFLTCFG_FLTSDA_SHIFT)) & I2C_SFLTCFG_FLTSDA_MASK)
/* I2C_SSTS Register */
#define I2C_SSTS_ACTIVE_MASK                               (0x20000U)
#define I2C_SSTS_ACTIVE_SHIFT                              (17U)
#define I2C_SSTS_ACTIVE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ACTIVE_SHIFT)) & I2C_SSTS_ACTIVE_MASK)
#define I2C_SSTS_BUSY_MASK                                 (0x10000U)
#define I2C_SSTS_BUSY_SHIFT                                (16U)
#define I2C_SSTS_BUSY(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_BUSY_SHIFT)) & I2C_SSTS_BUSY_MASK)
#define I2C_SSTS_OPERRIF_MASK                              (0x2000U)
#define I2C_SSTS_OPERRIF_SHIFT                             (13U)
#define I2C_SSTS_OPERRIF(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_OPERRIF_SHIFT)) & I2C_SSTS_OPERRIF_MASK)
#define I2C_SSTS_ALERTIF_MASK                              (0x1000U)
#define I2C_SSTS_ALERTIF_SHIFT                             (12U)
#define I2C_SSTS_ALERTIF(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ALERTIF_SHIFT)) & I2C_SSTS_ALERTIF_MASK)
#define I2C_SSTS_GCIF_MASK                                 (0x800U)
#define I2C_SSTS_GCIF_SHIFT                                (11U)
#define I2C_SSTS_GCIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_GCIF_SHIFT)) & I2C_SSTS_GCIF_MASK)
#define I2C_SSTS_ADRBIF_MASK                               (0x400U)
#define I2C_SSTS_ADRBIF_SHIFT                              (10U)
#define I2C_SSTS_ADRBIF(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ADRBIF_SHIFT)) & I2C_SSTS_ADRBIF_MASK)
#define I2C_SSTS_MATCHAIF_MASK                             (0x200U)
#define I2C_SSTS_MATCHAIF_SHIFT                            (9U)
#define I2C_SSTS_MATCHAIF(x)                               (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_MATCHAIF_SHIFT)) & I2C_SSTS_MATCHAIF_MASK)
#define I2C_SSTS_ARBIF_MASK                                (0x80U)
#define I2C_SSTS_ARBIF_SHIFT                               (7U)
#define I2C_SSTS_ARBIF(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ARBIF_SHIFT)) & I2C_SSTS_ARBIF_MASK)
#define I2C_SSTS_RSIF_MASK                                 (0x20U)
#define I2C_SSTS_RSIF_SHIFT                                (5U)
#define I2C_SSTS_RSIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_RSIF_SHIFT)) & I2C_SSTS_RSIF_MASK)
#define I2C_SSTS_STOPIF_MASK                               (0x10U)
#define I2C_SSTS_STOPIF_SHIFT                              (4U)
#define I2C_SSTS_STOPIF(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_STOPIF_SHIFT)) & I2C_SSTS_STOPIF_MASK)
#define I2C_SSTS_ADDRIF_MASK                               (0x8U)
#define I2C_SSTS_ADDRIF_SHIFT                              (3U)
#define I2C_SSTS_ADDRIF(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ADDRIF_SHIFT)) & I2C_SSTS_ADDRIF_MASK)
#define I2C_SSTS_ACKIF_MASK                                (0x4U)
#define I2C_SSTS_ACKIF_SHIFT                               (2U)
#define I2C_SSTS_ACKIF(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_ACKIF_SHIFT)) & I2C_SSTS_ACKIF_MASK)
#define I2C_SSTS_TXIF_MASK                                 (0x2U)
#define I2C_SSTS_TXIF_SHIFT                                (1U)
#define I2C_SSTS_TXIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_TXIF_SHIFT)) & I2C_SSTS_TXIF_MASK)
#define I2C_SSTS_RXIF_MASK                                 (0x1U)
#define I2C_SSTS_RXIF_SHIFT                                (0U)
#define I2C_SSTS_RXIF(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SSTS_RXIF_SHIFT)) & I2C_SSTS_RXIF_MASK)
/* I2C_SIE Register */
#define I2C_SIE_OPERRIE_MASK                               (0x2000U)
#define I2C_SIE_OPERRIE_SHIFT                              (13U)
#define I2C_SIE_OPERRIE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SIE_OPERRIE_SHIFT)) & I2C_SIE_OPERRIE_MASK)
#define I2C_SIE_ALERTIE_MASK                               (0x1000U)
#define I2C_SIE_ALERTIE_SHIFT                              (12U)
#define I2C_SIE_ALERTIE(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SIE_ALERTIE_SHIFT)) & I2C_SIE_ALERTIE_MASK)
#define I2C_SIE_GCIE_MASK                                  (0x800U)
#define I2C_SIE_GCIE_SHIFT                                 (11U)
#define I2C_SIE_GCIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_SIE_GCIE_SHIFT)) & I2C_SIE_GCIE_MASK)
#define I2C_SIE_MAT1IE_MASK                                (0x400U)
#define I2C_SIE_MAT1IE_SHIFT                               (10U)
#define I2C_SIE_MAT1IE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SIE_MAT1IE_SHIFT)) & I2C_SIE_MAT1IE_MASK)
#define I2C_SIE_MAT0IE_MASK                                (0x200U)
#define I2C_SIE_MAT0IE_SHIFT                               (9U)
#define I2C_SIE_MAT0IE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SIE_MAT0IE_SHIFT)) & I2C_SIE_MAT0IE_MASK)
#define I2C_SIE_ARBIE_MASK                                 (0x80U)
#define I2C_SIE_ARBIE_SHIFT                                (7U)
#define I2C_SIE_ARBIE(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SIE_ARBIE_SHIFT)) & I2C_SIE_ARBIE_MASK)
#define I2C_SIE_RSIE_MASK                                  (0x20U)
#define I2C_SIE_RSIE_SHIFT                                 (5U)
#define I2C_SIE_RSIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_SIE_RSIE_SHIFT)) & I2C_SIE_RSIE_MASK)
#define I2C_SIE_STOPIE_MASK                                (0x10U)
#define I2C_SIE_STOPIE_SHIFT                               (4U)
#define I2C_SIE_STOPIE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SIE_STOPIE_SHIFT)) & I2C_SIE_STOPIE_MASK)
#define I2C_SIE_ADDRIE_MASK                                (0x8U)
#define I2C_SIE_ADDRIE_SHIFT                               (3U)
#define I2C_SIE_ADDRIE(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SIE_ADDRIE_SHIFT)) & I2C_SIE_ADDRIE_MASK)
#define I2C_SIE_ACKIE_MASK                                 (0x4U)
#define I2C_SIE_ACKIE_SHIFT                                (2U)
#define I2C_SIE_ACKIE(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SIE_ACKIE_SHIFT)) & I2C_SIE_ACKIE_MASK)
#define I2C_SIE_TXIE_MASK                                  (0x2U)
#define I2C_SIE_TXIE_SHIFT                                 (1U)
#define I2C_SIE_TXIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_SIE_TXIE_SHIFT)) & I2C_SIE_TXIE_MASK)
#define I2C_SIE_RXIE_MASK                                  (0x1U)
#define I2C_SIE_RXIE_SHIFT                                 (0U)
#define I2C_SIE_RXIE(x)                                    (((uint32_t)(((uint32_t)(x)) << I2C_SIE_RXIE_SHIFT)) & I2C_SIE_RXIE_MASK)
/* I2C_SDATA Register */
#define I2C_SDATA_EMPTY_MASK                               (0x10000U)
#define I2C_SDATA_EMPTY_SHIFT                              (16U)
#define I2C_SDATA_EMPTY(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SDATA_EMPTY_SHIFT)) & I2C_SDATA_EMPTY_MASK)
#define I2C_SDATA_DATA_MASK                                (0xFFU)
#define I2C_SDATA_DATA_SHIFT                               (0U)
#define I2C_SDATA_DATA(x)                                  (((uint32_t)(((uint32_t)(x)) << I2C_SDATA_DATA_SHIFT)) & I2C_SDATA_DATA_MASK)
/* I2C_SACK Register */
#define I2C_SACK_NACK_MASK                                 (0x1U)
#define I2C_SACK_NACK_SHIFT                                (0U)
#define I2C_SACK_NACK(x)                                   (((uint32_t)(((uint32_t)(x)) << I2C_SACK_NACK_SHIFT)) & I2C_SACK_NACK_MASK)
/* I2C_SADDR Register */
#define I2C_SADDR_ADDRB_MASK                               (0x7FF0000U)
#define I2C_SADDR_ADDRB_SHIFT                              (16U)
#define I2C_SADDR_ADDRB(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SADDR_ADDRB_SHIFT)) & I2C_SADDR_ADDRB_MASK)
#define I2C_SADDR_ADDRA_MASK                               (0x7FFU)
#define I2C_SADDR_ADDRA_SHIFT                              (0U)
#define I2C_SADDR_ADDRA(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SADDR_ADDRA_SHIFT)) & I2C_SADDR_ADDRA_MASK)
/* I2C_SRADDR Register */
#define I2C_SRADDR_VALID_MASK                              (0x8000U)
#define I2C_SRADDR_VALID_SHIFT                             (15U)
#define I2C_SRADDR_VALID(x)                                (((uint32_t)(((uint32_t)(x)) << I2C_SRADDR_VALID_SHIFT)) & I2C_SRADDR_VALID_MASK)
#define I2C_SRADDR_ADDR_MASK                               (0x7FFU)
#define I2C_SRADDR_ADDR_SHIFT                              (0U)
#define I2C_SRADDR_ADDR(x)                                 (((uint32_t)(((uint32_t)(x)) << I2C_SRADDR_ADDR_SHIFT)) & I2C_SRADDR_ADDR_MASK)


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- TMR Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Peripheral_Access_Layer TMR Peripheral Access Layer
 * @{
 */


/** TMR - Size of Registers Arrays */
#define TMR_CH_COUNT                     (4)

/* TMR Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t PRS;                                /**< Prescaler Register, offset: 0x0004 */
    __IO uint32_t CNT;                                /**< Count Register, offset: 0x0008 */
    __IO uint32_t RESERVED0[ 1];                      /**< RESERVED0, offset: 0x000C */
    struct {
        __IO uint32_t CTRL;                               /**< Channel Control Register, offset: 0x0010 */
        __IO uint32_t INT;                                /**< Channel Interrupt Register, offset: 0x0014 */
        __IO uint32_t CMP;                                /**< Channel Compare Register, offset: 0x0018 */
    __IO uint32_t RESERVED1[ 1];                      /**< RESERVED1, offset: 0x001C */

    } CH[4];

} TMR_Type, *TMR_MemMapPtr;

/** Number of instances of the TMR module. */
#define TMR_INSTANCE_COUNT                             (1u)

/* TMR0  base address */
#define TMR0_BASE                                          (0x40054000)
#define TMR0                                               ((TMR_Type *)(TMR0_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */
#define TMR0_MIRROR_BASE                                   (0x40054800)
#define TMR0_MIRROR                                        ((TMR_Type *)(TMR0_MIRROR_BASE))

#define TMR0_PPU_BASE                                      (0x40054000)
#define TMR0_PPU                                           ((PPU_Type *)(TMR0_BASE))
/*-------------------------- PPU PROTECTED REGISTER --------------------------- */


/** Array initializer of TMR peripheral base addresses */
#define TMR_BASE_ADDRS                                     { TMR0_BASE }
/** Array initializer of TMR peripheral base pointers */
#define TMR_BASE_PTRS                                      { TMR0 }
/** Number of interrupt vector arrays for the TMR module. */
#define TMR_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the TMR. */
#define TMR_IRQS_CH_COUNT                         (4u)
/** Interrupt vectors for the TMR peripheral type */
#define TMR_IRQS                                  { TMR0_Ch0_IRQn, TMR0_Ch1_IRQn, TMR0_Ch2_IRQn, TMR0_Ch3_IRQn }

/* TMR Register Mask */
/* TMR_CTRL Register */
#define TMR_CTRL_DBGDIS_MASK                               (0x2U)
#define TMR_CTRL_DBGDIS_SHIFT                              (1U)
#define TMR_CTRL_DBGDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << TMR_CTRL_DBGDIS_SHIFT)) & TMR_CTRL_DBGDIS_MASK)
#define TMR_CTRL_TEN_MASK                                  (0x1U)
#define TMR_CTRL_TEN_SHIFT                                 (0U)
#define TMR_CTRL_TEN(x)                                    (((uint32_t)(((uint32_t)(x)) << TMR_CTRL_TEN_SHIFT)) & TMR_CTRL_TEN_MASK)
/* TMR_PRS Register */
#define TMR_PRS_PRS_MASK                                   (0xFFU)
#define TMR_PRS_PRS_SHIFT                                  (0U)
#define TMR_PRS_PRS(x)                                     (((uint32_t)(((uint32_t)(x)) << TMR_PRS_PRS_SHIFT)) & TMR_PRS_PRS_MASK)
/* TMR_CNT Register */
#define TMR_CNT_CNT_MASK                                   (0xFFFFFFFFU)
#define TMR_CNT_CNT_SHIFT                                  (0U)
#define TMR_CNT_CNT(x)                                     (((uint32_t)(((uint32_t)(x)) << TMR_CNT_CNT_SHIFT)) & TMR_CNT_CNT_MASK)
/* TMR_CH_CTRL Register */
#define TMR_CH_CTRL_CHEN_MASK                                 (0x1U)
#define TMR_CH_CTRL_CHEN_SHIFT                                (0U)
#define TMR_CH_CTRL_CHEN(x)                                   (((uint32_t)(((uint32_t)(x)) << TMR_CH_CTRL_CHEN_SHIFT)) & TMR_CH_CTRL_CHEN_MASK)
/* TMR_CH_INT Register */
#define TMR_CH_INT_CHIF_MASK                                  (0x1U)
#define TMR_CH_INT_CHIF_SHIFT                                 (0U)
#define TMR_CH_INT_CHIF(x)                                    (((uint32_t)(((uint32_t)(x)) << TMR_CH_INT_CHIF_SHIFT)) & TMR_CH_INT_CHIF_MASK)
/* TMR_CH_CMP Register */
#define TMR_CH_CMP_CHCMP_MASK                                 (0xFFFFFFFFU)
#define TMR_CH_CMP_CHCMP_SHIFT                                (0U)
#define TMR_CH_CMP_CHCMP(x)                                   (((uint32_t)(((uint32_t)(x)) << TMR_CH_CMP_CHCMP_SHIFT)) & TMR_CH_CMP_CHCMP_MASK)



/*!
 * @}
 */ /* end of group TMR_Register_Masks */


/*!
 * @}
 */ /* end of group TMR_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- pTMR Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup pTMR_Peripheral_Access_Layer pTMR Peripheral Access Layer
 * @{
 */


/** pTMR - Size of Registers Arrays */
#define pTMR_CH_COUNT                     (4)

/* pTMR Register Layout Typedef */
typedef struct {
    __IO uint32_t MCR;                                /**< Module Control Register, offset: 0x0000 */
    __IO uint32_t RESERVED0[63];                      /**< RESERVED0, offset: 0x0004 */
    struct {
        __IO uint32_t TSV;                                /**< Timer Start Value Register, offset: 0x0100 */
        __IO uint32_t TCV;                                /**< Timer Current Value Register, offset: 0x0104 */
        __IO uint32_t TCR;                                /**< Timer Control Register, offset: 0x0108 */
        __IO uint32_t TFR;                                /**< Timer Flag Register, offset: 0x010C */

    } CH[4];

} pTMR_Type, *pTMR_MemMapPtr;

/** Number of instances of the pTMR module. */
#define pTMR_INSTANCE_COUNT                            (1u)

/* pTMR base address */
#define pTMR_BASE                                         (0x4005A000)
#define pTMR                                              ((pTMR_Type *)(pTMR_BASE))

/** Array initializer of pTMR peripheral base addresses */
#define pTMR_BASE_ADDRS                                    { pTMR_BASE }
/** Array initializer of pTMR peripheral base pointers */
#define pTMR_BASE_PTRS                                     { pTMR }
/** Number of interrupt vector arrays for the pTMR module. */
#define pTMR_IRQS_ARR_COUNT                                (1u)
/** Number of interrupt channels for the pTMR. */
#define pTMR_IRQS_CH_COUNT                        (4u)
/** Interrupt vectors for the pTMR peripheral type */
#define pTMR_IRQS                                 { {pTMR_Ch0_IRQn, pTMR_Ch1_IRQn, pTMR_Ch2_IRQn, pTMR_Ch3_IRQn} }

/* pTMR Register Mask */
/* pTMR_MCR Register */
#define pTMR_MCR_FRZ_MASK                                   (0x2U)
#define pTMR_MCR_FRZ_SHIFT                                  (1U)
#define pTMR_MCR_FRZ(x)                                     (((uint32_t)(((uint32_t)(x)) << pTMR_MCR_FRZ_SHIFT)) & pTMR_MCR_FRZ_MASK)
#define pTMR_MCR_EN_MASK                                    (0x1U)
#define pTMR_MCR_EN_SHIFT                                   (0U)
#define pTMR_MCR_EN(x)                                      (((uint32_t)(((uint32_t)(x)) << pTMR_MCR_EN_SHIFT)) & pTMR_MCR_EN_MASK)
/* pTMR_CH_TSV Register */
#define pTMR_CH_TSV_STVAL_MASK                                 (0xFFFFFFFFU)
#define pTMR_CH_TSV_STVAL_SHIFT                                (0U)
#define pTMR_CH_TSV_STVAL(x)                                   (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TSV_STVAL_SHIFT)) & pTMR_CH_TSV_STVAL_MASK)
/* pTMR_CH_TCV Register */
#define pTMR_CH_TCV_CVAL_MASK                                  (0xFFFFFFFFU)
#define pTMR_CH_TCV_CVAL_SHIFT                                 (0U)
#define pTMR_CH_TCV_CVAL(x)                                    (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TCV_CVAL_SHIFT)) & pTMR_CH_TCV_CVAL_MASK)
/* pTMR_CH_TCR Register */
#define pTMR_CH_TCR_CHAIN_MASK                                 (0x4U)
#define pTMR_CH_TCR_CHAIN_SHIFT                                (2U)
#define pTMR_CH_TCR_CHAIN(x)                                   (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TCR_CHAIN_SHIFT)) & pTMR_CH_TCR_CHAIN_MASK)
#define pTMR_CH_TCR_TIE_MASK                                   (0x2U)
#define pTMR_CH_TCR_TIE_SHIFT                                  (1U)
#define pTMR_CH_TCR_TIE(x)                                     (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TCR_TIE_SHIFT)) & pTMR_CH_TCR_TIE_MASK)
#define pTMR_CH_TCR_TEN_MASK                                   (0x1U)
#define pTMR_CH_TCR_TEN_SHIFT                                  (0U)
#define pTMR_CH_TCR_TEN(x)                                     (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TCR_TEN_SHIFT)) & pTMR_CH_TCR_TEN_MASK)
/* pTMR_CH_TFR Register */
#define pTMR_CH_TFR_TIF_MASK                                   (0x1U)
#define pTMR_CH_TFR_TIF_SHIFT                                  (0U)
#define pTMR_CH_TFR_TIF(x)                                     (((uint32_t)(((uint32_t)(x)) << pTMR_CH_TFR_TIF_SHIFT)) & pTMR_CH_TFR_TIF_MASK)



/*!
 * @}
 */ /* end of group pTMR_Register_Masks */


/*!
 * @}
 */ /* end of group pTMR_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- lpTMR Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup lpTMR_Peripheral_Access_Layer lpTMR Peripheral Access Layer
 * @{
 */


/** lpTMR - Size of Registers Arrays */

/* lpTMR Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t PRS;                                /**< Prescaler Register, offset: 0x0004 */
    __IO uint32_t DIE;                                /**< DMA and Interrupt Enable Register, offset: 0x0008 */
    __IO uint32_t STS;                                /**< Status Register, offset: 0x000C */
    __IO uint32_t CMP;                                /**< Compare Value Register, offset: 0x0010 */
    __O  uint32_t LCNT;                               /**< Latch Timer Counter Register, offset: 0x0014 */
    __IO uint32_t CNT;                                /**< Timer Current Counter Register, offset: 0x0018 */

} lpTMR_Type, *lpTMR_MemMapPtr;

/** Number of instances of the lpTMR module. */
#define lpTMR_INSTANCE_COUNT                           (1u)

/* lpTMR0  base address */
#define lpTMR0_BASE                                        (0x4005D000)
#define lpTMR0                                             ((lpTMR_Type *)(lpTMR0_BASE))

/** Array initializer of lpTMR peripheral base addresses */
#define lpTMR_BASE_ADDRS                                   { lpTMR0_BASE }
/** Array initializer of lpTMR peripheral base pointers */
#define lpTMR_BASE_PTRS                                    { lpTMR0 }
/** Number of interrupt vector arrays for the lpTMR module. */
#define lpTMR_IRQS_ARR_COUNT                               (1u)
/** Number of interrupt channels for the lpTMR. */
#define lpTMR_IRQS_CH_COUNT                       (1u)
/** Interrupt vectors for the lpTMR peripheral type */
#define lpTMR_IRQS                                { lpTMR_IRQn }

/* lpTMR Register Mask */
/* lpTMR_CTRL Register */
#define lpTMR_CTRL_PINSEL_MASK                               (0x30U)
#define lpTMR_CTRL_PINSEL_SHIFT                              (4U)
#define lpTMR_CTRL_PINSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << lpTMR_CTRL_PINSEL_SHIFT)) & lpTMR_CTRL_PINSEL_MASK)
#define lpTMR_CTRL_PINPOL_MASK                               (0x8U)
#define lpTMR_CTRL_PINPOL_SHIFT                              (3U)
#define lpTMR_CTRL_PINPOL(x)                                 (((uint32_t)(((uint32_t)(x)) << lpTMR_CTRL_PINPOL_SHIFT)) & lpTMR_CTRL_PINPOL_MASK)
#define lpTMR_CTRL_TMODE_MASK                                (0x4U)
#define lpTMR_CTRL_TMODE_SHIFT                               (2U)
#define lpTMR_CTRL_TMODE(x)                                  (((uint32_t)(((uint32_t)(x)) << lpTMR_CTRL_TMODE_SHIFT)) & lpTMR_CTRL_TMODE_MASK)
#define lpTMR_CTRL_MODE_MASK                                 (0x2U)
#define lpTMR_CTRL_MODE_SHIFT                                (1U)
#define lpTMR_CTRL_MODE(x)                                   (((uint32_t)(((uint32_t)(x)) << lpTMR_CTRL_MODE_SHIFT)) & lpTMR_CTRL_MODE_MASK)
#define lpTMR_CTRL_EN_MASK                                   (0x1U)
#define lpTMR_CTRL_EN_SHIFT                                  (0U)
#define lpTMR_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << lpTMR_CTRL_EN_SHIFT)) & lpTMR_CTRL_EN_MASK)
/* lpTMR_PRS Register */
#define lpTMR_PRS_PRES_WIDTH                                 (4)
#define lpTMR_PRS_PRES_MASK                                  (0x78U)
#define lpTMR_PRS_PRES_SHIFT                                 (3U)
#define lpTMR_PRS_PRES(x)                                    (((uint32_t)(((uint32_t)(x)) << lpTMR_PRS_PRES_SHIFT)) & lpTMR_PRS_PRES_MASK)
#define lpTMR_PRS_BYPASS_MASK                                (0x4U)
#define lpTMR_PRS_BYPASS_SHIFT                               (2U)
#define lpTMR_PRS_BYPASS(x)                                  (((uint32_t)(((uint32_t)(x)) << lpTMR_PRS_BYPASS_SHIFT)) & lpTMR_PRS_BYPASS_MASK)
#define lpTMR_PRS_CLKSEL_MASK                                (0x3U)
#define lpTMR_PRS_CLKSEL_SHIFT                               (0U)
#define lpTMR_PRS_CLKSEL(x)                                  (((uint32_t)(((uint32_t)(x)) << lpTMR_PRS_CLKSEL_SHIFT)) & lpTMR_PRS_CLKSEL_MASK)
/* lpTMR_DIE Register */
#define lpTMR_DIE_DMAEN_MASK                                 (0x2U)
#define lpTMR_DIE_DMAEN_SHIFT                                (1U)
#define lpTMR_DIE_DMAEN(x)                                   (((uint32_t)(((uint32_t)(x)) << lpTMR_DIE_DMAEN_SHIFT)) & lpTMR_DIE_DMAEN_MASK)
#define lpTMR_DIE_IE_MASK                                    (0x1U)
#define lpTMR_DIE_IE_SHIFT                                   (0U)
#define lpTMR_DIE_IE(x)                                      (((uint32_t)(((uint32_t)(x)) << lpTMR_DIE_IE_SHIFT)) & lpTMR_DIE_IE_MASK)
/* lpTMR_STS Register */
#define lpTMR_STS_CCF_MASK                                   (0x1U)
#define lpTMR_STS_CCF_SHIFT                                  (0U)
#define lpTMR_STS_CCF(x)                                     (((uint32_t)(((uint32_t)(x)) << lpTMR_STS_CCF_SHIFT)) & lpTMR_STS_CCF_MASK)
/* lpTMR_CMP Register */
#define lpTMR_CMP_CMP_MASK                                   (0xFFFFU)
#define lpTMR_CMP_CMP_SHIFT                                  (0U)
#define lpTMR_CMP_CMP(x)                                     (((uint32_t)(((uint32_t)(x)) << lpTMR_CMP_CMP_SHIFT)) & lpTMR_CMP_CMP_MASK)
/* lpTMR_LCNT Register */
#define lpTMR_LCNT_LCVAL_MASK                                (0xFFFFU)
#define lpTMR_LCNT_LCVAL_SHIFT                               (0U)
#define lpTMR_LCNT_LCVAL(x)                                  (((uint32_t)(((uint32_t)(x)) << lpTMR_LCNT_LCVAL_SHIFT)) & lpTMR_LCNT_LCVAL_MASK)
/* lpTMR_CNT Register */
#define lpTMR_CNT_CVAL_WIDTH                                 (16)
#define lpTMR_CNT_CVAL_MASK                                  (0xFFFFU)
#define lpTMR_CNT_CVAL_SHIFT                                 (0U)
#define lpTMR_CNT_CVAL(x)                                    (((uint32_t)(((uint32_t)(x)) << lpTMR_CNT_CVAL_SHIFT)) & lpTMR_CNT_CVAL_MASK)


/*!
 * @}
 */ /* end of group lpTMR_Register_Masks */


/*!
 * @}
 */ /* end of group lpTMR_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- eTMR Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup eTMR_Peripheral_Access_Layer eTMR Peripheral Access Layer
 * @{
 */


/** eTMR - Size of Registers Arrays */
#define eTMR_CH_COUNT                     (8)

/* eTMR Register Layout Typedef */
typedef struct {
    __IO uint32_t STS;                                /**< Status Register, offset: 0x0000 */
    __I  uint32_t IOSTS;                              /**< Input/Output Status Register, offset: 0x0004 */
    __IO uint32_t CNT;                                /**< Counter Value Register, offset: 0x0008 */
    __I  uint32_t QDCNT;                              /**< Quadrature Decoder Counter Value Register, offset: 0x000C */
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0010 */
    __IO uint32_t SYNC;                               /**< Synchronous Register, offset: 0x0014 */
    __IO uint32_t OTRIG;                              /**< Output Trigger Register, offset: 0x0018 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x001C */
    __IO uint32_t CHINIT;                             /**< Channel Output Initial Value Register, offset: 0x0020 */
    __IO uint32_t CHSWV;                              /**< Channel Software Value Register, offset: 0x0024 */
    __IO uint32_t CHMASK;                             /**< Channel Output Mask Value Register, offset: 0x0028 */
    __IO uint32_t CHFV;                               /**< Channel Fault Value Register, offset: 0x002C */
    __IO uint32_t INIT;                               /**< Counter Initial Value Register, offset: 0x0030 */
    __IO uint32_t MOD;                                /**< Counter Modulus Value Register, offset: 0x0034 */
    __IO uint32_t DITHMOD;                            /**< Dithering MOD Register, offset: 0x0038 */
    __IO uint32_t MID;                                /**< Counter Middle Value Register, offset: 0x003C */
    __IO uint32_t QDCTRL;                             /**< Quadrature Decoder Control Register, offset: 0x0040 */
    __IO uint32_t QDINIT;                             /**< Quadrature Decoder Counter Initial Value Register, offset: 0x0044 */
    __IO uint32_t QDMOD;                              /**< Quadrature Decoder Modulus Register, offset: 0x0048 */
    __IO uint32_t FAULT;                              /**< Fault Control Register, offset: 0x004C */
    __IO uint32_t RESERVED0[12];                      /**< RESERVED0, offset: 0x0050 */
    struct {
        __IO uint32_t CTRL;                               /**< Channel Control Register, offset: 0x0080 */
        __IO uint32_t VAL0;                               /**< Value 0 Register, offset: 0x0084 */
        __IO uint32_t VAL1;                               /**< Value 1 Register, offset: 0x0088 */
        __IO uint32_t DITHVAL1;                           /**< Dithering Value 1 Register, offset: 0x008C */
        __IO uint32_t DT;                                 /**< Deadtime Register, offset: 0x0090 */
        __I  uint32_t CVAL;                               /**< Capture Value Register, offset: 0x0094 */
        __I  uint32_t PPCNTN;                             /**< Positive Pulse Timeout Flag Number Register, offset: 0x0098 */
        __I  uint32_t PPCNTV;                             /**< Positive Pulse Width Capture Value Register, offset: 0x009C */
        __I  uint32_t NPCNTN;                             /**< Negative Pulse Timeout Flag Number Register, offset: 0x00A0 */
        __I  uint32_t NPCNTV;                             /**< Negative Pulse Width Capture Value Register, offset: 0x00A4 */
    __IO uint32_t RESERVED1[ 6];                      /**< RESERVED1, offset: 0x00A8 */

    } CH[8];

} eTMR_Type, *eTMR_MemMapPtr;

/** Number of instances of the eTMR module. */
#define eTMR_INSTANCE_COUNT                            (6u)

/* eTMR0  base address */
#define eTMR0_BASE                                         (0x40049000)
#define eTMR0                                              ((eTMR_Type *)(eTMR0_BASE))
/* eTMR1  base address */
#define eTMR1_BASE                                         (0x4004A000)
#define eTMR1                                              ((eTMR_Type *)(eTMR1_BASE))
/* eTMR2  base address */
#define eTMR2_BASE                                         (0x4004B000)
#define eTMR2                                              ((eTMR_Type *)(eTMR2_BASE))
/* eTMR3  base address */
#define eTMR3_BASE                                         (0x4004C000)
#define eTMR3                                              ((eTMR_Type *)(eTMR3_BASE))
/* eTMR4  base address */
#define eTMR4_BASE                                         (0x4004D000)
#define eTMR4                                              ((eTMR_Type *)(eTMR4_BASE))
/* eTMR5  base address */
#define eTMR5_BASE                                         (0x4004E000)
#define eTMR5                                              ((eTMR_Type *)(eTMR5_BASE))

/** Array initializer of eTMR peripheral base addresses */
#define eTMR_BASE_ADDRS                                    { eTMR0_BASE,  eTMR1_BASE,  eTMR2_BASE,  eTMR3_BASE,  eTMR4_BASE,  eTMR5_BASE }
/** Array initializer of eTMR peripheral base pointers */
#define eTMR_BASE_PTRS                                     { eTMR0,  eTMR1,  eTMR2,  eTMR3,  eTMR4,  eTMR5 }
/** Number of interrupt vector arrays for the eTMR module. */
#define eTMR_IRQS_ARR_COUNT                                (3u)
/** Number of interrupt channels for the capture and compare interrupt type of eTMR. */
#define eTMR_CHN_IRQS_CH_COUNT                    (24u)
#define eTMR_CHN_IRQS                             { {eTMR0_Ch0_Ch1_IRQn, eTMR0_Ch2_Ch3_IRQn, eTMR0_Ch4_Ch5_IRQn, eTMR0_Ch6_Ch7_IRQn}, {eTMR1_Ch0_Ch1_IRQn, eTMR1_Ch2_Ch3_IRQn, eTMR1_Ch4_Ch5_IRQn, eTMR1_Ch6_Ch7_IRQn}, {eTMR2_Ch0_Ch1_IRQn, eTMR2_Ch2_Ch3_IRQn, eTMR2_Ch4_Ch5_IRQn, eTMR2_Ch6_Ch7_IRQn}, {eTMR3_Ch0_Ch1_IRQn, eTMR3_Ch2_Ch3_IRQn, eTMR3_Ch4_Ch5_IRQn, eTMR3_Ch6_Ch7_IRQn}, {eTMR4_Ch0_Ch1_IRQn, eTMR4_Ch2_Ch3_IRQn, eTMR4_Ch4_Ch5_IRQn, eTMR4_Ch6_Ch7_IRQn}, {eTMR5_Ch0_Ch1_IRQn, eTMR5_Ch2_Ch3_IRQn, eTMR5_Ch4_Ch5_IRQn, eTMR5_Ch6_Ch7_IRQn} }
/** Number of interrupt channels for the fault interrupt type of eTMR. */
#define eTMR_FAULT_IRQS_CH_COUNT                  (6u)
#define eTMR_FAULT_IRQS                           { eTMR0_Fault_IRQn, eTMR1_Fault_IRQn, eTMR2_Fault_IRQn, eTMR3_Fault_IRQn, eTMR4_Fault_IRQn, eTMR5_Fault_IRQn }
/** Number of interrupt channels for the counter overflow interrupt type of eTMR. */
#define eTMR_OVF_IRQS_CH_COUNT                    (6u)
#define eTMR_OVF_IRQS                             { eTMR0_Ovf_IRQn, eTMR1_Ovf_IRQn, eTMR2_Ovf_IRQn, eTMR3_Ovf_IRQn, eTMR4_Ovf_IRQn, eTMR5_Ovf_IRQn }

/* eTMR Register Mask */
/* eTMR_STS Register */
#define eTMR_STS_CH7NPF_MASK                                (0x80000000U)
#define eTMR_STS_CH7NPF_SHIFT                               (31U)
#define eTMR_STS_CH7NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH7NPF_SHIFT)) & eTMR_STS_CH7NPF_MASK)
#define eTMR_STS_CH6NPF_MASK                                (0x40000000U)
#define eTMR_STS_CH6NPF_SHIFT                               (30U)
#define eTMR_STS_CH6NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH6NPF_SHIFT)) & eTMR_STS_CH6NPF_MASK)
#define eTMR_STS_CH5NPF_MASK                                (0x20000000U)
#define eTMR_STS_CH5NPF_SHIFT                               (29U)
#define eTMR_STS_CH5NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH5NPF_SHIFT)) & eTMR_STS_CH5NPF_MASK)
#define eTMR_STS_CH4NPF_MASK                                (0x10000000U)
#define eTMR_STS_CH4NPF_SHIFT                               (28U)
#define eTMR_STS_CH4NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH4NPF_SHIFT)) & eTMR_STS_CH4NPF_MASK)
#define eTMR_STS_CH3NPF_MASK                                (0x8000000U)
#define eTMR_STS_CH3NPF_SHIFT                               (27U)
#define eTMR_STS_CH3NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH3NPF_SHIFT)) & eTMR_STS_CH3NPF_MASK)
#define eTMR_STS_CH2NPF_MASK                                (0x4000000U)
#define eTMR_STS_CH2NPF_SHIFT                               (26U)
#define eTMR_STS_CH2NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH2NPF_SHIFT)) & eTMR_STS_CH2NPF_MASK)
#define eTMR_STS_CH1NPF_MASK                                (0x2000000U)
#define eTMR_STS_CH1NPF_SHIFT                               (25U)
#define eTMR_STS_CH1NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH1NPF_SHIFT)) & eTMR_STS_CH1NPF_MASK)
#define eTMR_STS_CH0NPF_MASK                                (0x1000000U)
#define eTMR_STS_CH0NPF_SHIFT                               (24U)
#define eTMR_STS_CH0NPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH0NPF_SHIFT)) & eTMR_STS_CH0NPF_MASK)
#define eTMR_STS_CH7PPF_MASK                                (0x800000U)
#define eTMR_STS_CH7PPF_SHIFT                               (23U)
#define eTMR_STS_CH7PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH7PPF_SHIFT)) & eTMR_STS_CH7PPF_MASK)
#define eTMR_STS_CH6PPF_MASK                                (0x400000U)
#define eTMR_STS_CH6PPF_SHIFT                               (22U)
#define eTMR_STS_CH6PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH6PPF_SHIFT)) & eTMR_STS_CH6PPF_MASK)
#define eTMR_STS_CH5PPF_MASK                                (0x200000U)
#define eTMR_STS_CH5PPF_SHIFT                               (21U)
#define eTMR_STS_CH5PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH5PPF_SHIFT)) & eTMR_STS_CH5PPF_MASK)
#define eTMR_STS_CH4PPF_MASK                                (0x100000U)
#define eTMR_STS_CH4PPF_SHIFT                               (20U)
#define eTMR_STS_CH4PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH4PPF_SHIFT)) & eTMR_STS_CH4PPF_MASK)
#define eTMR_STS_CH3PPF_MASK                                (0x80000U)
#define eTMR_STS_CH3PPF_SHIFT                               (19U)
#define eTMR_STS_CH3PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH3PPF_SHIFT)) & eTMR_STS_CH3PPF_MASK)
#define eTMR_STS_CH2PPF_MASK                                (0x40000U)
#define eTMR_STS_CH2PPF_SHIFT                               (18U)
#define eTMR_STS_CH2PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH2PPF_SHIFT)) & eTMR_STS_CH2PPF_MASK)
#define eTMR_STS_CH1PPF_MASK                                (0x20000U)
#define eTMR_STS_CH1PPF_SHIFT                               (17U)
#define eTMR_STS_CH1PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH1PPF_SHIFT)) & eTMR_STS_CH1PPF_MASK)
#define eTMR_STS_CH0PPF_MASK                                (0x10000U)
#define eTMR_STS_CH0PPF_SHIFT                               (16U)
#define eTMR_STS_CH0PPF(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH0PPF_SHIFT)) & eTMR_STS_CH0PPF_MASK)
#define eTMR_STS_QDDIR_MASK                                 (0x8000U)
#define eTMR_STS_QDDIR_SHIFT                                (15U)
#define eTMR_STS_QDDIR(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_STS_QDDIR_SHIFT)) & eTMR_STS_QDDIR_MASK)
#define eTMR_STS_QDTOF_MASK                                 (0x4000U)
#define eTMR_STS_QDTOF_SHIFT                                (14U)
#define eTMR_STS_QDTOF(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_STS_QDTOF_SHIFT)) & eTMR_STS_QDTOF_MASK)
#define eTMR_STS_TOF_MASK                                   (0x2000U)
#define eTMR_STS_TOF_SHIFT                                  (13U)
#define eTMR_STS_TOF(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_STS_TOF_SHIFT)) & eTMR_STS_TOF_MASK)
#define eTMR_STS_RF_MASK                                    (0x1000U)
#define eTMR_STS_RF_SHIFT                                   (12U)
#define eTMR_STS_RF(x)                                      (((uint32_t)(((uint32_t)(x)) << eTMR_STS_RF_SHIFT)) & eTMR_STS_RF_MASK)
#define eTMR_STS_F3F_MASK                                   (0x800U)
#define eTMR_STS_F3F_SHIFT                                  (11U)
#define eTMR_STS_F3F(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_STS_F3F_SHIFT)) & eTMR_STS_F3F_MASK)
#define eTMR_STS_F2F_MASK                                   (0x400U)
#define eTMR_STS_F2F_SHIFT                                  (10U)
#define eTMR_STS_F2F(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_STS_F2F_SHIFT)) & eTMR_STS_F2F_MASK)
#define eTMR_STS_F1F_MASK                                   (0x200U)
#define eTMR_STS_F1F_SHIFT                                  (9U)
#define eTMR_STS_F1F(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_STS_F1F_SHIFT)) & eTMR_STS_F1F_MASK)
#define eTMR_STS_F0F_MASK                                   (0x100U)
#define eTMR_STS_F0F_SHIFT                                  (8U)
#define eTMR_STS_F0F(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_STS_F0F_SHIFT)) & eTMR_STS_F0F_MASK)
#define eTMR_STS_CH7F_MASK                                  (0x80U)
#define eTMR_STS_CH7F_SHIFT                                 (7U)
#define eTMR_STS_CH7F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH7F_SHIFT)) & eTMR_STS_CH7F_MASK)
#define eTMR_STS_CH6F_MASK                                  (0x40U)
#define eTMR_STS_CH6F_SHIFT                                 (6U)
#define eTMR_STS_CH6F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH6F_SHIFT)) & eTMR_STS_CH6F_MASK)
#define eTMR_STS_CH5F_MASK                                  (0x20U)
#define eTMR_STS_CH5F_SHIFT                                 (5U)
#define eTMR_STS_CH5F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH5F_SHIFT)) & eTMR_STS_CH5F_MASK)
#define eTMR_STS_CH4F_MASK                                  (0x10U)
#define eTMR_STS_CH4F_SHIFT                                 (4U)
#define eTMR_STS_CH4F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH4F_SHIFT)) & eTMR_STS_CH4F_MASK)
#define eTMR_STS_CH3F_MASK                                  (0x8U)
#define eTMR_STS_CH3F_SHIFT                                 (3U)
#define eTMR_STS_CH3F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH3F_SHIFT)) & eTMR_STS_CH3F_MASK)
#define eTMR_STS_CH2F_MASK                                  (0x4U)
#define eTMR_STS_CH2F_SHIFT                                 (2U)
#define eTMR_STS_CH2F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH2F_SHIFT)) & eTMR_STS_CH2F_MASK)
#define eTMR_STS_CH1F_MASK                                  (0x2U)
#define eTMR_STS_CH1F_SHIFT                                 (1U)
#define eTMR_STS_CH1F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH1F_SHIFT)) & eTMR_STS_CH1F_MASK)
#define eTMR_STS_CH0F_MASK                                  (0x1U)
#define eTMR_STS_CH0F_SHIFT                                 (0U)
#define eTMR_STS_CH0F(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_STS_CH0F_SHIFT)) & eTMR_STS_CH0F_MASK)
/* eTMR_IOSTS Register */
#define eTMR_IOSTS_PHB_MASK                                 (0x2000000U)
#define eTMR_IOSTS_PHB_SHIFT                                (25U)
#define eTMR_IOSTS_PHB(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_PHB_SHIFT)) & eTMR_IOSTS_PHB_MASK)
#define eTMR_IOSTS_PHA_MASK                                 (0x1000000U)
#define eTMR_IOSTS_PHA_SHIFT                                (24U)
#define eTMR_IOSTS_PHA(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_PHA_SHIFT)) & eTMR_IOSTS_PHA_MASK)
#define eTMR_IOSTS_F3_MASK                                  (0x80000U)
#define eTMR_IOSTS_F3_SHIFT                                 (19U)
#define eTMR_IOSTS_F3(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_F3_SHIFT)) & eTMR_IOSTS_F3_MASK)
#define eTMR_IOSTS_F2_MASK                                  (0x40000U)
#define eTMR_IOSTS_F2_SHIFT                                 (18U)
#define eTMR_IOSTS_F2(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_F2_SHIFT)) & eTMR_IOSTS_F2_MASK)
#define eTMR_IOSTS_F1_MASK                                  (0x20000U)
#define eTMR_IOSTS_F1_SHIFT                                 (17U)
#define eTMR_IOSTS_F1(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_F1_SHIFT)) & eTMR_IOSTS_F1_MASK)
#define eTMR_IOSTS_F0_MASK                                  (0x10000U)
#define eTMR_IOSTS_F0_SHIFT                                 (16U)
#define eTMR_IOSTS_F0(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_F0_SHIFT)) & eTMR_IOSTS_F0_MASK)
#define eTMR_IOSTS_CH7IO_MASK                               (0x80U)
#define eTMR_IOSTS_CH7IO_SHIFT                              (7U)
#define eTMR_IOSTS_CH7IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH7IO_SHIFT)) & eTMR_IOSTS_CH7IO_MASK)
#define eTMR_IOSTS_CH6IO_MASK                               (0x40U)
#define eTMR_IOSTS_CH6IO_SHIFT                              (6U)
#define eTMR_IOSTS_CH6IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH6IO_SHIFT)) & eTMR_IOSTS_CH6IO_MASK)
#define eTMR_IOSTS_CH5IO_MASK                               (0x20U)
#define eTMR_IOSTS_CH5IO_SHIFT                              (5U)
#define eTMR_IOSTS_CH5IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH5IO_SHIFT)) & eTMR_IOSTS_CH5IO_MASK)
#define eTMR_IOSTS_CH4IO_MASK                               (0x10U)
#define eTMR_IOSTS_CH4IO_SHIFT                              (4U)
#define eTMR_IOSTS_CH4IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH4IO_SHIFT)) & eTMR_IOSTS_CH4IO_MASK)
#define eTMR_IOSTS_CH3IO_MASK                               (0x8U)
#define eTMR_IOSTS_CH3IO_SHIFT                              (3U)
#define eTMR_IOSTS_CH3IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH3IO_SHIFT)) & eTMR_IOSTS_CH3IO_MASK)
#define eTMR_IOSTS_CH2IO_MASK                               (0x4U)
#define eTMR_IOSTS_CH2IO_SHIFT                              (2U)
#define eTMR_IOSTS_CH2IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH2IO_SHIFT)) & eTMR_IOSTS_CH2IO_MASK)
#define eTMR_IOSTS_CH1IO_MASK                               (0x2U)
#define eTMR_IOSTS_CH1IO_SHIFT                              (1U)
#define eTMR_IOSTS_CH1IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH1IO_SHIFT)) & eTMR_IOSTS_CH1IO_MASK)
#define eTMR_IOSTS_CH0IO_MASK                               (0x1U)
#define eTMR_IOSTS_CH0IO_SHIFT                              (0U)
#define eTMR_IOSTS_CH0IO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_IOSTS_CH0IO_SHIFT)) & eTMR_IOSTS_CH0IO_MASK)
/* eTMR_CNT Register */
#define eTMR_CNT_CNT_MASK                                   (0xFFFFFFFFU)
#define eTMR_CNT_CNT_SHIFT                                  (0U)
#define eTMR_CNT_CNT(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_CNT_CNT_SHIFT)) & eTMR_CNT_CNT_MASK)
/* eTMR_QDCNT Register */
#define eTMR_QDCNT_QDCNT_MASK                               (0xFFFFU)
#define eTMR_QDCNT_QDCNT_SHIFT                              (0U)
#define eTMR_QDCNT_QDCNT(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_QDCNT_QDCNT_SHIFT)) & eTMR_QDCNT_QDCNT_MASK)
/* eTMR_CTRL Register */
#define eTMR_CTRL_CAPTST_MASK                               (0x80000000U)
#define eTMR_CTRL_CAPTST_SHIFT                              (31U)
#define eTMR_CTRL_CAPTST(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_CAPTST_SHIFT)) & eTMR_CTRL_CAPTST_MASK)
#define eTMR_CTRL_COMPL67_MASK                              (0x8000000U)
#define eTMR_CTRL_COMPL67_SHIFT                             (27U)
#define eTMR_CTRL_COMPL67(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_COMPL67_SHIFT)) & eTMR_CTRL_COMPL67_MASK)
#define eTMR_CTRL_COMPL45_MASK                              (0x4000000U)
#define eTMR_CTRL_COMPL45_SHIFT                             (26U)
#define eTMR_CTRL_COMPL45(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_COMPL45_SHIFT)) & eTMR_CTRL_COMPL45_MASK)
#define eTMR_CTRL_COMPL23_MASK                              (0x2000000U)
#define eTMR_CTRL_COMPL23_SHIFT                             (25U)
#define eTMR_CTRL_COMPL23(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_COMPL23_SHIFT)) & eTMR_CTRL_COMPL23_MASK)
#define eTMR_CTRL_COMPL01_MASK                              (0x1000000U)
#define eTMR_CTRL_COMPL01_SHIFT                             (24U)
#define eTMR_CTRL_COMPL01(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_COMPL01_SHIFT)) & eTMR_CTRL_COMPL01_MASK)
#define eTMR_CTRL_DBSW67_MASK                               (0x80000U)
#define eTMR_CTRL_DBSW67_SHIFT                              (19U)
#define eTMR_CTRL_DBSW67(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DBSW67_SHIFT)) & eTMR_CTRL_DBSW67_MASK)
#define eTMR_CTRL_DBSW45_MASK                               (0x40000U)
#define eTMR_CTRL_DBSW45_SHIFT                              (18U)
#define eTMR_CTRL_DBSW45(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DBSW45_SHIFT)) & eTMR_CTRL_DBSW45_MASK)
#define eTMR_CTRL_DBSW23_MASK                               (0x20000U)
#define eTMR_CTRL_DBSW23_SHIFT                              (17U)
#define eTMR_CTRL_DBSW23(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DBSW23_SHIFT)) & eTMR_CTRL_DBSW23_MASK)
#define eTMR_CTRL_DBSW01_MASK                               (0x10000U)
#define eTMR_CTRL_DBSW01_SHIFT                              (16U)
#define eTMR_CTRL_DBSW01(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DBSW01_SHIFT)) & eTMR_CTRL_DBSW01_MASK)
#define eTMR_CTRL_DBGDIS_MASK                               (0x8000U)
#define eTMR_CTRL_DBGDIS_SHIFT                              (15U)
#define eTMR_CTRL_DBGDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DBGDIS_SHIFT)) & eTMR_CTRL_DBGDIS_MASK)
#define eTMR_CTRL_CLKPRS_WIDTH                              (7)
#define eTMR_CTRL_CLKPRS_MASK                               (0x7F00U)
#define eTMR_CTRL_CLKPRS_SHIFT                              (8U)
#define eTMR_CTRL_CLKPRS(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_CLKPRS_SHIFT)) & eTMR_CTRL_CLKPRS_MASK)
#define eTMR_CTRL_CLKSRC_MASK                               (0x10U)
#define eTMR_CTRL_CLKSRC_SHIFT                              (4U)
#define eTMR_CTRL_CLKSRC(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_CLKSRC_SHIFT)) & eTMR_CTRL_CLKSRC_MASK)
#define eTMR_CTRL_DITHMD_WIDTH                              (2)
#define eTMR_CTRL_DITHMD_MASK                               (0xCU)
#define eTMR_CTRL_DITHMD_SHIFT                              (2U)
#define eTMR_CTRL_DITHMD(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_DITHMD_SHIFT)) & eTMR_CTRL_DITHMD_MASK)
#define eTMR_CTRL_GLOBEN_MASK                               (0x2U)
#define eTMR_CTRL_GLOBEN_SHIFT                              (1U)
#define eTMR_CTRL_GLOBEN(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_GLOBEN_SHIFT)) & eTMR_CTRL_GLOBEN_MASK)
#define eTMR_CTRL_EN_MASK                                   (0x1U)
#define eTMR_CTRL_EN_SHIFT                                  (0U)
#define eTMR_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_CTRL_EN_SHIFT)) & eTMR_CTRL_EN_MASK)
/* eTMR_SYNC Register */
#define eTMR_SYNC_GLOB_MASK                                 (0x80000000U)
#define eTMR_SYNC_GLOB_SHIFT                                (31U)
#define eTMR_SYNC_GLOB(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_GLOB_SHIFT)) & eTMR_SYNC_GLOB_MASK)
#define eTMR_SYNC_LDFRQ_WIDTH                               (4)
#define eTMR_SYNC_LDFRQ_MASK                                (0xF000000U)
#define eTMR_SYNC_LDFRQ_SHIFT                               (24U)
#define eTMR_SYNC_LDFRQ(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_LDFRQ_SHIFT)) & eTMR_SYNC_LDFRQ_MASK)
#define eTMR_SYNC_TRIG2EN_MASK                              (0x80000U)
#define eTMR_SYNC_TRIG2EN_SHIFT                             (19U)
#define eTMR_SYNC_TRIG2EN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIG2EN_SHIFT)) & eTMR_SYNC_TRIG2EN_MASK)
#define eTMR_SYNC_TRIG1EN_MASK                              (0x40000U)
#define eTMR_SYNC_TRIG1EN_SHIFT                             (18U)
#define eTMR_SYNC_TRIG1EN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIG1EN_SHIFT)) & eTMR_SYNC_TRIG1EN_MASK)
#define eTMR_SYNC_TRIG0EN_MASK                              (0x20000U)
#define eTMR_SYNC_TRIG0EN_SHIFT                             (17U)
#define eTMR_SYNC_TRIG0EN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIG0EN_SHIFT)) & eTMR_SYNC_TRIG0EN_MASK)
#define eTMR_SYNC_SWTRIG_MASK                               (0x10000U)
#define eTMR_SYNC_SWTRIG_SHIFT                              (16U)
#define eTMR_SYNC_SWTRIG(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_SWTRIG_SHIFT)) & eTMR_SYNC_SWTRIG_MASK)
#define eTMR_SYNC_MASKLD_WIDTH                              (2)
#define eTMR_SYNC_MASKLD_MASK                               (0xC000U)
#define eTMR_SYNC_MASKLD_SHIFT                              (14U)
#define eTMR_SYNC_MASKLD(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_MASKLD_SHIFT)) & eTMR_SYNC_MASKLD_MASK)
#define eTMR_SYNC_TRIGS2_WIDTH                              (2)
#define eTMR_SYNC_TRIGS2_MASK                               (0x3000U)
#define eTMR_SYNC_TRIGS2_SHIFT                              (12U)
#define eTMR_SYNC_TRIGS2(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIGS2_SHIFT)) & eTMR_SYNC_TRIGS2_MASK)
#define eTMR_SYNC_CNTLD_WIDTH                               (2)
#define eTMR_SYNC_CNTLD_MASK                                (0xC00U)
#define eTMR_SYNC_CNTLD_SHIFT                               (10U)
#define eTMR_SYNC_CNTLD(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_CNTLD_SHIFT)) & eTMR_SYNC_CNTLD_MASK)
#define eTMR_SYNC_TRIGS1_WIDTH                              (2)
#define eTMR_SYNC_TRIGS1_MASK                               (0x300U)
#define eTMR_SYNC_TRIGS1_SHIFT                              (8U)
#define eTMR_SYNC_TRIGS1(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIGS1_SHIFT)) & eTMR_SYNC_TRIGS1_MASK)
#define eTMR_SYNC_REGLD_WIDTH                               (2)
#define eTMR_SYNC_REGLD_MASK                                (0xC0U)
#define eTMR_SYNC_REGLD_SHIFT                               (6U)
#define eTMR_SYNC_REGLD(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_REGLD_SHIFT)) & eTMR_SYNC_REGLD_MASK)
#define eTMR_SYNC_TRIGS0_WIDTH                              (2)
#define eTMR_SYNC_TRIGS0_MASK                               (0x30U)
#define eTMR_SYNC_TRIGS0_SHIFT                              (4U)
#define eTMR_SYNC_TRIGS0(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_TRIGS0_SHIFT)) & eTMR_SYNC_TRIGS0_MASK)
#define eTMR_SYNC_CNTINIT_MASK                              (0x4U)
#define eTMR_SYNC_CNTINIT_SHIFT                             (2U)
#define eTMR_SYNC_CNTINIT(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_CNTINIT_SHIFT)) & eTMR_SYNC_CNTINIT_MASK)
#define eTMR_SYNC_CLDOK_MASK                                (0x2U)
#define eTMR_SYNC_CLDOK_SHIFT                               (1U)
#define eTMR_SYNC_CLDOK(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_CLDOK_SHIFT)) & eTMR_SYNC_CLDOK_MASK)
#define eTMR_SYNC_LDOK_MASK                                 (0x1U)
#define eTMR_SYNC_LDOK_SHIFT                                (0U)
#define eTMR_SYNC_LDOK(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_SYNC_LDOK_SHIFT)) & eTMR_SYNC_LDOK_MASK)
/* eTMR_OTRIG Register */
#define eTMR_OTRIG_TWD_WIDTH                                (8)
#define eTMR_OTRIG_TWD_MASK                                 (0xFF0000U)
#define eTMR_OTRIG_TWD_SHIFT                                (16U)
#define eTMR_OTRIG_TWD(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_TWD_SHIFT)) & eTMR_OTRIG_TWD_MASK)
#define eTMR_OTRIG_TFRQ_WIDTH                               (4)
#define eTMR_OTRIG_TFRQ_MASK                                (0xF000U)
#define eTMR_OTRIG_TFRQ_SHIFT                               (12U)
#define eTMR_OTRIG_TFRQ(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_TFRQ_SHIFT)) & eTMR_OTRIG_TFRQ_MASK)
#define eTMR_OTRIG_PULSESRC_WIDTH                           (3)
#define eTMR_OTRIG_PULSESRC_MASK                            (0x700U)
#define eTMR_OTRIG_PULSESRC_SHIFT                           (8U)
#define eTMR_OTRIG_PULSESRC(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_PULSESRC_SHIFT)) & eTMR_OTRIG_PULSESRC_MASK)
#define eTMR_OTRIG_TSRC_MASK                                (0x10U)
#define eTMR_OTRIG_TSRC_SHIFT                               (4U)
#define eTMR_OTRIG_TSRC(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_TSRC_SHIFT)) & eTMR_OTRIG_TSRC_MASK)
#define eTMR_OTRIG_MODTEN_MASK                              (0x4U)
#define eTMR_OTRIG_MODTEN_SHIFT                             (2U)
#define eTMR_OTRIG_MODTEN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_MODTEN_SHIFT)) & eTMR_OTRIG_MODTEN_MASK)
#define eTMR_OTRIG_MIDTEN_MASK                              (0x2U)
#define eTMR_OTRIG_MIDTEN_SHIFT                             (1U)
#define eTMR_OTRIG_MIDTEN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_MIDTEN_SHIFT)) & eTMR_OTRIG_MIDTEN_MASK)
#define eTMR_OTRIG_INITTEN_MASK                             (0x1U)
#define eTMR_OTRIG_INITTEN_SHIFT                            (0U)
#define eTMR_OTRIG_INITTEN(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_OTRIG_INITTEN_SHIFT)) & eTMR_OTRIG_INITTEN_MASK)
/* eTMR_INTE Register */
#define eTMR_INTE_QDTOIE_MASK                               (0x4000U)
#define eTMR_INTE_QDTOIE_SHIFT                              (14U)
#define eTMR_INTE_QDTOIE(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_QDTOIE_SHIFT)) & eTMR_INTE_QDTOIE_MASK)
#define eTMR_INTE_TOIE_MASK                                 (0x2000U)
#define eTMR_INTE_TOIE_SHIFT                                (13U)
#define eTMR_INTE_TOIE(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_TOIE_SHIFT)) & eTMR_INTE_TOIE_MASK)
#define eTMR_INTE_FIE_MASK                                  (0x100U)
#define eTMR_INTE_FIE_SHIFT                                 (8U)
#define eTMR_INTE_FIE(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_FIE_SHIFT)) & eTMR_INTE_FIE_MASK)
#define eTMR_INTE_CH7IE_MASK                                (0x80U)
#define eTMR_INTE_CH7IE_SHIFT                               (7U)
#define eTMR_INTE_CH7IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH7IE_SHIFT)) & eTMR_INTE_CH7IE_MASK)
#define eTMR_INTE_CH6IE_MASK                                (0x40U)
#define eTMR_INTE_CH6IE_SHIFT                               (6U)
#define eTMR_INTE_CH6IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH6IE_SHIFT)) & eTMR_INTE_CH6IE_MASK)
#define eTMR_INTE_CH5IE_MASK                                (0x20U)
#define eTMR_INTE_CH5IE_SHIFT                               (5U)
#define eTMR_INTE_CH5IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH5IE_SHIFT)) & eTMR_INTE_CH5IE_MASK)
#define eTMR_INTE_CH4IE_MASK                                (0x10U)
#define eTMR_INTE_CH4IE_SHIFT                               (4U)
#define eTMR_INTE_CH4IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH4IE_SHIFT)) & eTMR_INTE_CH4IE_MASK)
#define eTMR_INTE_CH3IE_MASK                                (0x8U)
#define eTMR_INTE_CH3IE_SHIFT                               (3U)
#define eTMR_INTE_CH3IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH3IE_SHIFT)) & eTMR_INTE_CH3IE_MASK)
#define eTMR_INTE_CH2IE_MASK                                (0x4U)
#define eTMR_INTE_CH2IE_SHIFT                               (2U)
#define eTMR_INTE_CH2IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH2IE_SHIFT)) & eTMR_INTE_CH2IE_MASK)
#define eTMR_INTE_CH1IE_MASK                                (0x2U)
#define eTMR_INTE_CH1IE_SHIFT                               (1U)
#define eTMR_INTE_CH1IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH1IE_SHIFT)) & eTMR_INTE_CH1IE_MASK)
#define eTMR_INTE_CH0IE_MASK                                (0x1U)
#define eTMR_INTE_CH0IE_SHIFT                               (0U)
#define eTMR_INTE_CH0IE(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_INTE_CH0IE_SHIFT)) & eTMR_INTE_CH0IE_MASK)
/* eTMR_CHINIT Register */
#define eTMR_CHINIT_CH7INIT_MASK                            (0x80U)
#define eTMR_CHINIT_CH7INIT_SHIFT                           (7U)
#define eTMR_CHINIT_CH7INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH7INIT_SHIFT)) & eTMR_CHINIT_CH7INIT_MASK)
#define eTMR_CHINIT_CH6INIT_MASK                            (0x40U)
#define eTMR_CHINIT_CH6INIT_SHIFT                           (6U)
#define eTMR_CHINIT_CH6INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH6INIT_SHIFT)) & eTMR_CHINIT_CH6INIT_MASK)
#define eTMR_CHINIT_CH5INIT_MASK                            (0x20U)
#define eTMR_CHINIT_CH5INIT_SHIFT                           (5U)
#define eTMR_CHINIT_CH5INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH5INIT_SHIFT)) & eTMR_CHINIT_CH5INIT_MASK)
#define eTMR_CHINIT_CH4INIT_MASK                            (0x10U)
#define eTMR_CHINIT_CH4INIT_SHIFT                           (4U)
#define eTMR_CHINIT_CH4INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH4INIT_SHIFT)) & eTMR_CHINIT_CH4INIT_MASK)
#define eTMR_CHINIT_CH3INIT_MASK                            (0x8U)
#define eTMR_CHINIT_CH3INIT_SHIFT                           (3U)
#define eTMR_CHINIT_CH3INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH3INIT_SHIFT)) & eTMR_CHINIT_CH3INIT_MASK)
#define eTMR_CHINIT_CH2INIT_MASK                            (0x4U)
#define eTMR_CHINIT_CH2INIT_SHIFT                           (2U)
#define eTMR_CHINIT_CH2INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH2INIT_SHIFT)) & eTMR_CHINIT_CH2INIT_MASK)
#define eTMR_CHINIT_CH1INIT_MASK                            (0x2U)
#define eTMR_CHINIT_CH1INIT_SHIFT                           (1U)
#define eTMR_CHINIT_CH1INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH1INIT_SHIFT)) & eTMR_CHINIT_CH1INIT_MASK)
#define eTMR_CHINIT_CH0INIT_MASK                            (0x1U)
#define eTMR_CHINIT_CH0INIT_SHIFT                           (0U)
#define eTMR_CHINIT_CH0INIT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_CHINIT_CH0INIT_SHIFT)) & eTMR_CHINIT_CH0INIT_MASK)
/* eTMR_CHSWV Register */
#define eTMR_CHSWV_CH7SWV_MASK                              (0x80U)
#define eTMR_CHSWV_CH7SWV_SHIFT                             (7U)
#define eTMR_CHSWV_CH7SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH7SWV_SHIFT)) & eTMR_CHSWV_CH7SWV_MASK)
#define eTMR_CHSWV_CH6SWV_MASK                              (0x40U)
#define eTMR_CHSWV_CH6SWV_SHIFT                             (6U)
#define eTMR_CHSWV_CH6SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH6SWV_SHIFT)) & eTMR_CHSWV_CH6SWV_MASK)
#define eTMR_CHSWV_CH5SWV_MASK                              (0x20U)
#define eTMR_CHSWV_CH5SWV_SHIFT                             (5U)
#define eTMR_CHSWV_CH5SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH5SWV_SHIFT)) & eTMR_CHSWV_CH5SWV_MASK)
#define eTMR_CHSWV_CH4SWV_MASK                              (0x10U)
#define eTMR_CHSWV_CH4SWV_SHIFT                             (4U)
#define eTMR_CHSWV_CH4SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH4SWV_SHIFT)) & eTMR_CHSWV_CH4SWV_MASK)
#define eTMR_CHSWV_CH3SWV_MASK                              (0x8U)
#define eTMR_CHSWV_CH3SWV_SHIFT                             (3U)
#define eTMR_CHSWV_CH3SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH3SWV_SHIFT)) & eTMR_CHSWV_CH3SWV_MASK)
#define eTMR_CHSWV_CH2SWV_MASK                              (0x4U)
#define eTMR_CHSWV_CH2SWV_SHIFT                             (2U)
#define eTMR_CHSWV_CH2SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH2SWV_SHIFT)) & eTMR_CHSWV_CH2SWV_MASK)
#define eTMR_CHSWV_CH1SWV_MASK                              (0x2U)
#define eTMR_CHSWV_CH1SWV_SHIFT                             (1U)
#define eTMR_CHSWV_CH1SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH1SWV_SHIFT)) & eTMR_CHSWV_CH1SWV_MASK)
#define eTMR_CHSWV_CH0SWV_MASK                              (0x1U)
#define eTMR_CHSWV_CH0SWV_SHIFT                             (0U)
#define eTMR_CHSWV_CH0SWV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHSWV_CH0SWV_SHIFT)) & eTMR_CHSWV_CH0SWV_MASK)
/* eTMR_CHMASK Register */
#define eTMR_CHMASK_CH7MV_WIDTH                             (2)
#define eTMR_CHMASK_CH7MV_MASK                              (0xC0000000U)
#define eTMR_CHMASK_CH7MV_SHIFT                             (30U)
#define eTMR_CHMASK_CH7MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH7MV_SHIFT)) & eTMR_CHMASK_CH7MV_MASK)
#define eTMR_CHMASK_CH6MV_WIDTH                             (2)
#define eTMR_CHMASK_CH6MV_MASK                              (0x30000000U)
#define eTMR_CHMASK_CH6MV_SHIFT                             (28U)
#define eTMR_CHMASK_CH6MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH6MV_SHIFT)) & eTMR_CHMASK_CH6MV_MASK)
#define eTMR_CHMASK_CH5MV_WIDTH                             (2)
#define eTMR_CHMASK_CH5MV_MASK                              (0xC000000U)
#define eTMR_CHMASK_CH5MV_SHIFT                             (26U)
#define eTMR_CHMASK_CH5MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH5MV_SHIFT)) & eTMR_CHMASK_CH5MV_MASK)
#define eTMR_CHMASK_CH4MV_WIDTH                             (2)
#define eTMR_CHMASK_CH4MV_MASK                              (0x3000000U)
#define eTMR_CHMASK_CH4MV_SHIFT                             (24U)
#define eTMR_CHMASK_CH4MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH4MV_SHIFT)) & eTMR_CHMASK_CH4MV_MASK)
#define eTMR_CHMASK_CH3MV_WIDTH                             (2)
#define eTMR_CHMASK_CH3MV_MASK                              (0xC00000U)
#define eTMR_CHMASK_CH3MV_SHIFT                             (22U)
#define eTMR_CHMASK_CH3MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH3MV_SHIFT)) & eTMR_CHMASK_CH3MV_MASK)
#define eTMR_CHMASK_CH2MV_WIDTH                             (2)
#define eTMR_CHMASK_CH2MV_MASK                              (0x300000U)
#define eTMR_CHMASK_CH2MV_SHIFT                             (20U)
#define eTMR_CHMASK_CH2MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH2MV_SHIFT)) & eTMR_CHMASK_CH2MV_MASK)
#define eTMR_CHMASK_CH1MV_WIDTH                             (2)
#define eTMR_CHMASK_CH1MV_MASK                              (0xC0000U)
#define eTMR_CHMASK_CH1MV_SHIFT                             (18U)
#define eTMR_CHMASK_CH1MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH1MV_SHIFT)) & eTMR_CHMASK_CH1MV_MASK)
#define eTMR_CHMASK_CH0MV_WIDTH                             (2)
#define eTMR_CHMASK_CH0MV_MASK                              (0x30000U)
#define eTMR_CHMASK_CH0MV_SHIFT                             (16U)
#define eTMR_CHMASK_CH0MV(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH0MV_SHIFT)) & eTMR_CHMASK_CH0MV_MASK)
#define eTMR_CHMASK_CH7M_MASK                               (0x80U)
#define eTMR_CHMASK_CH7M_SHIFT                              (7U)
#define eTMR_CHMASK_CH7M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH7M_SHIFT)) & eTMR_CHMASK_CH7M_MASK)
#define eTMR_CHMASK_CH6M_MASK                               (0x40U)
#define eTMR_CHMASK_CH6M_SHIFT                              (6U)
#define eTMR_CHMASK_CH6M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH6M_SHIFT)) & eTMR_CHMASK_CH6M_MASK)
#define eTMR_CHMASK_CH5M_MASK                               (0x20U)
#define eTMR_CHMASK_CH5M_SHIFT                              (5U)
#define eTMR_CHMASK_CH5M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH5M_SHIFT)) & eTMR_CHMASK_CH5M_MASK)
#define eTMR_CHMASK_CH4M_MASK                               (0x10U)
#define eTMR_CHMASK_CH4M_SHIFT                              (4U)
#define eTMR_CHMASK_CH4M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH4M_SHIFT)) & eTMR_CHMASK_CH4M_MASK)
#define eTMR_CHMASK_CH3M_MASK                               (0x8U)
#define eTMR_CHMASK_CH3M_SHIFT                              (3U)
#define eTMR_CHMASK_CH3M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH3M_SHIFT)) & eTMR_CHMASK_CH3M_MASK)
#define eTMR_CHMASK_CH2M_MASK                               (0x4U)
#define eTMR_CHMASK_CH2M_SHIFT                              (2U)
#define eTMR_CHMASK_CH2M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH2M_SHIFT)) & eTMR_CHMASK_CH2M_MASK)
#define eTMR_CHMASK_CH1M_MASK                               (0x2U)
#define eTMR_CHMASK_CH1M_SHIFT                              (1U)
#define eTMR_CHMASK_CH1M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH1M_SHIFT)) & eTMR_CHMASK_CH1M_MASK)
#define eTMR_CHMASK_CH0M_MASK                               (0x1U)
#define eTMR_CHMASK_CH0M_SHIFT                              (0U)
#define eTMR_CHMASK_CH0M(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CHMASK_CH0M_SHIFT)) & eTMR_CHMASK_CH0M_MASK)
/* eTMR_CHFV Register */
#define eTMR_CHFV_CH7FV_WIDTH                               (2)
#define eTMR_CHFV_CH7FV_MASK                                (0xC000U)
#define eTMR_CHFV_CH7FV_SHIFT                               (14U)
#define eTMR_CHFV_CH7FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH7FV_SHIFT)) & eTMR_CHFV_CH7FV_MASK)
#define eTMR_CHFV_CH6FV_WIDTH                               (2)
#define eTMR_CHFV_CH6FV_MASK                                (0x3000U)
#define eTMR_CHFV_CH6FV_SHIFT                               (12U)
#define eTMR_CHFV_CH6FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH6FV_SHIFT)) & eTMR_CHFV_CH6FV_MASK)
#define eTMR_CHFV_CH5FV_WIDTH                               (2)
#define eTMR_CHFV_CH5FV_MASK                                (0xC00U)
#define eTMR_CHFV_CH5FV_SHIFT                               (10U)
#define eTMR_CHFV_CH5FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH5FV_SHIFT)) & eTMR_CHFV_CH5FV_MASK)
#define eTMR_CHFV_CH4FV_WIDTH                               (2)
#define eTMR_CHFV_CH4FV_MASK                                (0x300U)
#define eTMR_CHFV_CH4FV_SHIFT                               (8U)
#define eTMR_CHFV_CH4FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH4FV_SHIFT)) & eTMR_CHFV_CH4FV_MASK)
#define eTMR_CHFV_CH3FV_WIDTH                               (2)
#define eTMR_CHFV_CH3FV_MASK                                (0xC0U)
#define eTMR_CHFV_CH3FV_SHIFT                               (6U)
#define eTMR_CHFV_CH3FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH3FV_SHIFT)) & eTMR_CHFV_CH3FV_MASK)
#define eTMR_CHFV_CH2FV_WIDTH                               (2)
#define eTMR_CHFV_CH2FV_MASK                                (0x30U)
#define eTMR_CHFV_CH2FV_SHIFT                               (4U)
#define eTMR_CHFV_CH2FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH2FV_SHIFT)) & eTMR_CHFV_CH2FV_MASK)
#define eTMR_CHFV_CH1FV_WIDTH                               (2)
#define eTMR_CHFV_CH1FV_MASK                                (0xCU)
#define eTMR_CHFV_CH1FV_SHIFT                               (2U)
#define eTMR_CHFV_CH1FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH1FV_SHIFT)) & eTMR_CHFV_CH1FV_MASK)
#define eTMR_CHFV_CH0FV_WIDTH                               (2)
#define eTMR_CHFV_CH0FV_MASK                                (0x3U)
#define eTMR_CHFV_CH0FV_SHIFT                               (0U)
#define eTMR_CHFV_CH0FV(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CHFV_CH0FV_SHIFT)) & eTMR_CHFV_CH0FV_MASK)
/* eTMR_INIT Register */
#define eTMR_INIT_INIT_MASK                                 (0xFFFFFFFFU)
#define eTMR_INIT_INIT_SHIFT                                (0U)
#define eTMR_INIT_INIT(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_INIT_INIT_SHIFT)) & eTMR_INIT_INIT_MASK)
/* eTMR_MOD Register */
#define eTMR_MOD_MOD_MASK                                   (0xFFFFFFFFU)
#define eTMR_MOD_MOD_SHIFT                                  (0U)
#define eTMR_MOD_MOD(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_MOD_MOD_SHIFT)) & eTMR_MOD_MOD_MASK)
/* eTMR_DITHMOD Register */
#define eTMR_DITHMOD_MODINT_WIDTH                           (7)
#define eTMR_DITHMOD_MODINT_MASK                            (0x7F00U)
#define eTMR_DITHMOD_MODINT_SHIFT                           (8U)
#define eTMR_DITHMOD_MODINT(x)                              (((uint32_t)(((uint32_t)(x)) << eTMR_DITHMOD_MODINT_SHIFT)) & eTMR_DITHMOD_MODINT_MASK)
#define eTMR_DITHMOD_MODFRAC_WIDTH                          (5)
#define eTMR_DITHMOD_MODFRAC_MASK                           (0x1FU)
#define eTMR_DITHMOD_MODFRAC_SHIFT                          (0U)
#define eTMR_DITHMOD_MODFRAC(x)                             (((uint32_t)(((uint32_t)(x)) << eTMR_DITHMOD_MODFRAC_SHIFT)) & eTMR_DITHMOD_MODFRAC_MASK)
/* eTMR_MID Register */
#define eTMR_MID_MID_MASK                                   (0xFFFFFFFFU)
#define eTMR_MID_MID_SHIFT                                  (0U)
#define eTMR_MID_MID(x)                                     (((uint32_t)(((uint32_t)(x)) << eTMR_MID_MID_SHIFT)) & eTMR_MID_MID_MASK)
/* eTMR_QDCTRL Register */
#define eTMR_QDCTRL_QDFCNT_WIDTH                            (4)
#define eTMR_QDCTRL_QDFCNT_MASK                             (0xF0000000U)
#define eTMR_QDCTRL_QDFCNT_SHIFT                            (28U)
#define eTMR_QDCTRL_QDFCNT(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_QDFCNT_SHIFT)) & eTMR_QDCTRL_QDFCNT_MASK)
#define eTMR_QDCTRL_QDFPER_WIDTH                            (4)
#define eTMR_QDCTRL_QDFPER_MASK                             (0xF000000U)
#define eTMR_QDCTRL_QDFPER_SHIFT                            (24U)
#define eTMR_QDCTRL_QDFPER(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_QDFPER_SHIFT)) & eTMR_QDCTRL_QDFPER_MASK)
#define eTMR_QDCTRL_PHBPOL_MASK                             (0x20000U)
#define eTMR_QDCTRL_PHBPOL_SHIFT                            (17U)
#define eTMR_QDCTRL_PHBPOL(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_PHBPOL_SHIFT)) & eTMR_QDCTRL_PHBPOL_MASK)
#define eTMR_QDCTRL_PHAPOL_MASK                             (0x10000U)
#define eTMR_QDCTRL_PHAPOL_SHIFT                            (16U)
#define eTMR_QDCTRL_PHAPOL(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_PHAPOL_SHIFT)) & eTMR_QDCTRL_PHAPOL_MASK)
#define eTMR_QDCTRL_QDCLKPRS_WIDTH                          (3)
#define eTMR_QDCTRL_QDCLKPRS_MASK                           (0x7000U)
#define eTMR_QDCTRL_QDCLKPRS_SHIFT                          (12U)
#define eTMR_QDCTRL_QDCLKPRS(x)                             (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_QDCLKPRS_SHIFT)) & eTMR_QDCTRL_QDCLKPRS_MASK)
#define eTMR_QDCTRL_QDMODE_WIDTH                            (2)
#define eTMR_QDCTRL_QDMODE_MASK                             (0x30U)
#define eTMR_QDCTRL_QDMODE_SHIFT                            (4U)
#define eTMR_QDCTRL_QDMODE(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_QDMODE_SHIFT)) & eTMR_QDCTRL_QDMODE_MASK)
#define eTMR_QDCTRL_QDEN_MASK                               (0x1U)
#define eTMR_QDCTRL_QDEN_SHIFT                              (0U)
#define eTMR_QDCTRL_QDEN(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_QDCTRL_QDEN_SHIFT)) & eTMR_QDCTRL_QDEN_MASK)
/* eTMR_QDINIT Register */
#define eTMR_QDINIT_QDINIT_MASK                             (0xFFFFU)
#define eTMR_QDINIT_QDINIT_SHIFT                            (0U)
#define eTMR_QDINIT_QDINIT(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_QDINIT_QDINIT_SHIFT)) & eTMR_QDINIT_QDINIT_MASK)
/* eTMR_QDMOD Register */
#define eTMR_QDMOD_QDMOD_MASK                               (0xFFFFU)
#define eTMR_QDMOD_QDMOD_SHIFT                              (0U)
#define eTMR_QDMOD_QDMOD(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_QDMOD_QDMOD_SHIFT)) & eTMR_QDMOD_QDMOD_MASK)
/* eTMR_FAULT Register */
#define eTMR_FAULT_FFCNT_WIDTH                              (4)
#define eTMR_FAULT_FFCNT_MASK                               (0xF0000000U)
#define eTMR_FAULT_FFCNT_SHIFT                              (28U)
#define eTMR_FAULT_FFCNT(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_FFCNT_SHIFT)) & eTMR_FAULT_FFCNT_MASK)
#define eTMR_FAULT_FFPER_WIDTH                              (4)
#define eTMR_FAULT_FFPER_MASK                               (0xF000000U)
#define eTMR_FAULT_FFPER_SHIFT                              (24U)
#define eTMR_FAULT_FFPER(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_FFPER_SHIFT)) & eTMR_FAULT_FFPER_MASK)
#define eTMR_FAULT_STRETCH_MASK                             (0x200000U)
#define eTMR_FAULT_STRETCH_SHIFT                            (21U)
#define eTMR_FAULT_STRETCH(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_STRETCH_SHIFT)) & eTMR_FAULT_STRETCH_MASK)
#define eTMR_FAULT_FCOMB_MASK                               (0x100000U)
#define eTMR_FAULT_FCOMB_SHIFT                              (20U)
#define eTMR_FAULT_FCOMB(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_FCOMB_SHIFT)) & eTMR_FAULT_FCOMB_MASK)
#define eTMR_FAULT_RCVRY_WIDTH                              (2)
#define eTMR_FAULT_RCVRY_MASK                               (0xC0000U)
#define eTMR_FAULT_RCVRY_SHIFT                              (18U)
#define eTMR_FAULT_RCVRY(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_RCVRY_SHIFT)) & eTMR_FAULT_RCVRY_MASK)
#define eTMR_FAULT_FAUTO_MASK                               (0x30000U)
#define eTMR_FAULT_FAUTO_SHIFT                              (16U)
#define eTMR_FAULT_FAUTO(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_FAUTO_SHIFT)) & eTMR_FAULT_FAUTO_MASK)
#define eTMR_FAULT_F3POL_MASK                               (0x800U)
#define eTMR_FAULT_F3POL_SHIFT                              (11U)
#define eTMR_FAULT_F3POL(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F3POL_SHIFT)) & eTMR_FAULT_F3POL_MASK)
#define eTMR_FAULT_F2POL_MASK                               (0x400U)
#define eTMR_FAULT_F2POL_SHIFT                              (10U)
#define eTMR_FAULT_F2POL(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F2POL_SHIFT)) & eTMR_FAULT_F2POL_MASK)
#define eTMR_FAULT_F1POL_MASK                               (0x200U)
#define eTMR_FAULT_F1POL_SHIFT                              (9U)
#define eTMR_FAULT_F1POL(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F1POL_SHIFT)) & eTMR_FAULT_F1POL_MASK)
#define eTMR_FAULT_F0POL_MASK                               (0x100U)
#define eTMR_FAULT_F0POL_SHIFT                              (8U)
#define eTMR_FAULT_F0POL(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F0POL_SHIFT)) & eTMR_FAULT_F0POL_MASK)
#define eTMR_FAULT_F3EN_MASK                                (0x8U)
#define eTMR_FAULT_F3EN_SHIFT                               (3U)
#define eTMR_FAULT_F3EN(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F3EN_SHIFT)) & eTMR_FAULT_F3EN_MASK)
#define eTMR_FAULT_F2EN_MASK                                (0x4U)
#define eTMR_FAULT_F2EN_SHIFT                               (2U)
#define eTMR_FAULT_F2EN(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F2EN_SHIFT)) & eTMR_FAULT_F2EN_MASK)
#define eTMR_FAULT_F1EN_MASK                                (0x2U)
#define eTMR_FAULT_F1EN_SHIFT                               (1U)
#define eTMR_FAULT_F1EN(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F1EN_SHIFT)) & eTMR_FAULT_F1EN_MASK)
#define eTMR_FAULT_F0EN_MASK                                (0x1U)
#define eTMR_FAULT_F0EN_SHIFT                               (0U)
#define eTMR_FAULT_F0EN(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_FAULT_F0EN_SHIFT)) & eTMR_FAULT_F0EN_MASK)
/* eTMR_CH_CTRL Register */
#define eTMR_CH_CTRL_DMAEN_MASK                                (0x40000000U)
#define eTMR_CH_CTRL_DMAEN_SHIFT                               (30U)
#define eTMR_CH_CTRL_DMAEN(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_DMAEN_SHIFT)) & eTMR_CH_CTRL_DMAEN_MASK)
#define eTMR_CH_CTRL_LDEN_MASK                                 (0x10000000U)
#define eTMR_CH_CTRL_LDEN_SHIFT                                (28U)
#define eTMR_CH_CTRL_LDEN(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_LDEN_SHIFT)) & eTMR_CH_CTRL_LDEN_MASK)
#define eTMR_CH_CTRL_CAPEDGE_WIDTH                             (2)
#define eTMR_CH_CTRL_CAPEDGE_MASK                              (0x3000000U)
#define eTMR_CH_CTRL_CAPEDGE_SHIFT                             (24U)
#define eTMR_CH_CTRL_CAPEDGE(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CAPEDGE_SHIFT)) & eTMR_CH_CTRL_CAPEDGE_MASK)
#define eTMR_CH_CTRL_CFCNT_WIDTH                               (4)
#define eTMR_CH_CTRL_CFCNT_MASK                                (0xF00000U)
#define eTMR_CH_CTRL_CFCNT_SHIFT                               (20U)
#define eTMR_CH_CTRL_CFCNT(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CFCNT_SHIFT)) & eTMR_CH_CTRL_CFCNT_MASK)
#define eTMR_CH_CTRL_CFPER_WIDTH                               (4)
#define eTMR_CH_CTRL_CFPER_MASK                                (0xF0000U)
#define eTMR_CH_CTRL_CFPER_SHIFT                               (16U)
#define eTMR_CH_CTRL_CFPER(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CFPER_SHIFT)) & eTMR_CH_CTRL_CFPER_MASK)
#define eTMR_CH_CTRL_VAL1CMP_WIDTH                             (2)
#define eTMR_CH_CTRL_VAL1CMP_MASK                              (0xC000U)
#define eTMR_CH_CTRL_VAL1CMP_SHIFT                             (14U)
#define eTMR_CH_CTRL_VAL1CMP(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_VAL1CMP_SHIFT)) & eTMR_CH_CTRL_VAL1CMP_MASK)
#define eTMR_CH_CTRL_VAL0CMP_WIDTH                             (2)
#define eTMR_CH_CTRL_VAL0CMP_MASK                              (0x3000U)
#define eTMR_CH_CTRL_VAL0CMP_SHIFT                             (12U)
#define eTMR_CH_CTRL_VAL0CMP(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_VAL0CMP_SHIFT)) & eTMR_CH_CTRL_VAL0CMP_MASK)
#define eTMR_CH_CTRL_PWMSRC_MASK                               (0x300U)
#define eTMR_CH_CTRL_PWMSRC_SHIFT                              (8U)
#define eTMR_CH_CTRL_PWMSRC(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_PWMSRC_SHIFT)) & eTMR_CH_CTRL_PWMSRC_MASK)
#define eTMR_CH_CTRL_VAL1TEN_MASK                              (0x80U)
#define eTMR_CH_CTRL_VAL1TEN_SHIFT                             (7U)
#define eTMR_CH_CTRL_VAL1TEN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_VAL1TEN_SHIFT)) & eTMR_CH_CTRL_VAL1TEN_MASK)
#define eTMR_CH_CTRL_VAL0TEN_MASK                              (0x40U)
#define eTMR_CH_CTRL_VAL0TEN_SHIFT                             (6U)
#define eTMR_CH_CTRL_VAL0TEN(x)                                (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_VAL0TEN_SHIFT)) & eTMR_CH_CTRL_VAL0TEN_MASK)
#define eTMR_CH_CTRL_CHPOL_MASK                                (0x20U)
#define eTMR_CH_CTRL_CHPOL_SHIFT                               (5U)
#define eTMR_CH_CTRL_CHPOL(x)                                  (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CHPOL_SHIFT)) & eTMR_CH_CTRL_CHPOL_MASK)
#define eTMR_CH_CTRL_CHINIT_MASK                               (0x10U)
#define eTMR_CH_CTRL_CHINIT_SHIFT                              (4U)
#define eTMR_CH_CTRL_CHINIT(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CHINIT_SHIFT)) & eTMR_CH_CTRL_CHINIT_MASK)
#define eTMR_CH_CTRL_CHMODE_WIDTH                              (2)
#define eTMR_CH_CTRL_CHMODE_MASK                               (0x3U)
#define eTMR_CH_CTRL_CHMODE_SHIFT                              (0U)
#define eTMR_CH_CTRL_CHMODE(x)                                 (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CTRL_CHMODE_SHIFT)) & eTMR_CH_CTRL_CHMODE_MASK)
/* eTMR_CH_VAL0 Register */
#define eTMR_CH_VAL0_VAL0_MASK                                 (0xFFFFFFFFU)
#define eTMR_CH_VAL0_VAL0_SHIFT                                (0U)
#define eTMR_CH_VAL0_VAL0(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_CH_VAL0_VAL0_SHIFT)) & eTMR_CH_VAL0_VAL0_MASK)
/* eTMR_CH_VAL1 Register */
#define eTMR_CH_VAL1_VAL1_MASK                                 (0xFFFFFFFFU)
#define eTMR_CH_VAL1_VAL1_SHIFT                                (0U)
#define eTMR_CH_VAL1_VAL1(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_CH_VAL1_VAL1_SHIFT)) & eTMR_CH_VAL1_VAL1_MASK)
/* eTMR_CH_DITHVAL1 Register */
#define eTMR_CH_DITHVAL1_VAL1INT_MASK                          (0x7F00U)
#define eTMR_CH_DITHVAL1_VAL1INT_SHIFT                         (8U)
#define eTMR_CH_DITHVAL1_VAL1INT(x)                            (((uint32_t)(((uint32_t)(x)) << eTMR_CH_DITHVAL1_VAL1INT_SHIFT)) & eTMR_CH_DITHVAL1_VAL1INT_MASK)
#define eTMR_CH_DITHVAL1_VAL1FRAC_MASK                         (0x1FU)
#define eTMR_CH_DITHVAL1_VAL1FRAC_SHIFT                        (0U)
#define eTMR_CH_DITHVAL1_VAL1FRAC(x)                           (((uint32_t)(((uint32_t)(x)) << eTMR_CH_DITHVAL1_VAL1FRAC_SHIFT)) & eTMR_CH_DITHVAL1_VAL1FRAC_MASK)
/* eTMR_CH_DT Register */
#define eTMR_CH_DT_DTVAL_MASK                                  (0xFFFFU)
#define eTMR_CH_DT_DTVAL_SHIFT                                 (0U)
#define eTMR_CH_DT_DTVAL(x)                                    (((uint32_t)(((uint32_t)(x)) << eTMR_CH_DT_DTVAL_SHIFT)) & eTMR_CH_DT_DTVAL_MASK)
/* eTMR_CH_CVAL Register */
#define eTMR_CH_CVAL_CVAL_MASK                                 (0xFFFFFFFFU)
#define eTMR_CH_CVAL_CVAL_SHIFT                                (0U)
#define eTMR_CH_CVAL_CVAL(x)                                   (((uint32_t)(((uint32_t)(x)) << eTMR_CH_CVAL_CVAL_SHIFT)) & eTMR_CH_CVAL_CVAL_MASK)
/* eTMR_CH_PPCNTN Register */
#define eTMR_CH_PPCNTN_PPCNTN_MASK                             (0xFFU)
#define eTMR_CH_PPCNTN_PPCNTN_SHIFT                            (0U)
#define eTMR_CH_PPCNTN_PPCNTN(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_CH_PPCNTN_PPCNTN_SHIFT)) & eTMR_CH_PPCNTN_PPCNTN_MASK)
/* eTMR_CH_PPCNTV Register */
#define eTMR_CH_PPCNTV_PPCNTV_MASK                             (0xFFFFFFFFU)
#define eTMR_CH_PPCNTV_PPCNTV_SHIFT                            (0U)
#define eTMR_CH_PPCNTV_PPCNTV(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_CH_PPCNTV_PPCNTV_SHIFT)) & eTMR_CH_PPCNTV_PPCNTV_MASK)
/* eTMR_CH_NPCNTN Register */
#define eTMR_CH_NPCNTN_NPCNTN_MASK                             (0xFFU)
#define eTMR_CH_NPCNTN_NPCNTN_SHIFT                            (0U)
#define eTMR_CH_NPCNTN_NPCNTN(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_CH_NPCNTN_NPCNTN_SHIFT)) & eTMR_CH_NPCNTN_NPCNTN_MASK)
/* eTMR_CH_NPCNTV Register */
#define eTMR_CH_NPCNTV_NPCNTV_MASK                             (0xFFFFFFFFU)
#define eTMR_CH_NPCNTV_NPCNTV_SHIFT                            (0U)
#define eTMR_CH_NPCNTV_NPCNTV(x)                               (((uint32_t)(((uint32_t)(x)) << eTMR_CH_NPCNTV_NPCNTV_SHIFT)) & eTMR_CH_NPCNTV_NPCNTV_MASK)



/*!
 * @}
 */ /* end of group eTMR_Register_Masks */


/*!
 * @}
 */ /* end of group eTMR_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */


/** RTC - Size of Registers Arrays */

/* RTC Register Layout Typedef */
typedef struct {
    __IO uint32_t SEC;                                /**< Second Register, offset: 0x0000 */
    __IO uint32_t RESERVED_1;                         /**< RESERVED_1, offset: 0x0004 */
    __IO uint32_t CMP;                                /**< Compensation Register, offset: 0x0008 */
    __IO uint32_t ALM;                                /**< Alarm Register, offset: 0x000C */
    __IO uint32_t EN;                                 /**< Enable Register, offset: 0x0010 */
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0014 */
    __IO uint32_t INTF;                               /**< Interrupt Flag Register, offset: 0x0018 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x001C */

} RTC_Type, *RTC_MemMapPtr;

/** Number of instances of the RTC module. */
#define RTC_INSTANCE_COUNT                             (1u)

/* RTC0  base address */
#define RTC0_BASE                                          (0x40060000)
#define RTC0                                               ((RTC_Type *)(RTC0_BASE))

/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                                     { RTC0_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                                      { RTC0 }
/** Number of interrupt vector arrays for the RTC module. */
#define RTC_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the RTC. */
#define RTC_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                  { RTC_IRQn }
/** Number of interrupt channels for the  type of RTC. */
#define RTC_SECONDS_IRQS_CH_COUNT                 (1u)
#define RTC_SECONDS_IRQS                          { RTC_Seconds_IRQn }

/* RTC Register Mask */
/* RTC_SEC Register */
#define RTC_SEC_SEC_MASK                                   (0xFFFFFFFFU)
#define RTC_SEC_SEC_SHIFT                                  (0U)
#define RTC_SEC_SEC(x)                                     (((uint32_t)(((uint32_t)(x)) << RTC_SEC_SEC_SHIFT)) & RTC_SEC_SEC_MASK)
/* RTC_CMP Register */
#define RTC_CMP_CMPIVS_MASK                                (0xFF000000U)
#define RTC_CMP_CMPIVS_SHIFT                               (24U)
#define RTC_CMP_CMPIVS(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_CMP_CMPIVS_SHIFT)) & RTC_CMP_CMPIVS_MASK)
#define RTC_CMP_CMPVS_MASK                                 (0xFF0000U)
#define RTC_CMP_CMPVS_SHIFT                                (16U)
#define RTC_CMP_CMPVS(x)                                   (((uint32_t)(((uint32_t)(x)) << RTC_CMP_CMPVS_SHIFT)) & RTC_CMP_CMPVS_MASK)
#define RTC_CMP_CMPIV_MASK                                 (0xFF00U)
#define RTC_CMP_CMPIV_SHIFT                                (8U)
#define RTC_CMP_CMPIV(x)                                   (((uint32_t)(((uint32_t)(x)) << RTC_CMP_CMPIV_SHIFT)) & RTC_CMP_CMPIV_MASK)
#define RTC_CMP_CMPV_MASK                                  (0xFFU)
#define RTC_CMP_CMPV_SHIFT                                 (0U)
#define RTC_CMP_CMPV(x)                                    (((uint32_t)(((uint32_t)(x)) << RTC_CMP_CMPV_SHIFT)) & RTC_CMP_CMPV_MASK)
/* RTC_ALM Register */
#define RTC_ALM_ALM_MASK                                   (0xFFFFFFFFU)
#define RTC_ALM_ALM_SHIFT                                  (0U)
#define RTC_ALM_ALM(x)                                     (((uint32_t)(((uint32_t)(x)) << RTC_ALM_ALM_SHIFT)) & RTC_ALM_ALM_MASK)
/* RTC_EN Register */
#define RTC_EN_EN_MASK                                     (0x1U)
#define RTC_EN_EN_SHIFT                                    (0U)
#define RTC_EN_EN(x)                                       (((uint32_t)(((uint32_t)(x)) << RTC_EN_EN_SHIFT)) & RTC_EN_EN_MASK)
/* RTC_CTRL Register */
#define RTC_CTRL_DBGDIS_MASK                               (0x20U)
#define RTC_CTRL_DBGDIS_SHIFT                              (5U)
#define RTC_CTRL_DBGDIS(x)                                 (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_DBGDIS_SHIFT)) & RTC_CTRL_DBGDIS_MASK)
#define RTC_CTRL_UNLOCK_MASK                               (0x10U)
#define RTC_CTRL_UNLOCK_SHIFT                              (4U)
#define RTC_CTRL_UNLOCK(x)                                 (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_UNLOCK_SHIFT)) & RTC_CTRL_UNLOCK_MASK)
#define RTC_CTRL_CLKOUTEN_MASK                             (0x8U)
#define RTC_CTRL_CLKOUTEN_SHIFT                            (3U)
#define RTC_CTRL_CLKOUTEN(x)                               (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_CLKOUTEN_SHIFT)) & RTC_CTRL_CLKOUTEN_MASK)
#define RTC_CTRL_CLKOUTSEL_MASK                            (0x4U)
#define RTC_CTRL_CLKOUTSEL_SHIFT                           (2U)
#define RTC_CTRL_CLKOUTSEL(x)                              (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_CLKOUTSEL_SHIFT)) & RTC_CTRL_CLKOUTSEL_MASK)
#define RTC_CTRL_CLKSEL_MASK                               (0x2U)
#define RTC_CTRL_CLKSEL_SHIFT                              (1U)
#define RTC_CTRL_CLKSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_CLKSEL_SHIFT)) & RTC_CTRL_CLKSEL_MASK)
#define RTC_CTRL_SWRST_MASK                                (0x1U)
#define RTC_CTRL_SWRST_SHIFT                               (0U)
#define RTC_CTRL_SWRST(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_SWRST_SHIFT)) & RTC_CTRL_SWRST_MASK)
/* RTC_INTF Register */
#define RTC_INTF_SECIF_MASK                                (0x4U)
#define RTC_INTF_SECIF_SHIFT                               (2U)
#define RTC_INTF_SECIF(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTF_SECIF_SHIFT)) & RTC_INTF_SECIF_MASK)
#define RTC_INTF_ALMIF_MASK                                (0x2U)
#define RTC_INTF_ALMIF_SHIFT                               (1U)
#define RTC_INTF_ALMIF(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTF_ALMIF_SHIFT)) & RTC_INTF_ALMIF_MASK)
#define RTC_INTF_OVFIF_MASK                                (0x1U)
#define RTC_INTF_OVFIF_SHIFT                               (0U)
#define RTC_INTF_OVFIF(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTF_OVFIF_SHIFT)) & RTC_INTF_OVFIF_MASK)
/* RTC_INTE Register */
#define RTC_INTE_SECOCS_MASK                               (0x700U)
#define RTC_INTE_SECOCS_SHIFT                              (8U)
#define RTC_INTE_SECOCS(x)                                 (((uint32_t)(((uint32_t)(x)) << RTC_INTE_SECOCS_SHIFT)) & RTC_INTE_SECOCS_MASK)
#define RTC_INTE_SECIE_MASK                                (0x4U)
#define RTC_INTE_SECIE_SHIFT                               (2U)
#define RTC_INTE_SECIE(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTE_SECIE_SHIFT)) & RTC_INTE_SECIE_MASK)
#define RTC_INTE_ALMIE_MASK                                (0x2U)
#define RTC_INTE_ALMIE_SHIFT                               (1U)
#define RTC_INTE_ALMIE(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTE_ALMIE_SHIFT)) & RTC_INTE_ALMIE_MASK)
#define RTC_INTE_OVFIE_MASK                                (0x1U)
#define RTC_INTE_OVFIE_SHIFT                               (0U)
#define RTC_INTE_OVFIE(x)                                  (((uint32_t)(((uint32_t)(x)) << RTC_INTE_OVFIE_SHIFT)) & RTC_INTE_OVFIE_MASK)


/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- PTU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup PTU_Peripheral_Access_Layer PTU Peripheral Access Layer
 * @{
 */


/** PTU - Size of Registers Arrays */
#define PTU_CHDLYn_COUNT                     (8)

/* PTU Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t PRS;                                /**< Prescaler Select Register, offset: 0x0004 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x0008 */
    __IO uint32_t STS;                                /**< Interrupt Flag Register, offset: 0x000C */
    __IO uint32_t MOD;                                /**< Modulus Register, offset: 0x0010 */
    __IO uint32_t CNT;                                /**< Counter Current Value Register, offset: 0x0014 */
    __IO uint32_t INTDLY;                             /**< Interrupt Delay Register, offset: 0x0018 */
    __IO uint32_t RESERVED0;                          /**< RESERVED0, offset: 0x001C */
    __IO uint32_t CHCTRL;                             /**< Channel Control Register, offset: 0x0020 */
    __IO uint32_t CHSTS;                              /**< Channel Status Register, offset: 0x0024 */
    __IO uint32_t CHDLYn[ 8];                         /**< Channel Delay n Register, offset: 0x0028 */
    __IO uint32_t RESERVED1[82];                      /**< RESERVED1, offset: 0x0048 */
    __IO uint32_t POEN;                               /**< Pulse-Out Enable Register, offset: 0x0190 */
    struct {
        __IO uint16_t PODLY0;                         /**< PTU Pulse-Out Delay 0, offset: 0x0194 */
        __IO uint16_t PODLY1;                         /**< PTU Pulse-Out Delay 1, offset: 0x0196 */
    } PODLY;

} PTU_Type, *PTU_MemMapPtr;

/** Number of instances of the PTU module. */
#define PTU_INSTANCE_COUNT                             (2u)

/* PTU0  base address */
#define PTU0_BASE                                          (0x40046000)
#define PTU0                                               ((PTU_Type *)(PTU0_BASE))
/* PTU1  base address */
#define PTU1_BASE                                          (0x40047000)
#define PTU1                                               ((PTU_Type *)(PTU1_BASE))

/** Array initializer of PTU peripheral base addresses */
#define PTU_BASE_ADDRS                                     { PTU0_BASE,  PTU1_BASE }
/** Array initializer of PTU peripheral base pointers */
#define PTU_BASE_PTRS                                      { PTU0,  PTU1 }
/** Number of interrupt vector arrays for the PTU module. */
#define PTU_IRQS_ARR_COUNT                                 (u)
/** Number of interrupt channels for the PTU. */
#define PTU_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the PTU peripheral type */
#define PTU_IRQS                                  { PTU0_IRQn, PTU1_IRQn }

/* PTU Register Mask */
/* PTU_CTRL Register */
#define PTU_CTRL_SWTRIG_MASK                               (0x80U)
#define PTU_CTRL_SWTRIG_SHIFT                              (7U)
#define PTU_CTRL_SWTRIG(x)                                 (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_SWTRIG_SHIFT)) & PTU_CTRL_SWTRIG_MASK)
#define PTU_CTRL_DMAEN_MASK                                (0x40U)
#define PTU_CTRL_DMAEN_SHIFT                               (6U)
#define PTU_CTRL_DMAEN(x)                                  (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_DMAEN_SHIFT)) & PTU_CTRL_DMAEN_MASK)
#define PTU_CTRL_TRIGSEL_MASK                              (0x20U)
#define PTU_CTRL_TRIGSEL_SHIFT                             (5U)
#define PTU_CTRL_TRIGSEL(x)                                (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_TRIGSEL_SHIFT)) & PTU_CTRL_TRIGSEL_MASK)
#define PTU_CTRL_CONT_MASK                                 (0x10U)
#define PTU_CTRL_CONT_SHIFT                                (4U)
#define PTU_CTRL_CONT(x)                                   (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_CONT_SHIFT)) & PTU_CTRL_CONT_MASK)
#define PTU_CTRL_LDMD_MASK                                 (0xCU)
#define PTU_CTRL_LDMD_SHIFT                                (2U)
#define PTU_CTRL_LDMD(x)                                   (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_LDMD_SHIFT)) & PTU_CTRL_LDMD_MASK)
#define PTU_CTRL_LDOK_MASK                                 (0x2U)
#define PTU_CTRL_LDOK_SHIFT                                (1U)
#define PTU_CTRL_LDOK(x)                                   (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_LDOK_SHIFT)) & PTU_CTRL_LDOK_MASK)
#define PTU_CTRL_EN_MASK                                   (0x1U)
#define PTU_CTRL_EN_SHIFT                                  (0U)
#define PTU_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << PTU_CTRL_EN_SHIFT)) & PTU_CTRL_EN_MASK)
/* PTU_PRS Register */
#define PTU_PRS_DIV_MASK                                   (0x1CU)
#define PTU_PRS_DIV_SHIFT                                  (2U)
#define PTU_PRS_DIV(x)                                     (((uint32_t)(((uint32_t)(x)) << PTU_PRS_DIV_SHIFT)) & PTU_PRS_DIV_MASK)
#define PTU_PRS_MULT_MASK                                  (0x3U)
#define PTU_PRS_MULT_SHIFT                                 (0U)
#define PTU_PRS_MULT(x)                                    (((uint32_t)(((uint32_t)(x)) << PTU_PRS_MULT_SHIFT)) & PTU_PRS_MULT_MASK)
/* PTU_INTE Register */
#define PTU_INTE_IE_MASK                                   (0x1U)
#define PTU_INTE_IE_SHIFT                                  (0U)
#define PTU_INTE_IE(x)                                     (((uint32_t)(((uint32_t)(x)) << PTU_INTE_IE_SHIFT)) & PTU_INTE_IE_MASK)
/* PTU_STS Register */
#define PTU_STS_IF_MASK                                    (0x1U)
#define PTU_STS_IF_SHIFT                                   (0U)
#define PTU_STS_IF(x)                                      (((uint32_t)(((uint32_t)(x)) << PTU_STS_IF_SHIFT)) & PTU_STS_IF_MASK)
/* PTU_MOD Register */
#define PTU_MOD_MOD_MASK                                   (0xFFFFU)
#define PTU_MOD_MOD_SHIFT                                  (0U)
#define PTU_MOD_MOD(x)                                     (((uint32_t)(((uint32_t)(x)) << PTU_MOD_MOD_SHIFT)) & PTU_MOD_MOD_MASK)
/* PTU_CNT Register */
#define PTU_CNT_CNT_MASK                                   (0xFFFFU)
#define PTU_CNT_CNT_SHIFT                                  (0U)
#define PTU_CNT_CNT(x)                                     (((uint32_t)(((uint32_t)(x)) << PTU_CNT_CNT_SHIFT)) & PTU_CNT_CNT_MASK)
/* PTU_INTDLY Register */
#define PTU_INTDLY_INTDLY_MASK                             (0xFFFFU)
#define PTU_INTDLY_INTDLY_SHIFT                            (0U)
#define PTU_INTDLY_INTDLY(x)                               (((uint32_t)(((uint32_t)(x)) << PTU_INTDLY_INTDLY_SHIFT)) & PTU_INTDLY_INTDLY_MASK)
/* PTU_CHCTRL Register */
#define PTU_CHCTRL_CHDLYEN_MASK                            (0xFF00U)
#define PTU_CHCTRL_CHDLYEN_SHIFT                           (8U)
#define PTU_CHCTRL_CHDLYEN(x)                              (((uint32_t)(((uint32_t)(x)) << PTU_CHCTRL_CHDLYEN_SHIFT)) & PTU_CHCTRL_CHDLYEN_MASK)
#define PTU_CHCTRL_CHEN_MASK                               (0xFFU)
#define PTU_CHCTRL_CHEN_SHIFT                              (0U)
#define PTU_CHCTRL_CHEN(x)                                 (((uint32_t)(((uint32_t)(x)) << PTU_CHCTRL_CHEN_SHIFT)) & PTU_CHCTRL_CHEN_MASK)
/* PTU_CHSTS Register */
#define PTU_CHSTS_CHF_MASK                                 (0xFF0000U)
#define PTU_CHSTS_CHF_SHIFT                                (16U)
#define PTU_CHSTS_CHF(x)                                   (((uint32_t)(((uint32_t)(x)) << PTU_CHSTS_CHF_SHIFT)) & PTU_CHSTS_CHF_MASK)
/* PTU_CHDLYn Register */
#define PTU_CHDLYn_CHDLYn_MASK                             (0xFFFFU)
#define PTU_CHDLYn_CHDLYn_SHIFT                            (0U)
#define PTU_CHDLYn_CHDLYn(x)                               (((uint32_t)(((uint32_t)(x)) << PTU_CHDLYn_CHDLYn_SHIFT)) & PTU_CHDLYn_CHDLYn_MASK)
/* PTU_POEN Register */
#define PTU_POEN_POEN_MASK                                 (0x1U)
#define PTU_POEN_POEN_SHIFT                                (0U)
#define PTU_POEN_POEN(x)                                   (((uint32_t)(((uint32_t)(x)) << PTU_POEN_POEN_SHIFT)) & PTU_POEN_POEN_MASK)
/* PTU_PODLY Register */
#define PTU_PODLY_PODLY1_MASK                              (0xFFFF0000U)
#define PTU_PODLY_PODLY1_SHIFT                             (16U)
#define PTU_PODLY_PODLY1(x)                                (((uint32_t)(((uint32_t)(x)) << PTU_PODLY_PODLY1_SHIFT)) & PTU_PODLY_PODLY1_MASK)
#define PTU_PODLY_PODLY0_MASK                              (0xFFFFU)
#define PTU_PODLY_PODLY0_SHIFT                             (0U)
#define PTU_PODLY_PODLY0(x)                                (((uint32_t)(((uint32_t)(x)) << PTU_PODLY_PODLY0_SHIFT)) & PTU_PODLY_PODLY0_MASK)


/*!
 * @}
 */ /* end of group PTU_Register_Masks */


/*!
 * @}
 */ /* end of group PTU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */


/** ADC - Size of Registers Arrays */
#define ADC_CHSEL_COUNT                     (8)

/* ADC Register Layout Typedef */
typedef struct {
    __IO uint32_t STS;                                /**< Status Register, offset: 0x0000 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x0004 */
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0008 */
    __IO uint32_t CFG0;                               /**< Configuration 0 Register, offset: 0x000C */
    __IO uint32_t CFG1;                               /**< Configuration 1 Register, offset: 0x0010 */
    __IO uint32_t SMP;                                /**< Sampling Register, offset: 0x0014 */
    __IO uint32_t WDCTRL;                             /**< Watchdog Control Register, offset: 0x0018 */
    __IO uint32_t WDTH;                               /**< Watchdog Threshold Register, offset: 0x001C */
    __IO uint32_t RESERVED0[ 3];                      /**< RESERVED0, offset: 0x0020 */
    __IO uint8_t CHSEL[ 8];                          /**< Channel Configure 0 Register, offset: 0x002C */
    __IO uint32_t RESERVED1[ 6];                      /**< RESERVED1, offset: 0x0034 */
    __IO uint32_t FIFO;                               /**< FIFO Access Register, offset: 0x004C */
    __IO uint32_t RESERVED_12;                        /**< RESERVED_12, offset: 0x0050 */

} ADC_Type, *ADC_MemMapPtr;

/** Number of instances of the ADC module. */
#define ADC_INSTANCE_COUNT                             (2u)

/* ADC0  base address */
#define ADC0_BASE                                          (0x40040000)
#define ADC0                                               ((ADC_Type *)(ADC0_BASE))
/* ADC1  base address */
#define ADC1_BASE                                          (0x40041000)
#define ADC1                                               ((ADC_Type *)(ADC1_BASE))

/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                                     { ADC0_BASE,  ADC1_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                                      { ADC0,  ADC1 }
/** Number of interrupt vector arrays for the ADC module. */
#define ADC_IRQS_ARR_COUNT                                 (u)
/** Number of interrupt channels for the ADC. */
#define ADC_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                  { ADC0_IRQn, ADC1_IRQn }

/* ADC Register Mask */
/* ADC_STS Register */
#define ADC_STS_WD_MASK                                    (0x80U)
#define ADC_STS_WD_SHIFT                                   (7U)
#define ADC_STS_WD(x)                                      (((uint32_t)(((uint32_t)(x)) << ADC_STS_WD_SHIFT)) & ADC_STS_WD_MASK)
#define ADC_STS_EMPTY_MASK                                 (0x40U)
#define ADC_STS_EMPTY_SHIFT                                (6U)
#define ADC_STS_EMPTY(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_STS_EMPTY_SHIFT)) & ADC_STS_EMPTY_MASK)
#define ADC_STS_FULL_MASK                                  (0x20U)
#define ADC_STS_FULL_SHIFT                                 (5U)
#define ADC_STS_FULL(x)                                    (((uint32_t)(((uint32_t)(x)) << ADC_STS_FULL_SHIFT)) & ADC_STS_FULL_MASK)
#define ADC_STS_OVR_MASK                                   (0x10U)
#define ADC_STS_OVR_SHIFT                                  (4U)
#define ADC_STS_OVR(x)                                     (((uint32_t)(((uint32_t)(x)) << ADC_STS_OVR_SHIFT)) & ADC_STS_OVR_MASK)
#define ADC_STS_EOSEQ_MASK                                 (0x8U)
#define ADC_STS_EOSEQ_SHIFT                                (3U)
#define ADC_STS_EOSEQ(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_STS_EOSEQ_SHIFT)) & ADC_STS_EOSEQ_MASK)
#define ADC_STS_EOC_MASK                                   (0x4U)
#define ADC_STS_EOC_SHIFT                                  (2U)
#define ADC_STS_EOC(x)                                     (((uint32_t)(((uint32_t)(x)) << ADC_STS_EOC_SHIFT)) & ADC_STS_EOC_MASK)
#define ADC_STS_EOSMP_MASK                                 (0x2U)
#define ADC_STS_EOSMP_SHIFT                                (1U)
#define ADC_STS_EOSMP(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_STS_EOSMP_SHIFT)) & ADC_STS_EOSMP_MASK)
#define ADC_STS_ADRDY_MASK                                 (0x1U)
#define ADC_STS_ADRDY_SHIFT                                (0U)
#define ADC_STS_ADRDY(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_STS_ADRDY_SHIFT)) & ADC_STS_ADRDY_MASK)
/* ADC_INTE Register */
#define ADC_INTE_WDIE_MASK                                 (0x80U)
#define ADC_INTE_WDIE_SHIFT                                (7U)
#define ADC_INTE_WDIE(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_INTE_WDIE_SHIFT)) & ADC_INTE_WDIE_MASK)
#define ADC_INTE_OVRIE_MASK                                (0x10U)
#define ADC_INTE_OVRIE_SHIFT                               (4U)
#define ADC_INTE_OVRIE(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_INTE_OVRIE_SHIFT)) & ADC_INTE_OVRIE_MASK)
#define ADC_INTE_EOSEQIE_MASK                              (0x8U)
#define ADC_INTE_EOSEQIE_SHIFT                             (3U)
#define ADC_INTE_EOSEQIE(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_INTE_EOSEQIE_SHIFT)) & ADC_INTE_EOSEQIE_MASK)
#define ADC_INTE_EOCIE_MASK                                (0x4U)
#define ADC_INTE_EOCIE_SHIFT                               (2U)
#define ADC_INTE_EOCIE(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_INTE_EOCIE_SHIFT)) & ADC_INTE_EOCIE_MASK)
#define ADC_INTE_EOSMPIE_MASK                              (0x2U)
#define ADC_INTE_EOSMPIE_SHIFT                             (1U)
#define ADC_INTE_EOSMPIE(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_INTE_EOSMPIE_SHIFT)) & ADC_INTE_EOSMPIE_MASK)
#define ADC_INTE_ADRDYIE_MASK                              (0x1U)
#define ADC_INTE_ADRDYIE_SHIFT                             (0U)
#define ADC_INTE_ADRDYIE(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_INTE_ADRDYIE_SHIFT)) & ADC_INTE_ADRDYIE_MASK)
/* ADC_CTRL Register */
#define ADC_CTRL_TSEN_MASK                                 (0x10U)
#define ADC_CTRL_TSEN_SHIFT                                (4U)
#define ADC_CTRL_TSEN(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_TSEN_SHIFT)) & ADC_CTRL_TSEN_MASK)
#define ADC_CTRL_ADSTOP_MASK                               (0x8U)
#define ADC_CTRL_ADSTOP_SHIFT                              (3U)
#define ADC_CTRL_ADSTOP(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ADSTOP_SHIFT)) & ADC_CTRL_ADSTOP_MASK)
#define ADC_CTRL_ADSTART_MASK                              (0x4U)
#define ADC_CTRL_ADSTART_SHIFT                             (2U)
#define ADC_CTRL_ADSTART(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ADSTART_SHIFT)) & ADC_CTRL_ADSTART_MASK)
#define ADC_CTRL_ADDIS_MASK                                (0x2U)
#define ADC_CTRL_ADDIS_SHIFT                               (1U)
#define ADC_CTRL_ADDIS(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ADDIS_SHIFT)) & ADC_CTRL_ADDIS_MASK)
#define ADC_CTRL_ADEN_MASK                                 (0x1U)
#define ADC_CTRL_ADEN_SHIFT                                (0U)
#define ADC_CTRL_ADEN(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ADEN_SHIFT)) & ADC_CTRL_ADEN_MASK)
/* ADC_CFG0 Register */
#define ADC_CFG0_OVRMD_MASK                                (0x40000000U)
#define ADC_CFG0_OVRMD_SHIFT                               (30U)
#define ADC_CFG0_OVRMD(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_OVRMD_SHIFT)) & ADC_CFG0_OVRMD_MASK)
#define ADC_CFG0_SEQLEN_MASK                               (0x7000000U)
#define ADC_CFG0_SEQLEN_SHIFT                              (24U)
#define ADC_CFG0_SEQLEN(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_SEQLEN_SHIFT)) & ADC_CFG0_SEQLEN_MASK)
#define ADC_CFG0_DISCEN_MASK                               (0x800000U)
#define ADC_CFG0_DISCEN_SHIFT                              (23U)
#define ADC_CFG0_DISCEN(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_DISCEN_SHIFT)) & ADC_CFG0_DISCEN_MASK)
#define ADC_CFG0_AUTOOFF_MASK                              (0x400000U)
#define ADC_CFG0_AUTOOFF_SHIFT                             (22U)
#define ADC_CFG0_AUTOOFF(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_AUTOOFF_SHIFT)) & ADC_CFG0_AUTOOFF_MASK)
#define ADC_CFG0_WAIT_MASK                                 (0x200000U)
#define ADC_CFG0_WAIT_SHIFT                                (21U)
#define ADC_CFG0_WAIT(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_WAIT_SHIFT)) & ADC_CFG0_WAIT_MASK)
#define ADC_CFG0_CONT_MASK                                 (0x100000U)
#define ADC_CFG0_CONT_SHIFT                                (20U)
#define ADC_CFG0_CONT(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_CONT_SHIFT)) & ADC_CFG0_CONT_MASK)
#define ADC_CFG0_TRIGMD_MASK                               (0x800U)
#define ADC_CFG0_TRIGMD_SHIFT                              (11U)
#define ADC_CFG0_TRIGMD(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_TRIGMD_SHIFT)) & ADC_CFG0_TRIGMD_MASK)
#define ADC_CFG0_RES_MASK                                  (0x300U)
#define ADC_CFG0_RES_SHIFT                                 (8U)
#define ADC_CFG0_RES(x)                                    (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_RES_SHIFT)) & ADC_CFG0_RES_MASK)
#define ADC_CFG0_WM_MASK                                   (0xF0U)
#define ADC_CFG0_WM_SHIFT                                  (4U)
#define ADC_CFG0_WM(x)                                     (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_WM_SHIFT)) & ADC_CFG0_WM_MASK)
#define ADC_CFG0_DMAEN_MASK                                (0x1U)
#define ADC_CFG0_DMAEN_SHIFT                               (0U)
#define ADC_CFG0_DMAEN(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_CFG0_DMAEN_SHIFT)) & ADC_CFG0_DMAEN_MASK)
/* ADC_CFG1 Register */
#define ADC_CFG1_PRS_MASK                                  (0xF00U)
#define ADC_CFG1_PRS_SHIFT                                 (8U)
#define ADC_CFG1_PRS(x)                                    (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_PRS_SHIFT)) & ADC_CFG1_PRS_MASK)
#define ADC_CFG1_STCNT_MASK                                (0xFFU)
#define ADC_CFG1_STCNT_SHIFT                               (0U)
#define ADC_CFG1_STCNT(x)                                  (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_STCNT_SHIFT)) & ADC_CFG1_STCNT_MASK)
/* ADC_SMP Register */
#define ADC_SMP_SMP_MASK                                   (0xFFU)
#define ADC_SMP_SMP_SHIFT                                  (0U)
#define ADC_SMP_SMP(x)                                     (((uint32_t)(((uint32_t)(x)) << ADC_SMP_SMP_SHIFT)) & ADC_SMP_SMP_MASK)
/* ADC_WDCTRL Register */
#define ADC_WDCTRL_WDEN_MASK                               (0x80U)
#define ADC_WDCTRL_WDEN_SHIFT                              (7U)
#define ADC_WDCTRL_WDEN(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_WDCTRL_WDEN_SHIFT)) & ADC_WDCTRL_WDEN_MASK)
#define ADC_WDCTRL_WDSGL_MASK                              (0x40U)
#define ADC_WDCTRL_WDSGL_SHIFT                             (6U)
#define ADC_WDCTRL_WDSGL(x)                                (((uint32_t)(((uint32_t)(x)) << ADC_WDCTRL_WDSGL_SHIFT)) & ADC_WDCTRL_WDSGL_MASK)
#define ADC_WDCTRL_WDCHSEL_MASK                            (0x1FU)
#define ADC_WDCTRL_WDCHSEL_SHIFT                           (0U)
#define ADC_WDCTRL_WDCHSEL(x)                              (((uint32_t)(((uint32_t)(x)) << ADC_WDCTRL_WDCHSEL_SHIFT)) & ADC_WDCTRL_WDCHSEL_MASK)
/* ADC_WDTH Register */
#define ADC_WDTH_THMD_MASK                                 (0x80000000U)
#define ADC_WDTH_THMD_SHIFT                                (31U)
#define ADC_WDTH_THMD(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_WDTH_THMD_SHIFT)) & ADC_WDTH_THMD_MASK)
#define ADC_WDTH_HIGH_MASK                                 (0xFFF0000U)
#define ADC_WDTH_HIGH_SHIFT                                (16U)
#define ADC_WDTH_HIGH(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_WDTH_HIGH_SHIFT)) & ADC_WDTH_HIGH_MASK)
#define ADC_WDTH_LOW_MASK                                  (0xFFFU)
#define ADC_WDTH_LOW_SHIFT                                 (0U)
#define ADC_WDTH_LOW(x)                                    (((uint32_t)(((uint32_t)(x)) << ADC_WDTH_LOW_SHIFT)) & ADC_WDTH_LOW_MASK)
/* ADC_CHSEL Register */
#define ADC_CHSEL_CHSEL_MASK                               (0x1FU)
#define ADC_CHSEL_CHSEL_SHIFT                              (0U)
#define ADC_CHSEL_CHSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << ADC_CHSEL_CHSEL_SHIFT)) & ADC_CHSEL_CHSEL_MASK)
/* ADC_FIFO Register */
#define ADC_FIFO_CHID_MASK                                 (0x1F0000U)
#define ADC_FIFO_CHID_SHIFT                                (16U)
#define ADC_FIFO_CHID(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_FIFO_CHID_SHIFT)) & ADC_FIFO_CHID_MASK)
#define ADC_FIFO_DATA_MASK                                 (0xFFFFU)
#define ADC_FIFO_DATA_SHIFT                                (0U)
#define ADC_FIFO_DATA(x)                                   (((uint32_t)(((uint32_t)(x)) << ADC_FIFO_DATA_SHIFT)) & ADC_FIFO_DATA_MASK)


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- ACMP Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Peripheral_Access_Layer ACMP Peripheral Access Layer
 * @{
 */


/** ACMP - Size of Registers Arrays */

/* ACMP Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t DAC;                                /**< DAC Register, offset: 0x0004 */
    __IO uint32_t MUX;                                /**< Channels Multiplexer, offset: 0x0008 */
    __IO uint32_t FILT;                               /**< Filter Register, offset: 0x000C */
    __IO uint32_t DMACR;                              /**< DMA Control Register, offset: 0x0010 */
    __IO uint32_t RESERVED_5;                         /**< RESERVED_5, offset: 0x0014 */
    __IO uint32_t STS;                                /**< Status Register, offset: 0x0018 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x001C */
    __IO uint32_t CONT;                               /**< Continuous Mode Register, offset: 0x0020 */

} ACMP_Type, *ACMP_MemMapPtr;

/** Number of instances of the ACMP module. */
#define ACMP_INSTANCE_COUNT                            (1u)

/* ACMP0  base address */
#define ACMP0_BASE                                         (0x40043000)
#define ACMP0                                              ((ACMP_Type *)(ACMP0_BASE))

/** Array initializer of ACMP peripheral base addresses */
#define ACMP_BASE_ADDRS                                    { ACMP0_BASE }
/** Array initializer of ACMP peripheral base pointers */
#define ACMP_BASE_PTRS                                     { ACMP0 }
/** Number of interrupt vector arrays for the ACMP module. */
#define ACMP_IRQS_ARR_COUNT                                (1u)
/** Number of interrupt channels for the ACMP. */
#define ACMP_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the ACMP peripheral type */
#define ACMP_IRQS                                 { ACMP0_IRQn }

/* ACMP Register Mask */
/* ACMP_CTRL Register */
#define ACMP_CTRL_EDGESEL_WIDTH                             (2)
#define ACMP_CTRL_EDGESEL_MASK                              (0x30000000U)
#define ACMP_CTRL_EDGESEL_SHIFT                             (28U)
#define ACMP_CTRL_EDGESEL(x)                                (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_EDGESEL_SHIFT)) & ACMP_CTRL_EDGESEL_MASK)
#define ACMP_CTRL_AUTODIS_MASK                              (0x200000U)
#define ACMP_CTRL_AUTODIS_SHIFT                             (21U)
#define ACMP_CTRL_AUTODIS(x)                                (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_AUTODIS_SHIFT)) & ACMP_CTRL_AUTODIS_MASK)
#define ACMP_CTRL_OUTSEL_MASK                               (0x100000U)
#define ACMP_CTRL_OUTSEL_SHIFT                              (20U)
#define ACMP_CTRL_OUTSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_OUTSEL_SHIFT)) & ACMP_CTRL_OUTSEL_MASK)
#define ACMP_CTRL_POL_MASK                                  (0x80000U)
#define ACMP_CTRL_POL_SHIFT                                 (19U)
#define ACMP_CTRL_POL(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_POL_SHIFT)) & ACMP_CTRL_POL_MASK)
#define ACMP_CTRL_OFFSET_MASK                               (0x40000U)
#define ACMP_CTRL_OFFSET_SHIFT                              (18U)
#define ACMP_CTRL_OFFSET(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_OFFSET_SHIFT)) & ACMP_CTRL_OFFSET_MASK)
#define ACMP_CTRL_HYSTVAL_WIDTH                             (2)
#define ACMP_CTRL_HYSTVAL_MASK                              (0x30000U)
#define ACMP_CTRL_HYSTVAL_SHIFT                             (16U)
#define ACMP_CTRL_HYSTVAL(x)                                (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_HYSTVAL_SHIFT)) & ACMP_CTRL_HYSTVAL_MASK)
#define ACMP_CTRL_INNSEL_WIDTH                              (2)
#define ACMP_CTRL_INNSEL_MASK                               (0x3000U)
#define ACMP_CTRL_INNSEL_SHIFT                              (12U)
#define ACMP_CTRL_INNSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_INNSEL_SHIFT)) & ACMP_CTRL_INNSEL_MASK)
#define ACMP_CTRL_INPSEL_WIDTH                              (2)
#define ACMP_CTRL_INPSEL_MASK                               (0x300U)
#define ACMP_CTRL_INPSEL_SHIFT                              (8U)
#define ACMP_CTRL_INPSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_INPSEL_SHIFT)) & ACMP_CTRL_INPSEL_MASK)
#define ACMP_CTRL_CLKSEL_WIDTH                              (2)
#define ACMP_CTRL_CLKSEL_MASK                               (0xC0U)
#define ACMP_CTRL_CLKSEL_SHIFT                              (6U)
#define ACMP_CTRL_CLKSEL(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_CLKSEL_SHIFT)) & ACMP_CTRL_CLKSEL_MASK)
#define ACMP_CTRL_SMPMD_WIDTH                               (2)
#define ACMP_CTRL_SMPMD_MASK                                (0x30U)
#define ACMP_CTRL_SMPMD_SHIFT                               (4U)
#define ACMP_CTRL_SMPMD(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_SMPMD_SHIFT)) & ACMP_CTRL_SMPMD_MASK)
#define ACMP_CTRL_IREF_WIDTH                                (2)
#define ACMP_CTRL_IREF_MASK                                 (0xCU)
#define ACMP_CTRL_IREF_SHIFT                                (2U)
#define ACMP_CTRL_IREF(x)                                   (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_IREF_SHIFT)) & ACMP_CTRL_IREF_MASK)
#define ACMP_CTRL_PWRMD_MASK                                (0x2U)
#define ACMP_CTRL_PWRMD_SHIFT                               (1U)
#define ACMP_CTRL_PWRMD(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_PWRMD_SHIFT)) & ACMP_CTRL_PWRMD_MASK)
#define ACMP_CTRL_EN_MASK                                   (0x1U)
#define ACMP_CTRL_EN_SHIFT                                  (0U)
#define ACMP_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << ACMP_CTRL_EN_SHIFT)) & ACMP_CTRL_EN_MASK)
/* ACMP_DAC Register */
#define ACMP_DAC_VAL_WIDTH                                  (8)
#define ACMP_DAC_VAL_MASK                                   (0xFF00U)
#define ACMP_DAC_VAL_SHIFT                                  (8U)
#define ACMP_DAC_VAL(x)                                     (((uint32_t)(((uint32_t)(x)) << ACMP_DAC_VAL_SHIFT)) & ACMP_DAC_VAL_MASK)
#define ACMP_DAC_VREF_MASK                                  (0x2U)
#define ACMP_DAC_VREF_SHIFT                                 (1U)
#define ACMP_DAC_VREF(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_DAC_VREF_SHIFT)) & ACMP_DAC_VREF_MASK)
#define ACMP_DAC_EN_MASK                                    (0x1U)
#define ACMP_DAC_EN_SHIFT                                   (0U)
#define ACMP_DAC_EN(x)                                      (((uint32_t)(((uint32_t)(x)) << ACMP_DAC_EN_SHIFT)) & ACMP_DAC_EN_MASK)
/* ACMP_MUX Register */
#define ACMP_MUX_CHNSEL_WIDTH                               (3)
#define ACMP_MUX_CHNSEL_MASK                                (0x70U)
#define ACMP_MUX_CHNSEL_SHIFT                               (4U)
#define ACMP_MUX_CHNSEL(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_MUX_CHNSEL_SHIFT)) & ACMP_MUX_CHNSEL_MASK)
#define ACMP_MUX_CHPSEL_WIDTH                               (3)
#define ACMP_MUX_CHPSEL_MASK                                (0x7U)
#define ACMP_MUX_CHPSEL_SHIFT                               (0U)
#define ACMP_MUX_CHPSEL(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_MUX_CHPSEL_SHIFT)) & ACMP_MUX_CHPSEL_MASK)
/* ACMP_FILT Register */
#define ACMP_FILT_CLKSRC_MASK                               (0x10000U)
#define ACMP_FILT_CLKSRC_SHIFT                              (16U)
#define ACMP_FILT_CLKSRC(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_FILT_CLKSRC_SHIFT)) & ACMP_FILT_CLKSRC_MASK)
#define ACMP_FILT_CNT_WIDTH                                 (3)
#define ACMP_FILT_CNT_MASK                                  (0x700U)
#define ACMP_FILT_CNT_SHIFT                                 (8U)
#define ACMP_FILT_CNT(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_FILT_CNT_SHIFT)) & ACMP_FILT_CNT_MASK)
#define ACMP_FILT_PER_WIDTH                                 (8)
#define ACMP_FILT_PER_MASK                                  (0xFFU)
#define ACMP_FILT_PER_SHIFT                                 (0U)
#define ACMP_FILT_PER(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_FILT_PER_SHIFT)) & ACMP_FILT_PER_MASK)
/* ACMP_DMACR Register */
#define ACMP_DMACR_EN_MASK                                  (0x1U)
#define ACMP_DMACR_EN_SHIFT                                 (0U)
#define ACMP_DMACR_EN(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_DMACR_EN_SHIFT)) & ACMP_DMACR_EN_MASK)
/* ACMP_STS Register */
#define ACMP_STS_CH7OUT_MASK                                (0x80000000U)
#define ACMP_STS_CH7OUT_SHIFT                               (31U)
#define ACMP_STS_CH7OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH7OUT_SHIFT)) & ACMP_STS_CH7OUT_MASK)
#define ACMP_STS_CH6OUT_MASK                                (0x40000000U)
#define ACMP_STS_CH6OUT_SHIFT                               (30U)
#define ACMP_STS_CH6OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH6OUT_SHIFT)) & ACMP_STS_CH6OUT_MASK)
#define ACMP_STS_CH5OUT_MASK                                (0x20000000U)
#define ACMP_STS_CH5OUT_SHIFT                               (29U)
#define ACMP_STS_CH5OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH5OUT_SHIFT)) & ACMP_STS_CH5OUT_MASK)
#define ACMP_STS_CH4OUT_MASK                                (0x10000000U)
#define ACMP_STS_CH4OUT_SHIFT                               (28U)
#define ACMP_STS_CH4OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH4OUT_SHIFT)) & ACMP_STS_CH4OUT_MASK)
#define ACMP_STS_CH3OUT_MASK                                (0x8000000U)
#define ACMP_STS_CH3OUT_SHIFT                               (27U)
#define ACMP_STS_CH3OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH3OUT_SHIFT)) & ACMP_STS_CH3OUT_MASK)
#define ACMP_STS_CH2OUT_MASK                                (0x4000000U)
#define ACMP_STS_CH2OUT_SHIFT                               (26U)
#define ACMP_STS_CH2OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH2OUT_SHIFT)) & ACMP_STS_CH2OUT_MASK)
#define ACMP_STS_CH1OUT_MASK                                (0x2000000U)
#define ACMP_STS_CH1OUT_SHIFT                               (25U)
#define ACMP_STS_CH1OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH1OUT_SHIFT)) & ACMP_STS_CH1OUT_MASK)
#define ACMP_STS_CH0OUT_MASK                                (0x1000000U)
#define ACMP_STS_CH0OUT_SHIFT                               (24U)
#define ACMP_STS_CH0OUT(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH0OUT_SHIFT)) & ACMP_STS_CH0OUT_MASK)
#define ACMP_STS_CH7F_MASK                                  (0x800000U)
#define ACMP_STS_CH7F_SHIFT                                 (23U)
#define ACMP_STS_CH7F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH7F_SHIFT)) & ACMP_STS_CH7F_MASK)
#define ACMP_STS_CH6F_MASK                                  (0x400000U)
#define ACMP_STS_CH6F_SHIFT                                 (22U)
#define ACMP_STS_CH6F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH6F_SHIFT)) & ACMP_STS_CH6F_MASK)
#define ACMP_STS_CH5F_MASK                                  (0x200000U)
#define ACMP_STS_CH5F_SHIFT                                 (21U)
#define ACMP_STS_CH5F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH5F_SHIFT)) & ACMP_STS_CH5F_MASK)
#define ACMP_STS_CH4F_MASK                                  (0x100000U)
#define ACMP_STS_CH4F_SHIFT                                 (20U)
#define ACMP_STS_CH4F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH4F_SHIFT)) & ACMP_STS_CH4F_MASK)
#define ACMP_STS_CH3F_MASK                                  (0x80000U)
#define ACMP_STS_CH3F_SHIFT                                 (19U)
#define ACMP_STS_CH3F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH3F_SHIFT)) & ACMP_STS_CH3F_MASK)
#define ACMP_STS_CH2F_MASK                                  (0x40000U)
#define ACMP_STS_CH2F_SHIFT                                 (18U)
#define ACMP_STS_CH2F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH2F_SHIFT)) & ACMP_STS_CH2F_MASK)
#define ACMP_STS_CH1F_MASK                                  (0x20000U)
#define ACMP_STS_CH1F_SHIFT                                 (17U)
#define ACMP_STS_CH1F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH1F_SHIFT)) & ACMP_STS_CH1F_MASK)
#define ACMP_STS_CH0F_MASK                                  (0x10000U)
#define ACMP_STS_CH0F_SHIFT                                 (16U)
#define ACMP_STS_CH0F(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CH0F_SHIFT)) & ACMP_STS_CH0F_MASK)
#define ACMP_STS_CHID_WIDTH                                 (3)
#define ACMP_STS_CHID_MASK                                  (0x700U)
#define ACMP_STS_CHID_SHIFT                                 (8U)
#define ACMP_STS_CHID(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_STS_CHID_SHIFT)) & ACMP_STS_CHID_MASK)
#define ACMP_STS_OUTNF_MASK                                 (0x4U)
#define ACMP_STS_OUTNF_SHIFT                                (2U)
#define ACMP_STS_OUTNF(x)                                   (((uint32_t)(((uint32_t)(x)) << ACMP_STS_OUTNF_SHIFT)) & ACMP_STS_OUTNF_MASK)
#define ACMP_STS_OUTPF_MASK                                 (0x2U)
#define ACMP_STS_OUTPF_SHIFT                                (1U)
#define ACMP_STS_OUTPF(x)                                   (((uint32_t)(((uint32_t)(x)) << ACMP_STS_OUTPF_SHIFT)) & ACMP_STS_OUTPF_MASK)
#define ACMP_STS_OUT_MASK                                   (0x1U)
#define ACMP_STS_OUT_SHIFT                                  (0U)
#define ACMP_STS_OUT(x)                                     (((uint32_t)(((uint32_t)(x)) << ACMP_STS_OUT_SHIFT)) & ACMP_STS_OUT_MASK)
/* ACMP_INTE Register */
#define ACMP_INTE_CONTIE_MASK                               (0x10000U)
#define ACMP_INTE_CONTIE_SHIFT                              (16U)
#define ACMP_INTE_CONTIE(x)                                 (((uint32_t)(((uint32_t)(x)) << ACMP_INTE_CONTIE_SHIFT)) & ACMP_INTE_CONTIE_MASK)
#define ACMP_INTE_IE_MASK                                   (0x1U)
#define ACMP_INTE_IE_SHIFT                                  (0U)
#define ACMP_INTE_IE(x)                                     (((uint32_t)(((uint32_t)(x)) << ACMP_INTE_IE_SHIFT)) & ACMP_INTE_IE_MASK)
/* ACMP_CONT Register */
#define ACMP_CONT_SMP_WIDTH                                 (8)
#define ACMP_CONT_SMP_MASK                                  (0xFF000000U)
#define ACMP_CONT_SMP_SHIFT                                 (24U)
#define ACMP_CONT_SMP(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_SMP_SHIFT)) & ACMP_CONT_SMP_MASK)
#define ACMP_CONT_PER_WIDTH                                 (8)
#define ACMP_CONT_PER_MASK                                  (0xFF0000U)
#define ACMP_CONT_PER_SHIFT                                 (16U)
#define ACMP_CONT_PER(x)                                    (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_PER_SHIFT)) & ACMP_CONT_PER_MASK)
#define ACMP_CONT_CH7EN_MASK                                (0x8000U)
#define ACMP_CONT_CH7EN_SHIFT                               (15U)
#define ACMP_CONT_CH7EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH7EN_SHIFT)) & ACMP_CONT_CH7EN_MASK)
#define ACMP_CONT_CH6EN_MASK                                (0x4000U)
#define ACMP_CONT_CH6EN_SHIFT                               (14U)
#define ACMP_CONT_CH6EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH6EN_SHIFT)) & ACMP_CONT_CH6EN_MASK)
#define ACMP_CONT_CH5EN_MASK                                (0x2000U)
#define ACMP_CONT_CH5EN_SHIFT                               (13U)
#define ACMP_CONT_CH5EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH5EN_SHIFT)) & ACMP_CONT_CH5EN_MASK)
#define ACMP_CONT_CH4EN_MASK                                (0x1000U)
#define ACMP_CONT_CH4EN_SHIFT                               (12U)
#define ACMP_CONT_CH4EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH4EN_SHIFT)) & ACMP_CONT_CH4EN_MASK)
#define ACMP_CONT_CH3EN_MASK                                (0x800U)
#define ACMP_CONT_CH3EN_SHIFT                               (11U)
#define ACMP_CONT_CH3EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH3EN_SHIFT)) & ACMP_CONT_CH3EN_MASK)
#define ACMP_CONT_CH2EN_MASK                                (0x400U)
#define ACMP_CONT_CH2EN_SHIFT                               (10U)
#define ACMP_CONT_CH2EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH2EN_SHIFT)) & ACMP_CONT_CH2EN_MASK)
#define ACMP_CONT_CH1EN_MASK                                (0x200U)
#define ACMP_CONT_CH1EN_SHIFT                               (9U)
#define ACMP_CONT_CH1EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH1EN_SHIFT)) & ACMP_CONT_CH1EN_MASK)
#define ACMP_CONT_CH0EN_MASK                                (0x100U)
#define ACMP_CONT_CH0EN_SHIFT                               (8U)
#define ACMP_CONT_CH0EN(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CH0EN_SHIFT)) & ACMP_CONT_CH0EN_MASK)
#define ACMP_CONT_MODE_MASK                                 (0x4U)
#define ACMP_CONT_MODE_SHIFT                                (2U)
#define ACMP_CONT_MODE(x)                                   (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_MODE_SHIFT)) & ACMP_CONT_MODE_MASK)
#define ACMP_CONT_CHFIX_MASK                                (0x2U)
#define ACMP_CONT_CHFIX_SHIFT                               (1U)
#define ACMP_CONT_CHFIX(x)                                  (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_CHFIX_SHIFT)) & ACMP_CONT_CHFIX_MASK)
#define ACMP_CONT_EN_MASK                                   (0x1U)
#define ACMP_CONT_EN_SHIFT                                  (0U)
#define ACMP_CONT_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << ACMP_CONT_EN_SHIFT)) & ACMP_CONT_EN_MASK)


/*!
 * @}
 */ /* end of group ACMP_Register_Masks */


/*!
 * @}
 */ /* end of group ACMP_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */


/** CRC - Size of Registers Arrays */

/* CRC Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t INIT;                               /**< Initial Seed Register, offset: 0x0004 */
    union {
        __O  uint32_t IN32;                               /**< Data in 32 bits, offset: 0x0008 */
        __O  uint16_t IN16;                               /**< Data in 16 bits, offset: 0x0008 */
        __O  uint8_t IN8;                                /**< Data in 8 Bits, offset: 0x0008 */

    } DATA;
    __I  uint32_t RESULT;                             /**< Result Register, offset: 0x000C */

} CRC_Type, *CRC_MemMapPtr;

/** Number of instances of the CRC module. */
#define CRC_INSTANCE_COUNT                             (1u)

/* CRC0  base address */
#define CRC0_BASE                                          (0x40065000)
#define CRC0                                               ((CRC_Type *)(CRC0_BASE))

/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                                     { CRC0_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                                      { CRC0 }

/* CRC Register Mask */
/* CRC_CTRL Register */
#define CRC_CTRL_INV_OUT_MASK                              (0x40U)
#define CRC_CTRL_INV_OUT_SHIFT                             (6U)
#define CRC_CTRL_INV_OUT(x)                                (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_INV_OUT_SHIFT)) & CRC_CTRL_INV_OUT_MASK)
#define CRC_CTRL_SWAP_OUT_MASK                             (0x20U)
#define CRC_CTRL_SWAP_OUT_SHIFT                            (5U)
#define CRC_CTRL_SWAP_OUT(x)                               (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_SWAP_OUT_SHIFT)) & CRC_CTRL_SWAP_OUT_MASK)
#define CRC_CTRL_SWAP_IN_MASK                              (0x10U)
#define CRC_CTRL_SWAP_IN_SHIFT                             (4U)
#define CRC_CTRL_SWAP_IN(x)                                (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_SWAP_IN_SHIFT)) & CRC_CTRL_SWAP_IN_MASK)
#define CRC_CTRL_MODE_MASK                                 (0x3U)
#define CRC_CTRL_MODE_SHIFT                                (0U)
#define CRC_CTRL_MODE(x)                                   (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_MODE_SHIFT)) & CRC_CTRL_MODE_MASK)
/* CRC_INIT Register */
#define CRC_INIT_SEED_MASK                                 (0xFFFFFFFFU)
#define CRC_INIT_SEED_SHIFT                                (0U)
#define CRC_INIT_SEED(x)                                   (((uint32_t)(((uint32_t)(x)) << CRC_INIT_SEED_SHIFT)) & CRC_INIT_SEED_MASK)
/* CRC_DATA_IN32 Register */
#define CRC_DATA_IN32_DATA_MASK                                 (0xFFFFFFFFU)
#define CRC_DATA_IN32_DATA_SHIFT                                (0U)
#define CRC_DATA_IN32_DATA(x)                                   (((uint32_t)(((uint32_t)(x)) << CRC_DATA_IN32_DATA_SHIFT)) & CRC_DATA_IN32_DATA_MASK)
/* CRC_DATA_IN16 Register */
#define CRC_DATA_IN16_DATA_MASK                                 (0xFFFFU)
#define CRC_DATA_IN16_DATA_SHIFT                                (0U)
#define CRC_DATA_IN16_DATA(x)                                   (((uint32_t)(((uint32_t)(x)) << CRC_DATA_IN16_DATA_SHIFT)) & CRC_DATA_IN16_DATA_MASK)
/* CRC_DATA_IN8 Register */
#define CRC_DATA_IN8_DATA_MASK                                  (0xFFU)
#define CRC_DATA_IN8_DATA_SHIFT                                 (0U)
#define CRC_DATA_IN8_DATA(x)                                    (((uint32_t)(((uint32_t)(x)) << CRC_DATA_IN8_DATA_SHIFT)) & CRC_DATA_IN8_DATA_MASK)

/* CRC_RESULT Register */
#define CRC_RESULT_RESULT_MASK                             (0xFFFFFFFFU)
#define CRC_RESULT_RESULT_SHIFT                            (0U)
#define CRC_RESULT_RESULT(x)                               (((uint32_t)(((uint32_t)(x)) << CRC_RESULT_RESULT_SHIFT)) & CRC_RESULT_RESULT_MASK)


/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- HCU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup HCU_Peripheral_Access_Layer HCU Peripheral Access Layer
 * @{
 */


/** HCU - Size of Registers Arrays */
#define HCU_KEY_COUNT                     (8)
#define HCU_AESCV_COUNT                     (4)
#define HCU_AESIV_COUNT                     (4)
#define HCU_AESMAC_COUNT                     (4)

/* HCU Register Layout Typedef */
typedef struct {
    __IO uint32_t GO;                                 /**< Go Register, offset: 0x0000 */
    __IO uint32_t CR;                                 /**< Configuration Register, offset: 0x0004 */
    __IO uint32_t MSGINFO;                            /**< Message Information Register, offset: 0x0008 */
    __IO uint32_t MSGADL;                             /**< Message and Additional Data Length Register, offset: 0x000C */
    __IO uint32_t RESERVED0;                          /**< RESERVED0, offset: 0x0010 */
    __IO uint32_t FIFOWM;                             /**< FIFO Watermark Register, offset: 0x0014 */
    __IO uint32_t INTE;                               /**< Interrupt Enable Register, offset: 0x0018 */
    __IO uint32_t SR;                                 /**< Status Register, offset: 0x001C */
    __O  uint32_t KEY[ 8];                            /**< Key (0~7) Register, offset: 0x0020 */
    __IO uint32_t RESERVED1[ 4];                      /**< RESERVED1, offset: 0x0040 */
    __IO uint32_t AESCV[ 4];                          /**< AES Counter Value (0~3) Register, offset: 0x0050 */
    __IO uint32_t AESIV[ 4];                          /**< AES Initial Vector (0~3) Register, offset: 0x0060 */
    __IO uint32_t AESMAC[ 4];                         /**< AES MAC (0~3) Register, offset: 0x0070 */
    __IO uint32_t RESERVED2[12];                      /**< RESERVED2, offset: 0x0080 */
    __O  uint32_t IFDAT;                              /**< Input FIFO Data Register, offset: 0x00B0 */
    __I  uint32_t OFDAT;                              /**< Output FIFO Data Register, offset: 0x00B4 */

} HCU_Type, *HCU_MemMapPtr;

/** Number of instances of the HCU module. */
#define HCU_INSTANCE_COUNT                             (1u)

/* HCU base address */
#define HCU_BASE                                          (0x40067000)
#define HCU                                               ((HCU_Type *)(HCU_BASE))

/** Array initializer of HCU peripheral base addresses */
#define HCU_BASE_ADDRS                                     { HCU_BASE }
/** Array initializer of HCU peripheral base pointers */
#define HCU_BASE_PTRS                                      { HCU }
/** Number of interrupt vector arrays for the HCU module. */
#define HCU_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the HCU. */
#define HCU_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the HCU peripheral type */
#define HCU_IRQS                                  { HCU_IRQn }

/* HCU Register Mask */
/* HCU_GO Register */
#define HCU_GO_GO_MASK                                     (0x1U)
#define HCU_GO_GO_SHIFT                                    (0U)
#define HCU_GO_GO(x)                                       (((uint32_t)(((uint32_t)(x)) << HCU_GO_GO_SHIFT)) & HCU_GO_GO_MASK)
/* HCU_CR Register */
#define HCU_CR_OFSWR_MASK                                  (0x80000000U)
#define HCU_CR_OFSWR_SHIFT                                 (31U)
#define HCU_CR_OFSWR(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_CR_OFSWR_SHIFT)) & HCU_CR_OFSWR_MASK)
#define HCU_CR_IFSWR_MASK                                  (0x40000000U)
#define HCU_CR_IFSWR_SHIFT                                 (30U)
#define HCU_CR_IFSWR(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_CR_IFSWR_SHIFT)) & HCU_CR_IFSWR_MASK)
#define HCU_CR_OFDMAE_MASK                                 (0x20000000U)
#define HCU_CR_OFDMAE_SHIFT                                (29U)
#define HCU_CR_OFDMAE(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_OFDMAE_SHIFT)) & HCU_CR_OFDMAE_MASK)
#define HCU_CR_IFDMAE_MASK                                 (0x10000000U)
#define HCU_CR_IFDMAE_SHIFT                                (28U)
#define HCU_CR_IFDMAE(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_IFDMAE_SHIFT)) & HCU_CR_IFDMAE_MASK)
#define HCU_CR_MACLEN_MASK                                 (0xF000000U)
#define HCU_CR_MACLEN_SHIFT                                (24U)
#define HCU_CR_MACLEN(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_MACLEN_SHIFT)) & HCU_CR_MACLEN_MASK)
#define HCU_CR_CS_MASK                                     (0x40000U)
#define HCU_CR_CS_SHIFT                                    (18U)
#define HCU_CR_CS(x)                                       (((uint32_t)(((uint32_t)(x)) << HCU_CR_CS_SHIFT)) & HCU_CR_CS_MASK)
#define HCU_CR_MSGB_MASK                                   (0x20000U)
#define HCU_CR_MSGB_SHIFT                                  (17U)
#define HCU_CR_MSGB(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_CR_MSGB_SHIFT)) & HCU_CR_MSGB_MASK)
#define HCU_CR_MSGE_MASK                                   (0x10000U)
#define HCU_CR_MSGE_SHIFT                                  (16U)
#define HCU_CR_MSGE(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_CR_MSGE_SHIFT)) & HCU_CR_MSGE_MASK)
#define HCU_CR_ALGSEL_MASK                                 (0xF000U)
#define HCU_CR_ALGSEL_SHIFT                                (12U)
#define HCU_CR_ALGSEL(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_ALGSEL_SHIFT)) & HCU_CR_ALGSEL_MASK)
#define HCU_CR_KEYLEN_MASK                                 (0x300U)
#define HCU_CR_KEYLEN_SHIFT                                (8U)
#define HCU_CR_KEYLEN(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_KEYLEN_SHIFT)) & HCU_CR_KEYLEN_MASK)
#define HCU_CR_ENGSEL_MASK                                 (0xF0U)
#define HCU_CR_ENGSEL_SHIFT                                (4U)
#define HCU_CR_ENGSEL(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_ENGSEL_SHIFT)) & HCU_CR_ENGSEL_MASK)
#define HCU_CR_DATSWP_MASK                                 (0xCU)
#define HCU_CR_DATSWP_SHIFT                                (2U)
#define HCU_CR_DATSWP(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_CR_DATSWP_SHIFT)) & HCU_CR_DATSWP_MASK)
#define HCU_CR_ENC_MASK                                    (0x2U)
#define HCU_CR_ENC_SHIFT                                   (1U)
#define HCU_CR_ENC(x)                                      (((uint32_t)(((uint32_t)(x)) << HCU_CR_ENC_SHIFT)) & HCU_CR_ENC_MASK)
/* HCU_MSGINFO Register */
#define HCU_MSGINFO_MSGTOT_MASK                            (0xFFFFFFFU)
#define HCU_MSGINFO_MSGTOT_SHIFT                           (0U)
#define HCU_MSGINFO_MSGTOT(x)                              (((uint32_t)(((uint32_t)(x)) << HCU_MSGINFO_MSGTOT_SHIFT)) & HCU_MSGINFO_MSGTOT_MASK)
/* HCU_MSGADL Register */
#define HCU_MSGADL_ADLEN_MASK                              (0xFFFF0000U)
#define HCU_MSGADL_ADLEN_SHIFT                             (16U)
#define HCU_MSGADL_ADLEN(x)                                (((uint32_t)(((uint32_t)(x)) << HCU_MSGADL_ADLEN_SHIFT)) & HCU_MSGADL_ADLEN_MASK)
#define HCU_MSGADL_MSGLEN_MASK                             (0xFFFFU)
#define HCU_MSGADL_MSGLEN_SHIFT                            (0U)
#define HCU_MSGADL_MSGLEN(x)                               (((uint32_t)(((uint32_t)(x)) << HCU_MSGADL_MSGLEN_SHIFT)) & HCU_MSGADL_MSGLEN_MASK)
/* HCU_FIFOWM Register */
#define HCU_FIFOWM_OFWM_MASK                               (0x1F0000U)
#define HCU_FIFOWM_OFWM_SHIFT                              (16U)
#define HCU_FIFOWM_OFWM(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_FIFOWM_OFWM_SHIFT)) & HCU_FIFOWM_OFWM_MASK)
#define HCU_FIFOWM_IFWM_MASK                               (0x1FU)
#define HCU_FIFOWM_IFWM_SHIFT                              (0U)
#define HCU_FIFOWM_IFWM(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_FIFOWM_IFWM_SHIFT)) & HCU_FIFOWM_IFWM_MASK)
/* HCU_INTE Register */
#define HCU_INTE_IFWMIE_MASK                               (0x8000U)
#define HCU_INTE_IFWMIE_SHIFT                              (15U)
#define HCU_INTE_IFWMIE(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_INTE_IFWMIE_SHIFT)) & HCU_INTE_IFWMIE_MASK)
#define HCU_INTE_OFWMIE_MASK                               (0x4000U)
#define HCU_INTE_OFWMIE_SHIFT                              (14U)
#define HCU_INTE_OFWMIE(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_INTE_OFWMIE_SHIFT)) & HCU_INTE_OFWMIE_MASK)
#define HCU_INTE_IFOFIE_MASK                               (0x2000U)
#define HCU_INTE_IFOFIE_SHIFT                              (13U)
#define HCU_INTE_IFOFIE(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_INTE_IFOFIE_SHIFT)) & HCU_INTE_IFOFIE_MASK)
#define HCU_INTE_OFUFIE_MASK                               (0x1000U)
#define HCU_INTE_OFUFIE_SHIFT                              (12U)
#define HCU_INTE_OFUFIE(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_INTE_OFUFIE_SHIFT)) & HCU_INTE_OFUFIE_MASK)
#define HCU_INTE_IFEIE_MASK                                (0x400U)
#define HCU_INTE_IFEIE_SHIFT                               (10U)
#define HCU_INTE_IFEIE(x)                                  (((uint32_t)(((uint32_t)(x)) << HCU_INTE_IFEIE_SHIFT)) & HCU_INTE_IFEIE_MASK)
#define HCU_INTE_OFFIE_MASK                                (0x200U)
#define HCU_INTE_OFFIE_SHIFT                               (9U)
#define HCU_INTE_OFFIE(x)                                  (((uint32_t)(((uint32_t)(x)) << HCU_INTE_OFFIE_SHIFT)) & HCU_INTE_OFFIE_MASK)
#define HCU_INTE_ODIE_MASK                                 (0x1U)
#define HCU_INTE_ODIE_SHIFT                                (0U)
#define HCU_INTE_ODIE(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_INTE_ODIE_SHIFT)) & HCU_INTE_ODIE_MASK)
/* HCU_SR Register */
#define HCU_SR_IFWMF_MASK                                  (0x8000U)
#define HCU_SR_IFWMF_SHIFT                                 (15U)
#define HCU_SR_IFWMF(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_SR_IFWMF_SHIFT)) & HCU_SR_IFWMF_MASK)
#define HCU_SR_OFWMF_MASK                                  (0x4000U)
#define HCU_SR_OFWMF_SHIFT                                 (14U)
#define HCU_SR_OFWMF(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_SR_OFWMF_SHIFT)) & HCU_SR_OFWMF_MASK)
#define HCU_SR_IFOFF_MASK                                  (0x2000U)
#define HCU_SR_IFOFF_SHIFT                                 (13U)
#define HCU_SR_IFOFF(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_SR_IFOFF_SHIFT)) & HCU_SR_IFOFF_MASK)
#define HCU_SR_OFUFF_MASK                                  (0x1000U)
#define HCU_SR_OFUFF_SHIFT                                 (12U)
#define HCU_SR_OFUFF(x)                                    (((uint32_t)(((uint32_t)(x)) << HCU_SR_OFUFF_SHIFT)) & HCU_SR_OFUFF_MASK)
#define HCU_SR_IFFS_MASK                                   (0x800U)
#define HCU_SR_IFFS_SHIFT                                  (11U)
#define HCU_SR_IFFS(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_SR_IFFS_SHIFT)) & HCU_SR_IFFS_MASK)
#define HCU_SR_IFES_MASK                                   (0x400U)
#define HCU_SR_IFES_SHIFT                                  (10U)
#define HCU_SR_IFES(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_SR_IFES_SHIFT)) & HCU_SR_IFES_MASK)
#define HCU_SR_OFFS_MASK                                   (0x200U)
#define HCU_SR_OFFS_SHIFT                                  (9U)
#define HCU_SR_OFFS(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_SR_OFFS_SHIFT)) & HCU_SR_OFFS_MASK)
#define HCU_SR_OFES_MASK                                   (0x100U)
#define HCU_SR_OFES_SHIFT                                  (8U)
#define HCU_SR_OFES(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_SR_OFES_SHIFT)) & HCU_SR_OFES_MASK)
#define HCU_SR_AESVAL_MASK                                 (0x2U)
#define HCU_SR_AESVAL_SHIFT                                (1U)
#define HCU_SR_AESVAL(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_SR_AESVAL_SHIFT)) & HCU_SR_AESVAL_MASK)
#define HCU_SR_OD_MASK                                     (0x1U)
#define HCU_SR_OD_SHIFT                                    (0U)
#define HCU_SR_OD(x)                                       (((uint32_t)(((uint32_t)(x)) << HCU_SR_OD_SHIFT)) & HCU_SR_OD_MASK)
/* HCU_KEY Register */
#define HCU_KEY_KEY_MASK                                   (0xFFFFFFFFU)
#define HCU_KEY_KEY_SHIFT                                  (0U)
#define HCU_KEY_KEY(x)                                     (((uint32_t)(((uint32_t)(x)) << HCU_KEY_KEY_SHIFT)) & HCU_KEY_KEY_MASK)
/* HCU_AESCV Register */
#define HCU_AESCV_CNT_MASK                                 (0xFFFFFFFFU)
#define HCU_AESCV_CNT_SHIFT                                (0U)
#define HCU_AESCV_CNT(x)                                   (((uint32_t)(((uint32_t)(x)) << HCU_AESCV_CNT_SHIFT)) & HCU_AESCV_CNT_MASK)
/* HCU_AESIV Register */
#define HCU_AESIV_INIT_MASK                                (0xFFFFFFFFU)
#define HCU_AESIV_INIT_SHIFT                               (0U)
#define HCU_AESIV_INIT(x)                                  (((uint32_t)(((uint32_t)(x)) << HCU_AESIV_INIT_SHIFT)) & HCU_AESIV_INIT_MASK)
/* HCU_AESMAC Register */
#define HCU_AESMAC_MAC_MASK                                (0xFFFFFFFFU)
#define HCU_AESMAC_MAC_SHIFT                               (0U)
#define HCU_AESMAC_MAC(x)                                  (((uint32_t)(((uint32_t)(x)) << HCU_AESMAC_MAC_SHIFT)) & HCU_AESMAC_MAC_MASK)
/* HCU_IFDAT Register */
#define HCU_IFDAT_IFDAT_MASK                               (0xFFFFFFFFU)
#define HCU_IFDAT_IFDAT_SHIFT                              (0U)
#define HCU_IFDAT_IFDAT(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_IFDAT_IFDAT_SHIFT)) & HCU_IFDAT_IFDAT_MASK)
/* HCU_OFDAT Register */
#define HCU_OFDAT_OFDAT_MASK                               (0xFFFFFFFFU)
#define HCU_OFDAT_OFDAT_SHIFT                              (0U)
#define HCU_OFDAT_OFDAT(x)                                 (((uint32_t)(((uint32_t)(x)) << HCU_OFDAT_OFDAT_SHIFT)) & HCU_OFDAT_OFDAT_MASK)


/*!
 * @}
 */ /* end of group HCU_Register_Masks */


/*!
 * @}
 */ /* end of group HCU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- TRNG Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup TRNG_Peripheral_Access_Layer TRNG Peripheral Access Layer
 * @{
 */


/** TRNG - Size of Registers Arrays */
#define TRNG_ENT_COUNT                     (8)

/* TRNG Register Layout Typedef */
typedef struct {
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x0000 */
    __IO uint32_t STAT;                               /**< Status Register, offset: 0x0004 */
    __IO uint32_t SDCTL;                              /**< Seed Control Register, offset: 0x0008 */
    __IO uint32_t FRQMIN;                             /**< Frequency Minimum Limit Register, offset: 0x000C */
    __IO uint32_t FRQMAX;                             /**< Frequency Maximum Limit Register, offset: 0x0010 */
    __IO uint32_t FRQCNT;                             /**< Frequency Count Register, offset: 0x0014 */
    __IO uint32_t SCML;                               /**< Statistical Check Monobit Limit Register, offset: 0x0018 */
    __IO uint32_t SCMC;                               /**< Statistical Check Monobit Count Register, offset: 0x001C */
    __IO uint32_t RESERVED0[ 8];                      /**< RESERVED0, offset: 0x0020 */
    __IO uint32_t ENT[ 8];                            /**< Entropy Read Register, offset: 0x0040 */

} TRNG_Type, *TRNG_MemMapPtr;

/** Number of instances of the TRNG module. */
#define TRNG_INSTANCE_COUNT                            (1u)

/* TRNG base address */
#define TRNG_BASE                                         (0x40066000)
#define TRNG                                              ((TRNG_Type *)(TRNG_BASE))

/** Array initializer of TRNG peripheral base addresses */
#define TRNG_BASE_ADDRS                                    { TRNG_BASE }
/** Array initializer of TRNG peripheral base pointers */
#define TRNG_BASE_PTRS                                     { TRNG }

/* TRNG Register Mask */
/* TRNG_CTRL Register */
#define TRNG_CTRL_RTY_CT_MASK                               (0xF000000U)
#define TRNG_CTRL_RTY_CT_SHIFT                              (24U)
#define TRNG_CTRL_RTY_CT(x)                                 (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_RTY_CT_SHIFT)) & TRNG_CTRL_RTY_CT_MASK)
#define TRNG_CTRL_LRUN_MAX_MASK                             (0xFF0000U)
#define TRNG_CTRL_LRUN_MAX_SHIFT                            (16U)
#define TRNG_CTRL_LRUN_MAX(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_LRUN_MAX_SHIFT)) & TRNG_CTRL_LRUN_MAX_MASK)
#define TRNG_CTRL_FRQ_CT_IE_MASK                            (0x400U)
#define TRNG_CTRL_FRQ_CT_IE_SHIFT                           (10U)
#define TRNG_CTRL_FRQ_CT_IE(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_FRQ_CT_IE_SHIFT)) & TRNG_CTRL_FRQ_CT_IE_MASK)
#define TRNG_CTRL_ENT_VAL_IE_MASK                           (0x200U)
#define TRNG_CTRL_ENT_VAL_IE_SHIFT                          (9U)
#define TRNG_CTRL_ENT_VAL_IE(x)                             (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_ENT_VAL_IE_SHIFT)) & TRNG_CTRL_ENT_VAL_IE_MASK)
#define TRNG_CTRL_HW_ERR_IE_MASK                            (0x100U)
#define TRNG_CTRL_HW_ERR_IE_SHIFT                           (8U)
#define TRNG_CTRL_HW_ERR_IE(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_HW_ERR_IE_SHIFT)) & TRNG_CTRL_HW_ERR_IE_MASK)
#define TRNG_CTRL_FOR_SCLK_MASK                             (0x80U)
#define TRNG_CTRL_FOR_SCLK_SHIFT                            (7U)
#define TRNG_CTRL_FOR_SCLK(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_FOR_SCLK_SHIFT)) & TRNG_CTRL_FOR_SCLK_MASK)
#define TRNG_CTRL_UNLOCK_MASK                               (0x20U)
#define TRNG_CTRL_UNLOCK_SHIFT                              (5U)
#define TRNG_CTRL_UNLOCK(x)                                 (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_UNLOCK_SHIFT)) & TRNG_CTRL_UNLOCK_MASK)
#define TRNG_CTRL_CLK_OUT_MASK                              (0x10U)
#define TRNG_CTRL_CLK_OUT_SHIFT                             (4U)
#define TRNG_CTRL_CLK_OUT(x)                                (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_CLK_OUT_SHIFT)) & TRNG_CTRL_CLK_OUT_MASK)
#define TRNG_CTRL_OSC_DIV_MASK                              (0xCU)
#define TRNG_CTRL_OSC_DIV_SHIFT                             (2U)
#define TRNG_CTRL_OSC_DIV(x)                                (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_OSC_DIV_SHIFT)) & TRNG_CTRL_OSC_DIV_MASK)
#define TRNG_CTRL_TRNG_EN_MASK                              (0x2U)
#define TRNG_CTRL_TRNG_EN_SHIFT                             (1U)
#define TRNG_CTRL_TRNG_EN(x)                                (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_TRNG_EN_SHIFT)) & TRNG_CTRL_TRNG_EN_MASK)
#define TRNG_CTRL_SWR_MASK                                  (0x1U)
#define TRNG_CTRL_SWR_SHIFT                                 (0U)
#define TRNG_CTRL_SWR(x)                                    (((uint32_t)(((uint32_t)(x)) << TRNG_CTRL_SWR_SHIFT)) & TRNG_CTRL_SWR_MASK)
/* TRNG_STAT Register */
#define TRNG_STAT_FRQ_CT_IF_MASK                            (0x400U)
#define TRNG_STAT_FRQ_CT_IF_SHIFT                           (10U)
#define TRNG_STAT_FRQ_CT_IF(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_STAT_FRQ_CT_IF_SHIFT)) & TRNG_STAT_FRQ_CT_IF_MASK)
#define TRNG_STAT_ENT_VAL_IF_MASK                           (0x200U)
#define TRNG_STAT_ENT_VAL_IF_SHIFT                          (9U)
#define TRNG_STAT_ENT_VAL_IF(x)                             (((uint32_t)(((uint32_t)(x)) << TRNG_STAT_ENT_VAL_IF_SHIFT)) & TRNG_STAT_ENT_VAL_IF_MASK)
#define TRNG_STAT_HW_ERR_IF_MASK                            (0x100U)
#define TRNG_STAT_HW_ERR_IF_SHIFT                           (8U)
#define TRNG_STAT_HW_ERR_IF(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_STAT_HW_ERR_IF_SHIFT)) & TRNG_STAT_HW_ERR_IF_MASK)
#define TRNG_STAT_IDLE_MASK                                 (0x20U)
#define TRNG_STAT_IDLE_SHIFT                                (5U)
#define TRNG_STAT_IDLE(x)                                   (((uint32_t)(((uint32_t)(x)) << TRNG_STAT_IDLE_SHIFT)) & TRNG_STAT_IDLE_MASK)
#define TRNG_STAT_FCT_VAL_MASK                              (0x2U)
#define TRNG_STAT_FCT_VAL_SHIFT                             (1U)
#define TRNG_STAT_FCT_VAL(x)                                (((uint32_t)(((uint32_t)(x)) << TRNG_STAT_FCT_VAL_SHIFT)) & TRNG_STAT_FCT_VAL_MASK)
/* TRNG_SDCTL Register */
#define TRNG_SDCTL_ENT_DLY_MASK                             (0xFFFF0000U)
#define TRNG_SDCTL_ENT_DLY_SHIFT                            (16U)
#define TRNG_SDCTL_ENT_DLY(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_ENT_DLY_SHIFT)) & TRNG_SDCTL_ENT_DLY_MASK)
#define TRNG_SDCTL_SAMP_SIZE_MASK                           (0xFFFFU)
#define TRNG_SDCTL_SAMP_SIZE_SHIFT                          (0U)
#define TRNG_SDCTL_SAMP_SIZE(x)                             (((uint32_t)(((uint32_t)(x)) << TRNG_SDCTL_SAMP_SIZE_SHIFT)) & TRNG_SDCTL_SAMP_SIZE_MASK)
/* TRNG_FRQMIN Register */
#define TRNG_FRQMIN_FRQ_MIN_MASK                            (0x3FFFFFU)
#define TRNG_FRQMIN_FRQ_MIN_SHIFT                           (0U)
#define TRNG_FRQMIN_FRQ_MIN(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMIN_FRQ_MIN_SHIFT)) & TRNG_FRQMIN_FRQ_MIN_MASK)
/* TRNG_FRQMAX Register */
#define TRNG_FRQMAX_FRQ_MAX_MASK                            (0x3FFFFFU)
#define TRNG_FRQMAX_FRQ_MAX_SHIFT                           (0U)
#define TRNG_FRQMAX_FRQ_MAX(x)                              (((uint32_t)(((uint32_t)(x)) << TRNG_FRQMAX_FRQ_MAX_SHIFT)) & TRNG_FRQMAX_FRQ_MAX_MASK)
/* TRNG_FRQCNT Register */
#define TRNG_FRQCNT_FRQ_CT_MASK                             (0x3FFFFFU)
#define TRNG_FRQCNT_FRQ_CT_SHIFT                            (0U)
#define TRNG_FRQCNT_FRQ_CT(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_FRQCNT_FRQ_CT_SHIFT)) & TRNG_FRQCNT_FRQ_CT_MASK)
/* TRNG_SCML Register */
#define TRNG_SCML_MONO_RNG_MASK                             (0xFFFF0000U)
#define TRNG_SCML_MONO_RNG_SHIFT                            (16U)
#define TRNG_SCML_MONO_RNG(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_RNG_SHIFT)) & TRNG_SCML_MONO_RNG_MASK)
#define TRNG_SCML_MONO_MAX_MASK                             (0xFFFFU)
#define TRNG_SCML_MONO_MAX_SHIFT                            (0U)
#define TRNG_SCML_MONO_MAX(x)                               (((uint32_t)(((uint32_t)(x)) << TRNG_SCML_MONO_MAX_SHIFT)) & TRNG_SCML_MONO_MAX_MASK)
/* TRNG_SCMC Register */
#define TRNG_SCMC_MONO_CT_MASK                              (0xFFFFU)
#define TRNG_SCMC_MONO_CT_SHIFT                             (0U)
#define TRNG_SCMC_MONO_CT(x)                                (((uint32_t)(((uint32_t)(x)) << TRNG_SCMC_MONO_CT_SHIFT)) & TRNG_SCMC_MONO_CT_MASK)
/* TRNG_ENT Register */
#define TRNG_ENT_ENT_MASK                                   (0xFFFFFFFFU)
#define TRNG_ENT_ENT_SHIFT                                  (0U)
#define TRNG_ENT_ENT(x)                                     (((uint32_t)(((uint32_t)(x)) << TRNG_ENT_ENT_SHIFT)) & TRNG_ENT_ENT_MASK)


/*!
 * @}
 */ /* end of group TRNG_Register_Masks */


/*!
 * @}
 */ /* end of group TRNG_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- EMU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup EMU_Peripheral_Access_Layer EMU Peripheral Access Layer
 * @{
 */


/** EMU - Size of Registers Arrays */
#define EMU_EICHD_COUNT                     (2)
#define EMU_ERINFO_COUNT                     (2)

/* EMU Register Layout Typedef */
typedef struct {
    __IO uint32_t EIGCR;                              /**< Error Injection Global Control Register, offset: 0x0000 */
    __IO uint32_t EICHCR;                             /**< Error Injection Channel Control Register, offset: 0x0004 */
    __IO uint32_t RESERVED0[ 2];                      /**< RESERVED0, offset: 0x0008 */
    struct {
        __IO uint32_t ADDR;                               /**< Channel Error Injection Address Register, offset: 0x0010 */
        __IO uint32_t CHKBIT;                             /**< Error Injection CheckBit Mask Register, offset: 0x0014 */
        __IO uint32_t DATA;                               /**< Error Injection DATA Mask Register, offset: 0x0018 */
        __IO uint32_t RESERVED1;                          /**< RESERVED1, offset: 0x001C */

    } EICHD[2];
    __IO uint32_t RESERVED2[52];                      /**< RESERVED2, offset: 0x0030 */
    __IO uint32_t ERIE;                               /**< Error Report Interrupt Enable Register, offset: 0x0100 */
    __IO uint32_t ERIF;                               /**< Error Report Interrupt Flag Register, offset: 0x0104 */
    __IO uint32_t RESERVED3[ 2];                      /**< RESERVED3, offset: 0x0108 */
    struct {
        __I  uint32_t ADDR;                               /**< Error Report Address Register, offset: 0x0110 */
        __I  uint32_t SYND;                               /**< Error Report Syndrome Register, offset: 0x0114 */
        __O  uint32_t CNT;                                /**< Correctable Error Count Register, offset: 0x0118 */
        __IO uint32_t RESERVED4;                          /**< RESERVED4, offset: 0x011C */

    } ERINFO[2];

} EMU_Type, *EMU_MemMapPtr;

/** Number of instances of the EMU module. */
#define EMU_INSTANCE_COUNT                             (1u)

/* EMU base address */
#define EMU_BASE                                          (0x40072000)
#define EMU                                               ((EMU_Type *)(EMU_BASE))

/** Array initializer of EMU peripheral base addresses */
#define EMU_BASE_ADDRS                                     { EMU_BASE }
/** Array initializer of EMU peripheral base pointers */
#define EMU_BASE_PTRS                                      { EMU }
/** Number of interrupt vector arrays for the EMU module. */
#define EMU_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the EMU. */
#define EMU_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the EMU peripheral type */
#define EMU_IRQS                                  { EMU_IRQn }

/* EMU Register Mask */
/* EMU_EIGCR Register */
#define EMU_EIGCR_GEN_MASK                                 (0x1U)
#define EMU_EIGCR_GEN_SHIFT                                (0U)
#define EMU_EIGCR_GEN(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_EIGCR_GEN_SHIFT)) & EMU_EIGCR_GEN_MASK)
/* EMU_EICHCR Register */
#define EMU_EICHCR_CH1EN_MASK                              (0x2U)
#define EMU_EICHCR_CH1EN_SHIFT                             (1U)
#define EMU_EICHCR_CH1EN(x)                                (((uint32_t)(((uint32_t)(x)) << EMU_EICHCR_CH1EN_SHIFT)) & EMU_EICHCR_CH1EN_MASK)
#define EMU_EICHCR_CH0EN_MASK                              (0x1U)
#define EMU_EICHCR_CH0EN_SHIFT                             (0U)
#define EMU_EICHCR_CH0EN(x)                                (((uint32_t)(((uint32_t)(x)) << EMU_EICHCR_CH0EN_SHIFT)) & EMU_EICHCR_CH0EN_MASK)
/* EMU_EICHD_ADDR Register */
#define EMU_EICHD_ADDR_ADDR_MASK                                 (0xFFFFFFFFU)
#define EMU_EICHD_ADDR_ADDR_SHIFT                                (0U)
#define EMU_EICHD_ADDR_ADDR(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_EICHD_ADDR_ADDR_SHIFT)) & EMU_EICHD_ADDR_ADDR_MASK)
/* EMU_EICHD_CHKBIT Register */
#define EMU_EICHD_CHKBIT_CHKBIT_MASK                             (0x7FU)
#define EMU_EICHD_CHKBIT_CHKBIT_SHIFT                            (0U)
#define EMU_EICHD_CHKBIT_CHKBIT(x)                               (((uint32_t)(((uint32_t)(x)) << EMU_EICHD_CHKBIT_CHKBIT_SHIFT)) & EMU_EICHD_CHKBIT_CHKBIT_MASK)
/* EMU_EICHD_DATA Register */
#define EMU_EICHD_DATA_DATA_MASK                                 (0xFFFFFFFFU)
#define EMU_EICHD_DATA_DATA_SHIFT                                (0U)
#define EMU_EICHD_DATA_DATA(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_EICHD_DATA_DATA_SHIFT)) & EMU_EICHD_DATA_DATA_MASK)

/* EMU_ERIE Register */
#define EMU_ERIE_NCIE_WIDTH                                (2)
#define EMU_ERIE_NCIE_MASK                                 (0x30000U)
#define EMU_ERIE_NCIE_SHIFT                                (16U)
#define EMU_ERIE_NCIE(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_ERIE_NCIE_SHIFT)) & EMU_ERIE_NCIE_MASK)
#define EMU_ERIE_SCIE_WIDTH                                (2)
#define EMU_ERIE_SCIE_MASK                                 (0x3U)
#define EMU_ERIE_SCIE_SHIFT                                (0U)
#define EMU_ERIE_SCIE(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_ERIE_SCIE_SHIFT)) & EMU_ERIE_SCIE_MASK)
/* EMU_ERIF Register */
#define EMU_ERIF_NCIF_MASK                                 (0x30000U)
#define EMU_ERIF_NCIF_SHIFT                                (16U)
#define EMU_ERIF_NCIF(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_ERIF_NCIF_SHIFT)) & EMU_ERIF_NCIF_MASK)
#define EMU_ERIF_SCIF_MASK                                 (0x3U)
#define EMU_ERIF_SCIF_SHIFT                                (0U)
#define EMU_ERIF_SCIF(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_ERIF_SCIF_SHIFT)) & EMU_ERIF_SCIF_MASK)
/* EMU_ERINFO_ADDR Register */
#define EMU_ERINFO_ADDR_ADDR_MASK                                 (0xFFFFFFFFU)
#define EMU_ERINFO_ADDR_ADDR_SHIFT                                (0U)
#define EMU_ERINFO_ADDR_ADDR(x)                                   (((uint32_t)(((uint32_t)(x)) << EMU_ERINFO_ADDR_ADDR_SHIFT)) & EMU_ERINFO_ADDR_ADDR_MASK)
/* EMU_ERINFO_SYND Register */
#define EMU_ERINFO_SYND_SYNDROME_MASK                             (0x7FU)
#define EMU_ERINFO_SYND_SYNDROME_SHIFT                            (0U)
#define EMU_ERINFO_SYND_SYNDROME(x)                               (((uint32_t)(((uint32_t)(x)) << EMU_ERINFO_SYND_SYNDROME_SHIFT)) & EMU_ERINFO_SYND_SYNDROME_MASK)
/* EMU_ERINFO_CNT Register */
#define EMU_ERINFO_CNT_CNT_MASK                                   (0xFFU)
#define EMU_ERINFO_CNT_CNT_SHIFT                                  (0U)
#define EMU_ERINFO_CNT_CNT(x)                                     (((uint32_t)(((uint32_t)(x)) << EMU_ERINFO_CNT_CNT_SHIFT)) & EMU_ERINFO_CNT_CNT_MASK)



/*!
 * @}
 */ /* end of group EMU_Register_Masks */


/*!
 * @}
 */ /* end of group EMU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- INTM Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup INTM_Peripheral_Access_Layer INTM Peripheral Access Layer
 * @{
 */


/** INTM - Size of Registers Arrays */
#define INTM_MON_COUNT                     (4)

/* INTM Register Layout Typedef */
typedef struct {
    __IO uint32_t GCTRL;                              /**< Global Control Register, offset: 0x0000 */
    __IO uint32_t GINTACK;                            /**< Global Interrupt Acknowledge Register, offset: 0x0004 */
    __IO uint32_t RESERVED0[ 2];                      /**< RESERVED0, offset: 0x0008 */
    struct {
        __IO uint32_t SEL;                                /**< Monitor Channel Selection Register, offset: 0x0010 */
        __IO uint32_t THD;                                /**< Monitor Timer Threshold Register, offset: 0x0014 */
        __IO uint32_t TMR;                                /**< Monitor Timer Value Register, offset: 0x0018 */
        __I  uint32_t STS;                                /**< Monitor Status Register, offset: 0x001C */

    } MON[4];

} INTM_Type, *INTM_MemMapPtr;

/** Number of instances of the INTM module. */
#define INTM_INSTANCE_COUNT                            (1u)

/* INTM base address */
#define INTM_BASE                                         (0x40071000)
#define INTM                                              ((INTM_Type *)(INTM_BASE))

/** Array initializer of INTM peripheral base addresses */
#define INTM_BASE_ADDRS                                    { INTM_BASE }
/** Array initializer of INTM peripheral base pointers */
#define INTM_BASE_PTRS                                     { INTM }
/** Number of interrupt vector arrays for the INTM module. */
#define INTM_IRQS_ARR_COUNT                                (1u)
/** Number of interrupt channels for the INTM. */
#define INTM_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the INTM peripheral type */
#define INTM_IRQS                                 { INTM_IRQn }

/* INTM Register Mask */
/* INTM_GCTRL Register */
#define INTM_GCTRL_GEN_MASK                                 (0x1U)
#define INTM_GCTRL_GEN_SHIFT                                (0U)
#define INTM_GCTRL_GEN(x)                                   (((uint32_t)(((uint32_t)(x)) << INTM_GCTRL_GEN_SHIFT)) & INTM_GCTRL_GEN_MASK)
/* INTM_GINTACK Register */
#define INTM_GINTACK_SRC_WIDTH                              (10)
#define INTM_GINTACK_SRC_MASK                               (0x3FFU)
#define INTM_GINTACK_SRC_SHIFT                              (0U)
#define INTM_GINTACK_SRC(x)                                 (((uint32_t)(((uint32_t)(x)) << INTM_GINTACK_SRC_SHIFT)) & INTM_GINTACK_SRC_MASK)
/* INTM_MON_SEL Register */
#define INTM_MON_SEL_EN_MASK                                    (0x80000000U)
#define INTM_MON_SEL_EN_SHIFT                                   (31U)
#define INTM_MON_SEL_EN(x)                                      (((uint32_t)(((uint32_t)(x)) << INTM_MON_SEL_EN_SHIFT)) & INTM_MON_SEL_EN_MASK)
#define INTM_MON_SEL_IRQ_WIDTH                                  (10)
#define INTM_MON_SEL_IRQ_MASK                                   (0x3FFU)
#define INTM_MON_SEL_IRQ_SHIFT                                  (0U)
#define INTM_MON_SEL_IRQ(x)                                     (((uint32_t)(((uint32_t)(x)) << INTM_MON_SEL_IRQ_SHIFT)) & INTM_MON_SEL_IRQ_MASK)
/* INTM_MON_THD Register */
#define INTM_MON_THD_THRESHOLD_WIDTH                            (24)
#define INTM_MON_THD_THRESHOLD_MASK                             (0xFFFFFFU)
#define INTM_MON_THD_THRESHOLD_SHIFT                            (0U)
#define INTM_MON_THD_THRESHOLD(x)                               (((uint32_t)(((uint32_t)(x)) << INTM_MON_THD_THRESHOLD_SHIFT)) & INTM_MON_THD_THRESHOLD_MASK)
/* INTM_MON_TMR Register */
#define INTM_MON_TMR_CNT_WIDTH                                  (24)
#define INTM_MON_TMR_CNT_MASK                                   (0xFFFFFFU)
#define INTM_MON_TMR_CNT_SHIFT                                  (0U)
#define INTM_MON_TMR_CNT(x)                                     (((uint32_t)(((uint32_t)(x)) << INTM_MON_TMR_CNT_SHIFT)) & INTM_MON_TMR_CNT_MASK)
/* INTM_MON_STS Register */
#define INTM_MON_STS_OF_MASK                                    (0x1U)
#define INTM_MON_STS_OF_SHIFT                                   (0U)
#define INTM_MON_STS_OF(x)                                      (((uint32_t)(((uint32_t)(x)) << INTM_MON_STS_OF_SHIFT)) & INTM_MON_STS_OF_MASK)



/*!
 * @}
 */ /* end of group INTM_Register_Masks */


/*!
 * @}
 */ /* end of group INTM_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- PPU Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup PPU_Peripheral_Access_Layer PPU Peripheral Access Layer
 * @{
 */


/** PPU - Size of Registers Arrays */
#define PPU_SLOCK_COUNT                     (256)

/* PPU Register Layout Typedef */
typedef struct {
    __IO uint32_t RESERVED0[768];                      /**< RESERVED0, offset: 0x0000 */
    __IO uint8_t SLOCK[256];                          /**< Soft Lock Register, offset: 0x0C00 */
    __IO uint32_t RESERVED1[191];                      /**< RESERVED1, offset: 0x0C20 */
    __IO uint32_t PROTCFG;                            /**< Protect Configuration Register, offset: 0x0FFC */

} PPU_Type, *PPU_MemMapPtr;

/** Number of instances of the PPU module. */
#define PPU_INSTANCE_COUNT                             (1u)


/** Array initializer of PPU peripheral base addresses */
#define PPU_BASE_ADDRS                                     { }
/** Array initializer of PPU peripheral base pointers */
#define PPU_BASE_PTRS                                      { }

/* PPU Register Mask */
/* PPU_SLOCK Register */
#define PPU_SLOCK_WREN_MASK                                (0x10U)
#define PPU_SLOCK_WREN_SHIFT                               (4U)
#define PPU_SLOCK_WREN(x)                                  (((uint32_t)(((uint32_t)(x)) << PPU_SLOCK_WREN_SHIFT)) & PPU_SLOCK_WREN_MASK)
#define PPU_SLOCK_LOCKBIT_MASK                             (0x1U)
#define PPU_SLOCK_LOCKBIT_SHIFT                            (0U)
#define PPU_SLOCK_LOCKBIT(x)                               (((uint32_t)(((uint32_t)(x)) << PPU_SLOCK_LOCKBIT_SHIFT)) & PPU_SLOCK_LOCKBIT_MASK)
/* PPU_PROTCFG Register */
#define PPU_PROTCFG_UAE_MASK                               (0x100U)
#define PPU_PROTCFG_UAE_SHIFT                              (8U)
#define PPU_PROTCFG_UAE(x)                                 (((uint32_t)(((uint32_t)(x)) << PPU_PROTCFG_UAE_SHIFT)) & PPU_PROTCFG_UAE_MASK)
#define PPU_PROTCFG_HLOCK_MASK                             (0x1U)
#define PPU_PROTCFG_HLOCK_SHIFT                            (0U)
#define PPU_PROTCFG_HLOCK(x)                               (((uint32_t)(((uint32_t)(x)) << PPU_PROTCFG_HLOCK_SHIFT)) & PPU_PROTCFG_HLOCK_MASK)


/*!
 * @}
 */ /* end of group PPU_Register_Masks */


/*!
 * @}
 */ /* end of group PPU_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- WDG Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup WDG_Peripheral_Access_Layer WDG Peripheral Access Layer
 * @{
 */


/** WDG - Size of Registers Arrays */

/* WDG Register Layout Typedef */
typedef struct {
    __IO uint32_t SVCR;                               /**< Service Code Register, offset: 0x0000 */
    __IO uint32_t CR;                                 /**< Control Register, offset: 0x0004 */
    __IO uint32_t LR;                                 /**< Lock Register, offset: 0x0008 */
    __IO uint32_t TOVR;                               /**< Timer Overflow Value, offset: 0x000C */
    __IO uint32_t WVR;                                /**< Window Value Register, offset: 0x0010 */
    __IO uint32_t CNTCVR;                             /**< Counter Current Value Register, offset: 0x0014 */
    __IO uint32_t INTF;                               /**< Interrupt Flag register, offset: 0x0018 */

} WDG_Type, *WDG_MemMapPtr;

/** Number of instances of the WDG module. */
#define WDG_INSTANCE_COUNT                             (1u)

/* WDG base address */
#define WDG_BASE                                          (0x4006A000)
#define WDG                                               ((WDG_Type *)(WDG_BASE))

/** Array initializer of WDG peripheral base addresses */
#define WDG_BASE_ADDRS                                     { WDG_BASE }
/** Array initializer of WDG peripheral base pointers */
#define WDG_BASE_PTRS                                      { WDG }
/** Number of interrupt vector arrays for the WDG module. */
#define WDG_IRQS_ARR_COUNT                                 (1u)
/** Number of interrupt channels for the WDG. */
#define WDG_IRQS_CH_COUNT                         (1u)
/** Interrupt vectors for the WDG peripheral type */
#define WDG_IRQS                                  { WDG_IRQn }

/* WDG Register Mask */
/* WDG_SVCR Register */
#define WDG_SVCR_SVCODE_MASK                               (0xFFFFU)
#define WDG_SVCR_SVCODE_SHIFT                              (0U)
#define WDG_SVCR_SVCODE(x)                                 (((uint32_t)(((uint32_t)(x)) << WDG_SVCR_SVCODE_SHIFT)) & WDG_SVCR_SVCODE_MASK)
/* WDG_CR Register */
#define WDG_CR_RIA_MASK                                    (0x40U)
#define WDG_CR_RIA_SHIFT                                   (6U)
#define WDG_CR_RIA(x)                                      (((uint32_t)(((uint32_t)(x)) << WDG_CR_RIA_SHIFT)) & WDG_CR_RIA_MASK)
#define WDG_CR_WIN_MASK                                    (0x20U)
#define WDG_CR_WIN_SHIFT                                   (5U)
#define WDG_CR_WIN(x)                                      (((uint32_t)(((uint32_t)(x)) << WDG_CR_WIN_SHIFT)) & WDG_CR_WIN_MASK)
#define WDG_CR_IBR_MASK                                    (0x10U)
#define WDG_CR_IBR_SHIFT                                   (4U)
#define WDG_CR_IBR(x)                                      (((uint32_t)(((uint32_t)(x)) << WDG_CR_IBR_SHIFT)) & WDG_CR_IBR_MASK)
#define WDG_CR_CLKSRC_MASK                                 (0x8U)
#define WDG_CR_CLKSRC_SHIFT                                (3U)
#define WDG_CR_CLKSRC(x)                                   (((uint32_t)(((uint32_t)(x)) << WDG_CR_CLKSRC_SHIFT)) & WDG_CR_CLKSRC_MASK)
#define WDG_CR_DSDIS_MASK                                  (0x4U)
#define WDG_CR_DSDIS_SHIFT                                 (2U)
#define WDG_CR_DSDIS(x)                                    (((uint32_t)(((uint32_t)(x)) << WDG_CR_DSDIS_SHIFT)) & WDG_CR_DSDIS_MASK)
#define WDG_CR_DBGDIS_MASK                                 (0x2U)
#define WDG_CR_DBGDIS_SHIFT                                (1U)
#define WDG_CR_DBGDIS(x)                                   (((uint32_t)(((uint32_t)(x)) << WDG_CR_DBGDIS_SHIFT)) & WDG_CR_DBGDIS_MASK)
#define WDG_CR_EN_MASK                                     (0x1U)
#define WDG_CR_EN_SHIFT                                    (0U)
#define WDG_CR_EN(x)                                       (((uint32_t)(((uint32_t)(x)) << WDG_CR_EN_SHIFT)) & WDG_CR_EN_MASK)
/* WDG_LR Register */
#define WDG_LR_HL_MASK                                     (0x2U)
#define WDG_LR_HL_SHIFT                                    (1U)
#define WDG_LR_HL(x)                                       (((uint32_t)(((uint32_t)(x)) << WDG_LR_HL_SHIFT)) & WDG_LR_HL_MASK)
#define WDG_LR_SL_MASK                                     (0x1U)
#define WDG_LR_SL_SHIFT                                    (0U)
#define WDG_LR_SL(x)                                       (((uint32_t)(((uint32_t)(x)) << WDG_LR_SL_SHIFT)) & WDG_LR_SL_MASK)
/* WDG_TOVR Register */
#define WDG_TOVR_TO_MASK                                   (0xFFFFFFFFU)
#define WDG_TOVR_TO_SHIFT                                  (0U)
#define WDG_TOVR_TO(x)                                     (((uint32_t)(((uint32_t)(x)) << WDG_TOVR_TO_SHIFT)) & WDG_TOVR_TO_MASK)
/* WDG_WVR Register */
#define WDG_WVR_WIN_MASK                                   (0xFFFFFFFFU)
#define WDG_WVR_WIN_SHIFT                                  (0U)
#define WDG_WVR_WIN(x)                                     (((uint32_t)(((uint32_t)(x)) << WDG_WVR_WIN_SHIFT)) & WDG_WVR_WIN_MASK)
/* WDG_CNTCVR Register */
#define WDG_CNTCVR_CVAL_MASK                               (0xFFFFFFFFU)
#define WDG_CNTCVR_CVAL_SHIFT                              (0U)
#define WDG_CNTCVR_CVAL(x)                                 (((uint32_t)(((uint32_t)(x)) << WDG_CNTCVR_CVAL_SHIFT)) & WDG_CNTCVR_CVAL_MASK)
/* WDG_INTF Register */
#define WDG_INTF_IF_MASK                                   (0x1U)
#define WDG_INTF_IF_SHIFT                                  (0U)
#define WDG_INTF_IF(x)                                     (((uint32_t)(((uint32_t)(x)) << WDG_INTF_IF_SHIFT)) & WDG_INTF_IF_MASK)


/*!
 * @}
 */ /* end of group WDG_Register_Masks */


/*!
 * @}
 */ /* end of group WDG_Peripheral_Access_Layer */


/* -------------------------------------------------------------
   -- EWDG Peripheral Access Layer
   ------------------------------------------------------------- */

/*!
 * @addtogroup EWDG_Peripheral_Access_Layer EWDG Peripheral Access Layer
 * @{
 */


/** EWDG - Size of Registers Arrays */

/* EWDG Register Layout Typedef */
typedef struct {
    __IO uint32_t SERV;                               /**< Service Code Register, offset: 0x0000 */
    __O  uint32_t CMPL;                               /**< Compare Low Register, offset: 0x0004 */
    __O  uint32_t CMPH;                               /**< Compare High Register, offset: 0x0008 */
    __IO uint32_t CTRL;                               /**< Control Register, offset: 0x000C */
    __IO uint32_t CLK_CTRL;                           /**< Clock Control Register, offset: 0x0010 */

} EWDG_Type, *EWDG_MemMapPtr;

/** Number of instances of the EWDG module. */
#define EWDG_INSTANCE_COUNT                            (1u)

/* EWDG base address */
#define EWDG_BASE                                         (0x4006B000)
#define EWDG                                              ((EWDG_Type *)(EWDG_BASE))

/** Array initializer of EWDG peripheral base addresses */
#define EWDG_BASE_ADDRS                                    { EWDG_BASE }
/** Array initializer of EWDG peripheral base pointers */
#define EWDG_BASE_PTRS                                     { EWDG }
/** Number of interrupt vector arrays for the EWDG module. */
#define EWDG_IRQS_ARR_COUNT                                (1u)
/** Number of interrupt channels for the EWDG. */
#define EWDG_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the EWDG peripheral type */
#define EWDG_IRQS                                 { EWDG_IRQn }

/* EWDG Register Mask */
/* EWDG_SERV Register */
#define EWDG_SERV_SERVICE_MASK                              (0xFFU)
#define EWDG_SERV_SERVICE_SHIFT                             (0U)
#define EWDG_SERV_SERVICE(x)                                (((uint32_t)(((uint32_t)(x)) << EWDG_SERV_SERVICE_SHIFT)) & EWDG_SERV_SERVICE_MASK)
/* EWDG_CMPL Register */
#define EWDG_CMPL_COMPAREL_MASK                             (0xFFU)
#define EWDG_CMPL_COMPAREL_SHIFT                            (0U)
#define EWDG_CMPL_COMPAREL(x)                               (((uint32_t)(((uint32_t)(x)) << EWDG_CMPL_COMPAREL_SHIFT)) & EWDG_CMPL_COMPAREL_MASK)
/* EWDG_CMPH Register */
#define EWDG_CMPH_COMPAREH_MASK                             (0xFFU)
#define EWDG_CMPH_COMPAREH_SHIFT                            (0U)
#define EWDG_CMPH_COMPAREH(x)                               (((uint32_t)(((uint32_t)(x)) << EWDG_CMPH_COMPAREH_SHIFT)) & EWDG_CMPH_COMPAREH_MASK)
/* EWDG_CTRL Register */
#define EWDG_CTRL_INTEN_MASK                                (0x8U)
#define EWDG_CTRL_INTEN_SHIFT                               (3U)
#define EWDG_CTRL_INTEN(x)                                  (((uint32_t)(((uint32_t)(x)) << EWDG_CTRL_INTEN_SHIFT)) & EWDG_CTRL_INTEN_MASK)
#define EWDG_CTRL_INEN_MASK                                 (0x4U)
#define EWDG_CTRL_INEN_SHIFT                                (2U)
#define EWDG_CTRL_INEN(x)                                   (((uint32_t)(((uint32_t)(x)) << EWDG_CTRL_INEN_SHIFT)) & EWDG_CTRL_INEN_MASK)
#define EWDG_CTRL_POLARITY_MASK                             (0x2U)
#define EWDG_CTRL_POLARITY_SHIFT                            (1U)
#define EWDG_CTRL_POLARITY(x)                               (((uint32_t)(((uint32_t)(x)) << EWDG_CTRL_POLARITY_SHIFT)) & EWDG_CTRL_POLARITY_MASK)
#define EWDG_CTRL_EN_MASK                                   (0x1U)
#define EWDG_CTRL_EN_SHIFT                                  (0U)
#define EWDG_CTRL_EN(x)                                     (((uint32_t)(((uint32_t)(x)) << EWDG_CTRL_EN_SHIFT)) & EWDG_CTRL_EN_MASK)
/* EWDG_CLK_CTRL Register */
#define EWDG_CLK_CTRL_CLKSEL_MASK                           (0x10000U)
#define EWDG_CLK_CTRL_CLKSEL_SHIFT                          (16U)
#define EWDG_CLK_CTRL_CLKSEL(x)                             (((uint32_t)(((uint32_t)(x)) << EWDG_CLK_CTRL_CLKSEL_SHIFT)) & EWDG_CLK_CTRL_CLKSEL_MASK)
#define EWDG_CLK_CTRL_PRESCALER_MASK                        (0xFFU)
#define EWDG_CLK_CTRL_PRESCALER_SHIFT                       (0U)
#define EWDG_CLK_CTRL_PRESCALER(x)                          (((uint32_t)(((uint32_t)(x)) << EWDG_CLK_CTRL_PRESCALER_SHIFT)) & EWDG_CLK_CTRL_PRESCALER_MASK)


/*!
 * @}
 */ /* end of group EWDG_Register_Masks */


/*!
 * @}
 */ /* end of group EWDG_Peripheral_Access_Layer */




/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer for YTM32B1ME0
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer_YTM32B1L Device Peripheral Access Layer for YTM32B1ME0
 * @{
 */

/* @brief This module covers memory mapped registers available on SoC */

/* ----------------------------------------------------------------------------
   -- Backward Compatibility for YTM32B1ME0
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols_YTM32B1ME0 Backward Compatibility for YTM32B1ME0
 * @{
 */

/* No backward compatibility issues. */

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols_YTM32B1ME0 */


#else /* #if !defined(YTM32B1ME0_H_) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(YTM32B1ME0_H_) */

/* YTM32B1ME0.h, eof. */
/*******************************************************************************
* EOF
*******************************************************************************/
