#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const int ledPin = 3;

void setup() {
  Serial.begin(9600);
  if (!accel.begin()) {
    Serial.println("ADXL345 не найден!(Либо он сгорел)");
    while (1); 
  }

  Serial.println("ADXL345 подключен.");
  
  accel.setRange(ADXL345_RANGE_2_G);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event); 

  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" m/s², Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" m/s², Z: ");
  Serial.print(event.acceleration.z);
  Serial.println(" m/s²");

  if (abs(event.acceleration.z) < 0.2) {
    digitalWrite(ledPin, HIGH); 
    Serial.println("Невесомость обнаружена!");
  } else {
    digitalWrite(ledPin, LOW); 
  }

  delay(100); 
}
