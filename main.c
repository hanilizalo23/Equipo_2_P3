/**
	\file 	main.c
	\brief
		Program for the K64 that manipulates a RGB led according to the buttons pressed.
	\author Nelida Paulina Hernández Moya & Mauricio Peralta Osorio
	\date	01/05/2022
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "FlexTimer.h"
#include "Buttons.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB_led.h"
#include "MainMenu.h"
#include "Frequency.h"

int main(void) {

	/*Initialize RGB led and LCD*/
	Init_all();

	/*Go to the initial sequence*/
	Start();

    while(1)
    {

    }

    return 0;
}
