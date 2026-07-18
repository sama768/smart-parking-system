#ifndef CONFIG_H
#define CONFIG_H

#define ENTRY_TRIG_PIN 7
#define ENTRY_ECHO_PIN 6

#define EXIT_TRIG_PIN 5
#define EXIT_ECHO_PIN 4

#define BUZZER_PIN 11
#define SERVO_PIN 3

const int DETECTION_DISTANCE = 15;
const int BUZZER_SOUND_TIME = 1000;

bool prevEntryState = false;
bool prevExitState = false;
int reservedSlots = 0;
int availableSlots = 3;

#endif