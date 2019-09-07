#include "msp430g2231.h"

main(){
		WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
		P1DIR |= BIT0+BIT6;
		long int i;
		P1OUT |= BIT0;
		P1OUT &= ~BIT6;
		while(1){
			for(i = 0; i < 200000; i++ ){
				
			}
			P1OUT ^= BIT6+BIT0;
		}
		
}
