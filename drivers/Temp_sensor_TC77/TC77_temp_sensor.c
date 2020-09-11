#include <avr/io.h>
#include <stdint.h>

#include "TC77_temp_sensor.h"

void tc77_init(void){
    _DDR_TC77 |= (_TC77_CS_PIN | _TC77_SCK_PIN);
    _DDR_TC77 &= (~_TC77_DATA_PIN);
    return;
}

void _tc77_cs_enable(void){
    _PORT_TC77 &= (~_TC77_CS_PIN);
    return;
}

void _tc77_cs_disable(void){
    _PORT_TC77 |= _TC77_CS_PIN;
    return;
}

uint16_t _tc77_get_rawdata(void){
    uint16_t rawdata = 0x0000;
    int cnt = 0;
    
    for(cnt = 0; cnt < 16; cnt++){
        _TC77_SCK_HIGH;
        rawdata <<= 1;
        
        if(_PIN_TC77 & _TC77_DATA_PIN){
            rawdata |= 0x01;    
        }
        
        _TC77_SCK_LOW;
    }
    
    return rawdata;
}

float tc77_get_temp(void){
    uint16_t rawdata = 0x0000;
    float temp = 0;
    
    while(1){
        _tc77_cs_enable();
        rawdata = _tc77_get_rawdata();
        _tc77_cs_disable();
        
        //rawdata = 0x0C87; //for checking TC77 (expected: 25 celcious)
        
        if(rawdata & _CONV_COMP_MASK){
            break;
        }
    }    
    
    if(rawdata & _MASK_SIGN){
        rawdata = (~(rawdata & _MASK_TEMP) >> 3) + 0x01;
        temp = rawdata * _LSB * -1;
    }
    else{
        rawdata = ((rawdata & _MASK_TEMP) >> 3);
        temp = rawdata * _LSB;
    }
    
    return temp;
}