/*
 * TPM1.c
 *
 *  Created on: Apr 14, 2018
 *      Author: Pixior
 */

#include "derivative.h" /* include peripheral declarations */
#include "TPM.h" 


void TPM_init()
{
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK; 	// turn on all TPM clocks
	
	// configure TPM clock source to be 48 MHz
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;	// use MCGPLLCLK/2 clock when running from 8 MHz and PLL
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);		// MCGFLLCLK clock or MCGPLLCLK/2

	//Disable counters before setting prescalers
	TPM0_SC = 0;
	TPM0_CONF = 0;
	TPM1_SC = 0;
	TPM1_CONF = 0;
		
	// set TPM prescaler before enabling the timer
	TPM0_SC |= 7;					// prescaler for TPM0 (Motor) is 8 was 3
	TPM1_SC |= 7;					// prescaler for TPM1 (Servo) is 8 was 3
	
	// TPM modulo register, set frequency
	TPM0_MOD = 50000;		//was 600			// modulo TPM0 (Motor), periode = 0.10 ms (10000 Hz)
	TPM1_MOD = 60000;				// modulo TPM1 (Servo), periode = 10 ms (100 Hz)
		
	// set TPM clock mode to enable timer
	TPM0_SC |= TPM_SC_CMOD(1);		// enable TPM0 (Motor)
	TPM1_SC |= TPM_SC_CMOD(1);		// enable TPM1 (Servo)
		
	// configure TPM channel outputs high-true pulses
	TPM0_C1SC = 0x28;				// TPM0 channel1 Motor 1 In 1 speed left
	TPM0_C5SC = 0x28;				// TPM0 channel5 Motor 2 In 2 speed right
	TPM1_C0SC = 0x28;				// TPM1 channel0 Servo 1
		
	// TPM channel value registers, sets duty cycle
	TPM1_C0V = 9000;				// TPM1 channel0 Servo 1 ca. 1.5 ms (middle)
		
	// initial configuration of motors - only for safety - it should be overwritten in main code
	TPM0_C1V = 0;					// TPM0 channel1 left Motor 1 In 1 stop
	TPM0_C5V = 0;					// TPM0 channel5 right Motor 2 In 2 stop
	GPIOA_PDOR &= ~(1<<5);			// Set PTA5 left Motor 1 In 2 forward
	GPIOC_PDOR &= ~(1<<8);			// Set PTC8 right Motor 2 In 1 forward
		
	// configure interrupts in TPM1 & TPM0
	TPM1_SC |= TPM_SC_TOIE_MASK;	// enable overflow interrupt in TPM1 (10 ms rate)
	TPM0_SC |= TPM_SC_TOIE_MASK;	// enable overflow interrupt in TPM1 (100 ns rate)
	
    // enable interrupt 18 (TPM1 = FTM1)  in NVIC, no interrupt levels
    NVIC_ICPR |= (1 << 18);			// clear pending interrupt 18
    NVIC_ISER |= (1 << 18);			// enable interrupt 18
    
    // enable interrupt 17 (TPM0 = FTM0)  in NVIC, no interrupt levels   
    NVIC_ICPR |= (1 << 17);			// clear pending interrupt 17
    NVIC_ISER |= (1 << 17);			// enable interrupt 17
}
