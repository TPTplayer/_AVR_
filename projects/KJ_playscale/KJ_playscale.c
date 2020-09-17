#include "KJ_playscale.h"

float calc_scalefreq(int octave, int scale){
    float freq = 0.0f;
    float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    
    freq = (A_OCT1_FREQ * pow(2.0f, (float)octave)) * pow(2.0f, numerator[scale] / (float)SCALE_PER_OCTAVE);
    return freq;
}

float calc_clock(uint32_t clockspeed, float freq){
    float clock = 0.0f;
    float microsec_per_clock = (float)clockspeed / 1000000.0f;
    
    clock = microsec_per_clock * ((1.0f / freq / 2.0f) * 1000000.0f);
    return clock;
}

