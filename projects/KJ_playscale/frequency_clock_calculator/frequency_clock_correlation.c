#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define MASTERCLK			(uint32_t)16000000
#define REF_FREQ			55
#define SCALE_PER_OCTAVE	12
#define OCTAVE_NUM			8

float calc_scalefreq(int octave, int scale);
float calc_scaleclock(uint32_t clockspeed, float freq);

int main(int argc, char *argv[]) {
	int idx_octave = 0, idx_scale = 0;
	float freq = 0.0f, clock = 0.0f;
	
	for(idx_octave = 0; idx_octave < OCTAVE_NUM; idx_octave++){
		printf("octave: %d\n", idx_octave + 1);
		
		for(idx_scale = 0; idx_scale < SCALE_PER_OCTAVE; idx_scale++){
			freq = calc_scalefreq(idx_octave, idx_scale);
			clock = calc_scaleclock(MASTERCLK, freq);
			printf("frequency: %.4fHz > clock: %.4f @ %.4fMHz\n", freq, clock, ((float)MASTERCLK / 1000000.0f));
		}
		putchar('\n');
	}
	
	system("pause");
	return 0;
}

float calc_scalefreq(int octave, int scale){
	float freq = 0.0f;
	float numerator[SCALE_PER_OCTAVE] = {-9.0f, -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
	freq = (REF_FREQ * pow(2.0f, (float)octave)) * pow(2.0f, numerator[scale] / (float)SCALE_PER_OCTAVE);
    return freq;	
}

float calc_scaleclock(uint32_t clockspeed, float freq){
	float clock = 0.0f;
	float us_per_clock = (float)clockspeed / 1000000.0f;
	
	if(freq == 0.0f) return 0.0f;
	clock = us_per_clock * ((1.0f / freq) / 2.0f) * 1000000.0f;
	return clock;
}
