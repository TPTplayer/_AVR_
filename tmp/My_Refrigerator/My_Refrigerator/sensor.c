#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "sensor.h"

void ADC_initializer(void){
	volatile float dummy = 0;
	
	cli();
	/*ADC0 Initialize*/
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	_delay_ms(100);
	ADMUX = (0 << MUX0) | (1 << REFS0);
	_delay_ms(10);
	
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	dummy = ADC;
	_delay_ms(100);
	
	/*ADC1 Initialize*/
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	_delay_ms(100);
	ADMUX = (1 << MUX0) | (1 << REFS0);
	_delay_ms(10);
	
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	dummy = ADC;
	_delay_ms(100);
	
	/*ADC2 Initialize*/
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	_delay_ms(100);
	ADMUX = (1 << MUX1) | (0 << MUX0) | (1 << REFS0);
	_delay_ms(10);
	
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	dummy = ADC;
	_delay_ms(100);
	
	/*ADC3 Initialize*/
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	_delay_ms(100);
	ADMUX = (1 << MUX1) | (1 << MUX0) | (1 << REFS0);
	_delay_ms(10);
	
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	dummy = ADC;
	_delay_ms(100);
	
	sei();
}

/*Thremistor: 10KD-5K*/
/*10KD-5K's B-parameter: 4200*/
/*voltage dividing resistor: 2K*/

float getHeatsink1Temp(void){
	float Vo = 0;
	float T0 = 298.15, R = 2000.0, R0 = 10000, B = 4200;
	float Rt = 0, T = 0, Cel = 0;
	
	ADMUX = (1 << REFS0); 
	_delay_us(100);
	
	ADCSRA = ADCSRA | (1 << ADSC); 
	while(ADCSRA & (1 << ADSC)); 
	
	for(int i = 0; i < F_VAL; i++){
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		Vo += ADC;
	}
	
	Vo /= F_VAL;
	Rt = R*(1023.0/(float)Vo - 1.0);
	
	T = 1.0/((1.0/T0) + (1/B)*log((Rt/R0)));
	Cel = T - 273.15;
	return Cel;
}

float getHeatsink2Temp(void){ 
	float Vo = 0;
	float T0 = 298.15, R = 2000.0, R0 = 10000, B = 4200;
	float Rt = 0, T = 0, Cel = 0;
	
	ADMUX = (1 << MUX0) | (1 << REFS0);
	_delay_us(100);
	
	ADCSRA = ADCSRA | (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	
	for(int i = 0; i < F_VAL; i++){
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		Vo += ADC;
	}
	
	Vo /= F_VAL;
	Rt = R*(1023.0/(float)Vo - 1.0);
	
	T = 1.0/((1.0/T0) + (1/B)*log((Rt/R0)));
	Cel = T - 273.15;
	return Cel;
}

float getHeatsink3Temp(void){
	float Vo = 0;
	float T0 = 298.15, R = 2000.0, R0 = 10000, B = 4200;
	float Rt = 0, T = 0, Cel = 0;
	
	ADMUX = (1 << MUX1) | (1 << REFS0);
	_delay_us(100);
	
	ADCSRA = ADCSRA | (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	
	for(int i = 0; i < F_VAL; i++){
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		Vo += ADC;
	}
	
	Vo /= F_VAL;
	Rt = R*(1023.0/(float)Vo - 1.0);
	
	T = 1.0/((1.0/T0) + (1/B)*log((Rt/R0)));
	Cel = T - 273.15;
	return Cel;
}

float getHeatsink4Temp(void){
	float Vo = 0;
	float T0 = 298.15, R = 2000.0, R0 = 10000, B = 4200;
	float Rt = 0, T = 0, Cel = 0;
	
	ADMUX = (1 << MUX0) | (1 << MUX1) | (1 << REFS0);
	_delay_us(100);
	
	ADCSRA = ADCSRA | (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	
	for(int i = 0; i < F_VAL; i++){
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		Vo += ADC;
	}
	
	Vo /= F_VAL;
	Rt = R*(1023.0/(float)Vo - 1.0);
	
	T = 1.0/((1.0/T0) + (1/B)*log((Rt/R0)));
	Cel = T - 273.15;
	return Cel;
}

float getInsideTemp(void){ 
	float Vo = 0;
	float T0 = 298.15, R = 2000.0, R0 = 10000, B = 4200;
	float Rt = 0, T = 0, Cel = 0;
	
	ADMUX = (1 << MUX2) | (1 << REFS0);
	_delay_us(100);
	
	ADCSRA = ADCSRA | (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	
	for(int i = 0; i < F_VAL; i++){
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		Vo += ADC;
	}
	
	Vo /= F_VAL;
	Rt = R*(1023.0/(float)Vo - 1.0);
	
	T = 1.0/((1.0/T0) + (1/B)*log((Rt/R0)));
	Cel = T - 273.15;
	return Cel;
}