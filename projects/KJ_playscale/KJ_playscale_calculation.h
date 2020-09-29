#ifndef KJ_PLAYESCALE_CALCULATION_H_
#define KJ_PLAYESCALE_CALCULATION_H_

#include <math.h>
#include <stdint.h>
#include "KJ_playscale_scaledef.h"

/*
frequency default time unit:	microsecond
quarter note default time unit: millisecond
*/

//definition notes
#define NOTE1_IDX	0x00
#define NOTE2_IDX	0x01
#define NOTE4_IDX	0x02
#define NOTE8_IDX	0x03
#define NOTE16_IDX	0x04
#define NOTE32_IDX	0x05
#define NOTE64_IDX	0x06

#define GET_ROUNDCLOCK(_CLOCK_)     (floor(_CLOCK_ + 0.5f))

//octave1 scale A frequency: 55Hz
//standard frequency: octave4 scale A (440Hz)
#define A_OCT1_FREQ         55
#define SCALE_PER_OCTAVE    12
#define OCTAVE_NUM          8

//1, 2, 4, 8, 16, 32, 64
#define NOTE_DIVISION		7

typedef struct{
    uint32_t clock[SCALE_PER_OCTAVE + 1];
    uint32_t clockspeed;
}octaveclock_t;

typedef struct{
    uint16_t mm;
    uint32_t clock[NOTE_DIVISION];
    uint32_t clockspeed;
}noteclock_t;

octaveclock_t get_clockrange(uint32_t vclockspeed, uint8_t octave);
float calc_scalefreq(int octave, int scale);
float calc_clock(uint32_t vclockspeed, float freq);

noteclock_t get_noteclockrange(uint32_t vclockspeed, uint16_t mm);
float * calc_notetimes(uint16_t mm);
float calc_noteclock(uint32_t vclockspeed, float notetime);
void change_note_mm(noteclock_t *note, uint32_t note_mm, uint32_t vclockspeed);

#endif /* KJ_PLAYESCALE_CALCULATION_H_ */