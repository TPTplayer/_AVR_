#include <avr/io.h>
#include <stdint.h>
#include "mega128_SPI.h"

void SPI_master_initializer(void){
	PORT_SPI = (1 << SS);
	DDR_SPI = (1 << MOSI) | (1 << SCK) | (1 << SS);
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	//SPI enable, master mode, clork rate fck/16
	
	return;
}

void SPI_slave_initializer(void){
	DDR_SPI = (1 << MISO);
	SPCR = (1 << SPE);
	//SPI enable, slave mode
	
	return;
}

uint8_t SPI_master_com(uint8_t data){
	uint8_t slave_return = 0;
	
	SPDR = data;
	PORT_SPI &= ~(1 << SS);
	while(!(SPSR & (1 << SPIF)));
	
	PORT_SPI |= (1 << SS);
	
	return slave_return;
}

uint8_t SPI_slave_com(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

