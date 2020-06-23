#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdint.h>

#include "TWI_slave.h"

volatile uint8_t received_data;

void TWI_slave_initializer(void){
	TWAR = (SLAVE_ADDR << 1) & 0xFE;
	TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
}

ISR(TWI_vect){
	uint8_t status = TWSR & (~((1 << TWPS1) | (1 << TWPS0)));
	
	TWCR |= (1 << TWINT) | (1 << TWEA);
	TWCR &= ~(1 << TWSTO);
	
	if(status == 0x80){
		received_data = TWDR;
	}
}