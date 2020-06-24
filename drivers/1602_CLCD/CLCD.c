#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "CLCD.h"

void CLCD_DataTransmitter(uint8_t data){
	_delay_ms(1);
	CTRL_PORT = RS;
	_delay_us(1);
	CTRL_PORT = (RS | E);
	_delay_us(1);
	DATA_PORT = data;
	_delay_us(1);
	CTRL_PORT = RW;
}

void CLCD_DataTransmitter_4bit(uint8_t data){
	_delay_ms(1);
	
	DATA_PORT = (data & 0xF0);
	CTRL_PORT |= RS;
	CTRL_PORT &= ~RW;
	_delay_us(1);
	
	CTRL_PORT |= E;
	_delay_us(1);
	CTRL_PORT &= ~E;
	
	DATA_PORT = ((data << 4) & 0xF0);
	CTRL_PORT |= RS;
	CTRL_PORT &= ~RW;
	_delay_us(1);
	
	CTRL_PORT |= E;
	_delay_us(1);
	CTRL_PORT &= ~E;
}

void CLCD_Controller(uint8_t ctl){
	_delay_ms(30);
	CTRL_PORT = 0x00; //RW clear
	_delay_us(1);
	CTRL_PORT = E;
	_delay_us(1);
	DATA_PORT = ctl;
	_delay_us(1);
	CTRL_PORT = (RS | RW);
}

void CLCD_Controller_4bit(uint8_t ctl){
	_delay_ms(30);
	
	DATA_PORT = (ctl & 0xF0);
	CTRL_PORT &= ~RS;
	CTRL_PORT &= ~RW;
	_delay_us(1);
	
	CTRL_PORT |= E;
	_delay_us(1);
	CTRL_PORT &= ~E;
	
	DATA_PORT = ((ctl << 4) & 0xF0);
	CTRL_PORT &= ~RS;
	CTRL_PORT &= ~RW;
	_delay_us(1);
	
	CTRL_PORT |= E;
	_delay_us(1);
	CTRL_PORT &= ~E;
}

void CLCD_initializer(void){
	cli();
	_delay_ms(50);
	CLCD_Controller(FUNC_DISPLAY_LINE_2 | FUNC_DATA_LINE_8);
	_delay_us(40);
	CLCD_Controller(DISPLAY_ON);
	_delay_us(40);
	CLCD_Controller(CLEAR_DISPLAY);
	_delay_ms(2);
	CLCD_Controller(ENTRY_NO_SHIFT);
	sei();
}

void CLCD_initializer_4bit(void){
	cli();
	_delay_ms(50);
	CLCD_Controller_4bit(FUNC_DISPLAY_LINE_2 | FUNC_DATA_LINE_4);
	_delay_us(40);
	CLCD_Controller_4bit(DISPLAY_ON);
	_delay_us(40);
	CLCD_Controller_4bit(CLEAR_DISPLAY);
	_delay_ms(2);
	CLCD_Controller_4bit(ENTRY_NO_SHIFT);
	sei();	
}

void CLCD_putstr(uint8_t addr, char *str){
	int char_count = 0;
	
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
	while(*str != '\0'){
		if(((addr | CLCD_DD_RAM_BASE) + char_count) == 0x90){
			CLCD_Controller(CLCD_DD_RAM_BASE | 0x40);
		}
		CLCD_DataTransmitter(*str);
		
		str += 1;
		char_count += 1;
	}
}

void CLCD_putstr_4bit(uint8_t addr, char *str){
	int char_count = 0;
	
	CLCD_Controller_4bit(addr | CLCD_DD_RAM_BASE);
	while(*str != '\0'){
		if(((addr | CLCD_DD_RAM_BASE) + char_count) == 0x90){
			CLCD_Controller_4bit(CLCD_DD_RAM_BASE | 0x40);
		}
		CLCD_DataTransmitter_4bit(*str);
		
		str += 1;
		char_count += 1;
	}
}

void CLCD_printstr(uint8_t addr, char *str, uint8_t size){
	int char_count = 0;
	
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
	for(char_count = 0; char_count <= size - 1; char_count++){
		if(((addr | CLCD_DD_RAM_BASE) + char_count) == 0x90){
			CLCD_Controller(CLCD_DD_RAM_BASE | 0x40);
		}
		
		CLCD_DataTransmitter(*str);
		str += 1;
	}
}

void CLCD_printstr_4bit(uint8_t addr, char *str, uint8_t size){
	int char_count = 0;
	
	CLCD_Controller_4bit(addr | CLCD_DD_RAM_BASE);
	for(char_count = 0; char_count <= size - 1; char_count++){
		if(((addr | CLCD_DD_RAM_BASE) + char_count) == 0x90){
			CLCD_Controller_4bit(CLCD_DD_RAM_BASE | 0x40);
		}
		
		CLCD_DataTransmitter_4bit(*str);
		str += 1;
	}
}

void CLCD_move_cursor(uint8_t addr){
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
}

void CLCD_move_cursor_4bit(uint8_t addr){
	CLCD_Controller_4bit(addr | CLCD_DD_RAM_BASE);
}

void CLCD_move_cursor_s(uint8_t x, uint8_t y){
	uint8_t addr = CLCD_DD_RAM_BASE;
	
	if(y == 0){
		CLCD_Controller(addr + x);
	}
	else{
		CLCD_Controller((addr | 0x40) + x);
	}
}

void CLCD_move_cursor_s_4bit(uint8_t x, uint8_t y){
	uint8_t addr = CLCD_DD_RAM_BASE;
	
	if(y == 0){
		CLCD_Controller_4bit(addr + x);
	}
	else{
		CLCD_Controller_4bit((addr | 0x40) + x);
	}
}

void CLCD_input_font(char *font, int font_num, uint8_t cg_ram_addr){
	CLCD_Controller(CLCD_CG_RAM_BASE);
	_delay_ms(2);
	
	for(int i = 0; i < (cg_ram_addr * 8); i++){
		CLCD_DataTransmitter(0x00);
	}
	
	for(int i = 0; i < font_num; i++){
		CLCD_DataTransmitter(font[i]);
	}
}

void CLCD_input_font_4bit(char *font, int font_num, uint8_t cg_ram_addr){
	CLCD_Controller_4bit(CLCD_CG_RAM_BASE);
	_delay_ms(2);
	
	for(int i = 0; i < (cg_ram_addr * 8); i++){
		CLCD_DataTransmitter_4bit(0x00);
	}
	
	for(int i = 0; i < font_num; i++){
		CLCD_DataTransmitter_4bit(font[i]);
	}
}

void CLCD_print_font(uint8_t addr, uint8_t font_addr){
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
	CLCD_DataTransmitter(font_addr);
}

void CLCD_print_font_4bit(uint8_t addr, uint8_t font_addr){
	CLCD_Controller_4bit(addr | CLCD_DD_RAM_BASE);
	CLCD_DataTransmitter_4bit(font_addr);
}
