/**
	\file 	Frequency.c
	\brief
	 	API that contains functions to allow the FTM2 CH0 to read frequencies
	 	and the FTM3 CH4 to generate a signal.
	\author Mauricio Peralta
	\date	01/05/2022
 **/

#include "Frequency.h"
#include <stdio.h>
#include "RGB_led.h"
#include "FlexTimer.h"
#include "GPIO.h"
#include "Bits.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "RGB_led.h"
#include "LCD_nokia.h"

#define NOTHING 0U

/*Variables to obtain the CnV period of the input signal*/
static uint32_t g_tempPrev = 0x0000;
static uint32_t g_temp = 0x0000;
static uint32_t g_diff;

/*Stores many samples of the frequency to obtain an average and more precise frequency*/
static float g_frequency[FREQ_TOTAL_SAMPLES] = {(0.00F)};

static uint32_t g_freq_sample = NOTHING;

uint8_t g_str_khz[] = "KHz";
uint8_t g_str_hz[] = "Hz";

/*Configurations of the FTM for frequency reading and wave generator*/
const ftm_channel_config_t g_configure_ftm_freq =
{
	INPUT_CAPTURE_RE,			//uint32_t ftm_mode;
	0x000,						//uint16_t ftm_value;
	DISABLE,					//channel_enable_t ftm_enable_deadtime;
	DISABLE,					//channel_enable_t ftm_enable_complement;
	DISABLE,					//channel_enable_t ftm_enable_combine;
	0x00,						//uint8_t ftm_dtval;
	FLEX_TIMER_CLKS_1,			//uint8_t ftm_clocks;
	FLEX_TIMER_PS_1,			//uint8_t ftm_prescaler;
	DISABLE,					//channel_enable_t ftm_enable_toie;
	ENABLE						//channel_enable_t ftm_enable_interrupt;
};

const ftm_channel_config_t g_configure_ftm_pwm =
{
	EDGE_ALLIGNED_HT,			//uint32_t ftm_mode;
	0x0000,						//uint16_t ftm_value;
	DISABLE,					//channel_enable_t ftm_enable_deadtime;
	DISABLE,					//channel_enable_t ftm_enable_complement;
	DISABLE,					//channel_enable_t ftm_enable_combine;
	0x00,						//uint8_t ftm_dtval;
	FLEX_TIMER_CLKS_1,			//uint8_t ftm_clocks;
	FLEX_TIMER_PS_1,			//uint8_t ftm_prescaler;
	DISABLE,					//channel_enable_t ftm_enable_toie;
	DISABLE
};

/*Functions to generate a square wave*/
void Generate_trial_signal(void)
{
	/*Configure FTM3 CH4*/
	uint16_t mod_freq = 2100;
	FlexTimer_clock_gating(FTM_3);
	FlexTimer_set_mod(FTM_3,mod_freq);
	FlexTimer_configure_channel(FTM_3,CH_4,&g_configure_ftm_pwm);
	FlexTimer_change_cnv(FTM_3,CH_4,mod_freq/2);
}

void Increase_or_decrease_freq(increase_or_dicrease_frq_t increase_or_dicrease, float change_value)
{
	/*Obtain the actual frequency value*/
	float actual_freq_value = SYSTEM_CLOCK_FTM / (float)get_mod_value(FTM_3);
	float new_freq_value;
	uint32_t new_mod_value;
	/*Changes value (still in Hertz)*/
	switch(increase_or_dicrease)
	{
	case INCREASE_FRQ:
		new_freq_value = actual_freq_value + change_value;
		break;
	default:
		/*Verifies that the final value is not less than 0*/
		if(actual_freq_value <= change_value)
		{
			new_freq_value = actual_freq_value;
		}
		new_freq_value = actual_freq_value - change_value;
		break;
	}
	//Convert increment/decrement frequency to mod
	new_mod_value = (uint32_t)(SYSTEM_CLOCK_FTM / new_freq_value);
	if(MAX_MOD_VALUE < new_mod_value)
	{
		new_mod_value = MAX_MOD_VALUE;
	}
	FlexTimer_set_mod(FTM_3,(uint16_t)new_mod_value);
	FlexTimer_change_cnv(FTM_3,CH_4,new_mod_value/2);
}

/*To stop the signal*/
void Generate_trial_signal_stop(void)
{}

/*Functions to read frequency*/
void Frequency_read_initilize(void)
{}
