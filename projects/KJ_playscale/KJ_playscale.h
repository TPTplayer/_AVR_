#ifndef KJ_PLAYSCALE_H_
#define KJ_PLAYSCALE_H_

#include <math.h>
#include <stdint.h>

//definition octaves
#define OCT1    0
#define OCT2    1
#define OCT3    2
#define OCT4    3
#define OCT5    4
#define OCT6    5
#define OCT7    6
#define OCT8    7

//definition scales
#define C   0
#define CS  1
#define D   2
#define DS  3
#define E   4
#define F   5
#define FS  6
#define G   7
#define GS  8
#define A   9
#define AS  10
#define B   11  

//octave1 scale A frequency
//standard frequency: octave4 scale A (440Hz)
#define A_OCT1_FREQ         55
#define SCALE_PER_OCTAVE    12
#define OCTAVE_NUM          8

void init_KJ_playscale(void);
int scale_to_intagerf(uint8_t scale);
uint8_t intager_to_scalef(int scale_num);
int octave_to_intagerf(uint8_t octave);
uint8_t intager_to_octavef(int octave_num);
float calc_scalefreq(int octave, int scale);
float calc_clock(uint32_t clockspeed, float freq);
void get_all_scalefreq(float *p);
void get_all_required_clock(float *p, float *scalefreqs, uint32_t clockspeed);

#endif /* KJ_PLAYSCALE_H_ */