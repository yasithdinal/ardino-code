#include "HX711.h"

const int DT_PIN = 19;
const int SCK_PIN = 4;

HX711 scale;
float calibration_factor = -40000;  // Start with larger value
unsigned long previousMillis = 0;
const long interval = 10000;  // 10 second interval

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
  unsigned long currentMillis = millis();
  
  // Only take readings every 10 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    float raw = scale.read();
    float weight = scale.get_units(5);  // Average 5 readings
    
    // Only display weights between 0-10 kg
    if (weight >= 0 && weight <= 10) {
      Serial.print("Raw: ");
      Serial.print(raw);
      Serial.print(" | Weight: ");
      Serial.print(weight, 2);
      Serial.println(" kg");
    }
  }

  // Calibration adjustments (works anytime)
  if(Serial.available()) {
    char c = Serial.read();
    if(c == '+') {
      calibration_factor *= 1.1;  // Increase by 10%
      scale.set_scale(calibration_factor);
      Serial.print("New factor: ");
      Serial.println(calibration_factor);
    }
    if(c == '-') {
      calibration_factor *= 0.9; // Decrease by 10%
      scale.set_scale(calibration_factor);
      Serial.print("New factor: ");
      Serial.println(calibration_factor);
    }
    if(c == 't') {
      scale.tare();
      Serial.println("Tared (zeroed)");
    }
  }
}