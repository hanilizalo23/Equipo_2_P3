/**
	\file 	FlexTimer.c
	\brief
	 	Device driver for the FlexTimer. It contains the functions to
	 	configure and manipulate each FTM.
	\author Mauricio Peralta
	\date	01/05/2022
 **/

#include "FlexTimer.h"
#include "MK64F12.h"
#include "Bits.h"
#include "GPIO.h"
#include "stdio.h"

#define NOTHING 0U

static void (*ftm_0_callback)(void) = NOTHING;
static void (*ftm_1_callback)(void) = NOTHING;
static void (*ftm_2_callback)(void) = NOTHING;
static void (*ftm_3_callback)(void) = NOTHING;

void FlexTimer_clock_gating(ftm_name_t flextimer)
{
	switch(flextimer)
	{
		case FTM_0:
			SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
			break;
		case FTM_1:
			SIM->SCGC6 |= SIM_SCGC6_FTM1(1);
			break;
		case FTM_2:
			SIM->SCGC6 |= SIM_SCGC6_FTM2(1);
			break;
		default:
			SIM->SCGC3 |= SIM_SCGC3_FTM3(1);
			break;
	}
}

void FlexTimer_configure_channel(ftm_name_t flextimer, ftm_channel_name_t channel, const ftm_channel_config_t *ch_configuration)
{
	switch(flextimer)
	{
		case FTM_0:
			FTM0_configure_ch(channel,ch_configuration);
			break;
		case FTM_1:
			FTM1_configure_ch(channel,ch_configuration);
			break;
		case FTM_2:
			FTM2_configure_ch(channel,ch_configuration);
			break;
		default:
			FTM3_configure_ch(channel,ch_configuration);
			break;
	}
}

void FlexTimer_set_mod(ftm_name_t flextimer,uint16_t value)
{
	switch(flextimer)
	{
		case FTM_0:
			FTM0->MOD = value;
			break;
		case FTM_1:
			FTM1->MOD = value;
			break;
		case FTM_2:
			FTM2->MOD = value;
			break;
		default:
			FTM3->MOD = value;
			break;
	}
}

void FlexTimer_change_cnv(ftm_name_t flextimer,ftm_channel_name_t channel,uint16_t value)
{
	switch(flextimer)
	{
		case FTM_0:
			FTM0->CONTROLS[channel].CnV = value;
			break;
		case FTM_1:
			FTM1->CONTROLS[channel].CnV = value;
			break;
		case FTM_2:
			FTM2->CONTROLS[channel].CnV = value;
			break;
		default:
			FTM3->CONTROLS[channel].CnV = value;
			break;
	}
}

void FTM_callback_init(ftm_name_t flextimer,void (*handler)(void))
{
	switch(flextimer)
		{
		case FTM_0:
			ftm_0_callback = handler;
			break;
		case FTM_1:
			ftm_1_callback = handler;
			break;
		case FTM_2:
			ftm_2_callback = handler;
			break;
		default:
			ftm_3_callback = handler;
			break;
		}
}

