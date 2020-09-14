#include <avr/io.h>
#include <stdio.h>

#include "GPIO_SPI.h"

static Master_flag master_flag;
static Slave_flag slave_flag;

uint8_t SPI_master_isbusy(void){
    return ~(master_flag.transfer_complete);
}

uint8_t SPI_slave_isbusy(void){
    return ~(slave_flag.transfer_complete);
}

uint8_t SPI_slave_xfer_isbroken(void){
    return slave_flag.transfer_broke;
}

void SPI_master_init(void){
    _DDR_SS |= _SS_PIN;
    _DDR_SCK |= _SCK_PIN;
    _DDR_MOSI |= _MOSI_PIN;
    _DDR_MISO &= (~_MISO_PIN);
    
    _PORT_SS |= _SS_PIN;
    _PORT_SCK &= (~_SCK_PIN);
    _PORT_MOSI &= (~_MOSI_PIN);
    
    master_flag.transfer_complete = SET;
    return;
}

void SPI_SS_enable(void){
    _PORT_SS &= (~_SS_PIN);
    return;
}

void SPI_SS_disable(void){
    _PORT_SS |= _SS_PIN;
    return;
}

uint32_t SPI_master_transfer(uint8_t num_bit, uint32_t data){
    uint8_t cnt = 0x00;
    uint32_t receive = 0x00, mask = 0x00;
    
    master_flag.transfer_complete = CLEAR;
    if(num_bit != 0){
        mask = (1 << (num_bit - 1));
    }    
    
    for(cnt = 0; cnt < num_bit; cnt++){
        _PORT_SCK |= _SCK_PIN;
        
        if(data & mask){
            _PORT_MOSI |= _MOSI_PIN;
        }
        else{
            _PORT_MOSI &= (~_MOSI_PIN);
        }
        mask >>= 1;
        
        receive <<= 1;
        if(_PIN_MISO & _MISO_PIN){
            receive |= 0x01;        
        }
       
        _PORT_SCK &= (~_PORT_SCK);    
    }
    
    master_flag.transfer_complete = SET;
    return receive;
}

void SPI_slave_init(void){
    _DDR_SS &= (~_SS_PIN);
    _DDR_SCK &= (~_SCK_PIN);
    _DDR_MOSI &= (~_MOSI_PIN);
    _DDR_MISO |= _MISO_PIN;
    
    _PORT_MISO &= (~_MISO_PIN);
    
    slave_flag.transfer_complete = SET;
    slave_flag.transfer_broke = CLEAR;
    return;
}

uint8_t SPI_SS_check(void){
    if(_PIN_SS & _SS_PIN){
        return CLEAR;
    }
    
    return SET;
}
 
uint32_t SPI_slave_transfer(uint8_t num_bit, uint32_t data){
    uint8_t cnt = 0;
    uint32_t receive = 0x00, mask = 0x00;
    
    slave_flag.transfer_complete = CLEAR;
    if(num_bit != 0){
        mask = (1 << (num_bit - 1));
    }
    
    for(cnt = 0; cnt < num_bit; cnt++){
        if(!SPI_SS_check()){
            slave_flag.transfer_broke = SET;
            break;
        }
        
        if(_PIN_SCK & _SCK_PIN){
            if(data & mask){
                _PORT_MISO |= _MISO_PIN;
            }
            else{
                _PORT_MISO &= (~_MISO_PIN);
            }
            mask >>= 1;
            
            receive <<= 1;
            if(_PIN_MOSI & _MOSI_PIN){
                receive |= 0x01;
            }
        }
        else{
            cnt -= 1;
            continue;
        }
    }
    
    slave_flag.transfer_complete = SET;
    return receive;    
}


