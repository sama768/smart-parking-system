#include <Arduino.h>
#include "sensors.h"
#include "config.h"

void initSensors(){
    pinMode(ENTRY_TRIG_PIN, OUTPUT);
    pinMode(ENTRY_ECHO_PIN, INPUT);

    pinMode(EXIT_TRIG_PIN, OUTPUT);
    pinMode(EXIT_ECHO_PIN, INPUT);

    digitalWrite(ENTRY_TRIG_PIN, LOW);
    digitalWrite(EXIT_TRIG_PIN, LOW);
}

float getDistance(int trig_pin, int echo_pin){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH);
  float distance = float(duration) * 0.034 / 2; 

  return distance;
}

float getEntryDistance(){
  return getDistance(ENTRY_TRIG_PIN, ENTRY_ECHO_PIN);
}

float getExitDistance(){
  return getDistance(EXIT_TRIG_PIN, EXIT_ECHO_PIN);
}

