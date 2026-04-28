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