/**
	\file 	RGB_led.c
	\brief
	 	This source file contains the functions to manipulate an external RGB led.
	\author Nelida Hernández
	\date	01/05/2022
 **/

#include <stdio.h>
#include "RGB_led.h"
#include "FlexTimer.h"
#include "GPIO.h"
#include "Bits.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "ADC.h"
#include "MainMenu.h"
#include "LCD_nokia.h"

#define RESO 1U

//Counter to get 1 second
static uint32_t g_counter_1s = 0x00;
//Counter for the sequence of submenu 3
static uint16_t g_sequence_counter = 0x00;
//Variable that stores the total value of colors in the sequence
static uint16_t g_sequence_total = 0x00;
//Stores the colors in the sequence to use them on callbacks.
static color_sequence_t *g_colors_seq = 0x00;
//Stores if the sequence is specified to be stopped
static continue_seq_t g_stop_flag = FALSE;
//Counter for the ADC samples
static uint16_t g_adc_samples_counter = 0x00;
//Array that stores the ADC samples
static uint16_t g_adc_samples[ADC_SAMPLES_MAX] = {0};
/*FSM for bright change on each color*/

const rgb_bright_change_t Change_br_rgb[3]=
{
	{FTM_0, RED_CH},
	{FTM_0, GREEN_CH},
	{FTM_0, BLUE_CH}
};

/*Configurations for FTM for the RGB control signal and to get the 1s delays*/
const ftm_channel_config_t g_configure_ftm_rgb =
{
	EDGE_ALLIGNED_HT,			//uint32_t ftm_mode;
	FTM_CHV_RGB_INIT,			//uint16_t ftm_value;
	DISABLE,					//channel_enable_t ftm_enable_deadtime;
	DISABLE,					//channel_enable_t ftm_enable_complement;
	DISABLE,					//channel_enable_t ftm_enable_combine;
	0x00,						//uint8_t ftm_dtval;
	FLEX_TIMER_CLKS_1,			//uint8_t ftm_clocks;
	FLEX_TIMER_PS_1,			//uint8_t ftm_prescaler;
	DISABLE,					//channel_enable_t ftm_enable_toie;
	DISABLE
};

const ftm_channel_config_t g_configure_rgb_1s =
{
	EDGE_ALLIGNED_HT,			//uint32_t ftm_mode;
	FTM_CHV_RGB_INIT,			//uint16_t ftm_value;
	DISABLE,					//channel_enable_t ftm_enable_deadtime;
	DISABLE,					//channel_enable_t ftm_enable_complement;
	DISABLE,					//channel_enable_t ftm_enable_combine;
	0x00,						//uint8_t ftm_dtval;
	FLEX_TIMER_CLKS_1,			//uint8_t ftm_clocks;
	FLEX_TIMER_PS_1,			//uint8_t ftm_prescaler;
	DISABLE,					//channel_enable_t ftm_enable_toie;
	ENABLE
};

//Values per color (RGB codes) of the colors in the PH scale
const rgb_intensity_colors_t g_ph_scale[15] =
{
	{0, 	0, 	 	0},				//0
	{255, 	0, 	 	0},				//1
	{255, 	69, 	0},				//2
	{218, 	165, 	32},			//3
	{255, 	255, 	0},				//4
	{200, 	245, 	10},			//5
	{150, 	201, 	2},				//6
	{21, 	149, 	2},				//7
	{127, 	255, 	212},			//8
	{0, 	255, 	255},			//9
	{0, 	192, 	255},			//10
	{1, 	90, 	255},			//11
	{4, 	31, 	196},			//12
	{148, 	0, 		211},			//13
	{75, 	0, 		130}			//14
};

//RGB codes of the colors for the sequence
rgb_intensity_colors_t g_sequence_rgb_code[7] =
{
		{0,		0,		0	},			//NONE
		{0, 	0, 	 	255	},			//BLUE
		{255, 	0, 	 	0	},			//RED
		{0, 	255, 	0	},			//GREEN
		{255, 	255, 	0	},			//YELLOW
		{255, 	0, 		255	},			//PURPLE
		{255, 	255, 	255	},			//WHITE
};

/*Initialization and general use functions*/
void RGB_led_initialize(void)
{
	/*Configure FTM0 for RGB*/
	FlexTimer_clock_gating(FTM_0);
	FlexTimer_set_mod(FTM_0,FTM_MOD_RGB);
	FlexTimer_configure_channel(FTM_0,BLUE_CH,&g_configure_ftm_rgb);
	FlexTimer_configure_channel(FTM_0,RED_CH,&g_configure_ftm_rgb);
	FlexTimer_configure_channel(FTM_0,GREEN_CH,&g_configure_ftm_rgb);
}

void RGB_led_turn_off(void)
{
	FlexTimer_change_cnv(FTM_0,RED_CH,FTM_CHV_RGB_INIT);
	FlexTimer_change_cnv(FTM_0,GREEN_CH,FTM_CHV_RGB_INIT);
	FlexTimer_change_cnv(FTM_0,BLUE_CH,FTM_CHV_RGB_INIT);
}

uint16_t RGB_led_intensity_to_duty_cycle(uint8_t intensity)
{
	uint16_t duty_cycle = intensity * RGB_INTENSITY_GAIN;
	return(duty_cycle);
}

uint8_t RGB_led_duty_cycle_to_intensity(uint16_t duty_cycle)
{
	uint8_t intensity = duty_cycle / RGB_INTENSITY_GAIN;
	return(intensity);
}

void RGB_led_set_color(rgb_intensity_colors_t *rgb_code)
{
	//Obtains duty cycle from intensity value
	uint16_t duty_cycle_red =  RGB_led_intensity_to_duty_cycle(rgb_code->red);
	uint16_t duty_cycle_green =  RGB_led_intensity_to_duty_cycle(rgb_code->green);
	uint16_t duty_cycle_blue =  RGB_led_intensity_to_duty_cycle(rgb_code->blue);
	//Modifies CnV in each channel
	FlexTimer_change_cnv(FTM_0, RED_CH, duty_cycle_red);
	FlexTimer_change_cnv(FTM_0, GREEN_CH, duty_cycle_green);
	FlexTimer_change_cnv(FTM_0, BLUE_CH, duty_cycle_blue);
}

void RGB_led_ph_color(uint8_t ph_level)
{
	rgb_intensity_colors_t rgb_code;
	//To avoid problems
	if(PH_LEVELS_MAX < ph_level)
	{
		ph_level = PH_LEVELS_MAX;
	}
	//Searches the level on the array
	rgb_code = g_ph_scale[ph_level];
	RGB_led_set_color(&rgb_code);
}
