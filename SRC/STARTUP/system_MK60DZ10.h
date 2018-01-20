/*
** ###################################################################
**     Processors:          MK60DN512ZVLL10
**                          MK60DX256ZVLL10
**                          MK60DN256ZVLL10
**                          MK60DN512ZVLQ10
**                          MK60DN256ZVLQ10
**                          MK60DX256ZVLQ10
**                          MK60DN512ZVMC10
**                          MK60DN256ZVMC10
**                          MK60DX256ZVMC10
**                          MK60DN512ZVMD10
**                          MK60DX256ZVMD10
**                          MK60DN256ZVMD10
**
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K60P144M100SF2RM, Rev. 5, 8 May 2011
**     Version:             rev. 1.2, 2011-09-08
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2011-06-10)
**         Initial version.
**         Changes with respect to the previous MK60NxxxMD100 header file:
**         RTC  - CCR register removed. Replaced by IER register.
**         CRC  - added CTRLHU register for 8-bit access to the CTRL register.
**         FB   - bit FB_CSCR_EXALE renamed to FB_CSCR_EXTS.
**         SIM  - bit group FSIZE in SIM_FCFG1 split into groups PFSIZE and NVMSIZE.
**         I2S  - bit SSIEN in I2S_CR register renamed to I2SEN.
**         SDHC - bit VOLTSEL in SDHC_VENDOR register removed.
**     - rev. 1.1 (2011-06-29)
**         Order of declarations changed.
**     - rev. 1.2 (2011-09-08)
**         Cortex_Core_Configuration extended with additional parameters.
**         Gap between end of interrupt vector table and flash configuration field filled by default ISR.
**
** ###################################################################
*/

/**
 * @file MK60DZ10
 * @version 1.2
 * @date 2011-09-08
 * @brief Device specific configuration file for MK60DZ10 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef SYSTEM_MK60DZ10_H_
#define SYSTEM_MK60DZ10_H_                       /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_MK60DZ10_H_) */
