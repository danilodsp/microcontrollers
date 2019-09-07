#include <msp430g2231.h>

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

//Main code
 
void main(void) 
{ 
  WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog timer 
  InitializeButton();
  
  P1DIR = BIT6+BIT0;                   // P1.6 output (green LED) 
  //P1OUT = 0;                           // LED off 
   
  //BCSCTL3 |= LFXT1S_2;                 // LFXT1 = VLO 
  //IFG1 &= ~OFIFG;                      // Clear OSCFault flag 
  __bis_SR_register(SCG1 + SCG0);      // Stop DCO 
  BCSCTL2 |= SELM_3 + DIVM_3;          // MCLK = VLO/8 
  
  __enable_interrupt();
  
  while(1) 
  { 
	    P1OUT ^= BIT6;       	// Seta P1.6 
	    _delay_cycles(300); 
	    P1OUT &= ~BIT6;        	// Reseta P1.6
	    _delay_cycles(300);
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
  BUTTON_IE |= BUTTON;
}

//Interrupt

#pragma vector=PORT1_VECTOR
__interrupt void button_inter(void)
{   	
		BUTTON_IFG &= ~BUTTON;
		int DEBOUNCE = 2;
		do{
		if (DEBOUNCE != 0){
			DEBOUNCE--;
			}
		BUTTON_OUT |= BIT3;
		__no_operation();
		}while(((P1IN & BIT3) == 0) && !(DEBOUNCE == 0));
		// Se estiver com problemas no seu programa,
		// Nunca ache que sabe de tudo sobre seus componentes...
		// ... Sempre procure conhecer tudo sobre eles.
		if (DEBOUNCE == 0){
			BUTTON_OUT ^= BIT0;
			}

		do{
		BUTTON_OUT |= BIT3;
		__no_operation();
		}while((P1IN & BIT3) == 0);
/*						MUITA ATENÇÃO A ESTE PONTO
 * Caso o botão seja pressionado neste ponto do programa, P1IN3 irá
 * para zero e não haverá como ser gerada uma nova interrupção e 
 * consequentemente o botão não mais funcionará. A melhor solução
 * para contornar este problema foi setar periodicamente P1IN3 no 
 * tratamento da interrupção do Watchdog
 * */
}

//#pragma vector=WDT_VECTOR
//__interrupt void WDT_ISR(void)
//{
//    IE1 &= ~WDTIE;                   /* disable interrupt */
//    IFG1 &= ~WDTIFG;                 /* clear interrupt flag */
//    WDTCTL = WDTPW + WDTHOLD;        /* put WDT back in hold state */
//    BUTTON_IE |= BUTTON;             /* Debouncing complete */
//}
