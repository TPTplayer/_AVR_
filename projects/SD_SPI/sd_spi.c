#include "sd_funcdef.h"
#include "sd_macrodef.h"
#include "debug.h"

uint8_t response1 = 0x00;
uint16_t response2 = 0x00;
uint64_t response3 = 0x00, response7 = 0x00;

int sdcard_init(void){
	uint8_t check_pattern = 0xCC, vhs = 0x01;
	uint32_t ocr_register = 0x00;
	int attempts = 0;
	
	__sd_powerup();
	while(_MASK(response1, _R1_IN_IDLE_STATE) != _SD_SET){
		if(attempts == _ATTEMPT_LIMIT) return _SD_ERROR;
		__sd_cmd_transmit(_CMD0, 0x00);
		response1 = __sd_response_receive(_RESP1);
		attempts += 1;
	}
	
	__sd_cmd_transmit(_CMD8, _CMD8_ARGUMENT(vhs, check_pattern));
	response7 = __sd_response_receive(_RESP7);
	
	if((_R7_MASK_VCA(response7) != vhs) || (_R7_MASK_CHECKPATTERN(response7) != check_pattern)) return _SD_ERROR;
	if(_MASK(_R7_MASK_R1(response7), _R1_IN_IDLE_STATE) != _SD_SET) return _SD_ERROR;
	
	attempts = 0;
	do{
		if(attempts == _ATTEMPT_LIMIT) return _SD_ERROR;
		__sd_cmd_transmit(_CMD55, 0x00);
		response1 = __sd_response_receive(_RESP1);
		if(_MASK(response1, _R1_IN_IDLE_STATE) != _SD_SET){ 
			attempts += 1;
			continue;
		}
		
		__sd_cmd_transmit(_ACMD41, _ACMD41_ARGUMENT(1));
		response1 = __sd_response_receive(_RESP1); 
		attempts += 1;
		_delay_ms(40);
	}while(_MASK(response1, _R1_IN_IDLE_STATE) == _SD_SET);
	
	__sd_cmd_transmit(_CMD58, 0x00);
	response3 = __sd_response_receive(_RESP3);
	ocr_register = _R3_MASK_OCR(response3);
	
	/*SDSC Memory Card (unusable)*/
	if((_MASK(ocr_register, _OCR_CCS)) != _SD_SET) return _SD_ERROR;
	return _SD_SUCCESS;
}

int sdcard_read(uint32_t address, uint8_t *buf){
	int attempts = 0, idx = 0;
	uint8_t expected_start_token = 0xFE, received_start_token = 0x00;
	uint16_t crc_16;
	
	__sd_cmd_transmit(17, address);
	response1 = __sd_response_receive(_RESP1);
	if(response1 == 0xFF) return _SD_ERROR;
	
	while((received_start_token = SPI_master_transfer(8, 0xFF)) != expected_start_token){
		if(attempts == _ATTEMPT_LIMIT){
			return _SD_ERROR;
		}
		attempts += 1;
	}
	
	for(idx = 0; idx < _BLOCK_BYTE_LEN; idx++){
		buf[idx] = SPI_master_transfer(8, 0xFF);
	}
	crc_16 = SPI_master_transfer(16, 0xFF);
	return _SD_SUCCESS;
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
		receive = SPI_master_transfer(_RESP1_BIT_LEN, 0xFF);
		break;    
	case _RESP2:
		receive = SPI_master_transfer(_RESP2_BIT_LEN, 0xFF);
		break;
	case _RESP3:
		receive = SPI_master_transfer(_RESP3_BIT_LEN, 0xFF);
		break;
	case _RESP7:
		receive = SPI_master_transfer(_RESP7_BIT_LEN, 0xFF);
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

void __sd_powerup(void){
	SPI_SS_disable();
	_delay_ms(1);
	
	SPI_master_transfer(32, 0x00);
	SPI_master_transfer(32, 0x00);
	SPI_master_transfer(10, 0x00);
	
	SPI_SS_disable();
	return;
}