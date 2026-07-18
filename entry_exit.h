#ifndef SENSOR_H
#define SENSOR_H

void initUltraSonic();
float getDistance(int trig_pin, int echo_pin);
float getEntryDistance();
float getExitDistance();

void initServo();
void openGate();
void closeGate();

#endif