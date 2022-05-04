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


#define OSC_FREC 		25000000U

/* This function configures the clock for the Board K64 */
void Frec_SC(void);


#endif /* FREC_SYSTEM_CLOCK_H_ */
