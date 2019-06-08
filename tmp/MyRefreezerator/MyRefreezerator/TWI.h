#ifndef TWI_H_
#define TWI_H_

void TWI_initializer(void);
void TWI_transmit(uint8_t slave_addr, uint8_t data);

#define SLAVE_ADDR 0x23

#endif /* TWI_H_ */