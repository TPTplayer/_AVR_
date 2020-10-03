#include "KJ_playscale_calc.h"

float calc_scalefreq(int octave, int scale){
    float freq = 0.0f;
    float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    
    if(scale == REST){
        return 0.0f;
    }
    
    freq = (A_OCT1_FREQ * pow(2.0f, (float)octave)) * pow(2.0f, numerator[scale] / (float)SCALE_PER_OCTAVE);
    return freq;
}

float calc_clock(uint32_t clockspeed, float freq){
    float clock = 0.0f;
    float microsec_per_clock = (float)clockspeed / 1000000.0f;
    
    if(freq == 0.0f){
        return 0.0f;
    }
    
    clock = microsec_per_clock * (((1.0f / freq) / 2.0f) * 1000000.0f);
    return clock;
}

float calc_beattime(uint8_t beat, uint16_t mm){
    float msec_per_beat4 = (60.0f / (float)mm) * 1000.0f;
    float beattime;
    
    switch(beat){
    case BEAT1:
        beattime = msec_per_beat4 * 4.0f;
        break;
    case BEAT2:
        beattime = msec_per_beat4 * 2.0f;    
        break;
    case BEAT4:
        beattime = msec_per_beat4;
        break;
    case BEAT8:
        beattime = msec_per_beat4 / 2.0f;
        break;
    case BEAT16:
        beattime = msec_per_beat4 / 4.0f;
        break;
    case BEAT32:
        beattime = msec_per_beat4 / 8.0f;
        break;
    case BEAT64:
        beattime = msec_per_beat4 / 16.0f;
        break;
    }
    
    return beattime;
}

float calc_beatclock(uint32_t clockspeed, float beattime){
    float clock = 0.0f;
    float millisec_per_clock = (float)clockspeed / 1000.0f;
    
    clock = millisec_per_clock * beattime;
    return clock;
}
