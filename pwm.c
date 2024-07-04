/*
 * pwm.c
 *
 *  Created on: Jul 2, 2024
 *      Author: DELL
 */
#include "pwm.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */


void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0=0;
	OCR0 = (((float)duty_cycle/100)*255);
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	TCCR0 |=(1<<WGM00) |(1<<WGM01) |(1<<COM01) |(1<<CS01);
}
