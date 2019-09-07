int estado;

void main() {
     WDTCSR |= 0x40; // Desabilitando o WTD
     DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3);  // IOs B como saída
     SREG_I_bit = 1; // Habilita o GIE
     
     estado = 0;  // Estado inicial
     
     // Button
     PCICR = 1<<PCIE2; // Habilitando interrupção do PORTD
     PCMSK2 = (1<<PCINT23)|(1<<PCINT22); // Definindo pinos de interrupção PCINT23, 22 e 21
     
     // USART
     UART1_Init(9600); // Inicializando a UART
     //UART1_Init_Advanced(9600, _UART_EVENPARITY, _UART_TWO_STOPBITS);
     
     while(1);
}

void interrupt_rx() org IVT_ADDR_USART__RX{
     estado = UART1_Read();
     PORTB  = estado;
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
