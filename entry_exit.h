#ifndef SENSOR_H
#define SENSOR_H

void initGate();

float getDistance(int trig_pin, int echo_pin);
bool isCarEntering();
bool isCarExiting();

void openGate();
void closeGate();

void handleEntry();
void handleExit();

#endif