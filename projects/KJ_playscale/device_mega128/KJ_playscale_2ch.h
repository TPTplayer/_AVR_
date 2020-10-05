#ifndef KJ_PLAYSCALE_2CH_H_
#define KJ_PLAYSCALE_2CH_H_

#ifndef F_CPU
#define F_CPU 11059200
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdlib.h>

#include "KJ_playscale_def.h"
#include "KJ_playscale_calc.h"

typedef struct{
	uint16_t bpm;
	uint32_t len;
	uint32_t *scaleclock;
	uint32_t *beatclock;
}channel_t;

typedef struct{
	uint8_t activate;
	channel_t channel_01;
	channel_t channel_02;
}header_t;

typedef struct{
	uint32_t ch01_beatcounter;
	uint32_t ch01_dpointer;
	uint32_t ch02_beatcounter;
	uint32_t ch02_dpointer;
}counter_t;

#define CH01		(1 << 5)
#define CH02		(1 << 3)
#define	_DDR_CH01	DDRB
#define _DDR_CH02	DDRE
#define _PORT_CH01	PORTB
#define _PORT_CH02	PORTE	

#define _SCALECLOCKSPEED	F_CPU
#define _BEATCLOCKSPEED		F_CPU / 1024

#define _CH01_SETSCALECLOCK(_CLOCK_)	(OCR1A = _CLOCK_, ICR1 = _CLOCK_)
#define _CH02_SETSCALECLOCK(_CLOCK_)	(OCR3A = _CLOCK_, ICR3 = _CLOCK_)
#define _CH01_SET_REFBEATCLOCK			TCNT0 = 0xFF - (1024 / 64);
#define _CH02_SET_REFBEATCLOCK			TCNT2 = 0xFE  

#define _CH01_OUTPUT_ENABLE		_DDR_CH01 |= CH01
#define _CH01_OUTPUT_DISABLE	_DDR_CH01 &= ~CH01
#define _CH02_OUTPUT_ENABLE		_DDR_CH02 |= CH02
#define _CH02_OUTPUT_DISABLE	_DDR_CH02 &= ~CH02	

#define _CH01_BEATINT_ENABLE	TIMSK |= (1 << TOIE0)
#define _CH01_BEATINT_DISABLE	TIMSK &= ~(1 << TOIE0)
#define _CH02_BEATINT_ENABLE	TIMSK |= (1 << TOIE2)
#define _CH02_BEATINT_DISABLE	TIMSK &= ~(1 << TOIE2)

void init_channel01(void);
void init_channel02(void);
void set_channel01(uint16_t bpm, uint32_t len, uint8_t *scaledata, uint8_t *beatdata);
void set_channel02(uint16_t bpm, uint32_t len, uint8_t *scaledata, uint8_t *beatdata);
void play(void);

ISR(TIMER0_OVF_vect);
ISR(TIMER2_OVF_vect);

#endif /* KJ_PLAYSCALE_2CH_H_ */