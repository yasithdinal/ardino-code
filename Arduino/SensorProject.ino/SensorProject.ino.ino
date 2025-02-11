#include <TinyGPS++.h>  // GPS functionality using TinyGPS++ library

// Function declarations for temperature sensor, ultrasonic, and weight sensor (commented out)
// long readUltrasonic();  // Commented out
// void setupWeightSensor();  // Commented out
// long readWeight();  // Commented out

void setupGPS();  // GPS setup function declaration
String readGPS();  // GPS reading function declaration

void setup() {
  // Start serial communication for debugging and GPS data display
  Serial.begin(9600);
  
  // setupWeightSensor();  // Commented out for now
  setupGPS();  // Initialize GPS
  
  Serial.println("Setup complete.");
}

void loop() {
  // The following sensors are disabled for now:
  // Read data from Ultrasonic Sensor
  // long distance = readUltrasonic();
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  // Read data from Weight Sensor
  // long weight = readWeight();
  // Serial.print("Weight: ");
  // Serial.print(weight);
  // Serial.println(" g");

  // Read data from GPS
  String location = readGPS();
  if (location != "") {
    Serial.println(location);  // Print the GPS coordinates if updated
  }

  delay(1000); // Delay for 1 second before repeating the loop
}

// Setup function for GPS using default Serial (pins 0 and 1)
void setupGPS() {
  // Print initialization message to Serial Monitor
  Serial.println("GPS initialized.");
}

// Function to read GPS data using Serial communication
String readGPS() {
  TinyGPSPlus gps;

  while (Serial.available() > 0) {  // Read data from the GPS module connected to pins 0 and 1
    char c = Serial.read();  // Read the incoming byte from the GPS module
    gps.encode(c);  // Feed the byte to the TinyGPSPlus library

    // If a new GPS sentence is available
    if (gps.location.isUpdated()) {
      String location = "Latitude: " + String(gps.location.lat(), 6) + ", Longitude: " + String(gps.location.lng(), 6);
      return location;  // Return the formatted GPS location
    }
  }
  return "";  // Return empty string if no new data is available
}
