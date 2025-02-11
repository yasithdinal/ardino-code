#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3); // GPS RX → Arduino D4, GPS TX → Arduino D3

void setup() {
  Serial.begin(9600);   // Serial monitor for debugging
  gpsSerial.begin(9600); // GPS module communication
  Serial.println("GPS Initialized");
}

void loop() {
  while (gpsSerial.available() > 0) { // Read from GPS module
    char c = gpsSerial.read();
    gps.encode(c); // Feed the byte to TinyGPS++

    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude: ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}
