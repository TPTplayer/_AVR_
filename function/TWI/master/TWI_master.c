#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "TWI_master.h"

void TWI_master_initializer(void){
	TWBR = 12;
	TWSR = 0x00; 
}

void TWI_start(void){
	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT))); //wait for set interrupt flag
}

void TWI_transmit(uint8_t slave_addr, uint8_t data){
	TWDR = (slave_addr << 1) & 0xFE; // R/W: W (master -> slave)
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN); //transmit
	while(!(TWCR & (1 << TWINT))); //wait ACK (interrupt flag set)
	
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN); 
	while(!(TWCR & (1 << TWINT)));
}

void TWI_stop(void){
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}