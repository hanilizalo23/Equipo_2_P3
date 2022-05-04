/*
 * ADC.c
 *
 *  Created on: 01/05/2022
 *      Author: Mauricio Peralta
 */

#include "stdio.h"
#include "MK64F12.h"
#include "stdint.h"
#include "GPIO.h"
#include "RGB.h"
#include "NVIC.h"
#include "ADC.h"

#define NOTHING 0U

void ADC_init(void)
{
    volatile uint8_t result;
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    ADC0->CFG1 = ADC_CFG1_ADIV(0)| ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3)|ADC_CFG1_ADICLK(0);
    ADC0->CFG2 = NOTHING;
    ADC0->SC2 = NOTHING;
    ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
}

