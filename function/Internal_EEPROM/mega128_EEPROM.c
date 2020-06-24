#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mega128_EEPROM.h"

void eeprom_write(uint8_t addr, uint8_t data){
	while((EECR & (1 << EEWE)));
	
	EEAR = addr;
	EEDR = data;
	
	EECR |= (1 << EEMWE) | (1 << EEWE);
	return;
}

uint8_t eeprom_read(uint8_t addr){
	while((EECR & (1 << EEWE)));
	
	EEAR = addr;
	EECR |= (1 << EERE);
	
	return EEDR;
}