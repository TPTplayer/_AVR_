#include "KJ_playscale.h"

static octaveclock_t scales_clocktable[8];
static noteclock_t notes_clocktable;

volatile static sound_t sound[16];
volatile static uint16_t scaleclock[16];
volatile static uint16_t noteclock[16];
volatile static uint16_t availtrack;
volatile static uint8_t scaleflag[16] = {0,};
volatile static uint8_t noteflag[16] = {0,};

/*scale output*/
ISR(TIMER1_OVF_vect){
    if(availtrack & CH1_1st){
        scaleclock[0] += 1;
        if(scaleclock[0] == sound[0].scaleclock){
            scaleflag[0] = ~scaleflag[0];
            scaleclock[0] = 0;
        }
    }        
    
    if(availtrack & CH1_2nd){
        scaleclock[1] += 1;
        if(scaleclock[1] == sound[1].scaleclock){
            scaleflag[1] = ~scaleflag[1];
            scaleclock[1] = 0;
        }
    }
            
    if(availtrack & CH1_3rd){
        scaleclock[2] += 1;
        if(scaleclock[2] == sound[2].scaleclock){
            scaleflag[2] = ~scaleflag[2];
            scaleclock[2] = 0;
        }
    }
        
    if(availtrack & CH1_4th){
        scaleclock[3] += 1;
        if(scaleclock[3] == sound[3].scaleclock){
            scaleflag[3] = ~scaleflag[3];
            scaleclock[3] = 0;
        }
    }
            
    if(availtrack & CH1_5th){
        scaleclock[4] += 1;
        if(scaleclock[4] == sound[4].scaleclock){
            scaleflag[4] = ~scaleflag[4];
            scaleclock[4] = 0;
        }
    }
            
    if(availtrack & CH1_6th){
        scaleclock[5] += 1;
        if(scaleclock[5] == sound[5].scaleclock){
            scaleflag[5] = ~scaleflag[5];
            scaleclock[5] = 0;
        }
    }
            
    if(availtrack & CH1_7th){
        scaleclock[6] += 1;
        if(scaleclock[6] == sound[6].scaleclock){
            scaleflag[6] = ~scaleflag[6];
            scaleclock[6] = 0;
        }
    }
            
    if(availtrack & CH1_8th){
        scaleclock[7] += 1;
        if(scaleclock[7] == sound[7].scaleclock){
            scaleflag[7] = ~scaleflag[7];
            scaleclock[7] = 0;
        }
    }
            
    if(availtrack & (CH2_9th << 8)){
        scaleclock[8] += 1;
        if(scaleclock[8] == sound[8].scaleclock){
            scaleflag[8] = ~scaleflag[8];
            scaleclock[8] = 0;
        }
    }
            
    if(availtrack & (CH2_10th << 8)){
        scaleclock[9] += 1;
        if(scaleclock[9] == sound[9].scaleclock){
            scaleflag[9] = ~scaleflag[9];
            scaleclock[9] = 0;
        }
    }
            
    if(availtrack & (CH2_11th << 8)){
        scaleclock[10] += 1;
        if(scaleclock[10] == sound[10].scaleclock){
            scaleflag[10] = ~scaleflag[10];
            scaleclock[10] = 0;
        }
    }        
    
    if(availtrack & (CH2_12th << 8)){
        scaleclock[11] += 1;
        if(scaleclock[11] == sound[11].scaleclock){
            scaleflag[11] = ~scaleflag[11];
            scaleclock[11] = 0;
        }
    }
            
    if(availtrack & (CH2_13th << 8)){
        scaleclock[12] += 1;
        if(scaleclock[12] == sound[12].scaleclock){
            scaleflag[12] = ~scaleflag[12];
            scaleclock[12] = 0;
        }
    }
            
    if(availtrack & (CH2_14th << 8)){
        scaleclock[13] += 1;
        if(scaleclock[13] == sound[13].scaleclock){
            scaleflag[13] = ~scaleflag[13];
            scaleclock[13] = 0;
        }
    }        
    
    if(availtrack & (CH2_15th << 8)){
        scaleclock[14] += 1;
        if(scaleclock[14] == sound[14].scaleclock){
            scaleflag[14] = ~scaleflag[14];
            scaleclock[14] = 0;
        }
    }
            
    if(availtrack & (CH2_16th << 8)){     
        scaleclock[15] += 1;
        if(scaleclock[15] == sound[15].scaleclock){
            scaleflag[15] = ~scaleflag[15];
            scaleclock[15] = 0;
        }
    }
    
    if(scaleflag[0]) PORT_CH1 |= CH1_1st;
    else PORT_CH1 &= ~CH1_1st;
    
    if(scaleflag[1]) PORT_CH1 |= CH1_2nd;
    else PORT_CH1 &= ~CH1_2nd;
    
    if(scaleflag[2]) PORT_CH1 |= CH1_3rd;
    else PORT_CH1 &= ~CH1_3rd;
    
    if(scaleflag[3]) PORT_CH1 |= CH1_4th;
    else PORT_CH1 &= ~CH1_4th;
    
    if(scaleflag[4]) PORT_CH1 |= CH1_5th;
    else PORT_CH1 &= ~CH1_5th;
    
    if(scaleflag[5]) PORT_CH1 |= CH1_6th;
    else PORT_CH1 &= ~CH1_6th;
    
    if(scaleflag[6]) PORT_CH1 |= CH1_7th;
    else PORT_CH1 &= ~CH1_7th;
    
    if(scaleflag[7]) PORT_CH1 |= CH1_8th;
    else PORT_CH1 &= ~CH1_8th;
    
    if(scaleflag[8]) PORT_CH2 |= CH2_9th;
    else PORT_CH2 &= ~CH2_9th;
    
    if(scaleflag[9]) PORT_CH2 |= CH2_10th;
    else PORT_CH2 &= ~CH2_10th;
    
    if(scaleflag[10]) PORT_CH2 |= CH2_11th;
    else PORT_CH2 &= ~CH2_11th;
    
    if(scaleflag[11]) PORT_CH2 |= CH2_12th;
    else PORT_CH2 &= ~CH2_12th;
    
    if(scaleflag[12]) PORT_CH2 |= CH2_13th;
    else PORT_CH2 &= ~CH2_13th;
    
    if(scaleflag[13]) PORT_CH2 |= CH2_14th;
    else PORT_CH2 &= ~CH2_14th;
    
    if(scaleflag[14]) PORT_CH2 |= CH2_15th;
    else PORT_CH2 &= ~CH2_15th;
    
    if(scaleflag[15]) PORT_CH2 |= CH2_16th;
    else PORT_CH2 &= ~CH2_16th;
} 

