/**
 * \file		Switches.c
 * \brief
 * 		Source file for the Switches (SW2 and SW3) device driver for Kinetis K64.
 * 		This is the application programming interface (API) for the Switches.
 * 		It contains the definition of the special variables and functions
 * 		for the configuration of the Switches.
 *  \date:		01/05/2022
 *  \author:	Nelida Hernández
 */

#include "MK64F12.h"
#include "Switches.h"
#include "GPIO.h"
#include "Bits.h"

#define NOTHING 0U

/**Value for the PCR to configure as GPIO with pull-up enable*/
gpio_pin_control_register_t pcr_sw_pullup = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;
/**Value for the PCR to disable the switches*/
gpio_pin_control_register_t pcr_sw_disable = GPIO_MUX1;

uint8_t SW2_config(void)
{
	/**Clock gating activation for GPIOC*/
	GPIO_clock_gating(GPIO_C);
	/**Pin control configuration of GPIOC pin6 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_C, SW2_bit, &pcr_sw_pullup);
	/**Configures pin6 of GPIOC as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, SW2_bit);
	return(TRUE);
}

uint8_t SW2_disable(void)
{
	/**Pin control configuration of GPIOC pin6 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_C, SW2_bit, &pcr_sw_disable);
	/**Configures pin6 of GPIOC as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_OUTPUT, SW2_bit);
	return(TRUE);
}

uint8_t SW3_config(void)
{
	/**Clock gating activation for GPIOA*/
	GPIO_clock_gating(GPIO_A);
	/**Pin control configuration of GPIOA pin4 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_A, SW3_bit, &pcr_sw_pullup);
	/**Configures pin4 of GPIOA as input*/
	GPIO_data_direction_pin(GPIO_A,GPIO_INPUT, SW3_bit);
	return(TRUE);
}

uint8_t SW3_disable(void)
{
	/**Pin control configuration of GPIOC pin6 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_A, SW3_bit, &pcr_sw_disable);
	/**Configures pin6 of GPIOC as input*/
	GPIO_data_direction_pin(GPIO_A,GPIO_OUTPUT, SW3_bit);
	return(TRUE);
}

uint8_t sw_state(sw_name_t sw)
{

}
