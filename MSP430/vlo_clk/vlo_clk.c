
#include  <msp430g2231.h>

void main(void)
{
  volatile unsigned int i;                  // Volatile to prevent removal
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL1 &= (~XTS);
  //BCSCTL1 |= XT2OFF;
  BCSCTL2 |= SELM_3;						// VLO --> MCLK 
  BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  
  P1DIR = BIT0+BIT6;
  while(1){
  P1OUT ^= 0x41;
  	__delay_cycles(10000);
  }
}
