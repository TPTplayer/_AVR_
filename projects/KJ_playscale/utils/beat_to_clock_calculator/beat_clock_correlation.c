#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define MASTERCLK	16000000

#define BEAT1	0
#define BEAT2	1
#define BEAT4	2
#define BEAT8	3
#define BEAT16	4
#define BEAT32	5
#define BEAT64	6	

#define BPM 	120

float calc_beattime(uint8_t beat, uint16_t bpm);
float calc_beatclock(uint32_t clockspeed, float freq);

int main(int argc, char *argv[]) {
	printf("beat1: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT1, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT1, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat2: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT2, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT2, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat4: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT4, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT4, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat8: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT8, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT8, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat16: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT16, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT16, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat32: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT32, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT32, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
	printf("beat64: %.2fms > %.4fclk @ %"PRIu16"bpm > %.2fKHz\n", calc_beattime(BEAT64, BPM), calc_beatclock(MASTERCLK / 1024, calc_beattime(BEAT64, BPM)), BPM, (float)MASTERCLK / 1024.0f / 1000.0f);
		
	system("pause");
	return 0;
}

float calc_beattime(uint8_t beat, uint16_t bpm){
	float ms_per_beatquard = (60.0f / (float)bpm) * 1000.0f;
	float beattime;
	
	switch(beat){
	case BEAT1:
		beattime = ms_per_beatquard * 4.0f;
		break;
	case BEAT2:
		beattime = ms_per_beatquard * 2.0f;
		break;
	case BEAT4:
		beattime = ms_per_beatquard;
		break;
	case BEAT8:
		beattime = ms_per_beatquard / 2.0f;
		break;
	case BEAT16:
		beattime = ms_per_beatquard / 4.0f;
		break;
	case BEAT32:
		beattime = ms_per_beatquard / 8.0f;
		break;
	case BEAT64:
		beattime = ms_per_beatquard / 16.0f;
		break;
	default:
		break;
	}
	
	return beattime;
}

float calc_beatclock(uint32_t clockspeed, float beattime){
	float clock = 0.0f;
	float ms_per_clock = (float)clockspeed / 1000.0f;
	clock = ms_per_clock * beattime;
	return clock;
}
