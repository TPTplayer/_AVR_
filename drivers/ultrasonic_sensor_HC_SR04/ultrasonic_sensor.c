#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "ultrasonic_sensor.h"

// TRIG 0x01

volatile char stop = 0;
char t = 0;

ISR(TIMER1_OVF_vect){
	t += 1;
	TCNT1 = 65535 - 20;
}

ISR(INT0_vect){
	stop = 1;
}

void timer_start(void){
	cli();
	TCCR1A = 0x00;
	TCCR1B = 0x02;
	TCCR1C = 0x00;
	
	TIMSK = (1 << TOIE1);
	TCNT1 = 65535 - 20;
	sei();
}

void timer_end(void){
	cli();
	TCCR1B = 0x00;
	TIMSK = (0 << TOIE1);
	sei();
}

void falling_edge_EINT_set(void){
	cli();
	EICRA = (1 << ISC01);
	EIMSK = (1 << INT0);
	sei();
}

void trig_set(void){
	_delay_us(10);
	TRIG_PORT = TRIG;
	_delay_us(10);
	TRIG_PORT = 0x00;
}

float distance_calculation(int duration){
	float distance;
	distance = (float)(duration * 0.34)/2;
	return distance;
}


float ultrasonic_sensor(void){
	float distance;
	stop = 0;
	t = 0;
	
	trig_set();
	timer_start();
	falling_edge_EINT_set();
	
	while(1){
		if(stop == 1){
			timer_end();
			stop = 0;
			
			break;
		}
	}
	
	distance = distance_calculation(t);
	return distance;
}