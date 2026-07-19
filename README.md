# Smart Parking System using Arduino

## Project Overview

This project implements a **Smart Parking System** using Arduino. The system automatically detects vehicles entering and leaving the parking area, controls the entrance gate using a servo motor, monitors parking slot occupancy, displays the number of available parking spaces on an LCD, and indicates the parking status using LEDs and a buzzer.

---

# Features

* Automatic gate control using a Servo Motor.
* Vehicle detection using two Ultrasonic Sensors.
* Three parking slots monitored using digital sensors (IR sensors).
* Real-time calculation of available parking spaces.
* LCD display showing available spaces and slot status.
* Green LED indicates that parking spaces are available.
* Red LED indicates that the parking lot is full.
* Buzzer alerts when a vehicle attempts to enter while the parking lot is full.
* Reservation mechanism prevents multiple vehicles from taking the same parking space before parking.
* Invalid ultrasonic readings are filtered for reliable vehicle detection.

---

# Components

| Component                          |  Quantity |
| ---------------------------------- | --------: |
| Arduino Uno                        |         1 |
| HC-SR04 Ultrasonic Sensor          |         2 |
| Servo Motor (SG90)                 |         1 |
| 16x2 LCD (I2C)                     |         1 |
| IR sensor (Parking Slot Sensor)    |         3 |
| Green LED                          |         1 |
| Red LED                            |         1 |
| Buzzer                             |         1 |
| Jumper Wires                       | As needed |

---

# Pin Configuration

| Component                | Arduino Pin |
| ------------------------ | ----------: |
| Entry Ultrasonic Trigger |          D7 |
| Entry Ultrasonic Echo    |          D6 |
| Exit Ultrasonic Trigger  |          D5 |
| Exit Ultrasonic Echo     |          D4 |
| Servo Motor              |          D3 |
| Slot 1 Sensor            |          D8 |
| Slot 2 Sensor            |          D9 |
| Slot 3 Sensor            |         D10 |
| Buzzer                   |         D11 |
| Green LED                |         D12 |
| Red LED                  |         D13 |

---

# System Operation

## 1. Vehicle Entry

* The entrance ultrasonic sensor detects an approaching vehicle.
* If at least one parking space is available:

  * The gate opens.
  * One parking space is temporarily reserved.
* If the parking lot is full:

  * The gate remains closed.
  * The buzzer sounds.

---

## 2. Parking Reservation

To prevent two vehicles from occupying the same parking space:

* When a vehicle enters, one parking space is reserved immediately.
* The reserved space is removed from the available count.
* After the vehicle parks in one of the slots, the reservation is released automatically.

This ensures the displayed number of available spaces remains accurate.

---

## 3. Parking Slot Monitoring

Each parking slot is continuously monitored.

When a slot changes:

* Empty → Occupied

  * The reservation is removed.
* Occupied → Empty

  * The number of available parking spaces increases automatically.

---

## 4. Vehicle Exit

When a vehicle reaches the exit sensor:

* The exit gate opens.
* After the vehicle leaves, the gate closes automatically.

---

## 5. LCD Display

The LCD displays:

**First Line**

```text
Free:2
```

Displays the number of currently available parking spaces.

**Second Line**

```text
Slots:1 X 3
```

Meaning:

* 1 → Slot 1 is available.
* X → Slot 2 is occupied.
* 3 → Slot 3 is available.

---

# LED Indicators

| LED   | Meaning                      |
| ----- | ---------------------------- |
| Green | Parking spaces are available |
| Red   | Parking lot is full          |

---

# Buzzer

The buzzer activates when:

* A vehicle attempts to enter while no parking spaces are available.

---

# Software Logic

The system performs the following tasks continuously:

1. Read parking slot sensors.
2. Detect newly occupied parking slots.
3. Calculate available parking spaces.
4. Update LEDs.
5. Detect vehicles at the entrance.
6. Detect vehicles at the exit.
7. Control the servo gate.
8. Update the LCD display.

---

# Parking Availability Formula

The number of available parking spaces is calculated using:

```text
Available Spaces = Empty Slots − Reserved Slots
```

Where:

* **Empty Slots** are physically empty parking spaces.
* **Reserved Slots** are spaces temporarily assigned to vehicles that entered but have not parked yet.

---

# Libraries Used

```cpp
#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>
#include <Arduino.h>
```

---


# Future Improvements

* Add RFID authentication.
* Integrate Wi-Fi (ESP8266/ESP32) for remote monitoring.
* Develop a mobile application for real-time parking information.
* Store parking statistics in a cloud database.


# Error Handling

The system includes several mechanisms to improve reliability and prevent incorrect behavior.

### 1. Ultrasonic Sensor Timeout

If an ultrasonic sensor does not receive an echo signal within the specified timeout period, the system assumes that no object is detected and returns a safe distance value instead of blocking the program.

### 2. Entry Gate Timeout

If a vehicle is detected at the entrance but does not complete the entry process within 10 seconds, the system:

* Closes the gate automatically.
* Cancels the reserved parking space.
* Returns the parking availability to its previous state.

This prevents unavailable parking spaces from remaining reserved indefinitely.

### 3. Exit Gate Timeout

If the exit process is not completed within 10 seconds, the gate automatically closes to ensure normal system operation.

### 4. Parking Full Protection

When no parking spaces are available:

* The entrance gate remains closed.
* The buzzer is activated to notify the driver.
* The red LED indicates that the parking lot is full.

### 5. Reserved Parking Logic

To avoid assigning the same parking space to multiple vehicles, the system temporarily reserves a parking space immediately after a vehicle enters the gate. The reservation is automatically released once the vehicle occupies a parking slot.

### 6. Invalid Ultrasonic Readings

Ultrasonic sensors may occasionally return invalid distance measurements due to signal loss, environmental noise, or objects outside the sensor's operating range.

To improve system reliability, any reading outside the valid operating range (less than **2 cm** or greater than **400 cm**) is considered invalid and ignored. This prevents false vehicle detection and improves the overall accuracy of the parking system.


---


# Work Distribution


## abdo – Vehicle Detection & Gate Control

Responsible for the vehicle movement and gate operation.

### Tasks

* Configure the ultrasonic sensors.
* Detect vehicle entry and exit.
* Calculate vehicle distance.
* Control the servo motor.
* Manage gate opening and closing.
* Implement the parking reservation logic (`reservedSlots`).
* Handle gate timeout conditions.
* Control the buzzer when the parking lot is full.

---

## fatma – Parking Management & User Interface

Responsible for monitoring parking spaces and displaying system information.

### Tasks

* Read parking slot sensors.
* Detect occupied and empty parking spaces.
* Calculate available parking spaces.
* Update parking availability.
* Control the green and red LEDs.
* Display parking information on the LCD.
* Maintain parking slot status.
* Test and debug the system using the Serial Monitor.

---
# code requirements 

Commented Code

Meaningful Commits

Each member works on a dedicated branch

# Project Architecture

```text
                +----------------------+
                |   Entry Ultrasonic   |
                +----------+-----------+
                           |
                           v
                    +--------------+
                    |   Arduino    |
                    +------+-------+
                           |
        +------------------+------------------+
        |                  |                  |
        v                  v                  v
  Servo Motor         LCD Display      LEDs & Buzzer
        |
        v
 Parking Area
        |
        v
 Parking Slot Sensors
        |
        v
 Exit Ultrasonic
```
