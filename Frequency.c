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
{}

/*To stop the signal*/
void Generate_trial_signal_stop(void)
{}

/*Functions to read frequency*/
void Frequency_read_initilize(void)
{}

