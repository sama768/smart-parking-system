#ifndef SENSOR_H
#define SENSOR_H

void initSensors();
float getDistance(int trig_pin, int echo_pin);
float getEntryDistance();
float getExitDistance();


#endif