#include <avr/io.h>
#include <avr/interrupt.h>
#include "CLCD.h"
#include "sensor.h"
#include "switch.h"
#include "TWI.h"
#include "DataDisplay.h"

#define TEMP_LIMIT 120

uint8_t flag_overheat[4] = {0, };
uint8_t powcnt = 1;

ISR(INT3_vect){
	powcnt += 1;
	if(powcnt == 4){
		powcnt = 1;
	}
}

int main(void){
	DDRA = 0xFF; //SSR (0x0F | 0xFF)
	DDRB = 0xFF; //CLCD Databus (0xFF | 0xFF)
	DDRC = 0xFF; //status LED (0x0F | 0xFF)
	DDRD = (!0x08); //TWI, Switch
	DDRE = 0xFF; //CLCD Control (0x07 | 0xFF)
	DDRF = (!0x1F); //ADC
	DDRG = 0x1F; //unused
	
	float temp_heatsink[4] = {0, }, temp_inside = 0;
	
	PORTA = 0x01;
	PORTC = 0xFE;
	
	CLCD_initalizer();
	ADC_initializer();
	TWI_initializer();
	EINT_set();
	sei();
	
    while (1) {
		temp_heatsink[0] = getHeatsink1Temp();
		temp_heatsink[1] = getHeatsink2Temp();
		temp_heatsink[2] = getHeatsink3Temp();
		temp_heatsink[3] = getHeatsink4Temp();
		temp_inside = getInsideTemp();
		
		for(int cnt = 0; cnt < 4; cnt++){
			if(temp_heatsink[cnt] > TEMP_LIMIT){
				flag_overheat[cnt] = 1;
				DisplayWaringMessage();
			}
			else if(temp_heatsink[cnt] < TEMP_LIMIT - 30){
				flag_overheat[cnt] = 0;
			}
		}
		
		if(flag_overheat[0] == 1){
			PORTA &= 0xFE; //1111 1110
			PORTC &= 0xF7; //1111 0111
		}
		if(flag_overheat[1] == 1){
			PORTA &= 0xFD; //1111 1101
			PORTC &= 0xFB; //1111 1011
		}
		if(flag_overheat[2] == 1){
			PORTA &= 0xFB; //1111 1011
			PORTC &= 0xFD; //1111 1101
		}
		if(flag_overheat[3] == 1){
			PORTA &= 0xF7; //1111 0111
			PORTC &= 0xFE; //1111 1110
		}
		
		if(flag_overheat[0] == 0 && powcnt == 1){
			PORTA |= 0x01; //0000 0001
			PORTC |= 0x08; //0000 1000
		}
		if(flag_overheat[1] == 0 && powcnt == 2){
			PORTA |= 0x02; //0000 0010
			PORTC |= 0x04; //0000 0100
		}
		if(flag_overheat[2] == 0 && powcnt == 3){
			PORTA |= 0x04; //0000 0100
			PORTC |= 0x02; //0000 0010
		}
		if(flag_overheat[3] == 0 && powcnt == 4){
			PORTA |= 0x08; //0000 1000
			PORTC |= 0x01; //0000 0001
		}
		
		DisplayHeatsinkTemp(temp_heatsink);
		DisplayInsideTemp_master(temp_inside);
	}
}

