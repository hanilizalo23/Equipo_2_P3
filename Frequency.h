/**
	\file 	Frequency.h
	\brief
	 	API that contains functions to allow the FTM2 CH0 to read frequencies
	 	and the FTM3 CH4 to generate a signal.
	\author Mauricio Peralta
	\date	01/05/2022
 **/

#ifndef FREQUENCY_H_
#define FREQUENCY_H_


#include "MK64F12.h"
#define FREQ_TOTAL_SAMPLES (500U)

/*Divisors to display frequency*/
#define KHZ_DIVISOR 		(1000.0F)
#define KHZ_DIVISOR_10		(10000.0F)
#define KHZ_DIVISOR_1		(1000.0F)
#define HZ_DIVISOR_100		(100.0F)
#define HZ_DIVISOR_10		(10.0F)
#define HZ_DIVISOR_0_1		(0.1F)
#define HZ_DIVISOR_0_0_1	(0.01F)
#define MIN_KHZ 			(0.1F)
#define DIGITS_NUMBER 		(2U)

typedef enum
{
	INCREASE_FRQ,
	DECREASE_FRQ
}increase_or_dicrease_frq_t;

/*Functions to generate a square wave*/
/********************************************************************************************/
/*!
 	 \brief	 Initializes the FTM3 CH4 to generate an square wave of 9kHz approximately.
 	 \param[in]  void.
 	 \return void
 */
void Generate_trial_signal(void);
/********************************************************************************************/
/*!
 	 \brief	 Changes the frequency of the trial signal.
 	 \param[in]  increase_or_dicrease_frq_t increase_or_dicrease = choose to increment or
 	 	 	 	 decrement the frequency.
 	 \param[in]  float change_value = value of the increment/decrement.
 	 \return void
 */
void Increase_or_decrease_freq(increase_or_dicrease_frq_t increase_or_dicrease, float change_value);
/*To stop the signal*/
/********************************************************************************************/
/*!
 	 \brief	 Stops the trial signal.
 	 \param[in]  void.
 	 \return void
 */
void Generate_trial_signal_stop(void);

/*Functions to read frequency*/
/********************************************************************************************/
/*!
 	 \brief	 Initializes the FTM2 CH0 as input capture.
 	 \param[in]  void.
 	 \return void
 */
void Frequency_read_initilize(void);
#endif /* FREQUENCY_H_ */
