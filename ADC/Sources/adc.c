/*
 * adc.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Pixior
 */


#include "derivative.h" /* include peripheral declarations */
#include "adc.h" 


void ADC_init()		//inicjalizacja
{


// turn on ADC0 clock
SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

// ADC0 clock configuration
ADC0_CFG1 |= 0x01;				// clock is bus clock divided by 2 = 12 MHz

// ADC0 resolution    
ADC0_CFG1 |= 0x08;				// resolution 10 bit, max. value is 1023

// ADC0 conversion mode
ADC0_SC3 = 0x00;				// single conversion mode

}

int ADC_Read(int _channel) //odczyt dzialajacy w pollingu
{
	int value=0;
	/*
	if(_channel==11)
	{
		ADC0_CFG2 |= 0x10;
	}
	if(_channel==14)
	{
		ADC0_CFG2 |= 0x10;
	}*/
	ADC0_SC1A  =  _channel;							// set ADC0 channel
	while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
	value = ADC0_RA;	
	
	return value;
}
