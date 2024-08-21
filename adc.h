 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAX_VALUE        1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                                Enums&Structs                                *
 *******************************************************************************/
typedef enum{
	AREF,AVCC,RSRVD,INT_VREF
}ADC_ReferenceVolatge;

typedef enum{
	F_CPU_20,F_CPU_21,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge vref;
	ADC_Prescaler prsclr;
}ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType*);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);


#endif /* ADC_H_ */