/*note output*/
ISR(TIMER3_OVF_vect){
    if(availtrack & CH1_1st){
        noteclock[0] += 1;
        DDR_CH1 |= CH1_1st;
        if(noteclock[0] == sound[0].noteclock){
            noteclock[0] = 0;
            noteflag[0] = 1;
            DDR_CH1 &= ~CH1_1st;
        }
    }        
    
    if(availtrack & CH1_2nd){
        noteclock[1] += 1;
        DDR_CH1 |= CH1_2nd;
        if(noteclock[1] == sound[1].noteclock){
            noteclock[1] = 0;
            noteflag[1] = 1;
            DDR_CH1 &= ~CH1_2nd;
        }
    }
            
    if(availtrack & CH1_3rd){
        noteclock[2] += 1;
        DDR_CH1 |= CH1_3rd;
        if(noteclock[2] == sound[2].noteclock){
            noteclock[2] = 0;
            noteflag[2] = 1;
            DDR_CH1 &= ~CH1_3rd;
        }
    }
            
    if(availtrack & CH1_4th){
        noteclock[3] += 1;
        DDR_CH1 |= CH1_4th;
        if(noteclock[3] == sound[3].noteclock){
            noteclock[3] = 0;
            noteflag[3] = 1;
            DDR_CH1 &= ~CH1_4th;
        }
    }
            
    if(availtrack & CH1_5th){
        noteclock[4] += 1;
        DDR_CH1 |= CH1_5th;
        if(noteclock[4] == sound[4].noteclock){
            noteclock[4] = 0;
            noteflag[4] = 1;
            DDR_CH1 &= ~CH1_5th;
        }
    }
            
    if(availtrack & CH1_6th){
        noteclock[5] += 1;
        DDR_CH1 |= CH1_6th;
        if(noteclock[5] == sound[5].noteclock){
            noteclock[5] = 0;
            noteflag[5] = 1;
            DDR_CH1 &= ~CH1_6th;
        }
    }
            
    if(availtrack & CH1_7th){
        noteclock[6] += 1;
        DDR_CH1 |= CH1_7th;
        if(noteclock[6] == sound[6].noteclock){
            noteclock[6] = 0;
            noteflag[6] = 1;
            DDR_CH1 &= ~CH1_7th;
        }
    }
            
    if(availtrack & CH1_8th){
        noteclock[7] += 1;
        DDR_CH1 |= CH1_8th;
        if(noteclock[7] == sound[7].noteclock){
            noteclock[7] = 0;
            noteflag[7] = 1;
            DDR_CH1 &= ~CH1_8th;
        }
    }
            
    if(availtrack & (CH2_9th << 8)){
        noteclock[8] += 1;
        DDR_CH2 |= CH2_9th;
        if(noteclock[8] == sound[8].noteclock){
            noteclock[8] = 0;
            noteflag[8] = 1;
            DDR_CH2 &= ~CH2_9th;
        }
    }
            
    if(availtrack & (CH2_10th << 8)){
        noteclock[9] += 1;
        DDR_CH2 |= CH2_10th;
        if(noteclock[9] == sound[9].noteclock){
            noteclock[9] = 0;
            noteflag[9] = 1;
            DDR_CH2 &= ~CH2_10th;
        }
    }        
    
    if(availtrack & (CH2_11th << 8)){
        noteclock[10] += 1;
        DDR_CH2 |= CH2_11th;
        if(noteclock[10] == sound[10].noteclock){
            noteclock[10] = 0;
            noteflag[10] = 1;
            DDR_CH2 &= ~CH2_11th;
        }
    }
            
    if(availtrack & (CH2_12th << 8)){
        noteclock[11] += 1;
        DDR_CH2 |= CH2_12th;
        if(noteclock[11] == sound[11].noteclock){
            noteclock[11] = 0;
            noteflag[11] = 1;
            DDR_CH2 &= ~CH2_12th;
        }
    }
            
    if(availtrack & (CH2_13th << 8)){
        noteclock[12] += 1;
        DDR_CH2 |= CH2_13th;
        if(noteclock[12] == sound[12].noteclock){
            noteclock[12] = 0;
            noteflag[12] = 1;
            DDR_CH2 &= ~CH2_13th;
        }
    }        
    
    if(availtrack & (CH2_14th << 8)){
        noteclock[13] += 1;
        DDR_CH2 |= CH2_14th;
        if(noteclock[13] == sound[13].noteclock){
            noteclock[13] = 0;
            noteflag[13] = 1;
            DDR_CH2 &= ~CH2_14th;
        }
    }        
    
    if(availtrack & (CH2_15th << 8)){
        noteclock[14] += 1;
        DDR_CH2 |= CH2_15th;
        if(noteclock[14] == sound[14].noteclock){
            noteclock[14] = 0;
            noteflag[14] = 1;
            DDR_CH2 &= ~CH2_15th;
        }
    }        
    
    if(availtrack & (CH2_16th << 8)){
        noteclock[15] += 1;
        DDR_CH2 |= CH2_16th;
        if(noteclock[15] == sound[15].noteclock){
            noteclock[15] = 0;
            noteflag[15] = 1;
            DDR_CH2 &= ~CH2_16th;
        }
    }
}

