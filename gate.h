#ifndef GATE_H
#define GATE_H

const int DETECTION_DISTANCE = 15;
const int CLEAR_DISTANCE = 20;
const unsigned long DETECTION_CONFIRM = 1000;
const unsigned long ENTRY_COOLDOWN = 2000;


const int BUZZER_SOUND_TIME = 1000;
const int ENTRY_TIMEOUT = 10000;


enum GateMode{
    NONE,
    ENTRY,
    EXIT
};

void initGate();

float getDistance(int trig_pin, int echo_pin);
bool isCarEntering();
bool isCarExiting();

void openGate();
void closeGate();

void handleEntry();
void handleExit();
void updateGate();

void reserveSlot();
void releaseReservation();

#endif