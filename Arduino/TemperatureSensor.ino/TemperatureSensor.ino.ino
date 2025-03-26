#define LM35_PIN 34  // LM35 connected to GPIO34 (Analog pin)

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(LM35_PIN); // Read raw ADC value (0-4095)
  
  // Convert ADC value to voltage
  float voltage = sensorValue * (3.3 / 4095.0); 
  
  // Convert voltage to temperature (10mV per °C)
  float temperatureC = voltage * 100.0;  

  // Print Temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(2000);  // Wait 2 seconds before next reading
}
