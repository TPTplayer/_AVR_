#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "mega128_USART.h"

void UART0_initializer(uint32_t ubrr){
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	// set baudrate
			
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
	//8bit data, 2 stop bit, no parity
	
	return;
}

void UART1_initializer(uint32_t ubrr){
	UBRR1H = (uint8_t)(ubrr >> 8);
	UBRR1L = (uint8_t)ubrr;
		
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);	

	return;
}

void __UART0_transmit(uint8_t data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	
	return;
}

void __UART1_transmit(uint8_t data){
	while(!(UCSR1A & (1 << UDRE1)));
	UDR1 = data;	
	
	return;
}

uint8_t __UART0_receive(void){
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;	
}

uint8_t __UART1_receive(void){
	while(!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

void UART0_flush(void){
	uint8_t dummy;
	while(UCSR0A & (1 << RXC0)){
		dummy = UDR0;
	}	
	
	return;
}

void UART1_flush(void){
	uint8_t dummy;
	while(UCSR1A & (1 << RXC1)){
		dummy = UDR1;
	}
	
	return;
}

int __UART0_transmit_stdout(char data, FILE *stream){
	__UART0_transmit((uint8_t) data);
	return 0;
}

int __UART1_transmit_stdout(char data, FILE *stream){
	__UART1_transmit((uint8_t) data);
	return 0;
}

int __UART0_receive_stdin(FILE *stream){
	return __UART0_receive();
}

int __UART1_receive_stdin(FILE *stream){
	return __UART1_receive();
}

void UART0_setup_stdio(FILE *stream){
	stream = fdevopen(__UART0_transmit_stdout, __UART0_receive_stdin);
	return;
}

void UART1_setup_stdio(FILE *stream){
	stream = fdevopen(__UART1_transmit_stdout, __UART1_receive_stdin);
	return;
}
