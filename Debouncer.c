/**
 * \file		Debouncer.c
 * \brief
 * 		Source file for the software module to avoid debounces while reading keys.
 *  \date:		01/05/2022
 *  \author:	Nelida Hernández
 */

#include "Debouncer.h"
#include "Bits.h"
#include "NVIC.h"
#include "PIT.h"
#include "stdint.h"
#include "stdio.h"

#define NOTHING 0U
#define TIMES 50U

/*Flags to verify the change on the pin to debounce or the finish of the release wait*/
static uint8_t g_change_flag = FALSE;
static uint8_t g_release_wait_end = FALSE;

/*Saves the values to use them on the interruption function*/
static uint8_t g_initial_pin_status;
static uint8_t g_actual_pin_status;
static gpio_port_name_t g_gpio;
static uint8_t g_pin;

/*Helps to avoid problems with PortC caused by sw2 interrupt. When it gets to 50, the debouncer finishes*/
uint8_t g_counter;

void check_pin_status(void)
{
	g_actual_pin_status  = GPIO_read_pin(g_gpio, g_pin);
	g_counter ++;
	if((g_initial_pin_status != g_actual_pin_status) || (TIMES == g_counter))
	{
		g_change_flag = TRUE;
	}
}

void wait_release(void)
{
	g_release_wait_end = TRUE;
	PIT_clear_interrupt_flag();
	PIT_stop(PIT_0);
}

void debouncer(gpio_port_name_t gpio, uint8_t pin)
{

}
