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

#define NOTHING 0U

/**Value for the PCR to configure as GPIO with pull-up enable*/
gpio_pin_control_register_t pcr_sw_pullup = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;
/**Value for the PCR to disable the switches*/
gpio_pin_control_register_t pcr_sw_disable = GPIO_MUX1;

uint8_t SW2_config(void)
{

}

uint8_t SW2_disable(void)
{

}

uint8_t SW3_config(void)
{

}

uint8_t SW3_disable(void)
{

}

uint8_t sw_state(sw_name_t sw)
{

}
