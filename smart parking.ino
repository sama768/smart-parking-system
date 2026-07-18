#pragma once

#include "gate.h"
#include "config.h"

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