void FTM0_configure_ch(ftm_channel_name_t channel, const ftm_channel_config_t *ch_configuration)
{
	gpio_pin_control_register_t pcr_ftm_pin = GPIO_MUX4;
	uint32_t cpwns_flag = ((ch_configuration->ftm_mode & CPWNS_MASK) >> CPWNS_SHIFT);
	uint32_t combine_flag = (((ch_configuration->ftm_mode & COMBINE_MASK) >> COMBINE_SHIFT) | ch_configuration->ftm_enable_combine);
	uint32_t decapen_flag = ((ch_configuration->ftm_mode & DECAPEN_MASK) >> DECAPEN_SHIFT);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);
	if(FALSE == (ch_configuration->ftm_mode & CAPTURE_MODE))
	{
		FTM0->CONF = FTM_CONF_BDMMODE(3);
		FTM0->FMS = 0x00;
		FTM0->MODE |= (FTM_MODE_FTMEN(0) | FTM_MODE_WPDIS(1));
		FTM0->CNTIN = 0x00;
	}
	switch(channel)
	{
		case CH_0:
			GPIO_pin_control_register(GPIO_C,bit_1,&pcr_ftm_pin);
			FTM0->CONTROLS[0].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[0].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			FTM0->COMBINE |= (FTM_COMBINE_COMBINE0(combine_flag) | FTM_COMBINE_COMP0(ch_configuration->ftm_enable_complement) | FTM_COMBINE_DECAPEN0(decapen_flag));
			break;
		case CH_1:
			GPIO_pin_control_register(GPIO_C,bit_2,&pcr_ftm_pin);
			FTM0->CONTROLS[1].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[1].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
		case CH_2:
			GPIO_pin_control_register(GPIO_C,bit_3,&pcr_ftm_pin);
			FTM0->CONTROLS[2].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[2].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			FTM0->COMBINE |= (FTM_COMBINE_COMBINE1(combine_flag) | FTM_COMBINE_COMP1(ch_configuration->ftm_enable_complement) | FTM_COMBINE_DECAPEN1(decapen_flag));
			break;
		case CH_3:
			GPIO_pin_control_register(GPIO_C,bit_4,&pcr_ftm_pin);
			FTM0->CONTROLS[3].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[3].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
		case CH_4:
			GPIO_pin_control_register(GPIO_D,bit_4,&pcr_ftm_pin);
			FTM0->CONTROLS[4].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[4].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			FTM0->COMBINE |= (FTM_COMBINE_COMBINE2(combine_flag) | FTM_COMBINE_COMP2(ch_configuration->ftm_enable_complement) | FTM_COMBINE_DECAPEN2(decapen_flag));
			break;
		case CH_5:
			GPIO_pin_control_register(GPIO_D,bit_5,&pcr_ftm_pin);
			FTM0->CONTROLS[5].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[5].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
		case CH_6:
			GPIO_pin_control_register(GPIO_D,bit_6,&pcr_ftm_pin);
			FTM0->CONTROLS[6].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[6].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			FTM0->COMBINE |= (FTM_COMBINE_COMBINE3(combine_flag) | FTM_COMBINE_COMP3(ch_configuration->ftm_enable_complement) | FTM_COMBINE_DECAPEN3(decapen_flag));
			break;
		default:
			GPIO_pin_control_register(GPIO_D,bit_7,&pcr_ftm_pin);
			FTM0->CONTROLS[7].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM0->CONTROLS[7].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
	}
	if(FALSE == (ch_configuration->ftm_mode & CAPTURE_MODE))
	{
		FTM0->CONTROLS[channel].CnV = ch_configuration->ftm_value;
	}
	if(ch_configuration->ftm_enable_deadtime)
	{
		FTM0->DEADTIME = ch_configuration->ftm_dtval;
	}
	FTM0->SC = (FTM_SC_CLKS (ch_configuration->ftm_clocks)| FTM_SC_PS(ch_configuration->ftm_prescaler) | FTM_SC_CPWMS(cpwns_flag) | FTM_SC_TOIE(ch_configuration->ftm_enable_toie));
}

void FTM1_configure_ch(ftm_channel_name_t channel, const ftm_channel_config_t *ch_configuration)
{
	gpio_pin_control_register_t pcr_ftm_pin = GPIO_MUX3;
	uint32_t cpwns_flag = ((ch_configuration->ftm_mode & CPWNS_MASK) >> CPWNS_SHIFT);
	uint32_t combine_flag = ((ch_configuration->ftm_mode & COMBINE_MASK) >> COMBINE_SHIFT);
	uint32_t decapen_flag = ((ch_configuration->ftm_mode & DECAPEN_MASK) >> DECAPEN_SHIFT);
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_D);
	if(FALSE == (ch_configuration->ftm_mode & CAPTURE_MODE))
	{
		FTM1->CONF = FTM_CONF_BDMMODE(3);
		FTM1->FMS = 0x00;
		FTM1->MODE |= (FTM_MODE_FTMEN(0) | FTM_MODE_WPDIS(1));
		FTM1->CNTIN = 0x00;
	}
	switch(channel)
	{
		case CH_0:
			GPIO_pin_control_register(GPIO_A,bit_12,&pcr_ftm_pin);
			FTM1->CONTROLS[0].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM1->CONTROLS[0].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			FTM1->COMBINE |= (FTM_COMBINE_COMBINE0(combine_flag) | FTM_COMBINE_COMBINE0(ch_configuration->ftm_enable_complement) | FTM_COMBINE_DECAPEN0(decapen_flag));
			break;
		case CH_1:
			GPIO_pin_control_register(GPIO_A,bit_13,&pcr_ftm_pin);
			FTM1->CONTROLS[1].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM1->CONTROLS[1].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
		default:
			GPIO_pin_control_register(GPIO_D,bit_7,&pcr_ftm_pin);
			FTM1->CONTROLS[0].CnSC |= (ch_configuration->ftm_mode & CNSC_MASK);
			FTM1->CONTROLS[0].CnSC |= FTM_CnSC_CHIE(ch_configuration->ftm_enable_interrupt);
			break;
	}
	if(FALSE == (ch_configuration->ftm_mode & CAPTURE_MODE))
	{
		FTM1->CONTROLS[channel].CnV = ch_configuration->ftm_value;
	}
	if(ch_configuration->ftm_enable_deadtime)
	{
		FTM1->DEADTIME = ch_configuration->ftm_dtval;
	}
	FTM1->SC = (FTM_SC_CLKS (ch_configuration->ftm_clocks)| FTM_SC_PS(ch_configuration->ftm_prescaler) | FTM_SC_CPWMS(cpwns_flag) | FTM_SC_TOIE(ch_configuration->ftm_enable_toie));
}


