#include "gate.h"
#include "config.h"

void setup() {
  Serial.begin(9600);
  initGate();
}

void loop() {
  openGate();
  delay(1000);
  closeGate();
  delay(1000);
}
