#ifndef SENSOR_H
#define SENSOR_H

void initUltraSonic();

float getDistance(int trig_pin, int echo_pin);
void handleEntry();
void handleExit();


#endif