#ifndef TWI_SLAVE_H_
#define TWI_SLAVE_H_

#define SLAVE_ADDR 0x23

void TWI_initializer(void);
ISR(TWI_vect);

#endif /* TWI_SLAVE_H_ */