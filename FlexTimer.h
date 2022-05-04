/**
	\file 	FlexTimer.h
	\brief
	 	Device driver for the FlexTimer. It contains the functions to
	 	configure and manipulate each FTM.
	\author Mauricio Peralta
	\date	01/05/2022
 **/

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"
#include "stdint.h"

#define MAX_MOD_VALUE 		0xFFFF

/*Constants to configure FTM_CnSC channels*/
#define CPWMS_ON			0x40
#define COMBINE_ON			0x80
#define DECAPEN_ON			0x100
#define CAPTURE_MODE    	0x200

typedef enum{FTM_0,
			FTM_1,
			FTM_2,
			FTM_3
}ftm_name_t;



/*!
 	 \brief	 Configures clock gating for the specified FTM.
 	 \param[in]  flextimer.
 	 \return void
 */
void FlexTimer_clock_gating(ftm_name_t flextimer);



#endif /* FLEXTIMER_H_ */
