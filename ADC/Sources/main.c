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
#include "TPM.h"
#include "TFC_functions.h"
#include "stdio.h"

//DEFINITIONS
#define KP						50			// Proportional coefficient
#define KDP						25			// Differential coefficient

//VARIABLES
int a=0, b=0;


int main(void)
{
	//INITIALIZATIONS
	
	MCG_init;
	SysTick_init();
	
	GPIO_init();
	ADC_init();
	TPM_init();
	initUARTX();
	
	// enable interrupts globally
	asm (" CPSIE i ");
	
	//SOME NICE STURTUP CODE (DO NOT REMOVE!)
	ALL_LED_OFF;
	/*RED_LED_ON;
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
	ALL_LED_OFF;*/
	
	
	for(;;) 		//endless loop
	{	

		a=ADC_Read(14);
		b=ADC_Read(11);
		delay_ms(200);
		
		//UART
		char temp[20];
		sprintf(temp,"a: %d ; b: %d \n\r",a,b);
	    printt(temp);
	}				//end of endless loop
	return 0;
}				//end of main loop

void FTM0_IRQHandler()				// TPM0 ISR executing every 100ns
{
	TPM0_SC |= 0x80;							// clear TPM0 ISR flag
	//BLUE_LED_ON;
	BLUE_LED_TOGGLE;
	
	//BLUE_LED_OFF;
}

void FTM1_IRQHandler()				// TPM1 ISR executing every 10 ms
{
	TPM1_SC |= TPM_SC_TOF_MASK;					// clear TPM1 ISR flag
	//RED_LED_ON;
	RED_LED_TOGGLE;
	
	//RED_LED_OFF;
}

