/*
 * clock.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Pixior
 */

#include "derivative.h"
#include "clock.h"

void InitClock (void) {

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
