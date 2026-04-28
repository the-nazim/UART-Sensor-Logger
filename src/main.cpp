#include "main.h"

void setup() {
    Serial.begin(115200);
    dht.begin();

    sensorQueue = xQueueCreate(QUEUE_SIZE, sizeof(SensorReading)); // Create the sensor data queue

    xTaskCreate(sensorTask, "Sensor Task", 4096, NULL, 2, NULL); // Create the sensor task
    xTaskCreate(loggerTask, "Logger Task", 4096, NULL, 1, NULL); // Create the logger task
}

void loop() {

}