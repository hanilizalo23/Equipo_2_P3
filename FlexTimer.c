/**
	\file 	FlexTimer.c
	\brief
	 	Device driver for the FlexTimer. It contains the functions to
	 	configure and manipulate each FTM.
	\author Mauricio Peralta
	\date	01/05/2022
 **/

#include "FlexTimer.h"
#include "MK64F12.h"
#include "Bits.h"
#include "GPIO.h"
#include "stdio.h"

#define NOTHING 0U

static void (*ftm_0_callback)(void) = NOTHING;
static void (*ftm_1_callback)(void) = NOTHING;
static void (*ftm_2_callback)(void) = NOTHING;
static void (*ftm_3_callback)(void) = NOTHING;

void FlexTimer_clock_gating(ftm_name_t flextimer)
{
	switch(flextimer)
	{
		case FTM_0:
			SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
			break;
		case FTM_1:
			SIM->SCGC6 |= SIM_SCGC6_FTM1(1);
			break;
		case FTM_2:
			SIM->SCGC6 |= SIM_SCGC6_FTM2(1);
			break;
		default:
			SIM->SCGC3 |= SIM_SCGC3_FTM3(1);
			break;
	}
}

void FlexTimer_configure_channel(ftm_name_t flextimer, ftm_channel_name_t channel, const ftm_channel_config_t *ch_configuration)
{
	switch(flextimer)
	{
		case FTM_0:
			FTM0_configure_ch(channel,ch_configuration);
			break;
		case FTM_1:
			FTM1_configure_ch(channel,ch_configuration);
			break;
		case FTM_2:
			FTM2_configure_ch(channel,ch_configuration);
			break;
		default:
			FTM3_configure_ch(channel,ch_configuration);
			break;
	}
}

void FlexTimer_set_mod(ftm_name_t flextimer,uint16_t value)
{
	switch(flextimer)
	{
		case FTM_0:
			FTM0->MOD = value;
			break;
		case FTM_1:
			FTM1->MOD = value;
			break;
		case FTM_2:
			FTM2->MOD = value;
			break;
		default:
			FTM3->MOD = value;
			break;
	}
}

void FlexTimer_change_cnv(ftm_name_t flextimer,ftm_channel_name_t channel,uint16_t value)
{}
