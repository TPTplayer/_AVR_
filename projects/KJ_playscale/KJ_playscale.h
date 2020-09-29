#ifndef KJ_PLAYSCALE_H_
#define KJ_PLAYSCALE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>
#include "KJ_playscale_scaledef.h"
#include "KJ_playscale_calculation.h"

//definition outputs
#define DDR_CH1  DDRC
#define DDR_CH2  DDRA  
#define PORT_CH1 PORTC
#define PORT_CH2 PORTA

#define CH1_1st   (1 << 0)
#define CH1_2nd   (1 << 1)
#define CH1_3rd   (1 << 2)
#define CH1_4th   (1 << 3)
#define CH1_5th   (1 << 4)
#define CH1_6th   (1 << 5)
#define CH1_7th   (1 << 6)
#define CH1_8th   (1 << 7)

#define CH2_9th   (1 << 0)
#define CH2_10th  (1 << 1)
#define CH2_11th  (1 << 2)
#define CH2_12th  (1 << 3)
#define CH2_13th  (1 << 4)
#define CH2_14th  (1 << 5)
#define CH2_15th  (1 << 6)
#define CH2_16th  (1 << 7)

/*
virtual clockspeed:
Adjust GPIO to Overflow Interrupt to use multiple outputs.
*/
#define VCLOCK_SCALE    F_CPU / 8
#define VCLOCK_NOTE     F_CPU / 1024

//setup macros
#define SCALE_TIMER_INIT        TCCR1B |= (1 << CS10)
#define SCALE_TIMSK_INIT        TIMSK |= (1 << TOIE1)   
#define SCALE_COUNTER_SETCLOCK  TCNT1 = 0xFFFF - (8 / 1)    

#define NOTE_TIMER_INIT         TCCR3B |= (1 << CS32) | (1 << CS30);
#define NOTE_TIMSK_INIT         ETIMSK |= (1 << TOIE3);
#define NOTE_COUNTER_SETCLOCK   TCNT3 = 0xFFFE   

typedef struct {
    uint32_t scaleclock;
    uint32_t noteclock;
}sound_t;

typedef struct{
    uint8_t track_num;
    uint16_t avail_track;
    uint32_t track_length[16];
    uint32_t length;
    
    uint8_t *track0;
    uint8_t *notetrack0;
    uint8_t *track1;
    uint8_t *notetrack1;
    uint8_t *track2;
    uint8_t *notetrack2;
    uint8_t *track3;
    uint8_t *notetrack3;
    uint8_t *track4;
    uint8_t *notetrack4;
    uint8_t *track5;
    uint8_t *notetrack5;
    uint8_t *track6;
    uint8_t *notetrack6;
    uint8_t *track7;
    uint8_t *notetrack7;
    uint8_t *track8;
    uint8_t *notetrack8;
    uint8_t *track9;
    uint8_t *notetrack9;
    uint8_t *track10;
    uint8_t *notetrack10;
    uint8_t *track11;
    uint8_t *notetrack11;
    uint8_t *track12;
    uint8_t *notetrack12;
    uint8_t *track13;
    uint8_t *notetrack13;
    uint8_t *track14;
    uint8_t *notetrack14;
    uint8_t *track15;
    uint8_t *notetrack15;
}track_t;

ISR(TIMER1_OVF_vect);
ISR(TIMER3_OVF_vect);

void output_enable(void);
void output_disable(void);
void playscale_init(uint32_t vclockspeed_scale, uint32_t vclockspeed_note, uint32_t note_mm);
void playscale_play(track_t tracks);

#endif /* KJ_PLAYSCALE_H_ */