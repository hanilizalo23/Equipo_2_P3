/*
 * ADC.h
 *
 *  Created on: 01/05/2022
 *      Author: Mauricio Peralta
 */


#ifndef ADC_H_
#define ADC_H_

#include "stdio.h"
#include "MK64F12.h"
#include "stdint.h"
#include "GPIO.h"
#include "NVIC.h"

void ADC_init(void); //Initialization for ADC

uint8_t ADC_result(void); //Obtaining the result of the ADC read

#endif /* ADC_H_ */
