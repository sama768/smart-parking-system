#pragma once

#include "gate.h"
#include "config.h"
#include "parking.h"

int availableSlots = 3;
int reservedSlots = 0;

void setup() {
  Serial.begin(9600);
  initGate();

  initParking();
  closeGate();
}

void loop() {
  updateParking();
  updateGateSystem();
}
