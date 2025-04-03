#include "HX711.h"

const int DT_PIN = 19;
const int SCK_PIN = 4;

HX711 scale;
float calibration_factor = -40000;  // Start with larger value

void setup() {
  Serial.begin(115200);
  scale.begin(DT_PIN, SCK_PIN);
  
  // Debug: Print raw values first
  Serial.println("Raw readings (no calibration):");
  for(int i=0; i<10; i++) {
    Serial.println(scale.read());
    delay(500);
  }
  
  scale.tare();
  scale.set_scale(calibration_factor);
  Serial.println("Tared. Now add known weight and calibrate:");
  Serial.println("'+' = increase factor, '-' = decrease, 't' = tare");
}

void loop() {
  Serial.print("Raw: ");
  Serial.print(scale.read());  // Show raw reading
  Serial.print(" | Weight: ");
  Serial.print(scale.get_units(5), 2);  // Average 5 readings
  Serial.println(" kg");

  if(Serial.available()) {
    char c = Serial.read();
    if(c == '+') calibration_factor *= 1.1;  // Increase by 10%
    if(c == '-') calibration_factor *= 0.9; // Decrease by 10%
    if(c == 't') scale.tare();
    scale.set_scale(calibration_factor);
    Serial.print("New factor: ");
    Serial.println(calibration_factor);
  }
  
  delay(500);
}