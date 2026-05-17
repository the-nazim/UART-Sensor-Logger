# UART Sensor Logger

UART Sensor Logger is an ESP32 project that reads temperature and humidity from a DHT22 sensor and streams the readings over the serial UART. It uses FreeRTOS tasks to separate sensor sampling, logging, and command-line control.

## Features

- Reads temperature and humidity from a DHT22 sensor
- Prints readings to the serial monitor at 115200 baud
- Uses a FreeRTOS queue to pass sensor data between tasks
- Uses a mutex to protect runtime logger configuration
- Provides a simple UART CLI to start, stop, and configure logging
- Includes Wokwi simulation files

## Hardware

- ESP32 development board
- DHT22 temperature and humidity sensor
- USB cable for power, flashing, and serial monitor

## Wiring

| DHT22 Pin | ESP32 Pin |
| --- | --- |
| VCC | 3V3 |
| SDA/Data | GPIO 4 |
| GND | GND |

The sensor data pin is configured in [include/main.h](include/main.h) as `DHT_PIN 4`.

## Project Structure

```text
.
├── include/main.h          # Shared definitions, structs, globals, and task declarations
├── src/main.cpp            # Setup and FreeRTOS task creation
├── src/sensorHandler.cpp   # DHT22 reading task
├── src/logHandler.cpp      # Serial logging task
├── src/cliHandler.cpp      # UART command-line interface
├── platformio.ini          # PlatformIO configuration
├── diagram.json            # Wokwi circuit diagram
└── wokwi.toml              # Wokwi firmware configuration
```

## Requirements

- Visual Studio Code with the PlatformIO extension, or PlatformIO Core
- ESP32 board support through PlatformIO
- Adafruit DHT sensor library, installed automatically by PlatformIO from `platformio.ini`

## Build and Upload

Build the firmware:

```bash
pio run
```

Upload to the ESP32:

```bash
pio run --target upload
```

Open the serial monitor:

```bash
pio device monitor --baud 115200
```

## Wokwi Simulation

This project includes `diagram.json` and `wokwi.toml` for simulation.

Build the PlatformIO firmware first:

```bash
pio run
```

Then open the project in Wokwi. The simulator uses:

```text
.pio/build/esp32doit-devkit-v1/firmware.bin
.pio/build/esp32doit-devkit-v1/firmware.elf
```

## UART CLI

Send commands through the serial monitor. Use newline or carriage return to submit a command.

| Command | Description |
| --- | --- |
| `help` | Show available commands |
| `status` | Show logging state, interval, and log count |
| `start` | Resume sensor logging |
| `stop` | Pause sensor logging |
| `interval <sec>` | Set read interval from 1 to 60 seconds |

Example:

```text
interval 5
status
stop
start
```

## Example Output

```text
Temperature: 24.00 C, Humidity: 40.00 % ,Time: 2005 ms
Temperature: 24.00 C, Humidity: 40.00 % ,Time: 4008 ms
[STATUS] logging=ON  interval=2s  total_logs=2
```

## Runtime Design

The firmware creates three FreeRTOS tasks in `setup()`:

- `sensorTask` reads the DHT22 at the configured interval and sends readings to `sensorQueue`.
- `loggerTask` receives readings from the queue and prints them over UART.
- `cliTask` reads serial input and updates logger configuration.

The default logger configuration is:

| Setting | Default |
| --- | --- |
| Logging enabled | Yes |
| Read interval | 2000 ms |
| Queue size | 10 readings |
| Serial baud rate | 115200 |

## License

No license file is currently included.
