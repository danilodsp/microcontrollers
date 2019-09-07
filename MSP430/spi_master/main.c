#include <msp430x20x2.h>
#include <intrinsics.h> // Intrinsic functions
#include "stdint.h" // Integers of defined sizes

#define nSS		P1OUT // Output pin for _SS (active low)

uint8_t RXdata, TXdata = 0x5A; // Received and transmitted data,


//Definitions

#define     BUTTON                BIT3
#define     BUTTON_OUT            P1OUT
#define     BUTTON_DIR            P1DIR
#define     BUTTON_IN             P1IN
#define     BUTTON_IE             P1IE
#define     BUTTON_IES            P1IES
#define     BUTTON_IFG            P1IFG
#define     BUTTON_REN            P1REN

//Prototipes

void InitializeButton(void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  InitializeButton();
  P1DIR |= BIT4+BIT6;                       // P1.0 output
  P1OUT = BIT4; 							// nSS output
  P1IFG = 0; 
  P1REN = BIT0|BIT1|BIT2; // Pull resistors on unused pins
  											// Setando clocks
  BCSCTL2 |= DIVS_3;						// Dividindo SMCLK por 8
  BCSCTL1 |= (BIT3+BIT2+BIT1+BIT0);			// DCO = 21MHz
  											// SMCLK = 2,6 MHz
  											// Configurando SPI
  USICTL0 = USIPE7 | USIPE6 | USIPE5 | USIMST | USIOE | USISWRST; // Enable SDI, SDO, SCLK, msb first, master, enable output, latch data
  USICTL1 = USIIE | USIIFG | USICKPH; // Can't clear USIIFG in reset mode 
  USICKCTL = USIDIV_7 | USISSEL_2; // SCLK = SMCLK / 128, clock idles high (CPOL = CKPL = 1)// Write then read (CPHA = 1 -> CKPH = 0), SPI not I2C, enable interrupt
  USICTL0 &= ~USISWRST; // Release USI from reset
  USICTL1 &= ~USIIFG; // Avoid unwanted interrupt											
  
	for (;;) { // Loop forever with interrupts
			_BIS_SR(LPM0_bits + GIE);
			//__low_power_mode_0(); // LPM0 between interrupts
			}
}

//Functions definitions

// Configure Push Button
void InitializeButton(void)                  
{
  BUTTON_DIR &= ~BUTTON;
  BUTTON_OUT |= BUTTON;
  /* A linha anterior serviu para deixar o pino em nível alto, pois,
   * quando pressionado, o push button utilizado no LaunchPad leva
   * P1IN3 a 0 (zero). Desta forma, sempre que pressionado o botão,
   * P1IN3 deverá ser novamente setado para que possa ser pressionado
   * outra vez.*/
  BUTTON_REN |= BUTTON;
  BUTTON_IES |= BUTTON;
  BUTTON_IFG &= ~BUTTON;
  BUTTON_IE  |= BUTTON;
}

// Timer A0 interrupt service routine
/*#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= BIT6;                            // Toggle P1.0
  CCR0 += 15000;                            // Add Offset to CCR0
}*/

#pragma vector=PORT1_VECTOR
__interrupt void button_inter(void)
{   	
		BUTTON_IFG &= ~BUTTON;
		int DEBOUNCE = 2;
		do{
		if (DEBOUNCE != 0){
			DEBOUNCE--;
			}
		__no_operation();
		}while(((P1IN & BIT3) == 0) && !(DEBOUNCE == 0));
		// Se estiver com problemas no seu programa,
		// Nunca ache que sabe de tudo sobre seus componentes...
		// ... Sempre procure conhecer tudo sobre eles.
		do{
			BUTTON_OUT |= BIT3;
			__no_operation();
		}while((P1IN & BIT3) == 0);
		if (DEBOUNCE == 0){
				nSS &= ~BIT4; // Lower nSS (make active)
				USISRL = TXdata; // Load shift register for transfer
				USICNT = 8; // Start SPI to transfer 8 bits
			}

/*						MUITA ATENÇÃO A ESTE PONTO
 * Caso o botão seja pressionado neste ponto do programa, P1IN3 irá
 * para zero e não haverá como ser gerada uma nova interrupção e 
 * consequentemente o botão não mais funcionará. A melhor solução
 * para contornar este problema foi setar periodicamente P1IN3 no 
 * tratamento da interrupção do Watchdog
 * */
}

#pragma vector = USI_VECTOR
__interrupt void USI_ISR ( void ) // NOT acknowledged automatically
{
		nSS |= BIT4; // Raise nSS ( make inactive)
		USICTL1 &= ~USIIFG; // Clear flag (no bitfield?)
		RXdata = USISRL; // Store received data (low byte)
		TXdata = RXdata + 1; // Slightly different next time!
}

