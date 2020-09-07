#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "mega128_USART.h"

void UART_initializer(int uart_num, uint32_t ubrr){
	switch(uart_num){
	case 0:
		UBRR0H = (uint8_t)(ubrr >> 8);
		UBRR0L = (uint8_t)ubrr;
		// set baudrate
		
		UCSR0B = (1 << RXEN0) | (1 << TXEN0); 
		// receive/trasmit enable
		
		UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00); 
		//8bit character, 2 stop bit, no parity
		break;
	case 1:
		UBRR1H = (uint8_t)(ubrr >> 8);
		UBRR1L = (uint8_t)ubrr;
		
		UCSR1B = (1 << RXEN1) | (1 << TXEN1);
		UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);
		break;
	}
	
	return;	
}

void __UART_transmit(int uart_num, uint8_t data){
	switch(uart_num){
	case 0:
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = data;
		break;
	case 1:
		while(!(UCSR1A & (1 << UDRE1)));
		UDR1 = data;
		break;	
	}
	
	return;
}

uint8_t __UART_receive(int uart_num){
	uint8_t data = 0;
	
	switch(uart_num){
	case 0:
		while(!(UCSR0A & (1 << RXC0)));
		data = UDR0;
		break;
	case 1:
		while(!(UCSR1A & (1 << RXC1)));
		data = UDR1;
		break;
	}
	
	return data;
}

void UART_flush(int uart_num){
	uint8_t dummy;
	
	switch(uart_num){
	case 0:
		while(UCSR0A & (1 << RXC0)){
			dummy = UDR0;
		}
		break;
	case 1:
		while(UCSR1A & (1 << RXC1)){
			dummy = UDR1;
		}
		break;	
	}
}

int __UART_transmit_stdout_num0(char data, FILE *stream){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	
	return 0;
}

int __UART_transmit_stdout_num1(char data, FILE *stream){
	while(!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;
	
	return 0;
}

int __UART_receive_stdin_num0(FILE *stream){
	int data = 0;
	
	while(!(UCSR0A & (1 << RXC0)));
	data = UDR0;
	
	return data;
}

int __UART_receive_stdin_num1(FILE *stream){
	int data = 0;
	
	while(!(UCSR1A & (1 << RXC1)));
	data = UDR1;
	
	return data;
}

void setup_stdio(int uart_num, FILE *stream){
	switch(uart_num){
	case 0:
		stream = fdevopen(__UART_transmit_stdout_num0, __UART_receive_stdin_num0);
		break;
	case 1:
		stream = fdevopen(__UART_transmit_stdout_num1, __UART_receive_stdin_num1);
		break;
	}
	
	return;
}

