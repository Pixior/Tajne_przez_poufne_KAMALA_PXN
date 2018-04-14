/*
 * gpio.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Pixior
 */
#include "derivative.h"
#include "gpio.h"

void GPIO_init()
{
// turn on all port clocks
SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

//setting pins to work as gpio
PORTB_PCR18 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
PORTB_PCR19 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
PORTD_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
PORTB_PCR8  |= PORT_PCR_MUX(1);	// PTB8 Camera SI
PORTB_PCR9  |= PORT_PCR_MUX(1);	// PTB9 Camera Clock
PORTA_PCR4  = 0;				// Set PTA4 Pin Control Register to Zero
PORTA_PCR5  |= PORT_PCR_MUX(1);	// PTA5 Motor 1 In 2 (direction)
PORTC_PCR8  |= PORT_PCR_MUX(1);	// PTC8 Motor 2 In 1 (direction)

//setting pins for peripherals

// set ADC inputs to ADC 
PORTC_PCR2  |= PORT_PCR_MUX(0);		// Camera 1 PTC2 ADC0_SE11
PORTC_PCR0  |= PORT_PCR_MUX(0);		// Mode select button ADC0_SE14

//uart pins set in uart.c ( PTA1 & PTA2 )

//set PWM outputs of PTM
PORTC_PCR9  |= PORT_PCR_MUX(3);	// PTC9 Motor 2 In 2 (speed) PTC8 TPM0_CH5
PORTA_PCR4  |= PORT_PCR_MUX(3);	// PTA4 Motor 1 In 1 (speed) PTA4 TPM0_CH1
PORTA_PCR12 |= PORT_PCR_MUX(3);	// Servo Out  PTA12 TPM1_CH0

//setting outputs
GPIOB_PDDR |= RED_LED_LOC|GREEN_LED_LOC;
GPIOD_PDDR |=BLUE_LED_LOC;
GPIOB_PDDR |= (1<<8);			// PTB8 Camera SI
GPIOB_PDDR |= (1<<9);			// PTB9 Camera Clock
GPIOA_PDDR |= (1<<4);			// PTA4 Motor 1 In 1
GPIOA_PDDR |= (1<<5);			// PTA5 Motor 1 In 2 (direction)
GPIOC_PDDR |= (1<<8);			// PTC9 Motor 2 In 1 (direction)
GPIOC_PDDR |= (1<<9);			// PTC9 Motor 2 In 2 
}
