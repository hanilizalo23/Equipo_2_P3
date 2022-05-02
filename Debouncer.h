/**
 * \file		Debouncer.h
 * \brief
 * 		Source file for the software module to avoid debounces while reading keys.
 *  \date:		01/05/2022
 *  \author:	Nelida Hernández
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_


#include "PIT.h"
#include "GPIO.h"

#define SYSTEM_CLOCK (21000000U)

/*Time for delay on the first stage: verify key status change*/
#define CHECK_WAIT   (0.005F)

/*Time for delay on the second stage: wait for the input to stabilize*/
#define RELEASE_WAIT (0.1F)

void check_pin_status(void); //Checking

void wait_release(void); //Waiting

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*
 	 \brief	 This function eliminates false readings caused for debounces of keys.
 	 \param[in]  gpio Port where the input is being read.
 	 \param[in]  pin Number of input pin.
 	 \return void
 */
void debouncer(gpio_port_name_t gpio, uint8_t pin);


#endif /* DEBOUNCER_H_ */
