#ifndef MEGA128_SPI_H_
#define MEGA128_SPI_H_

#define DDR_SPI DDRB
#define PORT_SPI PORTB

#define SS 0
#define SCK 1
#define MOSI 2
#define MISO 3

void SPI_master_initializer(void);
void SPI_slave_initializer(void);
uint8_t SPI_master_com(uint8_t data);
uint8_t SPI_slave_com(uint8_t data);

/*
<connection>
SS(CS) - SS(CS)
SCK - SCK
MOSI - MOSI
MISO - MISO
*/

#endif /* MEGA128_SPI_H_ */