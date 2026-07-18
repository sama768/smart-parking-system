#pragma once

#include "gate.h"
#include "config.h"

int availableSlots = 3;


void setup() {
  Serial.begin(9600);
  initGate();
  closeGate();
}

void loop() {
  if(isCarExiting()){
    handleExit();
  }
}
