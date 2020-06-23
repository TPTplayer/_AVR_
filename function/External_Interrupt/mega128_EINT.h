#include <stdint.h>

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#define R_EDGE 0x03
#define F_EDGE 0x02
#define L_LEVEL 0x00

void extint_initializer(int extint_num, uint8_t trig_mode);

#endif