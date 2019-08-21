#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "CLCD.h"
#include "sensor.h"
#include "TWI.h"

void convertFloattoUint_8(float number, int8_t *v_uint_8){
	*v_uint_8 = (int8_t)number;
}

void DisplayHeatsinkTemp(float *temp){
	int8_t v_uint_8[4] = {0, };
	char str[17];
	char dummy[5] = {0, };
	
	memset(str, 0, 17);
	
	for(int cnt = 0; cnt < 4; cnt++){
		convertFloattoUint_8(temp[cnt], &(v_uint_8[cnt]));
	}
	
	for(int cnt = 0; cnt < 4; cnt++){
		sprintf(dummy, "%d", v_uint_8[cnt]);
	}
	
	sprintf(str, "P1:%dC  P2:%dC    ", v_uint_8[0], v_uint_8[1]);
	CLCD_putstr(0x00, str);
	
	memset(str, 0x00, 17);
	
	for(int cnt = 0; cnt < 4; cnt++){
		sprintf(dummy, "%d", v_uint_8[cnt]);
	}
	
	sprintf(str, "P3:%dC  P4:%dC    ", v_uint_8[2], v_uint_8[3]);
	CLCD_putstr(0x40, str);
}

void DisplayInsideTemp_master(float temp){
	int8_t v_int_8 = 0;
	convertFloattoUint_8(temp, &v_int_8);
	
	TWI_start();
	TWI_transmit(SLAVE_ADDR, v_int_8);
	TWI_stop();
}

void DisplayOverheatPeltier(uint8_t val){
	TWI_start();
	TWI_transmit(SLAVE_ADDR, val);
	TWI_stop();
}