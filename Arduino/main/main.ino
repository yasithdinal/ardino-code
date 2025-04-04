#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include "HX711.h"

// Ultrasonic Sensor Pins
#define TRIG_PIN 23
#define ECHO_PIN 22

// DHT11 Sensor Pins
#define DHTPIN 4
#define DHTTYPE DHT11

// GPS Configuration
HardwareSerial gpsSerial(2);  // Using UART2
TinyGPSPlus gps;
float latitude, longitude;

// Weight Sensor Pins
const int DT_PIN = 19;
const int SCK_PIN = 4;
HX711 scale;
float calibration_factor = -40000;  // Start with larger value

// Sensor objects
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  // Initialize Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize DHT11
  dht.begin();
  
  // Initialize GPS
  gpsSerial.begin(9600, SERIAL_8N1, 18, 19); // RX=18, TX=19
  
  // Initialize Weight Sensor
  scale.begin(DT_PIN, SCK_PIN);
  scale.tare();
  scale.set_scale(calibration_factor);
  
  Serial.println("All sensors initialized!");
}

void loop() {
  // Read and display all sensors with appropriate delays
  
  // 1. Read and display Ultrasonic sensor
  long distance = getStableDistance();
  if (distance >= 0 && distance <= 400) { 
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Ultrasonic: Out of range");
  }
  
  // 2. Read and display DHT11 sensor (FIXED SYNTAX ERROR HERE)
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature)) {  // <-- FIXED: Added missing ')'
    Serial.println("DHT11: Failed to read temperature!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }
  
  if (isnan(humidity)) {  // <-- FIXED: Removed extra ')'
    Serial.println("DHT11: Failed to read humidity!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  // 3. Read and display GPS data
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
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
  if (!gps.location.isValid()) {
    Serial.println("GPS: Waiting for signal...");
  }
  
  // 4. Read and display Weight sensor
  float raw = scale.read();
  float weight = scale.get_units(5);  // Average 5 readings
  if (weight >= 0 && weight <= 10) {
    Serial.print("Weight: ");
    Serial.print(weight, 2);
    Serial.println(" kg");
  } else {
    Serial.println("Weight: Out of range (0-10kg)");
  }
  
  // Calibration adjustments for weight sensor
  if(Serial.available()) {
    char c = Serial.read();
    if(c == '+') {
      calibration_factor *= 1.1;
      scale.set_scale(calibration_factor);
      Serial.print("New factor: ");
      Serial.println(calibration_factor);
    }
    if(c == '-') {
      calibration_factor *= 0.9;
      scale.set_scale(calibration_factor);
      Serial.print("New factor: ");
      Serial.println(calibration_factor);
    }
    if(c == 't') {
      scale.tare();
      Serial.println("Tared (zeroed)");
    }
  }
  
  Serial.println("----------------------");
  delay(2000); // Wait 2 seconds between readings
}

// Ultrasonic helper functions
long getStableDistance() {
  int numReadings = 5;
  long totalDistance = 0;
  int validReadings = 0;

  for (int i = 0; i < numReadings; i++) {
    long dist = readUltrasonic();
    if (dist >= 0) {
      totalDistance += dist;
      validReadings++;
    }
    delay(50);
  }

  if (validReadings == 0) return -1;
  return totalDistance / validReadings;
}

long readUltrasonic() {
  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  
  duration = pulseInLong(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) return -1;
  
  distance = (duration / 2) / 29.1;
  
  return distance;
}