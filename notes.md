# Gate Module Integration Notes

## Purpose

The Gate Module is responsible for:

- Detecting vehicle entry
- Detecting vehicle exit
- Opening and closing the gate
- Managing parking reservations
- Rejecting vehicles when parking is full

The Parking Module should NOT directly control the gate or reservation logic.

---

# Public API

The following functions are intended to be used by other modules.

---

## Initialization

### initGate()

Initializes:

- Ultrasonic sensors
- Servo motor
- Buzzer

Must be called once during setup.

```cpp
initGate();
```

---

## Main Update Loop

### handleEntry()

Processes vehicle entry events.

Should be called continuously from loop().

```cpp
handleEntry();
```

---

### handleExit()

Processes vehicle exit events.

Should be called continuously from loop().

```cpp
handleExit();
```

---

### updateGate()

Handles gate timeout logic.

Should be called continuously from loop().

```cpp
updateGate();
```

---

## Reservation Functions

### reserveSlot()

Creates a temporary reservation.

Normally called internally by the Gate Module.

Do NOT call from other modules.

---

### releaseReservation()

Releases a reservation after a vehicle occupies a parking space.

This function SHOULD be called by the Parking Module when:

```text
Empty -> Occupied
```

is detected.

Example:

```cpp
if(slotChangedFromEmptyToOccupied){
    releaseReservation();
}
```

---

# Shared Variables

## availableSlots

Owned by Parking Module.

Represents physically available parking spaces.

Example:

```cpp
availableSlots = 3;
```

The Gate Module reads this value to decide whether entry is allowed.

---

## reservedSlots

Owned by Gate Module.

Represents vehicles that entered but have not parked yet.

Example:

```cpp
reservedSlots = 1;
```

The Parking Module may read this value for display purposes.

Do NOT modify directly.

---

# Available Space Formula

The correct number of free spaces is:

```cpp
availableSlots - reservedSlots
```

Example:

```text
availableSlots = 3
reservedSlots = 1

Displayed Free Spaces = 2
```

LCD and LEDs should use this value.

---

# Slot Event Requirements

## Empty -> Occupied

Parking Module must:

```cpp
releaseReservation();
```

Reason:

The vehicle has successfully parked.

---

## Occupied -> Empty

Parking Module must:

```cpp
availableSlots++;
```

Reason:

A parking space has become available.

---

# What Other Modules Should NOT Do

Do NOT:

```cpp
reservedSlots++;
reservedSlots--;
```

Use:

```cpp
releaseReservation();
```

instead.

Do NOT:

```cpp
openGate();
closeGate();
```

from outside the Gate Module.

Vehicle movement should be handled only by the Gate Module.

---

# Required Main Loop

```cpp
void loop() {
    handleEntry();
    handleExit();
    updateGate();

    updateParkingSlots();
    updateLCD();
    updateLEDs();
}
```
