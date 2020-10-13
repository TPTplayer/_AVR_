#ifndef KJ_PLAYSCALE_CALC_H_
#define KJ_PLAYSCALE_CALC_H_

#include <math.h>
#include <stdint.h>
#include "KJ_playscale_def.h"

#define GET_ROUNDCLOCK(_CLOCK_)     (uint32_t)(floor(_CLOCK_ + 0.5f))

float calc_scalefreq(int octave, int scale);
float calc_clock(uint32_t clockspeed, float freq);

float calc_beattime(uint8_t beat, uint16_t mm);
float calc_beatclock(uint32_t clockspeed, float beattime);

#endif /* KJ_PLAYSCALE_CALC_H_ */