/*
 * Fan_Controller.c
 *
 *  Created on: Jul 1, 2024
 *      Author: DELL
 */
#include "adc.h"
#include "lcd.h"
#include "pwm.h"
#include "dcmotor.h"
#include "lm35_sensor.h"


int main(void){
	uint8 Temparature = 0;
	ADC_ConfigType ADC_Configurations = {Internal , F_CPU8};
	LCD_init();
	ADC_init(&ADC_Configurations);
	DcMotor_Init();
	LCD_displayStringRowColumn(0,3,"FAN IS ");
	LCD_displayStringRowColumn(1,3,"TEMP =  C");
	while(1){
		Temparature = LM35_getTemperature();
		LCD_moveCursor(1,9);
		LCD_intgerToString(Temparature);
				if(Temparature >= 120)
				{
					LCD_displayStringRowColumn(0,10,"ON");
					DcMotor_Rotate(CW,100);
				}
				else if(Temparature >= 90)
				{
					LCD_displayStringRowColumn(0,10,"ON");
					DcMotor_Rotate(CW,75);
				}
				else if(Temparature >= 60)
				{
					LCD_displayStringRowColumn(0,10,"ON");
					DcMotor_Rotate(CW,50);
				}
				else if(Temparature >= 30)
				{
					LCD_displayStringRowColumn(0,10,"ON");
					DcMotor_Rotate(CW,25);
				}
				else if(Temparature < 30)
				{
					LCD_displayStringRowColumn(0,10,"OFF");
					DcMotor_Rotate(STOP,0);
				}
		    }


	}





