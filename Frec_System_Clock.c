/**
**	\file 	Frec_System_Clock.c
**	\brief
**		Driver file have FRDM-K64F running at 60 MHz
 *  Created on: 01/05/2022
 *      Author: Mauricio Peralta
**/

#include "Frec_System_Clock.h"

uint8_t prd = 0xeU;
uint8_t vdl = 0xCU;

void Frec_SC(void){
	mcg_pll_config_t pll0config =
	{
			.enableMode = MCG_PLL_DISABLE,
			.prdiv = prd,
			.vdiv = vdl,
	};

	const osc_config_t osc_config =
	{
			.freq = OSC_FREC,
			.capLoad = (OSC_CAP0P),
			.workMode = kOSC_ModeExt,
			.oscerConfig ={
					.enableMode = kOSC_ErClkEnable,
			}
	};

	CLOCK_SetSimSafeDivs();
	CLOCK_InitOsc0(&osc_config);
	CLOCK_SetXtal0Freq(osc_config.freq);

	CLOCK_SetFbiMode(kMCG_Dmx32Default,kMCG_DrsLow,NULL);
	CLOCK_SetFbeMode(0,kMCG_Dmx32Default,kMCG_DrsLow,NULL);
	CLOCK_SetPbeMode(kMCG_PllClkSelPll0,&pll0config);
	CLOCK_SetPeeMode();
}
