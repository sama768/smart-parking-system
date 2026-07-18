#ifndef CONFIG_H
#define CONFIG_H

// Gate realted pins
#define ENTRY_TRIG_PIN 7
#define ENTRY_ECHO_PIN 6

#define EXIT_TRIG_PIN 5
#define EXIT_ECHO_PIN 4

#define BUZZER_PIN 11
#define SERVO_PIN 3

// reservation and availability variables
extern int reservedSlots;
extern int availableSlots;

#endif