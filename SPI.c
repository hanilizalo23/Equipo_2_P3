/**
 * Created on: 01/05/2022
 * Author: Nelida Hernández
 * @file    SPI.c
 * @brief   Configure SPI to communicate with Nokia_LCD peripheral.
 */

#include "SPI.h"
#include "MK64F12.h"
#include "bits.h"
#include "GPIO.h"
#include "stdio.h"
#include "Delay.h"

void SPI_enable(spi_channel_t channel)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->MCR &= ~ (SPI_MCR_MDIS_MASK | SPI_MCR_DCONF_MASK);
		break;
	case SPI_1:
		SPI1->MCR &= ~ (SPI_MCR_MDIS_MASK | SPI_MCR_DCONF_MASK);
		break;
	default:
		SPI2->MCR &= ~ (SPI_MCR_MDIS_MASK | SPI_MCR_DCONF_MASK);
		break;
	}
}

 void SPI_clk(spi_channel_t channel)
 {
		switch(channel)
		{
		case SPI_0:
			SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;
			break;
		case SPI_1:
			SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
			break;
		default:
			SIM->SCGC6 |= SIM_SCGC3_SPI2_MASK;
			break;
		}
 }

 void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
 {
		switch(channel)
		{
		case SPI_0:
			if(SPI_SLAVE == master_or_slave)
			{
				SPI0->MCR &= ~SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI0->MCR |= SPI_MCR_MSTR_MASK;
			}
			break;
		case SPI_1:
			if(SPI_SLAVE == master_or_slave)
			{
				SPI1->MCR &= ~SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI1->MCR |= SPI_MCR_MSTR_MASK;
			}
			break;
		default:
			if(SPI_SLAVE == master_or_slave)
			{
				SPI2->MCR &= ~SPI_MCR_MSTR_MASK;
			}
			else
			{
				SPI2->MCR |= SPI_MCR_MSTR_MASK;
			}
			break;
		}
 }

 void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
 {
		switch(channel)
		{
		case SPI_0:
			if(SPI_DISABLE_FIFO == enable_or_disable)
			{
				SPI0->MCR |= (SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			else
			{
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			break;
		case SPI_1:
			if(SPI_DISABLE_FIFO == enable_or_disable)
			{
				SPI1->MCR |= (SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			else
			{
				SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			break;
			break;
		default:
			if(SPI_DISABLE_FIFO == enable_or_disable)
			{
				SPI2->MCR |= (SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			else
			{
				SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);
			}
			break;
			break;
		}
 }

 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
 {
		switch(channel)
		{
		case SPI_0:
			if(SPI_LOW_POLARITY == cpol)
			{
				SPI0->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			break;
		case SPI_1:
			if(SPI_LOW_POLARITY == cpol)
			{
				SPI1->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			break;
		default:
			if(SPI_LOW_POLARITY == cpol)
			{
				SPI2->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPOL_MASK;
			}
			else
			{
				SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK;
			}
			break;
		}
 }

 void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
 {
		switch(channel)
		{
		case SPI_0:
			/*Clears the last value*/
			SPI0->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_FMSZ_MASK;
			/*Assigns new value*/
			SPI0->CTAR[SPI_CTAR_0] |= frame_size;
			break;
		case SPI_1:
			/*Clears the last value*/
			SPI1->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_FMSZ_MASK;
			/*Assigns new value*/
			SPI1->CTAR[SPI_CTAR_0] |= frame_size;
			break;
		default:
			/*Clears the last value*/
			SPI0->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_FMSZ_MASK;
			/*Assigns new value*/
			SPI0->CTAR[SPI_CTAR_0] |= frame_size;
			break;
		}
 }

 void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
 {
		switch(channel)
		{
		case SPI_0:
			/*Clears the last value*/
			SPI0->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPHA_MASK;
			/*Assigns new value*/
			SPI0->CTAR[SPI_CTAR_0] |= (cpha << SPI_CTAR_CPHA_SHIFT);
			break;
		case SPI_1:
			/*Clears the last value*/
			SPI1->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPHA_MASK;
			/*Assigns new value*/
			SPI1->CTAR[SPI_CTAR_0] |= (cpha << SPI_CTAR_CPHA_SHIFT);
			break;
		default:
			/*Clears the last value*/
			SPI2->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_CPHA_MASK;
			/*Assigns new value*/
			SPI2->CTAR[SPI_CTAR_0] |= (cpha << SPI_CTAR_CPHA_SHIFT);
			break;
		}
 }

void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
{
	 switch(channel)
	 {
	 case SPI_0:
		 SPI0->CTAR[SPI_CTAR_0] |= baud_rate;
		 break;
	 case SPI_1:
		 SPI1->CTAR[SPI_CTAR_0] |= baud_rate;
		 break;
	 case SPI_2:
		 SPI2->CTAR[SPI_CTAR_0] |= baud_rate;
		 break;
	 }
 }

/*It selects if MSB or LSM bits is first transmitted*/
 void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
 {
	 switch(channel)
	 {
	 case SPI_0:
		 if (SPI_MSB == msb)
			 SPI0->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_LSBFE_MASK;
		 else if (SPI_LSM == msb)
			 SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
		 break;
	 case SPI_1:
		 if (SPI_MSB == msb)
			 SPI1->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_LSBFE_MASK;
		 else if (SPI_LSM == msb)
			 SPI1->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
		 break;
	 case SPI_2:
		 if (SPI_MSB == msb)
			 SPI2->CTAR[SPI_CTAR_0] &= ~SPI_CTAR_LSBFE_MASK;
		 else if (SPI_LSM == msb)
			 SPI2->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK;
		 break;
	 }
 }

/*It stars the SPI transmission by modifying the value of HALT bit*/
 void SPI_start_tranference(spi_channel_t channel)
 {
	 switch(channel)
	 {
	 case SPI_0:
		 SPI0->MCR &= ~SPI_MCR_HALT_MASK;
		 break;
	 case SPI_1:
		 SPI1->MCR &= ~SPI_MCR_HALT_MASK;
		 break;
	 case SPI_2:
		 SPI2->MCR &= ~SPI_MCR_HALT_MASK;
		 break;
	 }
 }

/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel)
{
	 switch(channel)
	 {
	 case SPI_0:
		 SPI0->MCR |= SPI_MCR_HALT_MASK;
		 break;
	 case SPI_1:
		 SPI1->MCR |= SPI_MCR_HALT_MASK;
		 break;
	 case SPI_2:
		 SPI2->MCR |= SPI_MCR_HALT_MASK;
		 break;
	 }
}

void SPI_tranference(spi_channel_t channel, uint8_t data)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->PUSHR = ((SPI0->PUSHR) & ~(SPI_PUSHR_TXDATA_MASK)) | data;
		//SPI0->PUSHR = (data & SPI_PUSHR_TXDATA_MASK) | SPI_PUSHR_EOQ_MASK;
		while(FALSE == (SPI0->SR & SPI_SR_TCF_MASK))
		{
		}
		delay(100);
		SPI0->PUSHR |= SPI_SR_TCF_MASK;
		break;
	case SPI_1:
		SPI1->PUSHR = ((SPI1->PUSHR) & ~(SPI_PUSHR_TXDATA_MASK)) | data;
		while(FALSE == (SPI1->SR & SPI_SR_TCF_MASK))
		{
		}
		SPI1->PUSHR |= SPI_SR_TCF_MASK;
		break;
	default:
		SPI2->PUSHR = ((SPI1->PUSHR) & ~(SPI_PUSHR_TXDATA_MASK)) | data;
		while(FALSE == (SPI1->SR & SPI_SR_TCF_MASK))
		{
		}
		SPI2->PUSHR |= SPI_SR_TCF_MASK;
		break;
	}
}

void SPI_init(const spi_config_t* config_struct)
{
	spi_channel_t spi_channel = config_struct->spi_channel;
	gpio_port_name_t gpio_port = config_struct->spi_gpio_port.gpio_port_name;
	GPIO_clock_gating(gpio_port);
	GPIO_pin_control_register(gpio_port, config_struct->spi_gpio_port.spi_cs,  &(config_struct->pin_config));
	GPIO_pin_control_register(gpio_port, config_struct->spi_gpio_port.spi_clk, &(config_struct->pin_config));
	GPIO_pin_control_register(gpio_port, config_struct->spi_gpio_port.spi_sout,&(config_struct->pin_config));
	GPIO_pin_control_register(gpio_port, config_struct->spi_gpio_port.spi_sin, &(config_struct->pin_config));

	SPI_clk(spi_channel);
	SPI_enable(spi_channel);
	SPI_set_master(spi_channel,config_struct->spi_master);
	SPI_fifo(spi_channel,config_struct->spi_enable_fifo);
	SPI_clock_polarity(spi_channel,config_struct->spi_polarity);
	SPI_frame_size(spi_channel,config_struct->spi_frame_size);
	SPI_clock_phase(spi_channel,config_struct->spi_phase);
	SPI_baud_rate(spi_channel,config_struct->spi_baudrate);
	SPI_msb_first(spi_channel,config_struct->spi_lsb_or_msb);
}
