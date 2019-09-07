/* 
 * File:   main.c
 * Author: Danilo
 *
 * Created on May 24, 2016, 8:17 AM
 */

#pragma config FOSC = INTIO67 
#pragma config WDTEN = OFF, LVP = OFF 
#include  "p18f45K20.h" 
#include <delays.h>

void  main  (void) 
{ 
    TRISD = 0x00;
    
    while(1){
        PORTD = 0x55;
        Delay10KTCYx(10);
        PORTD = 0xAA;
        Delay10KTCYx(10); 
    }
} 
