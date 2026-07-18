#include <Arduino.h>
#include <Servo.h>

#include "entry_exit.h"
#include "config.h"

Servo gateServo;

void initUltraSonic(){
    pinMode(ENTRY_TRIG_PIN, OUTPUT);
    pinMode(ENTRY_ECHO_PIN, INPUT);

    pinMode(EXIT_TRIG_PIN, OUTPUT);
    pinMode(EXIT_ECHO_PIN, INPUT);

    digitalWrite(ENTRY_TRIG_PIN, LOW);
    digitalWrite(EXIT_TRIG_PIN, LOW);
}

void initServo(){
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

    return distance;
}

void openGate(){
    gateServo.write(90);
}

void closeGate(){
    gateServo.write(0);
}

void isCarEntering(){
    return getDistance(ENTRY_TRIG_PIN, ENTRY_ECHO_PIN) < DETECTION_DISTANCE;
}

void isCarExiting(){
    return getDistance(EXIT_TRIG_PIN, EXIT_ECHO_PIN) < DETECTION_DISTANCE;
}