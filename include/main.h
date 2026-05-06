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

void sensorTask(void *pvParameters);
void loggerTask(void *pvParameters);
void cliTask(void *pvParameters);
void commandHandler(const char* command);
void printHelp();

extern QueueHandle_t sensorQueue;
extern SemaphoreHandle_t configMutex;
extern DHT dht;

typedef struct {
    float temprature;
    float humidity;
    uint32_t timestamp;
    bool valid;
} SensorReading;

typedef struct {
    bool loggingEnabled;
    uint32_t readInterval; // in milliseconds
} LoggerConfig;

extern LoggerConfig logconfig;
extern uint32_t logCount;

#endif
