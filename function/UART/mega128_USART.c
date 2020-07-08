#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

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

void UART_transmit(int uart_num, uint8_t data){
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

uint8_t UART_receive(int uart_num){
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