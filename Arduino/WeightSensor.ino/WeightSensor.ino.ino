#include <HX711.h>

#define LOADCELL_DOUT_PIN 5
#define LOADCELL_SCK_PIN 6

HX711 loadCell;

void setupWeightSensor() {
  // Initialize load cell
  loadCell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadCell.set_scale(2280.f); // Calibrate this value based on your load cell
  loadCell.tare(); // Reset the scale to 0
}

long readWeight() {
  return loadCell.get_units(10); // Average over 10 readings
}
