/* 
 * File:   main.c
 * Author: Danilo
 *
 * Created on May 24, 2016, 9:17 AM
 * 
 * C�digo de transmissor com endere�amento para comunica��o serial
 * 
 */

#pragma config FOSC = INTIO67 
#pragma config WDTEN = OFF, LVP = OFF 
#include <delays.h>
#include "p18f45k20.h"  
// "PBADEN = OFF" define que os bits 1, 2, 3 e 4 da porta B
// devem ser configurados como pinos I/O digitais.
#pragma config PBADEN = OFF

// 1200 bps, 8 bits, sem bit de paridade e 1 stop bit
void configura_serial()
{
    // configura o transmissor, desta vez com transmiss�o de 9 bits
    TXSTA = 0b01100000;
    // configura o receptor, desta vez com recep��o de 9 bits
    RCSTA = 0b11010000;
     
    //Pinos
    TRISC = 0xFF;

    // velocidade = Fosc/(64*(SPBRG+1))
    SPBRG = 12; // 1200 bps
}

void main()
{
    // vari�vel que verificar� o estado da chave
    unsigned char chave;
    // vari�vel que verificar� o endere�o do microcontrolador
    unsigned char endereco;

    // configura a porta B como entrada
    TRISB = 0xFF;

    // chama a fun��o para configurar a serial
    configura_serial();

    // Sa�da do PORTD para sinalizar envio
    TRISD = 0x00;
    // repete para sempre
    while(1){
        // se a chave estiver pressionada
        if (PORTBbits.RB0 == 0) {
            
            TXSTAbits.TX9D = 1; // enviar endere�o
            if(PORTBbits.RB1 == 0){ // transmite o endere�o
                TXREG = 0x01;
            }
            else{
                TXREG = 0x02;
            }
            
            // espera transmitir o endere�o
            while (!(PIR1&0b00010000));
            
            
            TXSTAbits.TX9D = 0; // enviar dados
            
            // transmite o valor 85 (bits alternados)
            TXREG = 0b01010101;
            // Sinaliza envio
            PORTD = ~PORTD;

            // espera 10 ciclos
            Delay10TCYx(1);

            // espera transmitir o dado
            while (!(PIR1&0b00010000));
        }
    }
}
