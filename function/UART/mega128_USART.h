#ifndef MEAG128_USART_H_
#define MEAG128_USART_H_

#include <stdint.h>
#include <stdio.h>

#define USART_OSC 11059200
#define BAUD 9600
#define UBRR_VAL USART_OSC / 16 / BAUD - 1

void UART_initializer(int uart_num, uint32_t ubrr);
void __UART_transmit(int uart_num, uint8_t data);
uint8_t __UART_receive(int uart_num);
void UART_flush(int uart_num);

void setup_stdio(int uart_num, FILE *stream);
int __UART_transmit_stdout_num0(char data, FILE *stream);
int __UART_transmit_stdout_num1(char data, FILE *stream);
int __UART_receive_stdin_num0(FILE *stream);
int __UART_receive_stdin_num1(FILE *stream);

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