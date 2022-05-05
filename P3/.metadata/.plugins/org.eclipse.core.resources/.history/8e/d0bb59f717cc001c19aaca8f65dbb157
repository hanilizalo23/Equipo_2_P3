/*
 * Delay.c
 *
 *  Created on: 01/05/2022
 *      Author: Nelida Hernández
 */

#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"
#include "bits.h"
#include "delay.h"

void delay(uint32_t  delay)
{
	volatile uint32_t  j, i;
	i=0;

	for(j = delay; j > 0; j--)
	{
		__asm("nop");
		i++;
	}
}
