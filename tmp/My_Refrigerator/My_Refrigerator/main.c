#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "CLCD.h"
#include "sensor.h"
#include "TWI.h"
#include "DataDisplay.h"

#define TEMP_LIMIT 75

volatile uint8_t flag_overheat[4] = {0, };

int main(void){
	DDRA = 0xFF; //SSR (0x0F | 0xFF)
	DDRB = 0xFF; //CLCD Databus (0xFF | 0xFF)
	DDRC = 0xFF; //status LED (0x0F | 0xFF)
	DDRD = (!0x08); //TWI, Switch
	DDRE = 0xFF; //CLCD Control (0x07 | 0xFF)
	DDRF = (!0x1F); //ADC
	DDRG = 0x1F; //unused
	
	float temp_heatsink[4] = {0, }, temp_inside = 0;
	uint8_t powcnt = 1;
	
	CLCD_initalizer();
	ADC_initializer();
	TWI_initializer();
	sei();

	while (1) {
		temp_heatsink[0] = getHeatsink1Temp();
		_delay_ms(1);
		temp_heatsink[1] = getHeatsink2Temp();
		_delay_ms(1);
		temp_heatsink[2] = getHeatsink3Temp();
		_delay_ms(1);
		temp_heatsink[3] = getHeatsink4Temp();
		_delay_ms(1);
		temp_inside = getInsideTemp();
		
		for(int cnt = 0; cnt < 4; cnt++){
			if(temp_heatsink[cnt] > TEMP_LIMIT){
				flag_overheat[cnt] = 1;
			}
			else if(temp_heatsink[cnt] < TEMP_LIMIT - 20){
				flag_overheat[cnt] = 0;
			}
		}
		
		if(!(PIND & 0x08)){
			powcnt += 1;
			if(powcnt == 5){
				powcnt = 1;
			}
		}
		
		if(powcnt == 1){
			PORTA = 0x01; 
			PORTC = 0x08; 
		}
		
		else if(powcnt == 2){
			PORTA = 0x03; //0000 0011
			PORTC = 0x0C; //0000 1100
		}
		
		else if(powcnt == 3){
			PORTA = 0x07; //0000 0111
			PORTC = 0x0E; //0000 1110
		}
		
		else if(powcnt == 4){
			PORTA = 0x0F; //0000 1111
			PORTC = 0x0F; //0000 1111
		}
		
		for(int i = 0; i < 4; i++){
			if(flag_overheat[i] == 1){
				DDRA = 0x00;
			}	
		}	
		
		for(int i = 0; i < 4; i++){
			if(flag_overheat[i] == 0 && i == 3){
				DDRA = 0xFF;
			}
			else if(flag_overheat[i] == 1){
				break;
			}
		}
			
		DisplayHeatsinkTemp(temp_heatsink);
		DisplayInsideTemp_master(temp_inside);
		_delay_ms(50);
		
		for(int i = 0; i < 4; i++){
			if(flag_overheat[i] == 1){
				DisplayOverheatPeltier(1);
				break;
			}
			else if(i == 3){
				DisplayOverheatPeltier(0);
			}
		}
	}
}

