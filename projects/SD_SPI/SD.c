#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <inttypes.h>

#include "sd_funcdef.h"
#include "sd_macrodef.h"

uint8_t response1 = 0x00;
uint16_t response2 = 0x00;
uint64_t response3 = 0x00, response7 = 0x00;

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
#include <stdio.h>
#include <inttypes.h>
#endif

int sdcard_init(void){
    uint8_t check_pattern = 0xCC, vhs = 0x01;
    uint32_t ocr_register = 0x00;
    
    uint64_t resp = 0x00;
    
    __sd_initclock();
    __sd_cmd_transmit(_CMD0, 0x00);
    __sd_cmd_transmit(_CMD0, 0x00);
    
    __sd_cmd_transmit(_CMD8, _CMD8_ARGUMENT(vhs, check_pattern));
    response7 = __sd_response_receive(_RESP7);

    #ifdef DEBUG_ENABLE
	/*show response7*/
    printf("resp7: 0x%llx\n", response7);
	#endif
	
    if((_R7_MASK_R1(resp) != 0x01) || (_R7_MASK_VCA(resp) != vhs) || (_R7_MASK_CHECKPATTERN(resp) != check_pattern)){
        return -1;
    }        
    
    __sd_cmd_transmit(_CMD58, 0x00);
    response3 = __sd_response_receive(_RESP3);
    ocr_register = _R3_MASK_OCR(response3);
    
	#ifdef DEBUG_ENABLE
    /*show response3 and check ocr register*/
    printf("resp3->resp1: 0x%"PRIx8"\n", _R3_MASK_R1(response3));
	printf("resp3->ocr register: 0x%"PRIx32"\n", _R3_MASK_OCR(response3));
	#endif
	
    if(_R3_MASK_R1(resp) != 0x01){
        return -1;
    }
    
    __sd_cmd_transmit(_CMD55, 0x00);
    response1 = __sd_response_receive(_RESP1);
    
	#ifdef DEBUG_ENABLE
    /*show response1*/
	printf("resp1: 0x%"PRIx8"\n", response1);
	#endif
    
    if(response1 != 0x01){
        return -1;
    }
    
    do{
        __sd_cmd_transmit(_ACMD41, _ACMD41_ARGUMENT(1));
        response1 = __sd_response_receive(_RESP1);
        
		#ifdef DEBUG_ENABLE
        /*show response1*/
		printf("resp1: 0x%"PRIx8"\n", response1);
		#endif
    }while(response1 != 0x00);  
    
     __sd_cmd_transmit(_CMD58, 0x00);
     response3 = __sd_response_receive(_RESP3);
     ocr_register = _R3_MASK_OCR(response3);
	 
	 #ifdef DEBUG_ENABLE
	 /*show response3*/
	 printf("resp3: 0x%llx\n", response3);
	 #endif
	 
	 if((ocr_register & ((uint32_t)1 << _OCR_CCS)) != ((uint32_t)1 << _OCR_CCS)){
		 /*SDSC Memory Card (unusable)*/
		 return -1;
	 }  
	 return 0;
}

int sdcard_read(uint32_t address, uint8_t *buf){
	int idx = 0;
	__sd_cmd_transmit(_CMD17, address);
	response1 = __sd_response_receive(_RESP1);
	
	#ifdef DEBUG_ENABLE
	/*show response1*/
	printf("resp1: 0x%"PRIx8"\n", response1);
	#endif
	
	if(response1 != 0x00){
		return -1;
	}
	
	SPI_SS_enable();
	for(idx = 0; idx < _BLOCK_BYTE_LEN; idx++){
		buf[idx] = SPI_master_transfer(8, 0x00);
	}
	SPI_SS_disable();
	
	return 0;
}

void __sd_cmd_transmit(uint8_t cmd_index, uint32_t argument){
    uint64_t cmd_packet = 0x00;
    uint8_t crc = 0x00, cmd_header = 0x00;
    
    cmd_header = _CMD_HEADER(cmd_index);
    crc = _CMD_CRC7(__sd_crc7_generator(cmd_header, argument));
    cmd_packet = _CMD_PACKET(cmd_header, argument, crc);
    
    SPI_SS_enable();
    SPI_master_transfer(_CMD_BIT_LEN, cmd_packet);
    SPI_SS_disable();
    
    return;
}

uint64_t __sd_response_receive(int response){
    uint64_t receive = 0x00;
    
    SPI_SS_enable();
    switch(response){
    case _RESP1:
        receive = SPI_master_transfer(_RESP1_BIT_LEN, 0x00);
        break;    
    case _RESP2:
        receive = SPI_master_transfer(_RESP2_BIT_LEN, 0x00);
        break;
    case _RESP3:
        receive = SPI_master_transfer(_RESP3_BIT_LEN, 0x00);
        break;
    case _RESP7:
        receive = SPI_master_transfer(_RESP7_BIT_LEN, 0x00);
        break;
    default:
        break;    
    }
    
    SPI_SS_disable();
    return receive;         
}

uint8_t __sd_crc7_generator(uint8_t header, uint32_t argument){
    uint64_t body = ((0x40 | ((uint64_t)header & 0x3F)) << 32) | argument;
    uint64_t mask = 0xFF00000000;
    uint8_t crc = 0x00, data = 0x00;
    int cnt = 0, i = 0, bytes = 5;
    
    for(cnt = 0; cnt < bytes; cnt++){
        data = (body & (mask >> (cnt * 8))) >> ((bytes - 1 - cnt) * 8);
        for(i = 0; i < 8; i++){
            crc <<= 1;
            if((data & 0x80) ^ (crc & 0x80)){
                crc ^= 0x09;
            }
            data <<= 1;
        }
    }
    return crc;    
}

void __sd_initclock(void){
    SPI_master_transfer(32, 0x00);
    SPI_master_transfer(32, 0x00);
    SPI_master_transfer(10, 0x00);
    
    return;
}