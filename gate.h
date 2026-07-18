#ifndef GATE_H
#define GATE_H

const int DETECTION_DISTANCE = 15;
const int BUZZER_SOUND_TIME = 1000;

bool prevEntryState = false;
bool prevExitState = false;

void initGate();

float getDistance(int trig_pin, int echo_pin);
bool isCarEntering();
bool isCarExiting();

void openGate();
void closeGate();

void handleEntry();
void handleExit();

#endif