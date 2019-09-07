
#include  <msp430x20x2.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  /*if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } */
/* //1Mhz
  BCSCTL1 = CALBC1_1MHZ;                    // Set range
  DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation */

 //8Mhz
  BCSCTL1 = RSEL3+RSEL2+RSEL1+RSEL0;//+RSEL0                    // Set range
  DCOCTL = DCO2+DCO1+DCO0;//DCO2+                     // Set DCO step + modulation */

/* //12Mhz
  BCSCTL1 = CALBC1_12MHZ;                   // Set range
  DCOCTL = CALDCO_12MHZ;                    // Set DCO step + modulation*/

/* //16Mhz
  BCSCTL1 = CALBC1_16MHZ;                   // Set range
  DCOCTL = CALDCO_16MHZ;                    // Set DCO step + modulation*/

  P1DIR |= BIT6+BIT0;                            // P1.0,1 and P1.4 outputs
  //P1SEL |= 0x11;                            // P1.0,4 ACLK, SMCLK output

 
  while(1)
  {
  	P1OUT ^= BIT6+BIT0;    	                    // P1.1 = 1
  	__delay_cycles(21000000u);
 /* 	P1OUT ^= BIT6;
  	__delay_cycles(21000000u);
  	__delay_cycles(21000000u);
  	P1OUT ^= BIT6;
  	__delay_cycles(21000000u);
  	__delay_cycles(21000000u);
  	P1OUT ^= BIT6;
  	__delay_cycles(21000000u);
  	__delay_cycles(21000000u);
  	P1OUT ^= BIT6;
  	__delay_cycles(21000000u);
  	__delay_cycles(21000000u);*/
  }
}

