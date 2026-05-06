#include "main.h"

LoggerConfig logconfig = {
    true,
    2000
};

uint32_t logCount = 0;

void printHelp() {
  Serial.println(F("\r\n=== Sensor Logger CLI ==="));
  Serial.println(F("  start           - resume logging"));
  Serial.println(F("  stop            - pause logging"));
  Serial.println(F("  interval <sec>  - set read interval (1-60s)"));
  Serial.println(F("  status          - show current config"));
  Serial.println(F("  help            - this message"));
  Serial.println(F("========================\r\n"));
}

void printStatus() {
  if (xSemaphoreTake(configMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
    Serial.printf("[STATUS] logging=%s  interval=%lus  total_logs=%lu\r\n",
      logconfig.loggingEnabled ? "ON" : "OFF",
      logconfig.readInterval / 1000,
      logCount);
    xSemaphoreGive(configMutex);
  }
}

void cliTask(void *pvParameters) {
    char buf[CLI_BUF_SIZE];
    uint8_t idx = 0;
    char c;
    while(true) {
        if(Serial.available()) {
            c = (char)Serial.read();

            if(c == '\n' || c == '\r') {
                if(idx > 0) {
                    buf[idx] = '\0';
                    commandHandler(buf);
                    idx = 0; // Reset index for next command
                }
            }
            else if(idx < CLI_BUF_SIZE - 1) {
                buf[idx++] = c; // Add character to buffer
            }
            else {
                Serial.println("Error: Command too long");
                idx=0; // Reset index to prevent overflow
            }
        }
        else {
            vTaskDelay(pdMS_TO_TICKS(10)); // Sleep for a short time to yield CPU
        }
    }
}

void commandHandler(const char* command) {
    if (strcmp(command, "help") == 0)
        printHelp();
    else if (strcmp(command, "status") == 0)
        printStatus();
    
}
