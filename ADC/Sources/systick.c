/*
 * systick.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Pixior
 */

#include "derivative.h" /* include peripheral declarations */
#include "systick.h" 
#include "clock.h"

static volatile unsigned int DelayTimer;

void SysTick_init()
{
	SYST_RVR=CORE_CLOCK/SysTickFreq;
	SYST_CVR=0;
	SYST_CSR=SysTick_CSR_ENABLE_MASK|SysTick_CSR_TICKINT_MASK|SysTick_CSR_CLKSOURCE_MASK;
}

void SysTick_Handler()
{
	if(DelayTimer<0xFFFFFFFF) DelayTimer++;
}

void delay_ms(unsigned int _micros)
{
	DelayTimer=0;
	
	while(DelayTimer<_micros){}
}
