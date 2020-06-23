#ifndef TWI_H_
#define TWI_H_

void TWI_master_initializer(void);
void TWI_start(void);
void TWI_transmit(uint8_t slave_addr, uint8_t data);
void TWI_stop(void);

#define SLAVE_ADDR 0x23

#endif /* TWI_H_ */