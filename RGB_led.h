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
