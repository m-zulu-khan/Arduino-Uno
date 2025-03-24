#include <DHT.h>

// Define the DHT sensor type and the pin it's connected to
#define DHTPIN 2
#define DHTTYPE DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Read temperature and humidity values
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print the values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}
