#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("Ultrasonic Sensor Ready.");
}

void loop() {
  long distance = readUltrasonic();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000); // Delay for 1 second before repeating
}

// Function to read ultrasonic sensor
long readUltrasonic() {
  long duration, distance;
  // Send pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Distance in cm
  return distance;
}
