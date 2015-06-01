/*
 * MSP430 Debounce Switch Test
 * Anthony Scranney
 * www.coder-tronics.com
 * Rev 1.1
 *
 * Please visit the sponsors on my site if you have found this code useful
 */

#include <msp430g2253.h>
/*** Global variable ***/
volatile int Count = 0;

int main(void) {

	/*** Watchdog timer and clock Set-Up ***/
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	BCSCTL1 = CALBC1_8MHZ;  		// Set range
	DCOCTL = CALDCO_8MHZ;   		// Set DCO step + modulation
	
	/*** GPIO Set-Up ***/
	P1DIR |= BIT0 + BIT6; 		// P1.0 and P1.6 set as outputs
	P1OUT &= ~BIT0; 			// P1.0 Low therefore Red LED off
	P1OUT |= BIT6; 				// P1.6 High therefore Green LED on
	P2DIR &= ~BIT0;				// P2.0 set as input
	P2SEL |= BIT0;				// P1.2 set to primary peripheral Timer1_A

	/*** Timer1_A Set-Up ***/
	TA1CCTL0 |= CM_2 + CCIS_0 + CAP + CCIE; // Negative edge, Capture input select, Compare mode, Compare interrupt enable
	TA1CTL |= TASSEL_2 + TAIE + MC_3;		// SMCLK, Interrupt enable, Up/Down count

	_BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 with interrupts enabled
}

	//Timer_A1 TACCR0 Interrupt Vector Handler Routine
	#pragma vector=TIMER1_A0_VECTOR
	__interrupt void Timer1A0(void)
	{
	P1OUT ^= BIT0; // Toggle Red LED
	Count++;
	}