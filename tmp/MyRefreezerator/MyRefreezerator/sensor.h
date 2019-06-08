#ifndef SENSOR_H_
#define SENSOR_H_
#define F_VAL 10

void ADC_initializer(void);

float getHeatsink1Temp(void);
float getHeatsink2Temp(void);
float getHeatsink3Temp(void);
float getHeatsink4Temp(void);

float getInsideTemp(void);

#endif /* SENSOR_H_ */