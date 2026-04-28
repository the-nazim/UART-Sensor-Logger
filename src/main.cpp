#include "main.h"

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    SensorReading sr;
    
    sr.temprature = dht.readTemperature();
    sr.humidity = dht.readHumidity();
    sr.timestamp = millis();
    sr.valid = !isnan(sr.temprature) && !isnan(sr.humidity);

    if (sr.valid) {
        Serial.print("Temperature: ");
        Serial.print(sr.temprature);
        Serial.print(" °C, Humidity: ");
        Serial.print(sr.humidity);
        Serial.print(" %, Timestamp: ");
        Serial.println(sr.timestamp);
    } else {
        Serial.println("Failed to read from DHT sensor!");
    }

    delay(3000);
}