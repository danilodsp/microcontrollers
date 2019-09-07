/* 
 * File:   Ex01.c
 * Author: Danilo
 *
 * Created on May 24, 2015, 6:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f45k20.h>

void delay();

unsigned int ctr = 0;
unsigned int delayVal = 2048;

int main(void) {
    LATA = 0;
    TRISA = 0xFF00;
    
    while(1)
    {
        LATA = 0x0055;
        delay();
        
        LATA = 0x00AA;
        delay();
        
        ctr++;
    }
    
    return 0;
}

void delay()
{
    unsigned int i, j;
    
    for(i = 0; i < delayVal; i++)
    {
        for(j = 0; j < 20; j++);
    }
}