void output_enable(void){
   SCALE_TIMER_INIT;
   NOTE_TIMER_INIT;
   SCALE_COUNTER_SETCLOCK;
   NOTE_COUNTER_SETCLOCK;
   SCALE_TIMSK_INIT;
   NOTE_TIMSK_INIT;
   
   return;
}

void output_disable(void){
    TIMSK &= ~(1 << TOIE0);
    ETIMSK &= ~(1 << TOIE3);
    
    DDR_CH1 = 0x00;
    DDR_CH2 = 0x00;
    return;
}

void playscale_init(uint32_t vclockspeed_scale, uint32_t vclockspeed_note, uint32_t note_mm){
    int octidx = 0;
    
    for(octidx = 0; octidx < OCTAVE_NUM; octidx++){
        scales_clocktable[octidx] = get_clockrange(vclockspeed_scale, octidx);
    }
    change_note_mm(&notes_clocktable, note_mm, vclockspeed_note);
    output_disable();
    
    return;
}

void playscale_play(track_t tracks){
    uint32_t cnt[16] = {0, };
    uint8_t track_idx = 0;
    uint8_t idx = 0;
    
    uint8_t unpack_octave = 0x00, unpack_scale = 0x00, unpack_note = 0x00;
    
    availtrack = tracks.avail_track;
    output_enable();
    while(1){
        if(availtrack == 0x00){
            output_disable();
            break;
        }
        
        if(availtrack & CH1_1st){
            if(tracks.track_length[0] == cnt[0]){
                availtrack &= ~CH1_1st;
                DDR_CH1 &= ~CH1_1st;
            }
            else{
                unpack_note = tracks.notetrack0[cnt[0]];
                unpack_octave = (tracks.track0[cnt[0]] & 0xF0) >> 4;
                unpack_scale = tracks.track0[cnt[0]] & 0x0F;
                
                sound[0].noteclock = notes_clocktable.clock[unpack_note];
                sound[0].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }     
        }            
        
        if(availtrack & CH1_2nd){
            if(tracks.track_length[1] == cnt[1]){
                availtrack &= ~CH1_2nd;
                DDR_CH1 &= ~CH1_2nd;
            }
            else{
                unpack_note = tracks.notetrack1[cnt[1]];
                unpack_octave = (tracks.track1[cnt[1]] & 0xF0) >> 4;
                unpack_scale = tracks.track1[cnt[1]] & 0x0F;
                
                sound[1].noteclock = notes_clocktable.clock[unpack_note];
                sound[1].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }            
        
        if(availtrack & CH1_3rd){
            if(tracks.track_length[2] == cnt[2]){
                availtrack &= ~CH1_3rd;
                DDR_CH1 &= ~CH1_3rd;
            }
            else{
                unpack_note = tracks.notetrack2[cnt[2]];
                unpack_octave = (tracks.track2[cnt[2]] & 0xF0) >> 4;
                unpack_scale = tracks.track2[cnt[2]] & 0x0F;
                
                sound[2].noteclock = notes_clocktable.clock[unpack_note];
                sound[2].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];    
            }
        }
        
        if(availtrack & CH1_4th){
            if(tracks.track_length[3] == cnt[3]){
                availtrack &= ~CH1_4th;
                DDR_CH1 &= ~CH1_4th;
            }
            else{
                unpack_note = tracks.notetrack3[cnt[3]];
                unpack_octave = (tracks.track3[cnt[3]] & 0xF0) >> 4;
                unpack_scale = tracks.track3[cnt[3]] & 0x0F;
                
                sound[3].noteclock = notes_clocktable.clock[unpack_note];
                sound[3].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & CH1_5th){
            if(tracks.track_length[4] == cnt[4]){
                availtrack &= ~CH1_5th;
                DDR_CH1 &= ~CH1_5th;
            }
            else{
                unpack_note = tracks.notetrack4[cnt[4]];
                unpack_octave = (tracks.track4[cnt[4]] & 0xF0) >> 4;
                unpack_scale = tracks.track4[cnt[4]] & 0x0F;
                
                sound[4].noteclock = notes_clocktable.clock[unpack_note];
                sound[4].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & CH1_6th){
            if(tracks.track_length[5] == cnt[5]){
                availtrack &= ~CH1_6th;
                DDR_CH1 &= ~CH1_6th;
            }
            else{
                unpack_note = tracks.notetrack5[cnt[5]];
                unpack_octave = (tracks.track5[cnt[5]] & 0xF0) >> 4;
                unpack_scale = tracks.track5[cnt[5]] & 0x0F;
                
                sound[5].noteclock = notes_clocktable.clock[unpack_note];
                sound[5].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & CH1_7th){
            if(tracks.track_length[6] == cnt[6]){
                availtrack &= ~CH1_7th;
                DDR_CH1 &= ~CH1_7th;
            }
            else{
                unpack_note = tracks.notetrack6[cnt[6]];
                unpack_octave = (tracks.track6[cnt[6]] & 0xF0) >> 4;
                unpack_scale = tracks.track6[cnt[6]] & 0x0F;
                
                sound[6].noteclock = notes_clocktable.clock[unpack_note];
                sound[6].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & CH1_8th){
            if(tracks.track_length[7] == cnt[7]){
                availtrack &= ~CH1_8th;
                DDR_CH1 &= ~CH1_8th;
            }
            else{
                unpack_note = tracks.notetrack7[cnt[7]];
                unpack_octave = (tracks.track7[cnt[7]] & 0xF0) >> 4;
                unpack_scale = tracks.track7[cnt[7]] & 0x0F;
                
                sound[7].noteclock = notes_clocktable.clock[unpack_note];
                sound[7].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_9th << 8)){
            if(tracks.track_length[8] == cnt[8]){
                availtrack &= ~(CH2_9th << 8);
                DDR_CH2 &= ~CH2_9th;
            }
            else{
                unpack_note = tracks.notetrack8[cnt[8]];
                unpack_octave = (tracks.track8[cnt[8]] & 0xF0) >> 4;
                unpack_scale = tracks.track8[cnt[8]] & 0x0F;
                
                sound[8].noteclock = notes_clocktable.clock[unpack_note];
                sound[8].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_10th << 8)){
            if(tracks.track_length[9] == cnt[9]){
                availtrack &= ~(CH2_10th << 8);
                DDR_CH2 &= ~CH2_10th;
            }
            else{
                unpack_note = tracks.notetrack9[cnt[9]];
                unpack_octave = (tracks.track9[cnt[9]] & 0xF0) >> 4;
                unpack_scale = tracks.track9[cnt[9]] & 0x0F;
                
                sound[9].noteclock = notes_clocktable.clock[unpack_note];
                sound[9].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }    
        }
        
        if(availtrack & (CH2_11th << 8)){
            if(tracks.track_length[10] == cnt[10]){
                availtrack &= ~(CH2_11th << 8);
                DDR_CH2 &= ~CH2_11th;
            }
            else{
                unpack_note = tracks.notetrack10[cnt[10]];
                unpack_octave = (tracks.track10[cnt[10]] & 0xF0) >> 4;
                unpack_scale = tracks.track10[cnt[10]] & 0x0F;
                
                sound[10].noteclock = notes_clocktable.clock[unpack_note];
                sound[10].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_12th << 8)){
            if(tracks.track_length[11] == cnt[11]){
                availtrack &= ~(CH2_12th << 8);
                DDR_CH2 &= ~CH2_12th;
            }
            else{
                unpack_note = tracks.notetrack11[cnt[11]];
                unpack_octave = (tracks.track11[cnt[11]] & 0xF0) >> 4;
                unpack_scale = tracks.track11[cnt[11]] & 0x0F;
                
                sound[11].noteclock = notes_clocktable.clock[unpack_note];
                sound[11].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_13th << 8)){
            if(tracks.track_length[12] == cnt[12]){
                availtrack &= ~(CH2_13th << 8);
                DDR_CH2 &= ~CH2_13th;
            }
            else{
                unpack_note = tracks.notetrack12[cnt[12]];
                unpack_octave = (tracks.track12[cnt[12]] & 0xF0) >> 4;
                unpack_scale = tracks.track12[cnt[12]] & 0x0F;
                
                sound[12].noteclock = notes_clocktable.clock[unpack_note];
                sound[12].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_14th << 8)){
            if(tracks.track_length[13] == cnt[13]){
                availtrack &= ~(CH2_14th << 8);
                DDR_CH2 &= ~CH2_14th;
            }
            else{
                unpack_note = tracks.notetrack13[cnt[13]];
                unpack_octave = (tracks.track13[cnt[13]] & 0xF0) >> 4;
                unpack_scale = tracks.track13[cnt[13]] & 0x0F;
                
                sound[13].noteclock = notes_clocktable.clock[unpack_note];
                sound[13].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_15th << 8)){
            if(tracks.track_length[14] == cnt[14]){
                availtrack &= ~(CH2_15th << 8);
                DDR_CH2 &= ~CH2_15th;
            }
            else{
                unpack_note = tracks.notetrack14[cnt[14]];
                unpack_octave = (tracks.track14[cnt[14]] & 0xF0) >> 4;
                unpack_scale = tracks.track14[cnt[14]] & 0x0F;
                
                sound[14].noteclock = notes_clocktable.clock[unpack_note];
                sound[14].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        if(availtrack & (CH2_16th << 8)){
            if(tracks.track_length[15] == cnt[15]){
                availtrack &= ~(CH2_16th << 8);
                DDR_CH2 &= ~CH2_16th;
            }
            else{
                unpack_note = tracks.notetrack15[cnt[15]];
                unpack_octave = (tracks.track15[cnt[15]] & 0xF0) >> 4;
                unpack_scale = tracks.track15[cnt[15]] & 0x0F;
                
                sound[15].noteclock = notes_clocktable.clock[unpack_note];
                sound[15].scaleclock = scales_clocktable[unpack_octave].clock[unpack_scale];
            }
        }
        
        while(idx < 16){
            if(noteflag[idx]){
                cnt[idx] += 1;
            }
            idx += 1;
        }
    }
    
    return;
}



