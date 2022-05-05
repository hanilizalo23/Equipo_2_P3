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

#define DISABLE_CH								(FTM_CnSC_CHIE(0) | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(0))

#define INPUT_CAPTURE_RE						(CAPTURE_MODE | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))
#define INPUT_CAPTURE_FE						(CAPTURE_MODE | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define INPUT_CAPTURE_RE_OR_FE					(CAPTURE_MODE | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(1))

#define OUTPUT_COMP_TOGGLE						(FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))
#define OUTPUT_COMP_CLEAR						(FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define OUTPUT_COMP_SET							(FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(1))

#define EDGE_ALLIGNED_HT						(FTM_CnSC_MSB(1) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define EDGE_ALLIGNED_LT						(FTM_CnSC_MSB(1) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))

#define CENTER_ALLIGNED_HT						(CPWMS_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define CENTER_ALLIGNED_LT						(CPWMS_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))

#define COMBINE_PWM_HT							(COMBINE_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define COMBINE_PWM_LT							(COMBINE_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))

#define DUAL_EDGE_CAPTURE_ONE_SHOT_RE			(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))
#define DUAL_EDGE_CAPTURE_ONE_SHOT_FE			(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define DUAL_EDGE_CAPTURE_ONE_SHOT_RE_OR_FE		(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(0) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(1))
#define DUAL_EDGE_CAPTURE_CONTINUOUS_RE			(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(0) | FTM_CnSC_ELSA(1))
#define DUAL_EDGE_CAPTURE_CONTINUOUS_FE			(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(0))
#define DUAL_EDGE_CAPTURE_CONTINUOUS_RE_OR_FE	(CAPTURE_MODE | DECAPEN_ON | FTM_CnSC_MSB(0) | FTM_CnSC_MSA(1) | FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(1))

#define FLEX_TIMER_CLKS_0  (0U)
#define FLEX_TIMER_CLKS_1  (1U)
#define FLEX_TIMER_CLKS_2  (2U)
#define FLEX_TIMER_CLKS_3  (3U)

#define FLEX_TIMER_PS_1    (0U)
#define FLEX_TIMER_PS_2    (1U)
#define FLEX_TIMER_PS_4    (2U)
#define FLEX_TIMER_PS_8    (3U)
#define FLEX_TIMER_PS_16   (4U)
#define FLEX_TIMER_PS_32   (5U)
#define FLEX_TIMER_PS_64   (6U)
#define FLEX_TIMER_PS_128  (7U)

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
/*!
 	 \brief	 Configures the specified channel of the FTM1.
 	 \param[in]  channel.
 	 \param[in]  *ch_configuration = pointer to the configuration structure.
 	 \return void
 */
void FTM1_configure_ch(ftm_channel_name_t channel,const ftm_channel_config_t *ch_configuration);
/*!
 	 \brief	 Configures the specified channel of the FTM2.
 	 \param[in]  channel.
 	 \param[in]  *ch_configuration = pointer to the configuration structure.
 	 \return void
 */
void FTM2_configure_ch(ftm_channel_name_t channel,const ftm_channel_config_t *ch_configuration);
/*!
 	 \brief	 Configures the specified channel of the FTM3.
 	 \param[in]  channel.
 	 \param[in]  *ch_configuration = pointer to the configuration structure.
 	 \return void
 */
void FTM3_configure_ch(ftm_channel_name_t channel,const ftm_channel_config_t *ch_configuration);
/********************************************************************************************/
/*!
 	 \brief	 Reads the CV of the specified channel on the FTM selected.
 	 \param[in]  flextimer.
 	 \param[in]  channel.
 	 \return void
 */
uint16_t get_channel_value(ftm_name_t flextimer,ftm_channel_name_t channel);
/********************************************************************************************/
/*!
 	 \brief	 Reads the MOD value of the specified FTM.
 	 \param[in]  flextimer.
 	 \return void
 */
uint16_t get_mod_value(ftm_name_t flextimer);
/********************************************************************************************/
/*!
 	 \brief	 Disables the channel of the FlexTimer.
 	 \param[in]  flextimer.
 	 \param[in]  channel.
 	 \return void
 */
void FlexTimer_disable_channel(ftm_name_t flextimer,ftm_channel_name_t channel);

/**IRQs for FlexTimer*/
void FTM0_IRQHandler(void);
void FTM1_IRQHandler(void);
void FTM2_IRQHandler(void);
void FTM3_IRQHandler(void);


#endif /* FLEXTIMER_H_ */
