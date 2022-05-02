/**
	\file 	Buttons.c
	\brief
	 	API to control the B0-B6 and SW2-SW3 initializations and interruptions.
	\author Nelida Hernández
	\date	01/05/2022
 **/

#include "Buttons.h"
#include "Debouncer.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Bits.h"
#include "MainMenu.h"
#include "Switches.h"

gpio_pin_control_register_t g_pcr_buttons = GPIO_MUX1 | GPIO_PE | INTR_RISING_EDGE;

/*Initialization functions*/
void Initialize_B0(void)
{
	/**Clock gating activation for GPIOC*/
	GPIO_clock_gating(GPIO_C);
	/**Pin control configuration of GPIOC pin 5 as GPIO*/
	GPIO_pin_control_register(GPIO_C,bit_5,&g_pcr_buttons);
	/**Configuration of GPIOC pin 5 as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT,bit_5);
	/*Enable interrupts*/
	PIT_clock_gating();
	PIT_enable();
	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_3);
	GPIO_callback_init(GPIO_C, gpioC_pb_interrupt);
	NVIC_global_enable_interrupts;
}

void Initialize_B1(void)
{
	/**Pin control configuration of GPIOC pin 4 as GPIO*/
	GPIO_pin_control_register(GPIO_C,bit_4,&g_pcr_buttons);
	/**Configuration of GPIOC pin 4 as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT,bit_4);
}

void Initialize_B2(void)
{
	/**Clock gating activation for GPIOB*/
	GPIO_clock_gating(GPIO_B);
	/**Pin control configuration of GPIOB pin 3 as GPIO*/
	GPIO_pin_control_register(GPIO_B,bit_3,&g_pcr_buttons);
	/**Configuration of GPIOB pin 3 as input*/
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT,bit_3);
	/*Enable interrupts*/
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ, PRIORITY_5);
	GPIO_callback_init(GPIO_B, gpioB_pb_interrupt);
}

void Initialize_B3(void)
{
	/**Clock gating activation for GPIOD*/
	GPIO_clock_gating(GPIO_D);
	/**Pin control configuration of GPIOD pin 3 as GPIO*/
	GPIO_pin_control_register(GPIO_D,bit_3,&g_pcr_buttons);
	/**Configuration of GPIOD pin 3 as input*/
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT,bit_3);
	/*Enable interrupts*/
	NVIC_enable_interrupt_and_priotity(PORTD_IRQ, PRIORITY_5);
	GPIO_callback_init(GPIO_D, gpioD_pb_interrupt);
}

void Initialize_B4(void)
{
	/**Pin control configuration of GPIOB pin 11 as GPIO*/
	GPIO_pin_control_register(GPIO_B,bit_11,&g_pcr_buttons);
	/**Configuration of GPIOB pin 11 as input*/
	GPIO_data_direction_pin(GPIO_B,GPIO_INPUT,bit_11);
}

void Initialize_B5(void)
{
	/**Pin control configuration of GPIOC pin 11 as GPIO*/
	GPIO_pin_control_register(GPIO_C,bit_11,&g_pcr_buttons);
	/**Configuration of GPIOC pin 11 as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT,bit_11);
}

void Initialize_B6(void)
{
	/**Pin control configuration of GPIOC pin 10 as GPIO*/
	GPIO_pin_control_register(GPIO_C,bit_10,&g_pcr_buttons);
	/**Configuration of GPIOC pin 10 as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT,bit_10);
}

void Enable_sw2_and_sw3(void)
{
	SW2_config();
	SW3_config();
	/*Enable interrupts*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_8);
	GPIO_callback_init(GPIO_A, gpioA_pb_interrupt);
}

/*Ports interruptions*/
void gpioA_pb_interrupt(void)
{
	Mode_on();
}

void gpioB_pb_interrupt(void)
{
	/*Reads which button is being pressed*/
	uint32_t read_pb = GPIO_read_port(GPIO_B) & GPIOB_PB_MASK;
	/*Keeps the value of the pin for the debounce function*/
	uint8_t pin_debounce;
	switch(read_pb)
	{
	case GPIOB_B2:
		pin_debounce = bit_3;
		B2_choose_function();
		break;
	default:
		pin_debounce = bit_11;
		B4_choose_function();
		break;
	}
	debouncer(GPIO_B, pin_debounce);
}

void gpioC_pb_interrupt(void)
{
		/*Reads which button is being pressed*/
		uint32_t read_pb = GPIO_read_port(GPIO_C) & GPIOC_PB_MASK;
		/*Keeps the value of the pin for the debounce function*/
		uint8_t pin_debounce;
		switch(read_pb)
		{
		case GPIOC_B0:
			pin_debounce = bit_5;
			B0_choose_function();
			debouncer(GPIO_C, pin_debounce);
			break;
		case GPIOC_B1:
			pin_debounce = bit_4;
			B1_choose_function();
			debouncer(GPIO_C, pin_debounce);
			break;
		case GPIOC_B5:
			pin_debounce = bit_11;
			B5_choose_function();
			debouncer(GPIO_C, pin_debounce);
			break;
		case GPIOC_B6:
			pin_debounce = bit_10;
			B6_choose_function();
			debouncer(GPIO_C, pin_debounce);
			break;
		default:
			pin_debounce = bit_6;
			Mode_off();
			break;
		}
}

void gpioD_pb_interrupt(void)
{
	/**Unique for GPIO D*/
	B3_choose_function();
	debouncer(GPIO_D, bit_3);
}
