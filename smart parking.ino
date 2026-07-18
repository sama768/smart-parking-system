#include "entry_exit.h"
#include "config.h"

void setup() {
  Serial.begin(9600);
  initUltraSonic();
  initServo();
}

void loop() {
  openGate();
  delay(1000);
  closeGate();
  delay(1000);
}
