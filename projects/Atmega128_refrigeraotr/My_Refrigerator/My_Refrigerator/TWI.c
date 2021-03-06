﻿#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TWI.h"
#include "CLCD.h"

void TWI_initializer(void){
	cli();
	TWBR = 12;
	TWSR = 0x00; 
	sei();
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