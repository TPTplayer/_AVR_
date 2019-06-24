#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CLCD.h"

void DisplayCurrentStatus(int8_t temp, int8_t ovh_flag){
	char str[17] = {0, };
	char warning[17] = "WARNING OVERHEAT";
	char void_arr[17] = "                ";
	char dummy[4] = {0, };
	
	sprintf(dummy, "%d", temp);
		
	sprintf(str, "Inside: %d", temp);
	CLCD_putstr(0x00, str);
	CLCD_printstr(0x0F, "C", 1);
	
	if(ovh_flag == 1){
		CLCD_putstr(0x40, warning);	
	}
	else{
		CLCD_putstr(0x40, void_arr);
	}
}