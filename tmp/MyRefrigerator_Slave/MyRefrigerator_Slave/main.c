#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "TWI_slave.h"
#include "CLCD.h"
#include "DisplayData.h"

void setTimer_warning(void);

extern uint8_t receive_flag;
extern int8_t receive_tempdata;
extern int8_t receive_overheat_flag;

volatile int soundflag = 0;

ISR(TIMER3_OVF_vect){
	if(soundflag < 500){
		PORTB ^= 0x01;
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

int main(void){
	int8_t temp = 0, ovh_flag = 0; 
	
	DDRA = 0xFF; //CLCD Control (0x07 | 0xFF)
	DDRB = 0xFF; //speaker (0x01 | 0xFF)
	DDRC = 0xFF; //CLCD Databus (0xFF | 0xFF)
	DDRD = 0xFF; //TWI (0x03 | 0xFF)
	DDRE = 0xFF; //unused
	DDRF = 0xFF; //unused
	DDRG = 0x1F; //unused
	
	setTimer_warning();
	CLCD_initalizer();
	TWI_initializer();
	
	sei();
	
    while (1) {
		if(receive_flag == 1){
			temp = receive_tempdata;
		}
		if(receive_flag == 2){
			ovh_flag = receive_overheat_flag;
			receive_flag = 0;
		}
		
		if(ovh_flag == 1){
			setTimer_warning();
		}
		if(ovh_flag == 0){
			ETIMSK = 0x00;
			PORTB = 0x00;
		}
		
		DisplayCurrentStatus(temp, ovh_flag);
	}
}

void setTimer_warning(){
	TCCR3A = 0x00;
	TCCR3B = (1 << CS31) | (1 << CS30);
	TCCR3C = 0x00;
	ETIMSK = (1 << TOIE3);

	TCNT3 = 0xFFFF - 50;
}