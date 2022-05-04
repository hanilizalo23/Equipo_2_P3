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
	g_menu_level = SUB1_RGB_MANUAL;
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&g_str_submenu1[0]); /*! It prints a string stored in an array*/
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(&g_str_off[0]);
	LCD_nokia_goto_xy(10,2);
	/*Writes R G B to display the actual bright level of each color*/
	LCD_nokia_send_char('R');
	LCD_nokia_goto_xy(40,2);
	LCD_nokia_send_char('G');
	LCD_nokia_goto_xy(70,2);
	LCD_nokia_send_char('B');
	/*Displays initial bright levels of each color*/
	LCD_nokia_goto_xy(10,3);
	LCD_nokia_send_char('0');
	LCD_nokia_goto_xy(40,3);
	LCD_nokia_send_char('0');
	LCD_nokia_goto_xy(70,3);
	LCD_nokia_send_char('0');
	LCD_nokia_goto_xy(20,4);
}

void RGB_adc(void)
{
	g_menu_level = SUB2_RGB_ADC;
	LCD_nokia_clear();
	LCD_nokia_goto_xy(12,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&g_str_submenu2[0]); /*! It prints a string stored in an array*/
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(&g_str_off[0]);
	/*Sends the word "Voltaje" to print te actual voltage on the LCD*/
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(&g_str_voltaje[0]);
}

void RGB_sequence(void)
{
	g_menu_level = SUB3_RGB_SEQ;
	g_sequence_n = 0;
	LCD_nokia_clear();
	LCD_nokia_goto_xy(10,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&g_str_submenu3[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(&g_str_off[0]);
	LCD_nokia_goto_xy(0,1);
}

void RGB_frequence(void)
{
	g_menu_level = SUB4_RGB_FREQ;
	LCD_nokia_clear();
	LCD_nokia_goto_xy(10,0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&g_str_submenu4[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(&g_str_off[0]);
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(&g_str_freq[0]);
}

/*When the sw3 (on button) it chooses which functions will start according to the actual stage*/
void Mode_on(void)
{
	switch(g_menu_level)
	{
	case START:
		break;
	case MAIN_MENU:
		break;
	case SUB2_RGB_ADC:
		RGB_led_adc_init();
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_on[0]);
		break;
	case SUB3_RGB_SEQ:
		RGB_led_start_sequence(&g_colors_sequence[0],g_sequence_n,CONTINUE_SEQ);
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_on[0]);
		g_mode_on = TRUE;
		break;
	case SUB4_RGB_FREQ:
		Frequency_read_initilize();
		Generate_trial_signal();
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_on[0]);
		g_mode_on = TRUE;
		break;
	default:
		g_mode_on = TRUE;
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_on[0]);
		break;
	}
}

/*When the sw2 (off button) it chooses which functions will stop according to the actual stage*/
void Mode_off(void)
{
	switch(g_menu_level)
	{
	case START:
		break;
	case MAIN_MENU:
		break;
	case SUB2_RGB_ADC:
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_off[0]);
		RGB_led_adc_stop();
		break;
	case SUB3_RGB_SEQ:
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_off[0]);
		RGB_led_stop_sequence();
		RGB_sequence();
		g_mode_on = FALSE;
		break;
	case SUB4_RGB_FREQ:
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_off[0]);
		Frequency_read_stop();
		Generate_trial_signal_stop();
		g_mode_on = FALSE;
		break;
	default:
		LCD_nokia_goto_xy(0,5);
		LCD_nokia_send_string(&g_str_off[0]);
		g_mode_on = FALSE;
		break;
	}
}

/*When the B0 is pressed, it chooses which functions will be done according to the actual stage*/
void B0_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		Start();
		break;
	default:
		MainMenu_in();
		break;
	}
}

