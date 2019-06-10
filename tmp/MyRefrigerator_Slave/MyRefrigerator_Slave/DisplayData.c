#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DisplayCurrentStatus(int8_t temp, int8_t ovh_flag){
	char str[17] = {0, };
	char warning[17] = "WARNING OVERHEAT";
	char void_arr[17] = "                ";
		
	sprintf(str, "Inside: %d     C", temp);
	CLCD_putstr(0x00, str);
	
	if(ovh_flag == 1){
		CLCD_putstr(0x40, warning);	
		CLCD_putstr(0x40, void_arr);
	}
}