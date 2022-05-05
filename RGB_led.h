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

/*Initialization and general use functions*/
/********************************************************************************************/
/*!
 	 \brief	 Initializes the FTM0 channels for the RGB control.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_initialize(void);
/********************************************************************************************/
/*!
 	 \brief	 Turns off the RGB led.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_turn_off(void);
/********************************************************************************************/
/*!
 	 \brief	 Transforms the intensity (0 to 255 value) to the CnV needed for the RGB.
 	 \param[in]  uint8_t intensity = brightness value.
 	 \return uint16_t duty cycle needed
 */
uint16_t RGB_led_intensity_to_duty_cycle(uint8_t intensity);
/********************************************************************************************/
/*!
 	 \brief	 Transforms the CnV to a value from 0 to 255 (intensity).
 	 \param[in]  uint16_t duty cycle.
 	 \return uint8_t intensity.
 */
uint8_t RGB_led_duty_cycle_to_intensity(uint16_t duty_cycle);
/********************************************************************************************/
/*!
 	 \brief	 Changes the bright of each color according to the RGB code.
 	 \param[in]  rgb_intensity_colors_t *rgb_code = RGB code of the color.
 	 \return void
 */
void RGB_led_set_color(rgb_intensity_colors_t *rgb_code);
/********************************************************************************************/
/*!
 	 \brief	 Turns the RGB led on the color associated with the ph level.
 	 \param[in]  uint8_t ph level.
 	 \return void
 */
void RGB_led_ph_color(uint8_t ph_level);

/*For submenu 1: Manual*/
/********************************************************************************************/
/*!
 	 \brief	 Modifies the bright of the chosen color.
 	 \param[in]  color_value_t color = color that must be modified.
 	 \param[in]	 uint16_t value = how much it increases/decreases (the duty cycle).
 	 \param[in]	 increase_or_decrease_br_t option = to choose if the bright decreases or
 	 	 	 	 increases.
 	 \return intensity = the new value on a range of 0 to 255.
 */
uint8_t RGB_led_change_bright(color_value_t color,uint16_t value,increase_or_decrease_br_t option);

/*For submenu 2: ADC*/
/********************************************************************************************/
/*!
 	 \brief	 Initializes ADC reading and conversion.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_adc_init(void);
/********************************************************************************************/
/*!
 	 \brief	 Interruption to read the ADC.
 	 \param[in]  void.
 	 \return void
 */
void read_adc(void);
/********************************************************************************************/
/*!
 	 \brief	 Deactivates the FTM1 CH1 to stop the ADC reading.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_adc_stop(void);

/*For submenu 3: Sequence*/
/********************************************************************************************/
/*!
 	 \brief	 Function for the Main Menu that displays all the possible options on the LCD.
 	 \param[in]  color_sequence_t *colors = pointer to the array that contains the colors.
 	 \param[in]	 uint8_t sequence_total = total of colors in the array.
 	 \param[in]	 continue_seq_t stop = to choose if the sequence stops after it is completed
 	 	 	 		or if it continues.
 	 \return void
 */
void RGB_led_start_sequence(color_sequence_t *colors,uint8_t sequence_total,continue_seq_t stop);
/********************************************************************************************/
/*!
 	 \brief	 Deactivates the FTM1 CH0 to stop the 1s delay and the sequence.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_stop_sequence(void);
/********************************************************************************************/
/*!
 	 \brief	 Changes the RGB sequence to the next color.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_change_seq_color(void);

/*For submenu 4: Frequency*/
/********************************************************************************************/
/*!
 	 \brief	 Transforms a frequency between 1kHz to 10kHz into a ph level.
 	 \param[in]  void.
 	 \return void
 */
uint8_t RGB_led_frequency_to_phlevel(float frequency);

/*Functions to generate a one second delay*/
/********************************************************************************************/
/*!
 	 \brief	 Function to initialize the FTM1 CH0 to obtain the interruptions to generate a
 	  	  	  one second delay.
 	 \param[in]  void.
 	 \return void
 */
void RGB_led_delay_1s_init(void);
/********************************************************************************************/
/*!
 	 \brief	 Function fto increment a counter to generate a one second delay.
 	 \param[in]  void.
 	 \return void
 */
void Increase_interrupt_counter(void);


#endif /* RGB_LED_H_ */
