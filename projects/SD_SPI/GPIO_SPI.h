#ifndef GPIO_SPI_H_
#define GPIO_SPI_H_

#include <avr/io.h>
#include <stdint.h>

#define SET (uint8_t) 1
#define CLEAR (uint8_t) 0

#define _DDR_SS     DDRA
#define _DDR_SCK    DDRA
#define _DDR_MOSI   DDRA
#define _DDR_MISO   DDRA

#define _PORT_SS    PORTA
#define _PORT_SCK   PORTA
#define _PORT_MOSI  PORTA
#define _PORT_MISO  PORTA

#define _PIN_SS     PINA
#define _PIN_SCK    PINA
#define _PIN_MOSI   PINA
#define _PIN_MISO   PINA

#define _SS         0
#define _SCK        1
#define _MOSI       2
#define _MISO       3

#define _SS_PIN     (1 << _SS)
#define _SCK_PIN    (1 << _SCK)
#define _MOSI_PIN   (1 << _MOSI)
#define _MISO_PIN   (1 << _MISO)

typedef struct {
    uint8_t transfer_complete : 1;
}Master_flag;

typedef struct {
    uint8_t transfer_complete : 1;
    uint8_t transfer_broke : 1;
}Slave_flag;

void SPI_master_init(void);
void SPI_SS_enable(void);
void SPI_SS_disable(void);
uint64_t SPI_master_transfer(uint8_t num_bit, uint64_t data);

void SPI_slave_init(void);
uint8_t SPI_SS_check(void);
uint64_t SPI_slave_transfer(uint8_t num_bit, uint64_t data);

uint8_t SPI_master_isbusy(void);
uint8_t SPI_slave_isbusy(void);
uint8_t SPI_slave_xfer_isbroken(void);

#endif /* GPIO_SPI_H_ */