#include <avr/io.h>
#include <util/delay.h>
#include "TWI.h"

void TWI_initializer(void){
	TWBR = 12;
	TWSR = 0x00;
}

void TWI_transmit(uint8_t slave_addr, uint8_t data){
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); //transmit start signal
	while(((TWCR & 0x80) == 0) || (TWSR & 0xF8) != 0x08); //check status register
	
	_delay_us(2); 
	TWDR = (slave_addr << 1) & 0xFE; //TWD0 clear
	TWCR = (1 << TWINT) | (1 << TWEN); //TWI enable & Transmit TWDR
	while(((TWCR & 0x80) == 0) || (TWSR & 0xF8) != 0x18); //wait ACK signal
	
	TWDR = data; 
	TWCR = (1 << TWINT) | (1 << TWEN); //TWI enable & Transmit data
	while(((TWCR & 0x80) == 0) || (TWSR & 0xF8) != 0x28); //wait ACK signal
	
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); //transmit end signal
}