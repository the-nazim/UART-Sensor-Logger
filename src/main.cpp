#include "main.h"

QueueHandle_t sensorQueue;
SemaphoreHandle_t configMutex;
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    dht.begin(); 
    
    sensorQueue = xQueueCreate(QUEUE_SIZE, sizeof(SensorReading)); // Create the sensor data queue
    configMutex = xSemaphoreCreateMutex(); // Create the configuration mutex

    xTaskCreate(sensorTask, "Sensor Task", 4096, NULL, 2, NULL); // Create the sensor task
    xTaskCreate(loggerTask, "Logger Task", 4096, NULL, 1, NULL); // Create the logger task
    xTaskCreate(cliTask, "CLI Task", 4096, NULL, 1, NULL); // Create the CLI task
}

void loop() {

}
