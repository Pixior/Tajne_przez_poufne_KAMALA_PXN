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

//setting pins for peripherals

// set ADC inputs to ADC 
PORTC_PCR2  |= PORT_PCR_MUX(0);		// Camera 1 PTC2 ADC0_SE11
PORTC_PCR0  |= PORT_PCR_MUX(0);		// Mode select button ADC0_SE14

//uart pins set in uart.c ( PTA1 & PTA2 )

//setting outputs
GPIOB_PDDR |= RED_LED_LOC|GREEN_LED_LOC;
GPIOD_PDDR |=BLUE_LED_LOC;
}
