#include "main.h"

void sensorTask(void *pvParameters) {
    while (true)
    {
        SensorReading sr;
    
        sr.temprature = dht.readTemperature();
        sr.humidity = dht.readHumidity();
        sr.timestamp = millis();
        sr.valid = !isnan(sr.temprature) && !isnan(sr.humidity);

        xQueueSend(sensorQueue, &sr, portMAX_DELAY); // Send the sensor reading to the queue

        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
    }
}

void loggerTask(void *pvParameters) {

    SensorReading sr;
    while(true)
    {
        if(xQueueReceive(sensorQueue, &sr, portMAX_DELAY)) { // Wait for a sensor reading from the queue
            if(sr.valid) {
                Serial.printf("\rTemperature: %.2f C, Humidity: %.2f %% ,Time: %lu ms\n", sr.temprature, sr.humidity, sr.timestamp);
            } else {
                Serial.printf("Time: %lu ms, Invalid sensor reading\n", sr.timestamp);
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    dht.begin();

    sensorQueue = xQueueCreate(QUEUE_SIZE, sizeof(SensorReading)); // Create the sensor data queue

    xTaskCreate(sensorTask, "Sensor Task", 4096, NULL, 2, NULL); // Create the sensor task
    xTaskCreate(loggerTask, "Logger Task", 4096, NULL, 1, NULL); // Create the logger task
}

void loop() {

}