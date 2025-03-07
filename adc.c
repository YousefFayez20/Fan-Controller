 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 11 to choose to connect internal reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	if(Config_Ptr->ref_volt == AREF){
		ADMUX = 0;

	}
	else if(Config_Ptr->ref_volt == AVCC){
		ADMUX = (1<<REFS0);

	}
	else if(Config_Ptr->ref_volt == Reserved){
		ADMUX = (1<<REFS1);

	}
	else if(Config_Ptr->ref_volt == Internal){
		ADMUX = (1<<REFS0)|(1<<REFS1);

	}

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	SET_BIT(ADCSRA, ADEN);
	if(Config_Ptr->prescaler == F_CPU2)
			{
				SET_BIT(ADCSRA, ADPS0);
				CLEAR_BIT(ADCSRA,ADPS1);
		     	CLEAR_BIT(ADCSRA,ADPS2);
			}
			else if(Config_Ptr->prescaler == F_CPU4)
			{
				SET_BIT(ADCSRA, ADPS1);
				CLEAR_BIT(ADCSRA,ADPS0);
				CLEAR_BIT(ADCSRA,ADPS2);
			}
			else if(Config_Ptr->prescaler == F_CPU8)
			{
				SET_BIT(ADCSRA, ADPS1);
				SET_BIT(ADCSRA, ADPS0);
				CLEAR_BIT(ADCSRA,ADPS2);
			}
			else if(Config_Ptr->prescaler == F_CPU16)
			{
				SET_BIT(ADCSRA, ADPS2);
				CLEAR_BIT(ADCSRA,ADPS1);
				CLEAR_BIT(ADCSRA,ADPS0);
			}
			else if(Config_Ptr->prescaler == F_CPU32)
			{
				SET_BIT(ADCSRA, ADPS2);
				CLEAR_BIT(ADCSRA,ADPS1);
				SET_BIT(ADCSRA, ADPS0);
			}
			else if(Config_Ptr->prescaler == F_CPU64)
			{
				SET_BIT(ADCSRA, ADPS1);
				SET_BIT(ADCSRA, ADPS2);
				CLEAR_BIT(ADCSRA,ADPS0);
			}
			else if(Config_Ptr->prescaler == F_CPU128)
			{
				SET_BIT(ADCSRA, ADPS0);
				SET_BIT(ADCSRA, ADPS1);
				SET_BIT(ADCSRA, ADPS2);
			}

}


uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
