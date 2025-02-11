#define TEMPERATURE_PIN A0  // Analog pin to read LM35 sensor

void setup() {
  // Start serial communication
  Serial.begin(9600);  
}

void loop() {
  float temperature = readTemperature();  // Call the function to read temperature

  // Display the temperature on the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  // Check if the temperature is above 50°C and show a warning
  if (temperature > 50.0) {
    Serial.println("Warning: High temperature detected!");
  }

  delay(1000);  // Delay for 1 second before the next reading
}

// Function to read temperature from LM35 sensor
float readTemperature() {
  int sensorValue = analogRead(TEMPERATURE_PIN);  // Read the analog value from LM35
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert the analog value to voltage (0-5V)
  float temperature = voltage * 100.0;  // LM35 outputs 10mV per degree Celsius (so multiply by 100)
  return temperature;  // Return the temperature in Celsius
}
