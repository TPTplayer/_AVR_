#include <avr/io.h>
#include <util/delay.h>
#include "mega128_ADC.h"

void ADC_initalizer(){
	volatile float dummy = 0;
	
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	_delay_ms(100);
	ADMUX = (1 << MUX0) | (1 << REFS0);
	_delay_ms(10);
	
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	dummy = ADC;
	_delay_ms(100);
}