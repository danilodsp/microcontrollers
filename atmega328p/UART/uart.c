// Programa UART para ATMega328P
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>

#define BAUD_PRESCALE 51

FUSES =
{
	.low = LFUSE_DEFAULT,
	.high = HFUSE_DEFAULT,
	.extended = EFUSE_DEFAULT,
};

int count;
int limite;
int valor;

int main(){
	// PortB
	DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5);

	// Configurando UART
	UCSR0A |= (1<<TXC0); // Última transmissão completa
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Habilita RX e TX UART
	UCSR0C = 0x06; // Indica que a transmissão será de 8bits
	UBRR0H = (BAUD_PRESCALE >> 8); // Parte alta, 51, CLK = 8MHz, Baud Rate = 9600bps
	UBRR0L = BAUD_PRESCALE; // Parte baixa, 51, CLK = 8MHz, Baud Rate = 9600bps
	
	// Configurando o Timer0
    TIMSK0 |= (1<<TOIE0); // Desabilitando o Timer interrupt enable
    TCCR0B = 0x05; // Prescaller 1024
	limite = 2;

	// Configurando o AD
	ADMUX = (1<<ADLAR); // ADC0 e AD de 8bits
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); // Habilita o AD e Interrupção
	DIDR0 = (1<<ADC0D); // ADC0

	SREG |= (1<<SREG_I); // Habilita o GEI
	
	while(1);	
}

ISR(TIMER0_OVF_vect){
	if(count >= limite){
		ADCSRA |= (1<<ADSC); // Começa o AD
		count = 0;  // Zerando contador
    }
    else{
        count++;
    }
}

ISR(ADC_vect){
	valor = ADCH; // Carrega resultado do AD

	if(valor<50){
		PORTB = 0x01;
	}
	else if((valor>=50)&(valor<80)){
		PORTB = 0x03;
	}
	else if((valor>=80)&(valor<100)){
		PORTB = 0x07;
	}
	else if((valor>=100)&(valor<200)){
		PORTB = 0x0F;
	}
	else if(valor>=200){
		PORTB = 0x1F;
	}

	UCSR0B |= (1<<UDRIE0); // Habilita transmissão
}

ISR(USART_UDRE_vect){
	UDR0 = valor; // Carrega o resultado AD para transmitir
	UCSR0B &= ~(1<<UDRIE0); // Desabilita transmissão
}
