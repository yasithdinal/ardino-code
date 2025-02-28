#include <HX711.h>

#define LOADCELL_DOUT_PIN 5
#define LOADCELL_SCK_PIN 6

HX711 loadCell;

float scale_factor = 2280.0; // Adjust this based on calibration

void setup() {
  Serial.begin(9600);
  setupWeightSensor();
}

void setupWeightSensor() {
  // Initialize load cell
  loadCell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadCell.set_scale(scale_factor); // Calibrate this value
  loadCell.tare(); // Reset the scale to 0
}

float readWeight() {
  if (loadCell.is_ready()) {
    float weight = loadCell.get_units(10); // Average over 10 readings
    if (weight < 0) weight = 0; // Ensure no negative values
    if (weight > 7.0) weight = 7.0; // Cap weight at 7 kg
    return weight;
  } else {
    Serial.println("Error: Load cell not ready");
    return -1;
  }
}

void loop() {
  float weight = readWeight();
  if (weight != -1) {
    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" kg");
  }
  delay(1000); // Read every second
}
