#ifndef MEAG128_USART_H_
#define MEAG128_USART_H_

#include <stdint.h>

#define USART_OSC 16000000
#define BAUD 9600
#define UBRR_VAL USART_OSC / 16 / BAUD - 1

void UART_initializer(int uart_num, uint32_t ubrr);
void UART_transmit(int uart_num, uint8_t data);
uint8_t UART_receive(int uart_num);
void UART_flush(int uart_num);

/*
<connection>
green: RX
white: TX

<receiver settings>
baudrate: 9600
parity: none
stop bit: 2
flow control: none
*/

#endif /* MEAG128_USART_H_ */