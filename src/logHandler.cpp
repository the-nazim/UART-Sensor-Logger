#include "main.h"

void loggerTask(void *pvParameters) {

    SensorReading sr;
    
    while(true)
    {
        logconfig.logCount++; // Increment log count for status reporting
        if(xQueueReceive(sensorQueue, &sr, portMAX_DELAY)) { // Wait for a sensor reading from the queue
            if(sr.valid) {
                Serial.printf("Temperature: %.2f C, Humidity: %.2f %% ,Time: %lu ms\r\n", sr.temprature, sr.humidity, sr.timestamp);
            } else {
                Serial.printf("Time: %lu ms, Invalid sensor reading\r\n", sr.timestamp);
            }
        }
    }
}