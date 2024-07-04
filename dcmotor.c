/*
 * dcmotor.c
 *
 *  Created on: Jul 2, 2024
 *      Author: DELL
 */
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "dcmotor.h"
#include "gpio.h"
#include "pwm.h"

void DcMotor_Init(void){
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID , PIN_OUTPUT);
	GPIO_writePin( PORTB_ID, PIN1_ID , LOGIC_LOW);
	GPIO_writePin( PORTB_ID, PIN0_ID , LOGIC_LOW);

}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if(state == CW){
		GPIO_writePin( PORTB_ID, PIN1_ID , LOGIC_HIGH);
		GPIO_writePin( PORTB_ID, PIN0_ID , LOGIC_LOW);
		PWM_Timer0_Start(speed);

	}
	else if(state == A_CW){
		GPIO_writePin( PORTB_ID, PIN1_ID , LOGIC_LOW);
		GPIO_writePin( PORTB_ID, PIN0_ID , LOGIC_HIGH);
		PWM_Timer0_Start(speed);

	}
	else if(state == STOP){
		GPIO_writePin( PORTB_ID, PIN1_ID , LOGIC_LOW);
		GPIO_writePin( PORTB_ID, PIN0_ID , LOGIC_LOW);
		PWM_Timer0_Start(0);

	}



}
