 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#include <avr/io.h>
#include "adc.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*[FUNCTION NAME]	: ADC_Init
 *[DESCRIPTION]		: Function responsible for initialize the ADC driver.
 *[ARGUMENTS]		: pointer to struct of type ADC_ConfigType
 *[RETURNS]			: void
 */
void ADC_init(const ADC_ConfigType *adcconfig_ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 configured to choose reference voltage based on vref parameter
	 * ADLAR   configured as 0 or 1 to adjust data right or left respectively depend on res_adj parameter
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX&0x3f) | ((adcconfig_ptr->vref)<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 configured to choose ADC_Clock = F_CPU/prsclr = 1Mhz/prsclr --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (ADCSRA&0xf8) | (adcconfig_ptr->prsclr);
	SET_BIT(ADCSRA,ADEN);

}

/*[FUNCTION NAME]	: ADC_readChannel
 *[DESCRIPTION]		: Function responsible for read analog data from a certain ADC channel
                      and convert it to digital using the ADC driver.
 *[ARGUMENTS]		: adc channel number of type uint8
 *[RETURNS]			: uint16
 */
uint16 ADC_readChannel(uint8 channel_num)
{
//	channel_num &= 0x07;  /*Channel number must be from 0 -> 7*/
//	ADMUX &= 0xE0;        /*Clear the first five bits in ADMUX reg (channel number MUX4:0 bits) before set the required channel*/
//
//	ADMUX |= channel_num; /*Choose the correct channel by setting the channel number in MUX4:0 bits*/
	/* ADMUX Register Description:
	 * 1.Channel number must be from 0 -> 7
	 * 2.Clear the first five bits in ADMUX reg (channel number MUX4:0 bits) before set the required channel
	 * 3.Choose the correct channel by setting the channel number in MUX4:0 bits
	 */
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);

	SET_BIT(ADCSRA,ADSC); /* Start conversion -> write '1' to ADSC bit */

	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /*Wait for conversion completion -> ADIF = 1*/

	SET_BIT(ADCSRA,ADIF); /*Clear ADIF by writing '1' to it*/

	return ADC;
}


