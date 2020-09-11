#ifndef TC77_TEMP_SENSOR_H_
#define TC77_TEMP_SENSOR_H_

#include <avr/io.h>
#include <stdint.h>

#define SET     (unsigned) 1
#define CLEAR   (unsigned) 0

#define _MASK_SIGN   0x1000
#define _MASK_TEMP   0x7FF1
#define _LSB         0.0625

#define _CONV_COMP_MASK 0x0004 

#define _TC77_CS    0
#define _TC77_SCK   1
#define _TC77_DATA  3

#define _TC77_CS_PIN    (1 << _TC77_CS)
#define _TC77_SCK_PIN   (1 << _TC77_SCK)
#define _TC77_DATA_PIN  (1 << _TC77_DATA)

#define _DDR_TC77   DDRB
#define _PORT_TC77  PORTB
#define _PIN_TC77   PINB

#define _TC77_SCK_HIGH   _PORT_TC77 |= _TC77_SCK_PIN
#define _TC77_SCK_LOW    _PORT_TC77 &= (~_TC77_SCK_PIN)

void tc77_init(void);
float tc77_get_temp(void);

void _tc77_cs_enable(void);
void _tc77_cs_disable(void);
uint16_t _tc77_get_rawdata(void);

#endif /* TC77_TEMP_SENSOR_H_ */