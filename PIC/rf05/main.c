/* 
 * File:   main.c
 * Author: Danilo
 *
 * Created on May 24, 2016, 10:25 AM
 * 
 * C�digo do receptor com endere�amento para comunica��o serial
 * 
 */

#pragma config FOSC = INTIO67 
#pragma config WDTEN = OFF, LVP = OFF 
#include <delays.h>
#include "p18f45k20.h"

#define endereco_do_receptor 0x01

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

void main (void)
{
    // vari�vel que armazenar� o valor recebido da serial
    unsigned char valor_recebido;
    // endereco recebido
    int endereco;
    // dado recebido
    int dado;

    // chama a fun��o para configurar a serial
    configura_serial();

    // configura a porta D como sa�da
    TRISD = 0x00;
    PORTD = 0x00;

    // repete para sempre
    while(1){

        // prepara para receber
        RCSTA = 0b11010000;
        // espera chegar algum dado na serial
        while ((PIR1&32)==0);
        
        // ler o valor recebido
        valor_recebido = RCREG;
        
        if(RCSTAbits.RX9 == 1){ // estamos recebendo um endere�o
            endereco = valor_recebido;
        }
        else{ // estamos recebendo um dado
            dado = valor_recebido;
        }
        
        // reseta a serial para uma nova recep��o
        RCSTA = 0b10000000;

        // compara para ver se � o valor correto
        // e ent�o acende os LEDs
        if (valor_recebido == 0x55)
            PORTD = 0xFF;

        // espera alguns instantes
        Delay10KTCYx(10);

        // apaga os LEDs
        PORTD=0x00;
    }
}
