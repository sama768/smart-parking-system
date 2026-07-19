# Gate Module Integration Notes

## Purpose

The Gate Module is responsible for:

- Vehicle detection using ultrasonic sensors
- Gate control using a servo motor
- Entry/Exit direction detection
- Parking reservation management
- Full parking rejection and buzzer alerts
- Gate timeout handling

The module owns all gate-related logic.

---

# Architecture

The system uses two ultrasonic sensors mounted on opposite sides of the gate.

```text
Outside
   |
   |  Entry Sensor
   V
+--------+
|  Gate  |
+--------+
   ^
   |  Exit Sensor
   |
Parking Area
```

---

# Vehicle Entry

A vehicle is considered entering when:

```text
Entry Sensor
        ↓
Gate Opens
        ↓
Reservation Created
        ↓
Exit Sensor
        ↓
Gate Closes
```

Sequence:

```text
ENTRY → EXIT
```

---

# Vehicle Exit

A vehicle is considered exiting when:

```text
Exit Sensor
        ↓
Gate Opens
        ↓
Entry Sensor
        ↓
Gate Closes
```

Sequence:

```text
EXIT → ENTRY
```

---

# State Machine

The gate operates using a state machine.

## NONE

Idle state.

The gate is waiting for a vehicle.

```cpp
NONE
```

---

## ENTRY

An entry operation is in progress.

Expected sequence:

```text
ENTRY → EXIT
```

The gate is waiting for the vehicle to cross.

```cpp
ENTRY
```

---

## EXIT

An exit operation is in progress.

Expected sequence:

```text
EXIT → ENTRY
```

The gate is waiting for the vehicle to cross.

```cpp
EXIT
```

---

# Public API

## initGate()

Initializes:

- Servo
- Ultrasonic sensors
- Buzzer

Call once during setup.

```cpp
initGate();
```

---

## updateGateSystem()

Main gate update function.

Handles:

- Entry detection
- Exit detection
- Reservation logic
- Gate control
- Timeouts

Must be called continuously.

```cpp
updateGateSystem();
```

Example:

```cpp
void loop() {
    updateGateSystem();
}
```

---

# Shared Variables

## availableSlots

Owned by Parking Module.

Represents physically empty parking spaces.

Example:

```cpp
availableSlots = 2;
```

The Gate Module reads this value before allowing entry.

---

## reservedSlots

Owned by Gate Module.

Represents vehicles that entered the gate but have not yet occupied a parking slot.

Example:

```cpp
reservedSlots = 1;
```

Other modules may read this value.

Other modules must not modify this value directly.

---

# Reservation Logic

## Creating a Reservation

When:

```text
ENTRY detected
```

and parking is available:

```cpp
reserveSlot();
```

is called automatically.

---

## Releasing a Reservation

When the Parking Module detects:

```text
Empty → Occupied
```

it must call:

```cpp
releaseReservation();
```

Example:

```cpp
if(slotBecameOccupied){
    releaseReservation();
}
```

This indicates that the vehicle successfully parked.

---

# Available Space Formula

The number shown to the user should be:

```cpp
availableSlots - reservedSlots
```

Example:

```text
availableSlots = 3
reservedSlots = 1

Free Spaces = 2
```

LCD and LED logic should use this value.

---

# Sensor Filtering

The module implements:

- Distance validation
- Hysteresis
- Detection confirmation

to improve reliability.

---

## Invalid Readings

Ignored when:

```text
distance < 2 cm
distance > 400 cm
pulseIn timeout
```

These readings are treated as:

```cpp
999.0
```

---

## Hysteresis

Detection threshold:

```cpp
DETECTION_DISTANCE
```

Clear threshold:

```cpp
CLEAR_DISTANCE
```

This prevents sensor flickering near the threshold.

---

## Confirmation Delay

A vehicle must remain detected for approximately:

```text
1000 ms
```

before being considered present.

This reduces false triggers caused by noise.

---

# Parking Full Behavior

If:

```cpp
availableSlots - reservedSlots <= 0
```

then:

```text
Gate remains closed
Buzzer sounds
No reservation created
```

---

# Timeout Handling

If a gate operation is not completed within:

```cpp
ENTRY_TIMEOUT
```

the gate closes automatically.

---

## Entry Timeout

Sequence:

```text
ENTRY detected
        ↓
Reservation created
        ↓
Vehicle never crosses
        ↓
Timeout
        ↓
Reservation released
        ↓
Gate closes
```

---

## Exit Timeout

Sequence:

```text
EXIT detected
        ↓
Vehicle never crosses
        ↓
Timeout
        ↓
Gate closes
```

No reservation changes occur.

---

# Integration Requirements

The Parking Module must:

- Maintain `availableSlots`
- Call `releaseReservation()` when a slot changes from Empty → Occupied
- Use `availableSlots - reservedSlots` when displaying free spaces

The Gate Module handles everything else.