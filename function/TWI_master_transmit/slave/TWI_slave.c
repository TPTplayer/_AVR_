#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdint.h>

#include "TWI_slave.h"

void TWI_initializer(void){
	cli();
	TWAR = (SLAVE_ADDR << 1) & 0xFE;
	TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	sei();
}

ISR(TWI_vect){
	if(TW_STATUS == TW_SR_DATA_ACK){
		
	}
	else if(TW_STATUS == TW_BUS_ERROR){
		TWCR = 0x00;
		TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	}
}