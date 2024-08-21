 /******************************************************************************
 *
 * File Name: HMI.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#include "lcd.h"
#include "adc.h"
#include "lm35.h"
#include "dc_motor.h"

int main(void){
	uint8 LM_temperature;

	/*ADC Dynamic Configration struct with two members Vref and Prescaler*/
	ADC_ConfigType ADC_Configrations = {INT_VREF , F_CPU_8};

	/*initialization function of ADC with argument which is address of configuration structure  set above*/
	ADC_init(&ADC_Configrations);
	LCD_init();
	DcMotor_Init();

	LCD_displayStringRowColumn(0, 4, "FAN is ");
	LCD_displayStringRowColumn(1, 4, "Temp =     C");

	while(1){
		/*The Microcontroller will continuously monitor the temperature and based on the temperature value*/
		LM_temperature = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,12);

		/*LCD Display section */
		if(LM_temperature  >= 100)
		{
			LCD_integerToString(LM_temperature);
		}
		else
		{
			LCD_integerToString(LM_temperature);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		/*Motor actions section */
		/*If the temperature is less than 30C turn off the fan.*/
		if(LM_temperature < 30)
		{
			LCD_displayStringRowColumn(0, 12, "OFF");
			DcMotor_Rotate(STOP,0);
		}

		/*If the temperature is greater than or equal 30C turn on the fan with 25% of its maximum speed*/
		else if((LM_temperature >= 30) && (LM_temperature < 60))
		{
			LCD_displayStringRowColumn(0, 12, "ON ");
			DcMotor_Rotate(CW,25);
		}

		/*If the temperature is greater than or equal 60C turn on the fan with 50% of its maximum speed.*/
		else if((LM_temperature >= 60) && (LM_temperature < 90))
		{
			LCD_displayStringRowColumn(0, 12, "ON ");
			DcMotor_Rotate(CW,50);
		}

		/*If the temperature is greater than or equal 90C turn on the fan with 75% of its maximum speed*/
		else if((LM_temperature >= 90) && (LM_temperature < 120))
		{
			LCD_displayStringRowColumn(0, 12, "ON ");
			DcMotor_Rotate(CW,75);
		}

		/*If the temperature is greater than or equal 120C turn on the fan with 100% of its maximum speed.*/
		else if(LM_temperature >= 120)
		{
			LCD_displayStringRowColumn(0, 12, "ON ");
			DcMotor_Rotate(CW,100);
		}
	}
}
