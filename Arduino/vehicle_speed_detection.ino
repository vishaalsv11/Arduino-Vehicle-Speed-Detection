#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// IR sensor pins
const int sensor1Pin = 2;
const int sensor2Pin = 3;

// Distance between the two sensors in metres
const float distanceBetweenSensors = 0.10;

volatile unsigned long sensor1Time = 0;
volatile unsigned long sensor2Time = 0;

volatile bool sensor1Triggered = false;
volatile bool sensor2Triggered = false;

void sensor1ISR() {
  if (!sensor1Triggered) {
    sensor1Time = micros();
    sensor1Triggered = true;
  }
}

void sensor2ISR() {
  if (sensor1Triggered && !sensor2Triggered) {
    sensor2Time = micros();
    sensor2Triggered = true;
  }
}

void setup() {

  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Vehicle Speed");
  lcd.setCursor(0, 1);
  lcd.print("Detection");
  delay(2000);

  lcd.clear();

  attachInterrupt(digitalPinToInterrupt(sensor1Pin),
                  sensor1ISR, FALLING);

  attachInterrupt(digitalPinToInterrupt(sensor2Pin),
                  sensor2ISR, FALLING);
}

void loop() {

  if (sensor1Triggered && sensor2Triggered) {

    noInterrupts();
    unsigned long startTime = sensor1Time;
    unsigned long endTime = sensor2Time;
    interrupts();

    unsigned long timeDifference = endTime - startTime;

    if (timeDifference > 0) {

      float timeSeconds = timeDifference / 1000000.0;

      float speedMetersPerSecond =
          distanceBetweenSensors / timeSeconds;

      float speedKmPerHour =
          speedMetersPerSecond * 3.6;

      Serial.print("Time: ");
      Serial.print(timeSeconds, 6);
      Serial.print(" s | Speed: ");
      Serial.print(speedKmPerHour, 2);
      Serial.println(" km/h");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed:");

      lcd.setCursor(0, 1);
      lcd.print(speedKmPerHour, 2);
      lcd.print(" km/h");
    }

    delay(1000);

    sensor1Triggered = false;
    sensor2Triggered = false;

    lcd.clear();
  }
}
