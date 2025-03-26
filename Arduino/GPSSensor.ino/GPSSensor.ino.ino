#include <HardwareSerial.h>
#include <TinyGPS++.h>

HardwareSerial gpsSerial(2);  // Using UART2
TinyGPSPlus gps;

float latitude, longitude;

void setup() {
    Serial.begin(115200);   // Serial Monitor
   gpsSerial.begin(9600, SERIAL_8N1, 18, 19); // RX=18, TX=19
// GPS Serial (Baud rate, config, RX=D2(GPIO4), TX=D4(GPIO2))
    Serial.println("GPS Test Started...");
}

void loop() {
    while (gpsSerial.available()) {
        char c = gpsSerial.read();
        Serial.print(c);  // Print the raw GPS data received
        if (gps.encode(c)) {
            if (gps.location.isUpdated()) {
                latitude = gps.location.lat();
                longitude = gps.location.lng();

                Serial.print("Latitude: ");
                Serial.println(latitude, 6);
                Serial.print("Longitude: ");
                Serial.println(longitude, 6);
            }
        }
    }

    // Every second print if the GPS is still waiting for a signal
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 1000) {
        lastPrint = millis();
        if (!gps.location.isValid()) {
            Serial.println("Waiting for GPS signal...");
        }
    }
}
