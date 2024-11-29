# Automatic Cultivation Environment Monitoring and Control System

This project is an **Arduino-based system** that monitors and controls environmental conditions for an automatic cultivation environment. It integrates sensors and actuators to collect data, process it, and perform actions like irrigation and mechanical operations while allowing remote monitoring via Wi-Fi.

---

## Features

- **Environmental Monitoring**
  - Reads data from:
    - Temperature Sensor (TMP36)
    - Soil Moisture Sensor
    - Raindrop Sensor
- **Remote Data Transmission**
  - Sends sensor readings over Wi-Fi to a connected client.
  - Formats data as JSON for easy integration with external systems.
- **Actuator Control**
  - Controls a motor, water pump, and LED based on sensor thresholds.
- **Web Server**
  - Hosts a local web server to display real-time environmental data.

---

## Hardware Components

| Component                  | Description                                        |
|----------------------------|----------------------------------------------------|
| **Microcontroller**        | Arduino Uno WiFi Rev2                              |
| **Temperature Sensor**     | TMP36                                              |
| **Soil Moisture Sensor**   | Capacitive Soil Moisture Sensor v1.2               |
| **Raindrop Sensor**        | Raindrop Sensor                                    |
| **Actuators**              | Motor (for mechanical tasks), Water Pump, LED      |
| **Wi-Fi Module**           | Built into Arduino Uno WiFi Rev2                   |

---

## Software Dependencies

This project uses the following Arduino libraries:

- **[WiFiNINA](https://www.arduino.cc/en/Reference/WiFiNINA)**
- **[SPI](https://www.arduino.cc/en/Reference/SPI)**
- **[TMP36](https://github.com/arduino-libraries/TMP36)** (version 1.3.1 or later)

Ensure these libraries are installed before uploading the code.

---

## How It Works

### Sensors

1. **Temperature Sensor (TMP36)**
   - Reads ambient temperature.
   - Data is processed in Celsius and Fahrenheit.

2. **Soil Moisture Sensor**
   - Measures soil moisture levels.
   - Outputs a percentage indicating wetness.

3. **Raindrop Sensor**
   - Detects the presence of rain.
   - Outputs a percentage probability of rainfall.

### Data Transmission

- The system acts as a web server.
- Clients can connect to the Arduino's Wi-Fi network to access real-time data.
- Data is served in JSON format for compatibility with web and mobile applications.

### Actuators

- **Motor**: Performs mechanical tasks based on conditions.
- **Water Pump**: Activates for irrigation when soil moisture is low.
- **LED**: Provides status indication.

---

## Configuration

### Wi-Fi Credentials

Update the `SSID` and `PASSWORD` in the code to match your Wi-Fi network:

```cpp
#define SSID "Your_SSID"
#define PASSWORD "Your_PASSWORD"
```

## Hardware Setup
Sensor/Actuator	Arduino Pin
TMP36 Sensor : A0
Soil Moisture Sensor: A3
Raindrop Sensor :	A5

## Setup and Usage
- Install the required libraries in the Arduino IDE.
- Connect all hardware components to the Arduino board.
- Configure the Wi-Fi credentials in the code.
- Upload the code to the Arduino board.
- Open the serial monitor to view connection status and IP address.
- Navigate to the IP address in a web browser to view real-time sensor data.

---

## APIs
### Key Functions

```cpp
onRaining()
```

Checks if it is currently raining.
Returns true if rainfall is detected, false otherwise.

```cpp
notify(WiFiClient client, String content)
```

Sends a custom notification to the client.

```cpp
sendHttpResponse(WiFiClient client)
```

Sends the latest sensor data to the connected client in JSON format.

```cpp
convertToPercentage(value, lowerBound, upperBound)
```

Converts a sensor reading into a percentage between 1% and 100%.

## License
This code is developed for ELEC 290 Group 14 and is open-source. It can be used or modified for educational and personal projects.

---

Author: Boyan Fan
Queen's University, ELEC 290 Group 14
Date: November 28, 2024
