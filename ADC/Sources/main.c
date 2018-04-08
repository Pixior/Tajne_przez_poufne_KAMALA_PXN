/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include "mcg.h"
#include "systick.h"
#include "adc.h"
#include "gpio.h"
#include "uart.h"
#include "TFC_functions.h"
#include "stdio.h"

//DEFINITIONS


//VARIABLES
int a=0, b=0;




int main(void)
{
	//INITIALIZATIONS
	
	MCG_init;
	SysTick_init();
	
	GPIO_init();
	ADC_init();
	initUARTX();
	
	// enable interrupts globally
	asm (" CPSIE i ");
	
	//SOME NICE STURTUP CODE (DO NOT REMOVE!)
	ALL_LED_OFF;
	RED_LED_ON;
	delay_ms(400);
	WHITE;
	delay_ms(400);
	YELLOW;
	delay_ms(400);
	CYAN;
	delay_ms(400);
	PINK3;
	delay_ms(2000);
	
	//nothing important
	ALL_LED_OFF;
	
	
	for(;;) 		//endless loop
	{	
		a=ADC_Read(14);
		b=ADC_Read(11);
		delay_ms(100);
		printt(sprintf("a: %d ; b: %d \n\r",a,b));
	   
	}				//end of endless loop
	return 0;
}				//end of main loop


