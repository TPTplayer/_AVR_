#include "KJ_playscale.h"

static uint8_t scale_to_intager[B + 1];
static uint8_t intager_to_scale[SCALE_PER_OCTAVE] = {C, CS, D, DS, E, F, FS, G, GS, A, AS, B};

static uint8_t octave_to_intager[OCT8 + 1];
static uint8_t intager_to_octave[OCTAVE_NUM] = {OCT1, OCT2, OCT3, OCT4, OCT5, OCT6, OCT7, OCT8};

void init_KJ_playscale(void){
    int oct_idx = 0, scale_idx = 0;
    
    for(oct_idx = 0; oct_idx < OCTAVE_NUM; oct_idx++){
        octave_to_intager[intager_to_octave[oct_idx]] = oct_idx;
    }
    for(scale_idx = 0; scale_idx < SCALE_PER_OCTAVE; scale_idx++){
        scale_to_intager[intager_to_scale[scale_idx]] = scale_idx;
    }
    
    return;    
}

int scale_to_intagerf(uint8_t scale){
    return scale_to_intager[scale];
}

uint8_t intager_to_scalef(int scale_num){
    return intager_to_scale[scale_num];
}

int octave_to_intagerf(uint8_t octave){
    return octave_to_intager[octave];
}

uint8_t intager_to_octavef(int octave_num){
    return intager_to_octave[octave_num];
}

float calc_scalefreq(int octave, int scale){
    float freq = 0.0f;
    float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    
    freq = (A_OCT1_FREQ * pow(2.0f, (float)octave)) * pow(2.0f, numerator[scale_to_intager[scale]] / (float)SCALE_PER_OCTAVE);
    return freq;
}

float calc_clock(uint32_t clockspeed, float freq){
    float clock = 0.0f;
    float microsec_per_clock = (float)clockspeed / 1000000.0f;
    
    clock = microsec_per_clock * ((1.0f / freq / 2.0f) * 1000000.0f);
    return clock;
}

void get_all_scalefreq(float *p){
    static float freqs[OCTAVE_NUM * SCALE_PER_OCTAVE] = {0.0f, };
    int oct_idx = 0, scale_idx = 0;
    
    for(oct_idx = 0; oct_idx < OCTAVE_NUM; oct_idx++){
        for(scale_idx = 0; scale_idx < SCALE_PER_OCTAVE; scale_idx++){
            freqs[(oct_idx * SCALE_PER_OCTAVE) + scale_idx] = calc_scalefreq(intager_to_octave[oct_idx], intager_to_scale[scale_idx]);
        }
    }        
    
    p = freqs;
    return;    
}

void get_all_required_clock(float *p, float *scalefreqs, uint32_t clockspeed){
    static float clocks[OCTAVE_NUM * SCALE_PER_OCTAVE] = {0.0f, };
    int oct_idx = 0, scale_idx = 0;
    
    for(oct_idx = 0; oct_idx < OCTAVE_NUM; oct_idx++){
        for(scale_idx = 0; scale_idx < SCALE_PER_OCTAVE; scale_idx++){
            clocks[(oct_idx * SCALE_PER_OCTAVE) + scale_idx] = calc_clock(clockspeed, scalefreqs[(oct_idx * SCALE_PER_OCTAVE) + scale_idx]);
        }
    }
    
    p = clocks;
    return;    
}