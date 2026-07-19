#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>

#include "parking.h"
#include "config.h"

Adafruit_LiquidCrystal lcd(0);

extern int reservedSlots;
extern int availableSlots;

const int TOTAL_SLOTS = 3;

const int slotPins[TOTAL_SLOTS] =
{
    SLOT1,
    SLOT2,
    SLOT3
};

bool currentState[TOTAL_SLOTS];
bool lastState[TOTAL_SLOTS];


void initParking()
{
    for(int i = 0; i < TOTAL_SLOTS; i++)
    {
        pinMode(slotPins[i], INPUT_PULLUP);
    }

    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    lcd.begin(16,2);
    lcd.setBacklight(HIGH);
}


void updateParking()
{
    int freeSlots = 0;
  
    // Read Slots

    for(int i = 0; i < TOTAL_SLOTS; i++)
    {
        currentState[i] = (digitalRead(slotPins[i]) == LOW);

        // العربية ركنت 
        if(!lastState[i] && currentState[i] && reservedSlots > 0)
        {
            reservedSlots--;
        }

        if(!currentState[i])
        {
            freeSlots++;
        }
    }

    // Calculate Available

    availableSlots = freeSlots - reservedSlots;

    if(availableSlots < 0)
    {
        availableSlots = 0;
    }

    // leds
    

    digitalWrite(GREEN_LED_PIN, availableSlots > 0);
    digitalWrite(RED_LED_PIN, availableSlots == 0);

    // lcd

    lcd.setCursor(0,0);
    lcd.print("Free:");
    lcd.print(availableSlots);
    lcd.print("   ");

    lcd.setCursor(0,1);
    lcd.print("S:");

    for(int i = 0; i < TOTAL_SLOTS; i++)
    {
        if(currentState[i])
        {
            lcd.print("X");
        }
        else
        {
            lcd.print(i + 1);
        }

        if(i < TOTAL_SLOTS - 1)
        {
            lcd.print(" ");
        }
    }

    // Serial Monitor

    Serial.print("Available: ");
    Serial.println(availableSlots);

    for(int i = 0; i < TOTAL_SLOTS; i++)
    {
        Serial.print("Slot ");
        Serial.print(i + 1);
        Serial.print(": ");

        if(currentState[i])
            Serial.println("Occupied");
        else
            Serial.println("Empty");
    }

    Serial.println("----------------");

    // save current state

    for(int i = 0; i < TOTAL_SLOTS; i++)
    {
        lastState[i] = currentState[i];
    }
}