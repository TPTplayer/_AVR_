#include "debug.h"

static FILE *stream;

void printf_activate(void){
	UART1_initializer(UBRR_VAL);
	UART1_setup_stdio(stream);
	return;
}