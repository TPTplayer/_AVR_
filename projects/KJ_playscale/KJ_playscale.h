#ifndef KJ_PLAYSCALE_H_
#define KJ_PLAYSCALE_H_

#include <math.h>
#include <stdint.h>

//definition octaves
#define BVAL_OCT    0x04
#define OCT1    0x00 + BVAL_OCT
#define OCT2    0x01 + BVAL_OCT
#define OCT3    0x02 + BVAL_OCT
#define OCT4    0x03 + BVAL_OCT
#define OCT5    0x04 + BVAL_OCT
#define OCT6    0x05 + BVAL_OCT
#define OCT7    0x06 + BVAL_OCT
#define OCT8    0x07 + BVAL_OCT

//definition scales
#define BVAL_SCALE  0x05
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

#define GET_OCTNUM(_OCTAVENAME_)    (_OCTAVENAME_ - BVAL_OCT)
#define GET_OCTNAME(_OCTNUM_)       (_OCTNUM_ + BVAL_OCT)
#define GET_SCALENUM(_SCALENAME_)   (_SCALENAME_ - BVAL_SCALE)
#define GET_SCALENAME(_SCALENUM_)   (_SCALENUM_ + BVAL_SCALE)

//octave1 scale A frequency
//standard frequency: octave4 scale A (440Hz)
#define A_OCT1_FREQ         55
#define SCALE_PER_OCTAVE    12
#define OCTAVE_NUM          8

typedef struct{
    float clock[SCALE_PER_OCTAVE];
    uint32_t clockspeed;
}octaveclock_t;

octaveclock_t get_clockrange(uint32_t clockspeed, uint8_t octavename);
float calc_scalefreq(int octavename, int scalename);
float calc_clock(uint32_t clockspeed, float freq);

#endif /* KJ_PLAYSCALE_H_ */