#ifndef MAIN_H
#define MAIN_H

#define DHT_PIN 4
#define DHT_TYPE DHT22
#define QUEUE_SIZE 10
#define CLI_BUF_SIZE 64

#include <Arduino.h>
#include <DHT.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

typedef struct {
    float temprature;
    float humidity;
    uint32_t timestamp;
    bool valid;
} SensorReading;

DHT dht(DHT_PIN, DHT_TYPE);

#endif