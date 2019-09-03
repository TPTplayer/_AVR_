#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#define TRIG 0x01
#define TRIG_PORT PORTA

void timer_start(void);
void timer_end(void);
void falling_edge_EINT_set(void);
void trig_set(void);
void start_echo_measurement(void);
void end_echo_measurement(void);
float distance_calculation(int duration);

float ultrasonic_sensor(void);

#endif /* ULTRASONIC_SENSOR_H_ */