#line 1 "C:/Users/Danilo Pena/Documents/ATMega328P/USART/usart.c"
int estado;

void main() {
 WDTCSR |= 0x40;
 DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3);
 SREG_I_bit = 1;

 estado = 0;


 PCICR = 1<<PCIE2;
 PCMSK2 = (1<<PCINT23)|(1<<PCINT22);


 UART1_Init(9600);


 while(1);
}

void interrupt_rx() org IVT_ADDR_USART__RX{
 estado = UART1_Read();
 PORTB = estado;
}

void interruptButton() org IVT_ADDR_PCINT2{
 if(PIND6_bit == 1){
 estado++;
 if(estado>15){
 estado=0;
 }
 PORTB = estado;
 }
 if(PIND7_bit == 1){
 UART1_Write(estado);
 }
 PIND = 0;
}
