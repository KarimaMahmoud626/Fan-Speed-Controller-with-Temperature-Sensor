/******************************************************************************
 *
 * Module: Pulse Width Modulation
 *
 * File Name: pwm.c
 *
 * Description: source file for the PWM driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#include <avr/io.h>
#include "pwm.h"
#include "gpio.h"

/*******************************************************************************
 *                                Functions Definitions                        *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;

	/*Setup compare value*/
	OCR0  = ((uint8)((uint16)(duty_cycle*255)/ 100));

	/*Configure PB3/OC0 as output pin*/
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);

	/*Configure timer control register
	 * 1.PWM mode --> FOC0 = 0
	 * 2.Fast PWM --> WGM01 = 1 & WGM00 = 1
	 * 3.Non-inverting mode --> COM01 = 1 & COM00 = 0
	 * 4.clock = F_CPU/8 CS00 = 0 & CS01 = 1 & CS02 = 0 */
	TCCR0 = 0x6A;
}
