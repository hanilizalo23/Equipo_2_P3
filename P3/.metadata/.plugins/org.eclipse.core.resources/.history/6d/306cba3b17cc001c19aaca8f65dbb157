/**
	\file 	RGB_led.h
	\brief
	 	This source file contains the functions to manipulate an external RGB led.
	\author Nelida Hernández
	\date	01/05/2022
 **/

#ifndef RGB_LED_H_
#define RGB_LED_H_


#include "MK64F12.h"
#include "FlexTimer.h"

/*Period of 1/500 (for PMW to control the RGB). Since we are using the system clock divided by 1,
 * MOD = (1/500) / (1/60000000)*/
#define FTM_CHV_RGB_INIT 	(0U)
#define FTM_MOD_RGB 		(41820U)  	//Multiple of 255 to make the levels division easier
#define FTM_MOD_500HZ		(42000U)	//To get approximately 500Hz, 0.002s

//Channels for each color
#define BLUE_CH 	CH_0
#define RED_CH		CH_1
#define GREEN_CH	CH_2

#define RGB_MANUAL_BR_CHANGE (4182U) 	//FTM_MOD_RGB/10 (10%)
//For intensity levels
#define RGB_INTENSITY_MAX	(255U)
#define RGB_INTENSITY_MIN	(0U)
#define RGB_INTENSITY_GAIN (164U)
//For PH levels convertions
#define PH_LEVELS_MAX (14U)
#define MAX_FREQ_PH   (10000U)
//Number of repetitions to get 1 second
#define COUNTS_ONE_SEC	(350000U)
//ADC constants needed
#define ADC_OFFSET		(40U)
#define ADC_INCREMENT	(0.01961F)
#define ADC_3_3_VOLTS	(168U)
#define ADC_LVLS_PER_PH	(12U)
#define ADC_SAMPLES_MAX (500U)
#define ADC_INT_FACTOR	(10U)
#define ADC_DIGS_NUMBER	(2U)

//Basic colors of RGB
typedef enum
{
	RED,
	GREEN,
	BLUE
}color_value_t;

//Colors to get on the sequence
typedef enum
{
	NONE_RGB,
	BLUE_RGB,
	RED_RGB,
	GREEN_RGB,
	YELLOW_RGB,
	PURPLE_RGB,
	WHITE_RGB
}color_sequence_t;

//To know if the bright must be increased or decreased
typedef enum
{
	INCREASE,
	DECREASE
}increase_or_decrease_br_t;

//To choose whether the RGB sequence stops after ending the last color period, or it continues
typedef enum
{
	CONTINUE_SEQ,
	STOP_SEQ
}continue_seq_t;

//Structures to store the chosen FTM and channels for RGB
typedef struct
{
	uint8_t ftm;
	uint8_t channel;
}rgb_bright_change_t;

//Structure to store the RGB code
typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}rgb_intensity_colors_t;


#endif /* RGB_LED_H_ */
