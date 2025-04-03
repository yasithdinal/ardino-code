#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4       // Define the GPIO pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // Define the sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature(); // Read temperature in Celsius
    float humidity = dht.readHumidity();       // Read humidity percentage

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    delay(2000); // Wait for 2 seconds before the next reading
}
