#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "CLCD.h"

/*
E0: E
E1: RW
E2: RS
*/

/*It is a function based on 8bit data bus.*/

void CLCD_DataTransmitter(char data){
	_delay_ms(1);
	PORTE = RS; 
	_delay_us(1); 
	PORTE = (RS | E); 
	_delay_us(1);
	PORTB = data; 
	_delay_us(1);
	PORTE = RW;	
}

void CLCD_Controller(char ctl){
	_delay_ms(30);
	PORTE = 0x00; //RW clear
	_delay_us(1);
	PORTE = E;
	_delay_us(1);
	PORTB = ctl;
	_delay_us(1);
	PORTE = (RS | RW);
}

void CLCD_initalizer(void){
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

void CLCD_putstr(char addr, char *str){
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

void CLCD_printstr(char addr, char *str, char size){
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

void CLCD_move_cursor(char addr){
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
}

void CLCD_move_cursor_s(char x, char y){
	char addr = CLCD_DD_RAM_BASE;
	
	if(y == 0){
		CLCD_Controller(addr + x);
	}
	else{
		CLCD_Controller((addr | 0x40) + x);
	}
}

void CLCD_input_font(char *font, int font_num, char cg_ram_addr){
	CLCD_Controller(CLCD_CG_RAM_BASE);
	_delay_ms(2);
	
	for(int i = 0; i < (cg_ram_addr * 8); i++){
		CLCD_DataTransmitter(0x00);
	}
	
	for(int i = 0; i < font_num; i++){
		CLCD_DataTransmitter(font[i]);
	}
}

void CLCD_print_font(char addr, char font_addr){
	CLCD_Controller(addr | CLCD_DD_RAM_BASE);
	CLCD_DataTransmitter(font_addr);
}

void CLCD_font_initailizer(void){
	char dummy[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
					
	CLCD_input_font(dummy, 64, 0x00);
}