#include "KJ_playscale_2ch.h"

header_t ch_header;
counter_t ch_counter;

void init_channel01(void){
	_CH01_BEATINT_DISABLE;
	_CH01_OUTPUT_DISABLE;
	
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TCCR1A |= (1 << COM1A0);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
	
	ch_header.activate &= ~CH01;
	ch_counter.ch01_beatcounter = 0x00;
	ch_counter.ch01_dpointer = 0x00;
	return;
}

void init_channel02(void){
	_CH02_BEATINT_DISABLE;
	_CH02_OUTPUT_DISABLE;
	
	TCCR2 |= (1 << CS22) | (1 << CS20);
	TCCR3A |= (1 << COM1A0);
	TCCR3B |= (1 << WGM33) | (1 << WGM32) | (1 << CS30);
	
	ch_header.activate &= ~CH02;
	ch_counter.ch02_beatcounter = 0x00;
	ch_counter.ch02_dpointer = 0x00;
	return;
}

void set_channel01(uint16_t bpm, uint32_t len, uint32_t *scaledata, uint32_t *beatdata){
	uint8_t octave = 0x00, scale = 0x00;
	uint32_t idx = 0x00;
	
	ch_header.activate |= CH01;
	ch_header.channel_01.bpm = bpm;
	ch_header.channel_01.len = len;
	ch_header.channel_01.scaleclock = malloc(sizeof(uint32_t) * len);
	ch_header.channel_01.beatclock = malloc(sizeof(uint32_t) * len);
	
	for(idx = 0; idx < len; idx++){
		octave = (scaledata[idx] & 0xF0) >> 4;
		scale = scaledata[idx] & 0x0F;
		
		ch_header.channel_01.scaleclock[idx] = calc_clock(_SCALECLOCKSPEED, calc_scalefreq(octave, scale));
		ch_header.channel_01.beatclock[idx] = calc_beatclock(_BEATCLOCKSPEED, calc_beattime(beatdata[idx], bpm));	
	}
	return;
}

void set_channel02(uint16_t bpm, uint32_t len, uint32_t *scaledata, uint32_t *beatdata){
	uint8_t octave = 0x00, scale = 0x00;
	uint32_t idx = 0x00;
	
	ch_header.activate |= CH02;
	ch_header.channel_02.bpm = bpm;
	ch_header.channel_02.len = len;
	ch_header.channel_02.scaleclock = malloc(sizeof(uint32_t) * len);
	ch_header.channel_02.beatclock = malloc(sizeof(uint32_t) * len);
	
	for(idx = 0; idx < len; idx++){
		octave = (scaledata[idx] & 0xF0) >> 4;
		scale = scaledata[idx] & 0x0F;
		
		ch_header.channel_02.scaleclock[idx] = calc_clock(_SCALECLOCKSPEED, calc_scalefreq(octave, scale));
		ch_header.channel_02.beatclock[idx] = calc_beatclock(_BEATCLOCKSPEED, calc_beattime(beatdata[idx], bpm));
	}
	return;
}

void play(void){
	if((ch_header.activate & CH01) == CH01){
		_CH01_SETSCALECLOCK(ch_header.channel_01.scaleclock[ch_counter.ch01_dpointer]);
		_CH01_SET_REFBEATCLOCK;
		_CH01_BEATINT_ENABLE;	
	}	
	if((ch_header.activate & CH02) == CH02){
		_CH02_SETSCALECLOCK(ch_header.channel_02.scaleclock[ch_counter.ch02_dpointer]);
		_CH02_SET_REFBEATCLOCK;
		_CH02_BEATINT_ENABLE;
	}
	
	return;
}

ISR(TIMER0_OVF_vect){
	ch_counter.ch01_beatcounter += 1;
	if(ch_counter.ch01_beatcounter == ch_header.channel_01.beatclock[ch_counter.ch01_dpointer]){
		ch_counter.ch01_beatcounter = 0x00;
		ch_counter.ch01_dpointer += 1;
		
		_CH01_SETSCALECLOCK(ch_header.channel_01.scaleclock[ch_counter.ch01_dpointer]);
		_CH01_OUTPUT_DISABLE;
	}
	else{
		_CH01_OUTPUT_ENABLE;
	}
	
	if(ch_counter.ch02_dpointer == ch_header.channel_01.len){
		ch_header.activate &= ~CH01;
		_CH01_BEATINT_DISABLE;
		_CH01_OUTPUT_DISABLE;
	}
	
	_CH01_SET_REFBEATCLOCK;
}

ISR(TIMER2_OVF_vect){
	ch_counter.ch02_beatcounter += 1;
	if(ch_counter.ch02_beatcounter == ch_header.channel_02.beatclock[ch_counter.ch02_dpointer]){
		ch_counter.ch02_beatcounter = 0x00;
		ch_counter.ch02_dpointer += 1;
		
		_CH02_SETSCALECLOCK(ch_header.channel_02.scaleclock[ch_counter.ch02_dpointer]);
		_CH02_OUTPUT_DISABLE;
	}
	else{
		_CH02_OUTPUT_ENABLE;
	}
	
	if(ch_counter.ch02_dpointer == ch_header.channel_02.len){
		ch_header.activate &= ~CH02;
		_CH02_BEATINT_DISABLE;
		_CH02_OUTPUT_DISABLE;
	}
	
	_CH02_SET_REFBEATCLOCK;
}