#include <Arduino.h>
#include <Servo.h>

#include "gate.h"
#include "config.h"

Servo gateServo;

bool prevEntryState = false;
bool prevExitState = false;

bool isGateOpen = false;
unsigned long gateOpenedAt = 0;

int reservedSlots = 0;

bool isCarAtEntry = false;
unsigned long entryDetectionStart = 0;

GateMode gateMode = NONE;

void initGate(){
    pinMode(ENTRY_TRIG_PIN, OUTPUT);
    pinMode(ENTRY_ECHO_PIN, INPUT);

    pinMode(EXIT_TRIG_PIN, OUTPUT);
    pinMode(EXIT_ECHO_PIN, INPUT);

    pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(ENTRY_TRIG_PIN, LOW);
    digitalWrite(EXIT_TRIG_PIN, LOW);

    gateServo.attach(SERVO_PIN);
}

float getDistance(int trig_pin, int echo_pin){
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);

    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    long duration = pulseIn(echo_pin, HIGH, 30000);

    if(duration == 0){
        return 999.0;
    }

    float distance = float(duration) * 0.034 / 2; 

    if(distance < 2 || distance > 400){
        return 999.0;
    }

    return distance;
}

void openGate(){
    gateServo.write(90);
    isGateOpen = true;
    gateOpenedAt = millis();
}

void closeGate(){
    gateServo.write(0);
    isGateOpen = false;
    gateMode = NONE;
}

bool isCarEntering(){
    float distance = getDistance(ENTRY_TRIG_PIN, ENTRY_ECHO_PIN);

    if(distance <= DETECTION_DISTANCE){
        if(entryDetectionStart == 0){
            entryDetectionStart = millis();
        }

        if(millis() - entryDetectionStart >= 1000){
            isCarAtEntry = true;
        }
    }
    else if(distance >= CLEAR_DISTANCE){
        entryDetectionStart = 0;
        isCarAtEntry = false;
    }

    return isCarAtEntry;
}

bool isCarExiting(){
    return getDistance(EXIT_TRIG_PIN, EXIT_ECHO_PIN) <= DETECTION_DISTANCE;
}

void handleEntry(){
    bool canEnter = availableSlots - reservedSlots > 0;
    bool currentEntryState = isCarEntering();

    if(currentEntryState && !prevEntryState){
        if(canEnter){
            Serial.print(currentEntryState);
            openGate();
            reserveSlot();
            gateMode = ENTRY;
        } else{
            tone(BUZZER_PIN, 1000, BUZZER_SOUND_TIME);
        }
    } 
    if(!currentEntryState && prevEntryState){
        closeGate();
    }

    prevEntryState = currentEntryState;
}

void handleExit(){
    bool currentExitState = isCarExiting();

    if(currentExitState && !prevExitState){
        openGate();
        gateMode = EXIT;
    }
    
    if(!currentExitState && prevExitState){
        closeGate();
    }

    prevExitState = currentExitState;
}

void reserveSlot(){
    if(reservedSlots < availableSlots){
        reservedSlots++;
    }
}

void releaseReservation(){
    if(reservedSlots > 0){
        reservedSlots--;
    }
}

void updateGate(){
    if(isGateOpen && millis() - gateOpenedAt >= ENTRY_TIMEOUT){
        if(gateMode == ENTRY){
            releaseReservation();
        }
        closeGate();
    }
}