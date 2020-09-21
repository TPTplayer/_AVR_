#include "KJ_playscale.h"

octaveclock_t get_clockrange(uint32_t clockspeed, uint8_t octavename){
    int cnt = 0;
    float freq, clk;
    octaveclock_t clocks;
    
    clocks.clockspeed = clockspeed;
    for(cnt = 0; cnt < SCALE_PER_OCTAVE; cnt++){
        freq = calc_scalefreq(octavename, GET_SCALENAME(cnt));
        clk = calc_clock(clockspeed, freq);
        clocks.clock[cnt] = (uint32_t)GET_ROUNDCLOCK(clk);
    }
    
    return clocks;
}

float calc_scalefreq(int octavename, int scalename){
    float freq = 0.0f;
    float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    
    freq = (A_OCT1_FREQ * pow(2.0f, (float)GET_OCTNUM(octavename))) * pow(2.0f, numerator[GET_SCALENUM(scalename)] / (float)SCALE_PER_OCTAVE);
    return freq;
}

float calc_clock(uint32_t clockspeed, float freq){
    float clock = 0.0f;
    float microsec_per_clock = (float)clockspeed / 1000000.0f;
    
    clock = microsec_per_clock * (((1.0f / freq) / 2.0f) * 1000000.0f);
    return clock;
}