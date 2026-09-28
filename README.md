# Arduino Vehicle Speed Detection

An Arduino UNO-based vehicle speed detection system that uses two IR sensors to measure the time taken by a moving object to travel a known distance and displays the calculated speed on a 16×2 I2C LCD.

## 📌 Project Overview

This project detects a moving vehicle using two IR sensors placed at a fixed distance of 0.10 metres.

When the vehicle passes the first IR sensor, the Arduino records the start time. When it passes the second sensor, the Arduino records the end time.

The Arduino UNO calculates the vehicle speed from the measured time interval and the known distance between the sensors.

## 🎯 Objectives

- Detect the passage of a moving vehicle using IR sensors.
- Measure the time interval between two sensor detections.
- Calculate vehicle speed using distance and time.
- Display the calculated speed on an I2C LCD.

## 🧰 Components Used

- Arduino UNO R3
- 2 × IR sensor modules
- 16×2 I2C LCD
- Breadboard
- Jumper wires
- USB cable / power supply

## 💻 Software Used

- Arduino IDE
- Embedded C/C++
- Proteus (if applicable)

## ⚙️ Working Principle

Two IR sensors are positioned at a known distance from each other.

```text
          Vehicle Movement
                 ↓
        ┌────────────────┐
        │  IR Sensor 1   │
        └───────┬────────┘
                │
             0.10 m
                │
        ┌───────▼────────┐
        │  IR Sensor 2   │
        └───────┬────────┘
                │
                ▼
           Arduino UNO
                │
                ▼
        Speed Calculation
                │
                ▼
             I2C LCD
                │
                ▼
          Speed Display
