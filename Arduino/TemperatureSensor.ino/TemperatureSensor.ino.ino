#define LM35_PIN 35  // Define LM35 VOUT connected to GPIO35
#define ADC_MAX 4095  // ESP32 ADC is 12-bit (0-4095)
#define REF_VOLTAGE 3.3  // ESP32 operates at 3.3V

void setup() {
  Serial.begin(115200); // Start serial communication
  delay(1000); // Allow sensor stabilization
}

void loop() {
  int adcValue = analogRead(LM35_PIN);  // Read raw ADC value
  float voltage = adcValue * (REF_VOLTAGE / ADC_MAX); // Convert ADC value to voltage
  float temperature = voltage * 100.0;  // LM35 outputs 10mV per °C

  // **Fix for incorrect high readings**
  if (temperature > 100 || temperature < 0) { 
    Serial.println("Sensor Error! Check wiring.");
  } else {
    Serial.print(temperature, 2);  // Print accurate temperature
    Serial.println(" °C");
  }

  delay(1000);  
}
