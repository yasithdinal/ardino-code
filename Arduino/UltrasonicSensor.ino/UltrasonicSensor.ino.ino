#define TRIG_PIN 23  // Trigger pin on ESP32
#define ECHO_PIN 22  // Echo pin on ESP32

void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("Ultrasonic Sensor Ready on ESP32.");
}

void loop() {
  long distance = getStableDistance();
  
  if (distance >= 0 && distance <= 400) { 
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range");
  }

  delay(1000); // 1-second delay before next reading
}

// Function to read multiple ultrasonic readings and get a stable value
long getStableDistance() {
  int numReadings = 5; // Take 5 readings and average them
  long totalDistance = 0;
  int validReadings = 0;

  for (int i = 0; i < numReadings; i++) {
    long dist = readUltrasonic();
    if (dist >= 0) { // Only count valid readings
      totalDistance += dist;
      validReadings++;
    }
    delay(50); // Small delay to stabilize sensor
  }

  if (validReadings == 0) return -1; // No valid readings
  
  return totalDistance / validReadings; // Return average distance
}

// Function to read the ultrasonic sensor
long readUltrasonic() {
  long duration, distance;
  
  // Ensure the trigger pin is LOW before sending a pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  
  // Use pulseInLong for ESP32 (better stability)
  duration = pulseInLong(ECHO_PIN, HIGH, 30000); // Timeout after 30ms (~400cm max range)
  
  if (duration == 0) return -1; // No valid echo detected
  
  distance = (duration / 2) / 29.1; // Convert duration to cm
  
  return distance;
}
