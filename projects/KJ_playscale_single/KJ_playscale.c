#include "KJ_playscale.h"

static uint8_t flag = 0;

ISR(TIMER3_OVF_vect){
    flag = 1;
    OUTPUT_DS;
}

pack_t data_pack(uint8_t *scaledata, uint8_t *beatdata, uint16_t len, uint16_t mm){
    pack_t packdata;
    
    packdata.len = len;
    packdata.mm = mm;
    
    packdata.scaledata = scaledata;
    packdata.beatdata = beatdata;
    return packdata;
}

track_t get_sound(pack_t packdata){
    uint16_t cnt = 0;
    uint8_t scalen = 0x00, octaven = 0x00;
    sound_t *sounds = malloc(sizeof(sound_t) * packdata.len);
    track_t track;
    
    track.track_len = packdata.len;
    track.track = sounds;
    
    for(cnt = 0; cnt < packdata.len; cnt++){
        octaven = (packdata.scaledata[cnt] & 0xF0) >> 4;
        scalen = packdata.scaledata[cnt] & 0x0F;
        track.track[cnt].scaleclock = calc_clock(SCALECLK, calc_scalefreq(octaven, scalen));
        track.track[cnt].beatclock = calc_beatclock(BEATCLK, calc_beattime(packdata.beatdata[cnt], packdata.mm));
    }
    
    return track;        
}

void play(track_t track){
    uint16_t cnt = 0;
    
    scaletimer_init();
    beattimer_init();
    
    _SCALECLOCK_SET(track.track[0].scaleclock);
    _BEATCLOCK_SET(track.track[0].beatclock);
    
    while(cnt < track.track_len){
        _SCALETIMER_EN;
        _BEATTIMER_EN;
        
        OUTPUT_EN;
        
        if(flag == 1){
            cnt += 1;
            flag = 0;
            _SCALECLOCK_SET(track.track[cnt].scaleclock);
            _BEATCLOCK_SET(track.track[cnt].beatclock);
        }
    }
    
    OUTPUT_DS;
    _SCALETIMER_DS;
    _BEATTIMER_DS;
    
    return;
}

void scaletimer_init(void){
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    _SCALETIMER_DS;
    
    return;
}

void beattimer_init(void){
    ETIMSK |= (1 << TOIE3);
    _BEATTIMER_DS;
    
    return;
}