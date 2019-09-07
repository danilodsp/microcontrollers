/* 
 * File:   main.c
 * Author: Danilo
 *
 * Created on June 6, 2016, 9:24 AM
 */

#include <spi.h>
#include <delays.h>
#include "p18f45k20.h"

/*
 * 
 */
void main(){

    OpenSPI(0x00, 0x00, 0x00);
    WriteSPI( (1 << PWR_UP) );
    
}

