/**
*	\file 	MainMenu.h
*	\brief
*	 	Definition of the different functions for each stage (start, menu and submenus)
*		and the state machines to choose the functionality of each button according to
*		the current stage.
*	\author Nelida Hernández
*	\date	01/05/2022
**/

#ifndef MAINMENU_H_
#define MAINMENU_H_


#include "MK64F12.h"
#include <stdio.h>

//Number of values on the initial RGB sequence
#define INIT_SEQ_VAL 	(4U)
//Max. number of values on the sequence array
#define MAX_SEQ_VAL		(10U)
//Change of the trial frequency (1KHz)
#define FRQ_CHANGE 		(1000.0F)
//Maximun factor of the bright level
#define BR_FACTOR		(100U)
//Number of digits (max) of the bright level
#define BR_DIGITS		(3U)

//Enumeration for the program stages
typedef enum{
	START,
	MAIN_MENU,
	SUB1_RGB_MANUAL,
	SUB2_RGB_ADC,
	SUB3_RGB_SEQ,
	SUB4_RGB_FREQ
}menu_level_t;

/********************************************************************************************/
/*!
 	 \brief	 This function initialize the RGB led and LCD.
 	 \param[in]  void.
 	 \return void
 */
void Init_all(void);
/********************************************************************************************/
/*!
 	 \brief	 Start sequence of the program.
 	 \param[in]  void.
 	 \return void
 */
void Start(void);
/********************************************************************************************/
/*!
 	 \brief	 Function for the Main Menu that displays all the possible options on the LCD.
 	 \param[in]  void.
 	 \return void
 */
void MainMenu_in(void);
/********************************************************************************************/
/*!
 	 \brief	 Function for the Submenu 1.
 	 \param[in]  void.
 	 \return void
 */
void RGB_manual(void);
/********************************************************************************************/
/*!
 	 \brief	 Function for the Submenu 2.
 	 \param[in]  void.
 	 \return void
 */
void RGB_adc(void);
/********************************************************************************************/
/*!
 	 \brief	 Function for the Submenu 3.
 	 \param[in]  void.
 	 \return void
 */
void RGB_sequence(void);
/********************************************************************************************/
/*!
 	 \brief	 Function for the Submenu 4.
 	 \param[in]  void.
 	 \return void
 */
void RGB_frequence(void);
/********************************************************************************************/
/*!
 	 \brief	 When the sw3 (on button) it chooses which functions will start according to the
 	 	 	 actual stage
 	 \param[in]  void.
 	 \return void
 */
void Mode_on(void);
/********************************************************************************************/
/*!
 	 \brief	 When the sw2 (off button) it chooses which functions will start according to the
 	 	 	 actual stage
 	 \param[in]  void.
 	 \return void
 */
void Mode_off(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B0 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B0_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B1 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B1_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B2 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B2_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B3 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B3_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B4 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B4_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B5 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B5_choose_function(void);
/********************************************************************************************/
/*!
 	 \brief	 When the B6 is pressed, it chooses which functions will be done according to
 	 	 	 the actual stage
 	 \param[in]  void.
 	 \return void
 */
void B6_choose_function(void);


#endif /* MAINMENU_H_ */
