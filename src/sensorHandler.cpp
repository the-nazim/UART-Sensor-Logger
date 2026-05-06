#include "main.h"

void sensorTask(void *pvParameters) {
    while (true)
    {
        SensorReading sr;
        uint32_t localInterval;
        bool localLogging;

        if(xSemaphoreTake(configMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
            localInterval = logconfig.readInterval;
            localLogging = logconfig.loggingEnabled;
            xSemaphoreGive(configMutex);
        }

        if (localLogging) 
        {    
            sr.temprature = dht.readTemperature();
            sr.humidity = dht.readHumidity();
            sr.timestamp = millis();
            sr.valid = !isnan(sr.temprature) && !isnan(sr.humidity);

            xQueueSend(sensorQueue, &sr, portMAX_DELAY); // Send the sensor reading to the queue
        }    
        vTaskDelay(pdMS_TO_TICKS(localInterval));
    }
}
