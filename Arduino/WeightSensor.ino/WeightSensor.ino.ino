#include "HX711.h"

#define DOUT 4  // DT pin (Change if needed)
#define CLK 15   // SCK pin (Change if needed)

HX711 scale;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing HX711...");

  scale.begin(DOUT, CLK);

  if (scale.is_ready()) {
    Serial.println("HX711 is ready!");

    scale.set_scale(2280.0);  // Set scale factor (adjust this)
    scale.tare();             // Reset to zero
    Serial.println("Scale is ready for weighing.");
  } else {
    Serial.println("ERROR: HX711 not detected. Check wiring!");
  }
}

void loop() {
  if (scale.is_ready()) {
    delay(500); // Stabilization delay
    float weight = scale.get_units(10);  // Average of 10 readings

    if (weight >= 0 && weight <= 10000) {  // Check range
      float weight_kg = weight / 1000.0;
      Serial.print("Weight: ");
      Serial.print(weight_kg, 2);
      Serial.println(" kg");
    } else {
      Serial.println("Warning: Weight out of range. Recalibrate.");
    }
  } else {
    Serial.println("ERROR: HX711 not responding.");
  }

  delay(1000);
}
