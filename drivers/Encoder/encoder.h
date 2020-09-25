#ifndef VSB_KEY_ENCODER_H_
#define VSB_KEY_ENCODER_H_

#ifndef F_CPU
#define F_CPU 11059200
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "vsb_key_logicdef.h"

#define _ENC_A_PIN   0x10
#define _ENC_B_PIN   0x40
#define _ENC_SW_PIN  0x40
#define _ENC_LED_PIN 0x04

#define _DDR_ENC_A_INIT      (DDRE &= (~_ENC_A_PIN))
#define _DDR_ENC_B_INIT      (DDRB &= (~_ENC_B_PIN))
#define _DDR_ENC_SW_INIT     (DDRE &= (~_ENC_SW_PIN))
#define _DDR_ENC_LED_INIT    (DDRG |= _ENC_LED_PIN)

#define _PORT_ENC_A_INIT     (PORTE &= (~_ENC_A_PIN))
#define _PORT_ENC_B_INIT     (PORTB &= (~_ENC_B_PIN))
#define _PORT_ENC_SW_INIT    (PORTE &= (~_ENC_SW_PIN))

#define _ENC_LED_SET         (PORTG |= _ENC_LED_PIN);
#define _ENC_LED_CLEAR       (PORTG &= (~_ENC_LED_PIN));

#define _PIN_ENC_A  PINE
#define _PIN_ENC_B  PINB
#define _PIN_ENC_SW PINE

#define _INT_ENC_A  INT4
#define _INT_ENC_SW INT6

#define _INT_VECT_INT_ENC_A     INT4_vect
#define _INT_VECT_INT_ENC_SW    INT6_vect

#define _ENC_INT_EN (EIMSK |= (1 << _INT_ENC_A))
#define _ENC_INT_DS (EIMSK &= (~(1 << _INT_ENC_A)))

#define _ENC_SW_INT_EN  (EIMSK |= (1 << _INT_ENC_SW))
#define _ENC_SW_INT_DS  (EIMSK &= (~(1 << _INT_ENC_SW)))

#define _ENC_STABLE_TIMER_INIT      TCCR2 |= ((1 << CS22) | (1 << CS20))       
#define _ENC_STABLE_COUNTER_INIT    TCNT2 = 0xFE - ((F_CPU / 1024) / 100)
#define _ENC_STABLE_TINT_EN         TIMSK |= (1 << TOIE2)
#define _ENC_STABLE_TINT_DS         TIMSK &= (~(1 << TOIE2))

#define _ENC_SW_STABLE_TIMER_INIT   TCCR3B |= ((1 << CS32) | (1 << CS30))
#define _ENC_SW_STABLE_COUNTER_INIT TCNT3 = 0xFFFE - ((F_CPU / 1024) / 100)
#define _ENC_SW_STABLE_TINT_EN      ETIMSK |= (1 << TOIE3)
#define _ENC_SW_STABLE_TINT_DS      ETIMSK &= (~(1 << TOIE3))

#define _INT_VECT_ENC       TIMER2_OVF_vect
#define _INT_VECT_ENC_SW    TIMER3_OVF_vect

typedef struct {
    uint8_t flag_a : 1;
    uint8_t flag_sw : 1;
}Enc_int_flag;

typedef struct {
    uint8_t flag_clockwise : 1;
    uint8_t flag_cntclockwise : 1;
    uint8_t flag_click : 1;    
}Enc_state_flag;

ISR(_INT_VECT_INT_ENC_A);
ISR(_INT_VECT_INT_ENC_SW);
ISR(_INT_VECT_ENC);
ISR(_INT_VECT_ENC_SW);

void enc_init(void);
void __enc_extint_init(void);
void __enc_flag_init(void);
void __enc_stabilizer_init(void);

void get_enc_state(void);
uint8_t enc_is_clockwise(void);
uint8_t enc_is_cntclockwise(void);
uint8_t enc_is_click(void);

void enc_led_init(void);
void enc_led_set(void);
void enc_led_clear(void);

#endif /* VSB_KEY_ENCODER_H_ */