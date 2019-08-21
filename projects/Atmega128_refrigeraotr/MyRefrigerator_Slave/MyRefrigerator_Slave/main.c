#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdint.h>

#include "CLCD.h"
#include "DisplayData.h"

#define SLAVE_ADDR 0x23

void setTimer_warning(void);
void TWI_initializer(void);

uint8_t receive_flag;
int8_t receive_tempdata;
int8_t receive_overheat_flag;

volatile int soundflag = 0;

ISR(TIMER3_OVF_vect){
	if(soundflag < 500){
		PORTF ^= 0x01;
		TCNT3 = 0xFFFF - 50;
		soundflag += 1;
	}
	else if(soundflag >= 500 && soundflag < 1000){
		TCNT3 = 0xFFFF - 50;
		soundflag += 1;
	}
	else if(soundflag == 1000){
		soundflag = 0;
		TCNT3 = 0xFFFF - 50;
	}
}

ISR(TWI_vect){
	if(TWSR == 0x60){ //after receive start condition and slave address
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	}
	else if(TWSR == 0x80 && receive_flag == 0){ //after receive data
		receive_tempdata = TWDR;
		receive_flag += 1;
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	}
	else if(TWSR == 0x80 && receive_flag == 1){ //after receive data
		receive_overheat_flag = TWDR;
		receive_flag += 1;
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
	}
	else if(TWSR == 0xA0){
		TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
	}
}

int main(void){
	DDRA = 0xFF; //unused
	DDRB = 0xFF; //CLCD Databus (0xFF | 0xFF)
	DDRC = 0xFF; //unused
	DDRD = 0x00; //TWI
	DDRE = 0xFF; //CLCD Control (0x07 | 0xFF)
	DDRF = 0xFF; //speaker (0x01 | 0xFF)
	DDRG = 0x1F; //unused
	
	int8_t temp = 0, ovh_flag = 0;
	
	setTimer_warning();
	CLCD_initalizer();
	TWI_initializer();
	
	sei();
	
	PORTF = 0x00;
	
    while (1) {
		if(receive_flag == 2){
			temp = receive_tempdata;
			ovh_flag = receive_overheat_flag;
			receive_flag = 0;
		}
		
		if(ovh_flag == 0){
			ETIMSK = 0x00;
			PORTF = 0x00;
		}
		else{
			ETIMSK = (1 << TOIE3);
		}
		
		DisplayCurrentStatus(temp, ovh_flag);
	}
}

void TWI_initializer(void){
	cli();
	TWAR = (SLAVE_ADDR << 1) & 0xFE; 
	TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWEN);
	sei();
}


void setTimer_warning(){
	TCCR3A = 0x00;
	TCCR3B = (1 << CS31) | (1 << CS30);
	TCCR3C = 0x00;
	ETIMSK = (1 << TOIE3);

	TCNT3 = 0xFFFF - 50;
}