/**
*	\file 	MainMenu.c
*	\brief
*	 	Definition of the different functions for each stage (start, menu and submenus)
*		and the state machines to choose the functionality of each button according to
*		the current stage.
*	\author Nelida Hernández
*	\date	01/05/2022
**/

#include "MainMenu.h"
#include "Debouncer.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Bits.h"
#include "Buttons.h"
#include "RGB_led.h"
#include "Frequency.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"

//Current stage of the program.


//Strings for LCD


//Initial RGB sequence
color_sequence_t initial_sequence[5] =
{
		BLUE_RGB,
		RED_RGB,
		GREEN_RGB,
		NONE_RGB
};

//Start image, extern is permitted here
extern const uint8_t ITESO[504];

void Init_all(void)
{
	/*Initialize LCD and RGB*/
	LCD_nokia_init();
	RGB_led_initialize();
}

void Start(void)
{

}

void MainMenu_in(void)
{

}

void RGB_manual(void)
{

}

void RGB_adc(void)
{

}

void RGB_sequence(void)
{

}

void RGB_frequence(void)
{

}

/*When the sw3 (on button) it chooses which functions will start according to the actual stage*/
void Mode_on(void)
{

}

/*When the sw2 (off button) it chooses which functions will stop according to the actual stage*/
void Mode_off(void)
{

}

/*When the B0 is pressed, it chooses which functions will be done according to the actual stage*/
void B0_choose_function(void)

}

/*When the B1 is pressed, it chooses which functions will be done according to the actual stage*/
void B1_choose_function(void)
{

}

/*When the B2 is pressed, it chooses which functions will be done according to the actual stage*/
void B2_choose_function(void)
{

}

/*When the B3 is pressed, it chooses which functions will be done according to the actual stage*/
void B3_choose_function(void)
{

}

/*When the B4 is pressed, it chooses which functions will be done according to the actual stage*/
void B4_choose_function(void)
{

}

/*When the B5 is pressed, it chooses which functions will be done according to the actual stage*/
void B5_choose_function(void)
{

}

/*When the B6 is pressed, it chooses which functions will be done according to the actual stage*/
void B6_choose_function(void)
{

}
