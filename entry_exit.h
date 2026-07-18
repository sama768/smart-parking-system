#ifndef SENSOR_H
#define SENSOR_H

void initUltraSonic();
float getDistance(int trig_pin, int echo_pin);
bool isCarEntering();
bool isCarExiting();

void initServo();
void openGate();
void closeGate();

#endif