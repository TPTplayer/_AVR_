#ifndef DATADISPLAY_H_
#define DATADISPLAY_H_

void convertFloattoUint_8(float number, uint8_t *v_uint_8);
void DisplayHeatsinkTemp(float *temp);
void DisplayInsideTemp_master(float temp);
void DisplayOverheatPeltier(uint8_t val);

#endif /* DATADISPLAY_H_ */