/*
 * systick.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Pixior
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SysTickFreq		1000; //T=1ms

void SysTick_init();
void SysTick_Handler();
void delay_ms(unsigned int _micros);

#endif /* SYSTICK_H_ */
