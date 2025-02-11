#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Function declarations for temperature sensor, ultrasonic, and weight sensor
// long readUltrasonic();  // Commented out
// void setupWeightSensor();  // Commented out
// long readWeight();  // Commented out

// GPS Setup
TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3); // GPS RX → Arduino D4, GPS TX → Arduino D3

void setupGPS();
String readGPS();

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  
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

// Setup function for GPS
void setupGPS() {
  Serial.println("GPS initialized.");
}

// Function to read GPS data using SoftwareSerial
String readGPS() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    gps.encode(c);

    // If new GPS location data is available
    if (gps.location.isUpdated()) {
      return "Latitude: " + String(gps.location.lat(), 6) + ", Longitude: " + String(gps.location.lng(), 6);
    }
  }
  return "";  // Return empty string if no new data is available
}
