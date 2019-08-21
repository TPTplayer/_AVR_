#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdint.h>

#include "TWI_slave.h"

volatile uint8_t receive_flag = 0;
volatile int8_t receive_tempdata = 0;
volatile int8_t receive_overheat_flag = 0;

void TWI_initializer(void){
	cli();
	TWAR = (SLAVE_ADDR << 1) & 0xFE;
	TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	sei();
}

ISR(TWI_vect){
	if(TW_STATUS == TW_SR_DATA_ACK){
		if(receive_flag == 0){
			receive_tempdata = TWDR;
			receive_flag += 1;
		}
		else if(receive_flag == 1){
			receive_overheat_flag = TWDR;
			receive_flag += 1;
		}
	}
	else if(TW_STATUS == TW_BUS_ERROR){
		TWCR = 0x00;
		TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	}
}