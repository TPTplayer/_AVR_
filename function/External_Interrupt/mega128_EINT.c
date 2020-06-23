#include <avr/io.h>
#include <avr/interrupt.h>

#include "mega128_EINT.h"

void extint_initializer(int extint_num, uint8_t trig_mode){
	if(extint_num < 4){
		EICRA |= (trig_mode << extint_num);
	}
	else{
		EICRB |= (trig_mode << (extint_num - 4));
	}
	EIMSK |= (1 << extint_num);
	
	return;
}