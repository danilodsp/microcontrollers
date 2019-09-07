#line 1 "E:/Users/Danilo Pena/Documents/ATMega328P/LED.c"
int count;
int limite;
char estado;

void main() {
 WDTCSR |= 0x40;
 CLKPR = 0x88;
 DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2);
 DDRD = 0;
 SREG_I_bit = 1;

 estado = 1;
 limite = 8;


 PCICR = 1<<PCIE2;
 PCMSK2 = (1<<PCINT23)|(1<<PCINT22)|(1<<PCINT21);


 TIMSK0 &= ~(1<<TOIE0);
 TCCR0B = 0x05;
 while(1);
}

void interruptTimer() org IVT_ADDR_TIMER0_OVF {
 if(count >= limite){
 PORTB0_bit = ~PORTB0_bit;
 count = 0;
 }
 else{
 count++;
 }
}

void interruptButton() org IVT_ADDR_PCINT2 {
 int DEBOUNCE = 5;

 do{
 DEBOUNCE--;
 }while((PIND5_bit|PIND6_bit|PIND7_bit)&&(DEBOUNCE>0));

 if(DEBOUNCE==0){
 if(PIND5_bit == 1){
 if(estado!=3){
 estado = 1;
 TIMSK0 = 0;
 PORTB0_bit = 0;
 PORTB1_bit = 1;
 PORTB2_bit = 0;
 }
 }
 else if(PIND6_bit == 1){
 estado = 2;
 TIMSK0 = (1<<TOIE0);
 limite = 4;
 PORTB1_bit = 0;
 PORTB2_bit = 1;
 }
 else if(PIND7_bit == 1){
 if(estado!=1){
 estado = 3;
 TIMSK0 = (1<<TOIE0);
 limite = 1;
 PORTB1_bit = 1;
 PORTB2_bit = 1;
 }
 }}
 PIND = 0;
}
