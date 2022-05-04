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

#define CNSC_MASK			0x3C
#define CPWNS_MASK			0x40
#define COMBINE_MASK		0x80
#define DECAPEN_MASK		0x100
#define CAPTURE_MODE_MASK   0x200

#define CPWNS_SHIFT 		(6U)
#define COMBINE_SHIFT 		(7U)
#define DECAPEN_SHIFT		(8U)

#define SYSTEM_CLOCK_FTM (60000000.0F)

typedef enum{FTM_0,
			FTM_1,
			FTM_2,
			FTM_3
}ftm_name_t;

typedef enum{CH_0,
			CH_1,
			CH_2,
			CH_3,
			CH_4,
			CH_5,
			CH_6,
			CH_7
}ftm_channel_name_t;

typedef enum{
	DISABLE,
	ENABLE
}channel_enable_t;

typedef struct{
	uint32_t ftm_mode;
	uint16_t ftm_value;
	channel_enable_t ftm_enable_deadtime;
	channel_enable_t ftm_enable_combine;
	channel_enable_t ftm_enable_complement;
	uint8_t ftm_dtval;
	uint8_t ftm_clocks;
	uint8_t ftm_prescaler;
	channel_enable_t ftm_enable_toie;
	channel_enable_t ftm_enable_interrupt;
}ftm_channel_config_t;

/********************************************************************************************/
/*!
 	 \brief	 Assigns the function handler for callbacks.
 	 \param[in]  flextimer.
 	 \param[in]	 *handler = pointer to the function.
 	 \return void
 */
void FTM_callback_init(ftm_name_t flextimer,void (*handler)(void));
/********************************************************************************************/
/*!
 	 \brief	 Configures clock gating for the specified FTM.
 	 \param[in]  flextimer.
 	 \return void
 */
void FlexTimer_clock_gating(ftm_name_t flextimer);
/********************************************************************************************/
/*!
 	 \brief	 Configures the specified channel of the FTM selected with the configuration
 	 	 	 contained on the structure.
 	 \param[in]  flextimer.
 	 \param[in]  channel.
 	 \param[in]  *ch_configuration = pointer to the configuration structure.
 	 \return void
 */
void FlexTimer_configure_channel(ftm_name_t flextimer,ftm_channel_name_t channel,const ftm_channel_config_t *ch_configuration);
/********************************************************************************************/
/*!
 	 \brief	 Disables the specified channel of the specified FTM.
 	 \param[in]  flextimer.
 	 \param[in]  channel.
 	 \return void
 */
void FlexTimer_disable_channel(ftm_name_t flextimer,ftm_channel_name_t channel);
/********************************************************************************************/
/*!
 	 \brief	 Changes the MOD of the specified FTM.
 	 \param[in]  flextimer.
 	 \param[in]  value = new MOD value.
 	 \return void
 */
void FlexTimer_set_mod(ftm_name_t flextimer,uint16_t value);
/********************************************************************************************/
/*!
 	 \brief	 Changes the CV of the specified channel on the FTM selected.
 	 \param[in]  flextimer.
 	 \param[in]  value = new MOD value.
 	 \return void
 */
void FlexTimer_change_cnv(ftm_name_t flextimer,ftm_channel_name_t channel,uint16_t value);
/*!
 	 \brief	 Configures the specified channel of the FTM0.
 	 \param[in]  channel.
 	 \param[in]  *ch_configuration = pointer to the configuration structure.
 	 \return void
 */
void FTM0_configure_ch(ftm_channel_name_t channel,const ftm_channel_config_t *ch_configuration);


#endif /* FLEXTIMER_H_ */
