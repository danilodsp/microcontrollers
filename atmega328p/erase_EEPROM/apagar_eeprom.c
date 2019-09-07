/*
Programa para apagar EEPROM
MCU: AtMega328P
*/
#include <avr/common.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define F_CPU 1000000UL  // 1 MHz

volatile int valor;
uint16_t addr;
volatile int cont;

int main(void){
	valor = 0x00;
	addr = 0x000;
	cont = 0;

	_delay_ms(10); // Comece a comentar aqui
	addr = 11;
	valor = 0x01;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	_delay_ms(10);
	addr = 13;
	valor = 0x01;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 139;
	valor = 0x01;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 141;
	valor = 0x02;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 267;
	valor = 0x01;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 269;
	valor = 0x03;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 395;
	valor = 0x01;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10);

	addr = 397;
	valor = 0x04;
	eeprom_write_word((uint16_t*)addr,valor);
	_delay_ms(10); // Até aqui

	while(1){
		/*if(addr<0x3FF){ // Para limpar descomente aqui e comente acima
			eeprom_write_word((uint16_t*)addr,valor);
			_delay_ms(10);
			addr++;
		}*/
	};
}
