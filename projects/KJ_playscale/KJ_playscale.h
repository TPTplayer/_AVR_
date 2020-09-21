#ifndef KJ_PLAYSCALE_H_
#define KJ_PLAYSCALE_H_

#include <math.h>
#include <stdint.h>

/*
frequency default time unit:	microsecond
quarter note default time unit: millisecond
*/

//definition octaves
#define BVAL_OCT    0x02
#define OCT1    0x00 + BVAL_OCT
#define OCT2    0x01 + BVAL_OCT
#define OCT3    0x02 + BVAL_OCT
#define OCT4    0x03 + BVAL_OCT
#define OCT5    0x04 + BVAL_OCT
#define OCT6    0x05 + BVAL_OCT
#define OCT7    0x06 + BVAL_OCT
#define OCT8    0x07 + BVAL_OCT

//definition scales
#define BVAL_SCALE  0x0A
#define C   0x00 + BVAL_SCALE
#define CS  0x01 + BVAL_SCALE
#define D   0x02 + BVAL_SCALE
#define DS  0x03 + BVAL_SCALE
#define E   0x04 + BVAL_SCALE
#define F   0x05 + BVAL_SCALE
#define FS  0x06 + BVAL_SCALE
#define G   0x07 + BVAL_SCALE
#define GS  0x08 + BVAL_SCALE
#define A   0x09 + BVAL_SCALE
#define AS  0x0A + BVAL_SCALE
#define B   0x0B + BVAL_SCALE

//definition notes
#define NOTE1_IDX	0x00
#define NOTE2_IDX	0x01
#define NOTE4_IDX	0x02
#define NOTE8_IDX	0x03
#define NOTE16_IDX	0x04
#define NOTE32_IDX	0x05
#define NOTE64_IDX	0x06

#define GET_OCTNUM(_OCTAVENAME_)    (_OCTAVENAME_ - BVAL_OCT)
#define GET_OCTNAME(_OCTNUM_)       (_OCTNUM_ + BVAL_OCT)
#define GET_SCALENUM(_SCALENAME_)   (_SCALENAME_ - BVAL_SCALE)
#define GET_SCALENAME(_SCALENUM_)   (_SCALENUM_ + BVAL_SCALE)

#define GET_ROUNDCLOCK(_CLOCK_)     (floor(_CLOCK_ + 0.5f))

//octave1 scale A frequency
//standard frequency: octave4 scale A (440Hz)
#define A_OCT1_FREQ         55
#define SCALE_PER_OCTAVE    12
#define OCTAVE_NUM          8

#define NOTE_DIVISION		7

typedef struct{
    uint32_t clock[SCALE_PER_OCTAVE];
    uint32_t clockspeed;
}octaveclock_t;

typedef struct{
	uint16_t mm;
	uint32_t clock[NOTE_DIVISION];
	uint32_t clockspeed;
}note_t;

octaveclock_t get_clockrange(uint32_t clockspeed, uint8_t octavename);
float calc_scalefreq(int octavename, int scalename);
float calc_clock(uint32_t clockspeed, float freq);

note_t get_noteclockrange(uint32_t clockspeed, uint16_t mm);
float * calc_notetimes(uint16_t mm);
float calc_noteclock(uint32_t clockspeed, float notetime);

#endif /* KJ_PLAYSCALE_H_ */