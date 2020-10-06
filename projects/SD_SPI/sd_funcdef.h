#ifndef SD_FUNCDEF_H_
#define SD_FUNCDEF_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <inttypes.h>

int sdcard_init(void);
int sdcard_read(uint32_t address, uint8_t *buf);

void __sd_cmd_transmit(uint8_t cmd_index, uint32_t argument);
uint64_t __sd_response_receive(int response);
uint8_t __sd_crc7_generator(uint8_t header, uint32_t argument);
void __sd_powerup(void);

#endif /* SD_FUNCDEF_H_ */