/*When the B1 is pressed, it chooses which functions will be done according to the actual stage*/
void B1_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		RGB_manual();
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the blue value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(BLUE,RGB_MANUAL_BR_CHANGE,INCREASE);
			LCD_nokia_goto_xy(63,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		/*Saves a new value (blue) in the sequence array when the mode is off*/
		if(FALSE == g_mode_on)
		{
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = BLUE_RGB;
			LCD_nokia_send_char('Z');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}
		break;
	case SUB4_RGB_FREQ:
		/*Increases frequency off the trial signal generated on the submenu 4*/
		if(g_mode_on)
		{
			Increase_or_decrease_freq(INCREASE_FRQ,FRQ_CHANGE);
		}
		break;
	default:
		break;
	}
}

/*When the B2 is pressed, it chooses which functions will be done according to the actual stage*/
void B2_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		RGB_adc();
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the blue value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(BLUE,RGB_MANUAL_BR_CHANGE,DECREASE);
			LCD_nokia_goto_xy(63,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		if(FALSE == g_mode_on)
		{
			/*Saves a new value (red) in the sequence array when the mode is off*/
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = RED_RGB;
			LCD_nokia_send_char('R');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}
		break;
	case SUB4_RGB_FREQ:
		/*Decreases frequency off the trial signal generated on the submenu 4*/
		if(g_mode_on)
		{
			Increase_or_decrease_freq(DECREASE_FRQ,FRQ_CHANGE);
		}
		break;
	default:
		break;
	}
}

/*When the B3 is pressed, it chooses which functions will be done according to the actual stage*/
void B3_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		RGB_sequence();
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the red bright value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(RED,RGB_MANUAL_BR_CHANGE,INCREASE);
			LCD_nokia_goto_xy(3,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		/*Saves a new value (green) in the sequence array when the mode is off*/
		if(FALSE == g_mode_on)
		{
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = GREEN_RGB;
			LCD_nokia_send_char('V');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}

		break;
	case SUB4_RGB_FREQ:
		break;
	default:
		break;
	}
}

/*When the B4 is pressed, it chooses which functions will be done according to the actual stage*/
void B4_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		RGB_frequence();
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the red bright value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(RED,RGB_MANUAL_BR_CHANGE,DECREASE);
			LCD_nokia_goto_xy(3,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		/*Saves a new value (yellow) in the sequence array when the mode is off*/
		if(FALSE == g_mode_on)
		{
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = YELLOW_RGB;
			LCD_nokia_send_char('A');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}

		break;
	case SUB4_RGB_FREQ:
		break;
	default:
		break;
	}
}

/*When the B5 is pressed, it chooses which functions will be done according to the actual stage*/
void B5_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the green bright value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(GREEN,RGB_MANUAL_BR_CHANGE,INCREASE);
			LCD_nokia_goto_xy(33,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		/*Saves a new value (purple) in the sequence array when the mode is off*/
		if(FALSE == g_mode_on)
		{
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = PURPLE_RGB;
			LCD_nokia_send_char('M');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}
		break;
	case SUB4_RGB_FREQ:
		break;
	default:
		break;
	}
}

/*When the B6 is pressed, it chooses which functions will be done according to the actual stage*/
void B6_choose_function(void)
{
	switch(g_menu_level)
	{
	case MAIN_MENU:
		break;
	case SUB1_RGB_MANUAL:
		/*If the mode is on, the changes the green bright value*/
		if(g_mode_on)
		{
			g_bright_level = RGB_led_change_bright(GREEN,RGB_MANUAL_BR_CHANGE,DECREASE);
			LCD_nokia_goto_xy(33,3);
			LCD_nokia_send_int(BR_FACTOR,g_bright_level,BR_DIGITS);
		}
		break;
	case SUB2_RGB_ADC:
		break;
	case SUB3_RGB_SEQ:
		/*Saves a new value (white) in the sequence array when the mode is off*/
		if(FALSE == g_mode_on)
		{
			if(MAX_SEQ_VAL == g_sequence_n)
			{
				RGB_sequence();
			}
			g_colors_sequence [g_sequence_n] = WHITE_RGB;
			LCD_nokia_send_char('B');
			LCD_nokia_send_char(' ');
			g_sequence_n ++;
		}
		break;
	case SUB4_RGB_FREQ:
		break;
	default:
		break;
	}
}
