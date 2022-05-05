/**
	\file 	Buttons.h
	\brief
	 	API to control the B0-B6 and SW2-SW3 initializations and interruptions.
	\author Nelida Hernández
	\date	01/05/2022
 **/

#ifndef BUTTONS_H_
#define BUTTONS_H_


#include "MK64F12.h"
#include <stdio.h>

/*Masks for PortC and PortB to obtain the inputs of the specified pins*/
#define GPIOC_PB_MASK 0xC30
#define GPIOB_PB_MASK 0x808

/*Value of each button on the port*/
#define GPIOC_B0	0x20
#define GPIOC_B1	0x10
#define GPIOB_B2	0x08
#define GPIOD_B3	0x08
#define GPIOC_B5	0x800
#define GPIOC_B6	0x400
#define GPIOC_SW2	0x40

/*Initialization functions*/
/********************************************************************************************/
/*!
 	 \brief	 This group of functions initialize the buttons pins and interruptions for each
 	 	 	 port, including sw2 and sw3.
 	 \param[in]  void.
 	 \return void
 */
void Initialize_B0(void);
void Initialize_B1(void);
void Initialize_B2(void);
void Initialize_B3(void);
void Initialize_B4(void);
void Initialize_B5(void);
void Initialize_B6(void);
void Enable_sw2_and_sw3(void);


#endif /* BUTTONS_H_ */
