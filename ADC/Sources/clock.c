/*
 * clock.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Pixior
 */

#include "derivative.h"
#include "clock.h"

void InitClock (void){
	int i, temp_reg;
	// configure clock to 48 MHz from a 8 MHz crystal
	MCG_C2 = (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK); 	// configure the oscillator settings
	MCG_C1 = (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3));		// divider for 8 MHz clock	
	for (i = 0 ; i < 24000 ; i++)						// wait for OSCINIT to set
	// now in FBE mode
	MCG_C6 |= MCG_C6_CME0_MASK;		// enable the clock monitor
	MCG_C5 |= MCG_C5_PRDIV0(1); 	// set PLL ref divider to divide by 2
	temp_reg = MCG_C6; 				// store present C6 value (as CME0 bit was previously set)
	temp_reg &= ~MCG_C6_VDIV0_MASK; // clear VDIV settings
	temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); 	// write new VDIV and enable PLL
	MCG_C6 = temp_reg; 				// update MCG_C6		
	for (i = 0 ; i < 4000 ; i++) 	// wait for PLLST status bit to set
	// now in PBE mode
	SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV4(1));	// core clock, bus clock div by 2	
	MCG_C1 &= ~MCG_C1_CLKS_MASK;	// switch CLKS mux to select the PLL as MCGCLKOUT	
	for (i = 0 ; i < 2000 ; i++)	// Wait for clock status bits to update
	// now in PEE mode, core and system clock 48 MHz, bus and flash clock 24 MHz
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
}

void InitClock2 (void) {

/***********************************************************************
 * 1) Transition from FEI to FBE mode.
 ***********************************************************************/
	MCG_C2 |= MCG_C2_RANGE0(1);		// Select high frequency range (3~32 MHz) for the crystal oscillator (which gives 8 MHz).
	MCG_C2 |= MCG_C2_EREFS0_MASK;	// Set oscillator to be an external reference.

	MCG_C1 |= MCG_C1_CLKS(2);		// Select an external reference clock to be a clock source.
	MCG_C1 |= MCG_C1_FRDIV(3);		// Set FLL external reference divider to 256. So the clock equals 31.25 kHz (required by FLL).
	MCG_C1 &= ~MCG_C1_IREFS_MASK;	// Select external reference clock for the FLL.


	while (!(MCG_S & MCG_S_OSCINIT0_MASK)) {
		/* Wait until MCG_S[OSCINT0] bit isn't set.
		 * It means that external clock source has finished its initialization cycles and stabilized */
	}

	while (MCG_S & MCG_S_IREFST_MASK) {
		/* Wait until MCG_S[IREFST] bit isn't clear.
		 * It means that the internal synchronization between clock domains has finished
		 * and the source of FLL reference clock is the external reference clock. */
	}

	while (!(MCG_S & MCG_S_CLKST(10))) {
		/* Wait until MCG_S[CLKST] bits aren't 0b10.
		 * It means that the internal synchronization between clock domains has finished and the external reference clock is selected.*/
	}


/***********************************************************************
 * 2) Switching from FBE to PBE mode.
 ***********************************************************************/
	MCG_C5 |= MCG_C5_PRDIV0(3);		// Set PLL external reference divider (PLL_R) to 4.
	MCG_C6 |= MCG_C6_PLLS_MASK;		// Select PLL.

	while (!(MCG_S & MCG_S_PLLST_MASK)) {
		/* Wait until MCG_S[PLLST] isn't set.
		 * It means that the internal synchronization between clock domains has finished and the external reference clock is selected.*/
	}

	while (!(MCG_S & MCG_S_LOCK0_MASK)) {
		/* Wait until MCG_S[LOCK0] isn't set.
		 * It means that PLL clock is currently locked.*/
	}


/***********************************************************************
 * 3) Switching from PBE to PEE mode.
 ***********************************************************************/
	MCG_C1 &= ~MCG_C1_CLKS_MASK;	// Select PLL as a clock source.

	while (!(MCG_S & MCG_S_CLKST(11))) {
		/* Wait until MCG_S[CLKST] bits aren't 0b11 */
	}

}
