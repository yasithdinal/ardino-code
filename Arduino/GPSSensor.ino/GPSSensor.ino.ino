#include <TinyGPS++.h>  // GPS functionality using TinyGPS++ library

TinyGPSPlus gps;  // Create an instance of the TinyGPSPlus class

void setup() {
  // Start serial communication with the computer (for debugging and displaying GPS data)
  Serial.begin(9600);  // Default serial communication for both uploading and monitoring
  
  // Print initialization message to Serial Monitor
  Serial.println("GPS Initialized");
}

void loop() {
  // Continuously check if data is available from the GPS module (via pins 0 and 1)
  while (Serial.available() > 0) {  // Read from Serial (GPS module connected to RX/TX)
    char c = Serial.read();  // Read the incoming byte from the GPS module
    gps.encode(c);  // Feed the byte to the TinyGPSPlus library

    // Check if new GPS location data is available
    if (gps.location.isUpdated()) {
      // Print the current latitude and longitude to the Serial Monitor
      Serial.print("Latitude: ");
      Serial.print(gps.location.lat(), 6);  // Print latitude with 6 decimal places
      Serial.print(" Longitude: ");
      Serial.println(gps.location.lng(), 6);  // Print longitude with 6 decimal places
    }
  }
}
