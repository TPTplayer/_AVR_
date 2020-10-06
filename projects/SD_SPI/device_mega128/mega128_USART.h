#ifndef MEAG128_USART_H_
#define MEAG128_USART_H_

#include <stdint.h>
#include <stdio.h>

#define USART_OSC 11059200
#define BAUD 9600
#define UBRR_VAL USART_OSC / 16 / BAUD - 1

void UART0_initializer(uint32_t ubrr);
void UART1_initializer(uint32_t ubrr);

void UART0_setup_stdio(FILE *stream);
void UART1_setup_stdio(FILE *stream);

int __UART0_transmit_stdout(char data, FILE *stream);
int __UART1_transmit_stdout(char data, FILE *stream);
int __UART0_receive_stdin(FILE *stream);
int __UART1_receive_stdin(FILE *stream);

void __UART0_transmit(uint8_t data);
void __UART1_transmit(uint8_t data);
uint8_t __UART0_receive(void);
uint8_t __UART1_receive(void);

void UART0_flush(void);
void UART1_flush(void);

/*
<connection>
green: RX
white: TX

<receiver settings>
baudrate: 9600bit/s
parity: none
stop bit: 2
flow control: none
*/

#endif /* MEAG128_USART_H_ */