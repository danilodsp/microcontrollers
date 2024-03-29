//******************************************************************************
//  MSP430F20xx - Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
//
//           MSP430F20xx
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//******************************************************************************

#include <msp430x20x3.h>
//#include <io430.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT6;                            // P1.0 output
  BCSCTL2 |= DIVS_3;						// Dividindo SMCLK por 8
  BCSCTL1 &= ~(BIT2+BIT1+BIT0);				// Setando o DCO para 120KHz
  											// SMCLK = 15 KHz
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 50000;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= BIT6;                            // Toggle P1.0
  CCR0 += 1000;                            // Add Offset to CCR0
}

