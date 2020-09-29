#include <avr/io.h>
#include <avr/interrupt.h>

#include "encoder.h"

volatile static Enc_int_flag enc_int_flag;
volatile static Enc_state_flag enc_state_flag;

ISR(_INT_VECT_INT_ENC_A){
    enc_int_flag.flag_a = SET;
    _ENC_STABLE_TINT_EN;
    _ENC_STABLE_COUNTER_INIT;
    _ENC_INT_DS;
}

ISR(_INT_VECT_INT_ENC_SW){
    enc_int_flag.flag_sw = SET; 
    _ENC_SW_STABLE_TINT_EN;
    _ENC_SW_STABLE_COUNTER_INIT;
    _ENC_SW_INT_DS;
}

ISR(_INT_VECT_ENC){
    _ENC_STABLE_TINT_DS;
    _ENC_INT_EN;
}

ISR(_INT_VECT_ENC_SW){
    _ENC_SW_STABLE_TINT_DS;
    _ENC_SW_INT_EN;
}

void enc_init(void){
    _DDR_ENC_A_INIT;
    _DDR_ENC_B_INIT;
    _DDR_ENC_SW_INIT;
    
    _PORT_ENC_A_INIT;
    _PORT_ENC_B_INIT;
    _PORT_ENC_SW_INIT;
    
    __enc_flag_init();
    __enc_extint_init();
    __enc_stabilizer_init();
    
    return;
}

void __enc_extint_init(void){
    EICRB |= (1 << ISC41) | (1 << ISC61);
    _ENC_INT_EN;
    _ENC_SW_INT_EN;
    
    return;
}

void __enc_flag_init(void){
    enc_int_flag.flag_a = CLEAR;
    enc_int_flag.flag_sw = CLEAR;
    
    enc_state_flag.flag_click = CLEAR;
    enc_state_flag.flag_clockwise = CLEAR;
    enc_state_flag.flag_cntclockwise = CLEAR;
    
    return;
}

void __enc_stabilizer_init(void){
    _ENC_STABLE_TIMER_INIT;
    _ENC_STABLE_TINT_DS;
    
    _ENC_SW_STABLE_TIMER_INIT;
    _ENC_SW_STABLE_TINT_DS;
    
    return;
}

void get_enc_state(void){
    if(enc_int_flag.flag_a == SET){
        if(_PIN_ENC_B & _ENC_B_PIN){
            enc_state_flag.flag_clockwise = SET;
            enc_state_flag.flag_cntclockwise = CLEAR;
        }
        else{
            enc_state_flag.flag_cntclockwise = SET;
            enc_state_flag.flag_clockwise = CLEAR;
        }
        
        enc_int_flag.flag_a = CLEAR;
    }
    else{
        enc_state_flag.flag_clockwise = CLEAR;
        enc_state_flag.flag_cntclockwise = CLEAR;
    }
    
    if(enc_int_flag.flag_sw == SET){
        enc_state_flag.flag_click = SET;
        enc_int_flag.flag_sw = CLEAR;
    }   
    else{
        enc_state_flag.flag_click = CLEAR;
    }
    
    return;
}

uint8_t enc_is_clockwise(void){
    if(enc_state_flag.flag_clockwise == SET){
        return TRUE;
    }
    return FALSE;
}

uint8_t enc_is_cntclockwise(void){
    if(enc_state_flag.flag_cntclockwise == SET){
        return TRUE;
    }
    return FALSE;
}

uint8_t enc_is_click(void){
    if(enc_state_flag.flag_click == SET){
        return TRUE;
    }
    return FALSE;
}

void enc_led_init(void){
    _DDR_ENC_LED_INIT;
    return;
}

void enc_led_set(void){
    _ENC_LED_SET;
    return;
}

void enc_led_clear(void){
    _ENC_LED_CLEAR;
    return;
}