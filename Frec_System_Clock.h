/**
**	\file 	Frec_System_Clock.h
**	\brief
**		Driver file have FRDM-K64F running at 60 MHz
 *  Created on: 01/05/2022
 *      Author: Mauricio Peralta
**/

#ifndef FREC_SYSTEM_CLOCK_H_
#define FREC_SYSTEM_CLOCK_H_


#include <stdio.h>
#include "MK64F12.h"
#include "fsl_clock.h"

//Definitions
#define MCG_IRCLK_DISABLE 0U                   /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE 0U                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                           /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U                  /*!< Disable external reference clock */
#define SIM_CLKOUT_SEL_FLEXBUS_CLK 0U          /*!< CLKOUT pin clock select: FlexBus clock */
#define SIM_ENET_1588T_CLK_SEL_OSCERCLK_CLK 2U /*!< SDHC clock select: OSCERCLK clock */
#define SIM_ENET_RMII_CLK_SEL_EXTAL_CLK 0U     /*!< SDHC clock select: Core/system clock */
#define SIM_OSC32KSEL_RTC32KCLK_CLK 2U         /*!< OSC32KSEL select: RTC32KCLK clock (32.768kHz) */
#define SIM_PLLFLLSEL_IRC48MCLK_CLK 3U         /*!< PLLFLL select: IRC48MCLK clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK 1U         /*!< PLLFLL select: MCGPLLCLK clock */
#define SIM_SDHC_CLK_SEL_OSCERCLK_CLK 2U       /*!< SDHC clock select: OSCERCLK clock */
#define SIM_TRACE_CLK_SEL_CORE_SYSTEM_CLK 1U   /*!< Trace clock select: Core/system clock */
#define SIM_USB_CLK_120000000HZ 120000000U     /*!< Input SIM frequency for USB: 120000000Hz */

#define OSC_FREC 		25000000U

/* This function configures the clock for the Board K64 */
void Frec_SC(void);


#endif /* FREC_SYSTEM_CLOCK_H_ */
