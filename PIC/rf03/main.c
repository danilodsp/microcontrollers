/* 
 * File:   main.c
 * Author: Danilo
 *
 * Created on May 24, 2016, 10:25 AM
 * 
 * Código do receptor para comunicação serial para o IMD
 * 
 */

#pragma config FOSC = INTIO67 
#pragma config WDTEN = OFF, LVP = OFF 
#include <delays.h>
#include "p18f45k20.h"

// 1200 bps, 8 bits, sem bit de paridade e 1 stop bit
void configura_serial()
{
      // configura o transmissor
      TXSTA = 0b00100000;
      // configura o receptor
      RCSTA = 0b10010000;
      
      //Pinos
      TRISC = 0xFF;

      // velocidade = Fosc/(64*(SPBRG+1))
      SPBRG = 12; // 1200 bps
}

void main (void)
{
      // variável que armazenará o valor recebido da serial
      unsigned char valor_recebido;

      // chama a função para configurar a serial
      configura_serial();

      // configura a porta D como saída
      TRISD = 0x00;
      PORTD = 0x00;

      // repete para sempre
      while(1){

            // prepara para receber
           RCSTA = 0b10010000;
            // espera chegar algum dado na serial
           while ((PIR1&32)==0);

                  // ler o valor recebido
                  valor_recebido = RCREG;

                  // reseta a serial para uma nova recepção
                  RCSTA = 0b10000000;

                  // compara para ver se é o valor correto
                  // e então acende os LEDs
                  if (valor_recebido == 0x55)
                    PORTD = 0xFF;

                  // espera alguns instantes
                  Delay10KTCYx(10);

                  // apaga os LEDs
                  PORTD=0x00;
      }
}
