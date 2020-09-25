#ifndef KJ_PLAYSCALE_H_
#define KJ_PLAYSCALE_H_

#ifndef F_CPU
#define F_CPU 11059200
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "KJ_playscale_def.h"
#include "KJ_playscale_calc.h"

/*
frequency default time unit:	microsecond
quarter BEAT default time unit: millisecond
*/

#define SCALECLK F_CPU
#define BEATCLK F_CPU / 1024

#define _SCALETIMER_EN              TCCR1B |= (1 << CS10)
#define _SCALETIMER_DS              TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12))
#define _SCALECLOCK_SET(_CLOCK_)    (ICR1 = _CLOCK_,OCR1A = _CLOCK_)

#define _BEATTIMER_EN               TCCR3B |= (1 << CS30) | (1 << CS32);
#define _BEATTIMER_DS               TCCR3B &= ~((1 << CS30) | (1 << CS31) | (1 << CS32)) 
#define _BEATCLOCK_SET(_CLOCK_)     (TCNT3 = 0xFFFF - _CLOCK_)

#define OUTPUT_EN   DDRB |= 0x20
#define OUTPUT_DS   DDRB &= ~0x20

typedef struct{
    uint32_t clock[SCALE_PER_OCTAVE];
    uint32_t clockspeed;
}octaveclock_t;

typedef struct{
	uint16_t mm;
	uint32_t clock[BEAT_DIVISION];
	uint32_t clockspeed;
}beat_t;

typedef struct{
    uint16_t scaleclock;
    uint16_t beatclock;   
}sound_t;

typedef struct{
    uint16_t track_len;
    sound_t *track;    
}track_t;

typedef struct{
    uint16_t len;
    uint16_t mm;
    uint8_t *scaledata;
    uint8_t *beatdata;    
}pack_t;

ISR(TIMER3_OVF_vect);
pack_t data_pack(uint8_t *scaledata, uint8_t *beatdata, uint16_t len, uint16_t mm);
track_t get_sound(pack_t packdata);
void play(track_t track);

void scaletimer_init(void);
void beattimer_init(void);

#endif /* KJ_PLAYSCALE_H_ */