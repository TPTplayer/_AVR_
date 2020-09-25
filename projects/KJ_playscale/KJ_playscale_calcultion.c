#include "KJ_playscale_calculation.h"

void change_note_mm(noteclock_t *note, uint32_t note_mm, uint32_t vclockspeed){
    *note = get_noteclockrange(vclockspeed, note_mm);
}

octaveclock_t get_clockrange(uint32_t vclockspeed, uint8_t octave){
    int cnt = 0;
    float freq, clk;
    octaveclock_t clocks;
    
    clocks.clockspeed = vclockspeed;
    for(cnt = 0; cnt < SCALE_PER_OCTAVE; cnt++){
        freq = calc_scalefreq(octave, cnt);
        clk = calc_clock(vclockspeed, freq);
        clocks.clock[cnt] = (uint32_t)GET_ROUNDCLOCK(clk);
    }
    
    clocks.clock[SCALE_PER_OCTAVE] = 0; //rest
    
    return clocks;
}

float calc_scalefreq(int octave, int scale){
    float freq = 0.0f;
    float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    
    freq = (A_OCT1_FREQ * pow(2.0f, (float)octave)) * pow(2.0f, numerator[scale] / (float)SCALE_PER_OCTAVE);
    return freq;
}

float calc_clock(uint32_t vclockspeed, float freq){
    float clock = 0.0f;
    float microsec_per_clock = (float)vclockspeed / 1000000.0f;
    
    clock = microsec_per_clock * (((1.0f / freq) / 2.0f) * 1000000.0f);
    return clock;
}

noteclock_t get_noteclockrange(uint32_t vclockspeed, uint16_t mm){
    int idx = 0;
    float *notetime;
    noteclock_t noteclock;
    
    noteclock.mm = mm;
    noteclock.clockspeed = vclockspeed;
    notetime = calc_notetimes(mm);
    for(idx = 0; idx < NOTE_DIVISION; idx++){
        noteclock.clock[idx] = GET_ROUNDCLOCK(calc_noteclock(vclockspeed, notetime[idx]));
    }
    
    return noteclock;
}

float * calc_notetimes(uint16_t mm){
    float msec_per_note4 = (60.0f / (float)mm) * 1000.0f;
    static float notes[NOTE_DIVISION];
    
    notes[NOTE1_IDX] = msec_per_note4 * 4.0f;
    notes[NOTE2_IDX] = msec_per_note4 * 2.0f;
    notes[NOTE4_IDX] = msec_per_note4; /*reference*/
    notes[NOTE8_IDX] = msec_per_note4 / 2.0f;
    notes[NOTE16_IDX] = msec_per_note4 / 4.0f;
    notes[NOTE32_IDX] = msec_per_note4 / 8.0f;
    notes[NOTE64_IDX] = msec_per_note4 / 16.0f;
    return notes;
}

float calc_noteclock(uint32_t vclockspeed, float notetime){
    float clock = 0.0f;
    float millisec_per_clock = (float)vclockspeed / 1000.0f;
    
    clock = millisec_per_clock * notetime;
    return clock;
}
