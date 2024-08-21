 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35.c
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#include"lm35.h"
#include"adc.h"

/*[FUNCTION NAME]	: LM35_getTemperature
 *[DESCRIPTION]		: Function responsible for calculate the temperature from the ADC digital value
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 LM35_getTemperature(){

	uint8 temp_value = 0;
	uint16 adc_value = 0;
	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAX_VALUE *SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}
