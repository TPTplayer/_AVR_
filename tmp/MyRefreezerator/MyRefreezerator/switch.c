#include <avr/io.h>
#include <avr/interrupt.h>

void EINT_set(void){
	EICRA = (1 << ISC31);
	EIMSK = (1 << INT3);
}