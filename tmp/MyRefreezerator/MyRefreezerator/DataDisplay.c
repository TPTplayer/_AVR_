#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CLCD.h"
#include "sensor.h"
#include "TWI.h"

void convertFloattoUint_8(float number, uint8_t *v_uint_8){
	*v_uint_8 = number;
}

void DisplayHeatsinkTemp(float *temp){
	uint8_t v_uint_8[4] = {0, };
	char str[17] = {0, };
	
	for(int cnt = 0; cnt < 4; cnt++){
		convertFloattoUint_8(temp[cnt], &(v_uint_8[cnt]));
	}
	
	sprintf(str, "P1:%dC  P2:%dC", v_uint_8[0], v_uint_8[1]);
	CLCD_putstr(0x00, str);
	
	memset(str, 0x00, 17);
	
	sprintf(str, "P3:%dC  P4:%dC", v_uint_8[2], v_uint_8[3]);
	CLCD_putstr(0x40, str);
}

void DisplayInsideTemp_master(float temp){
	uint8_t v_uint_8 = 0;
	
	convertFloattoUint_8(temp, &v_uint_8);
	TWI_transmit(SLAVE_ADDR, v_uint_8);
}

void DisplayWaringMessage(void){
	uint8_t val = -127;
	
	TWI_transmit(SLAVE_ADDR, val);
}