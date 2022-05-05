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
static menu_level_t g_menu_level = START;
//Flag to determine if the current mode is on or off.
static uint8_t g_mode_on = FALSE;
//Variable to save a maximum of 10 colors for the sequence in the submenu 3.
static color_sequence_t g_colors_sequence [10] = {0};
//Variable to track how many colors are in the sequence of the submenu 3.
static uint8_t g_sequence_n = 0;
//Determines if the system has just started. It is used to know if the start RGB sequence must be shown.
static uint8_t g_start_system = FALSE;
//Keeps the actual bright level to send it to the LCD.
static uint8_t g_bright_level;

//Strings for LCD
uint8_t g_str_submenu1[] = "1)RGB Manual";
uint8_t g_str_submenu2[] = "2)RGB ADC";
uint8_t g_str_submenu3[] = "3)RGB Sec.";
uint8_t g_str_submenu4[] = "4)RGB Frec.";
uint8_t g_str_voltaje[] = "Voltaje: ";
uint8_t g_str_freq[] = "Freq: ";
uint8_t g_str_on[] = "ON ";
uint8_t g_str_off[] = "OFF";

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
	g_menu_level = START;
	LCD_nokia_clear();
	/*Start image*/
	LCD_nokia_bitmap(ITESO);
	/*If the program just started running, then the sequence will be shown*/
	if(FALSE == g_start_system)
	{
		RGB_led_start_sequence(&initial_sequence[0],INIT_SEQ_VAL,STOP_SEQ);
	}
	/*Initialize first button to allow interruption*/
	Initialize_B0();
	g_start_system = TRUE;
}

void MainMenu_in(void)
{
	RGB_led_stop_sequence();	//To make sure the RGB stops and clears
	RGB_led_turn_off();
	Mode_off(); 				//To make sure the last function is stopped
	g_menu_level = MAIN_MENU;
	g_mode_on = FALSE;
	LCD_nokia_clear();
	/*Initialize all buttons interruptions*/
	Initialize_B1();
	Initialize_B2();
	Initialize_B3();
	Initialize_B4();
	Initialize_B5();
	Initialize_B6();
	Enable_sw2_and_sw3();
	/*Displays submenus options on the LCD*/
	LCD_nokia_goto_xy(0,1); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&g_str_submenu1[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(12,2);
	LCD_nokia_send_string(&g_str_submenu2[0]);
	LCD_nokia_goto_xy(12,3);
	LCD_nokia_send_string(&g_str_submenu3[0]);
	LCD_nokia_goto_xy(10,4);
	LCD_nokia_send_string(&g_str_submenu4[0]);
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
