// main.ino
//
// Project: Automatic Cultivation Environment Monitoring and Control System
// Author: Boyan Fan from ELEC 290 Group 14
// Date: Nov 28, 2024
//
// Description:
// This Arduino program integrates sensors and actuators to monitor and control environmental conditions.
// The system includes the following features:
//  - Reading data from temperature, soil moisture, and raindrop sensors.
//  - Sending sensor data wirelessly via Wi-Fi for remote monitoring.
//  - Controlling a motor for mechanical operations, a water pump for irrigation, and an LED for status indication.
//
// Hardware Components:
//  - Arduino Uno WiFi Rev2
//  - Temperature Sensor: TMP36
//  - Soil Moisture Sensor: Capacitive Soil Moisture Sensor v1.2
//  - Raindrop Sensor: Raindrop Sensor
//  - Motor: N/A
//  - Water Pump: N/A
//  - LED: N/A
//  - Wi-Fi Module: N/A
//
// Software Libraries:
//  - <WiFiNINA.h>
//  - <SPI.h>
//  - <TMP36.h>, version: 1.3.1 or later
//
// Usage:
//  - Configure Wi-Fi credentials in the code.
//  - Connect the specified hardware components to the appropriate Arduino pins.
//  - Upload the code to the Arduino board.
//  - Open a web browser and navigate to the Arduino's IP address to view the data.
//
// Functionality:
//  - Sensor data is periodically collected and processed to determine environmental conditions.
//  - Data is transmitted over Wi-Fi to a designated server or application.
//  - Actuators (motor, LED, and water pump) are controlled based on the sensor readings and predefined thresholds.
//
// Usage:
//  - Configure Wi-Fi credentials and server details in the code.
//  - Connect the specified hardware components to the appropriate Arduino pins.
//  - Upload the code to the Arduino board and monitor its operation.
//
// License:
//  This code is primely used for course ELEC 290 project.
//  This code is open-source and can be used or modified for educational and personal projects.

#include <WiFiNINA.h>
#include <TMP36.h>
#include <SPI.h>

// ------------------------------------------------------------------------------------------------------ Function Definitions

// Function: convertToPercentage
//
// Converts a numeric value from a given range to a percentage range [1, 100].
//
// This generic function takes a numeric value within a specified range and scales it
// to a range between 1 and 100. It ensures that the input value lies within the bounds
// and validates that the lower bound is less than the upper bound.
//
// Template Parameters:
//   T - The numeric type of the input parameters (e.g., int, float, double).
//
// Parameters:
//   value - The numeric value to be converted.
//   lowerBound - The lower limit of the input range.
//   upperBound - The upper limit of the input range.
//
// Returns:
//   An integer scaled to the range [1, 100].
//
// Notes:
//   - The function assumes that the range [lowerBound, upperBound] is valid
//     and the value is within this range.
//
template<typename T> int convertToPercentage(T value, T lowerBound, T upperBound);

// Function: test
//
// This function checks if testing mode is enabled and displays a given title and value
// on the serial monitor if the `onTest` flag is true. The function always returns true.
//
// Template Parameters:
//   T - The type of the value to be displayed (e.g., int, float, double, etc.).
//
// Parameters:
//   onTest    - A boolean flag indicating whether testing mode is enabled.
//   testTitle - A string title to be displayed before the value.
//   value     - An integer value to be displayed on the serial monitor if `onTest` is true.
//
// Returns:
//   Always returns true.
//
template<typename T> bool test(bool onTest, String testTitle, T value);

// Function: sendHttpResponse
//
// This function handles sending an HTTP response to a connected Wi-Fi client. It reads sensor data,
// formats the data into a JSON object or HTML content, and sends it back to the client over the Wi-Fi connection.
//
// Functionality:
//   - Reads sensor data from the connected sensors (e.g., temperature, moisture, raindrop sensors).
//   - Converts the sensor readings into human-readable format (e.g., JSON or HTML).
//   - Sends the HTTP response headers and the content back to the client.
//
// Parameters:
//   client - A WiFiClient object representing the connected client to which the response will be sent.
//
// Returns:
//   This function does not return a value.
//
// Notes:
//   - Ensure that all sensors are properly connected and initialized before calling this function.
//   - This function is designed to work as part of a web server implementation.
//
void sendHttpResponse(WiFiClient client);

// ----------------------------------------------------------------------------------------------------------------------- API

// Function: onRaining
//
// Description:
// This function checks if it is currently raining based on the raindrop sensor data.
// It returns `true` if the sensor detects rainfall, otherwise `false`.
//
// Parameters:
//   None
//
// Returns:
//   bool - `true` if it is raining, `false` otherwise.
//
// Notes:
//   - The implementation of this function should rely on the input from a raindrop sensor.
//   - Ensure the sensor is calibrated correctly to avoid false positives or negatives.
//
bool onRaining();

// Function: notify
//
// Description:
// Sends a notification message to a connected client over a Wi-Fi network. 
// This function transmits the specified content string to the client, allowing the system to 
// communicate updates or alerts.
//
//
// Template Parameters:
//   T - The type of the value to be notify (e.g., int, string, etc.).
//
// Parameters:
//   WiFiClient client - The connected Wi-Fi client to which the notification will be sent.
//   String content    - The message or content to be sent to the client.
//
// Returns:
//   void
//
// Notes:
//   - The `WiFiClient` object must be connected before calling this function.
//   - The `content` string should be formatted appropriately for the receiving client (e.g., plain text, JSON, etc.).
//   - Ensure the client connection is checked before invoking this function to avoid errors.
//
template<typename T> void notify(WiFiClient client, T content);

// ----------------------------------------------------------------------------------------------------- Constants Definitions

// Baud rate for the serial connection, used for communication with the serial monitor
#define SERIAL_CONNECTION 9600

// Delay interval (in milliseconds) for the main loop to pause execution for 1 second
#define ITERATION_INTERVAL 1000

// The maximum percentage value (100% out of 100%)
#define MAX_PERCENTAGE 100

// The minimum percentage value (1% out of 100%)
#define MIN_PERCENTAGE 1

// The number of digits for displaying the readings from the sensors
#define DISPLAY_DIGITS 2

// End of a line for a given file
#define END_OF_LINE '\n'

// ---------------------------------------------------------------------------------------------------- Network Configurations

// Service Set Identifier (SSID) and Password for the Wi-Fi network
#define SSID "ELEC290-G14-S03"
#define PASSWORD "P-ELEC290-G14-S03"

// Holds the connection status of the Wi-Fi module
int status;

// Initialize the server on port 80
WiFiServer server(80);

// -------------------------------------------------------------------------------------------- Temperature Sensor Definitions

// TMP36 Connections:
//  - VCC pin of TMP36 to 5V (could be 3.3V) on Arduino
//  - GND pin of TMP36 to GND on Arduino
//  - AOUT pin of TMP36 to A0 on Arduino
#define TMP36_PIN A0
#define TMP36_VCC 5.0

// Create an instance of the TMP36 class named 'temperarureSensor' and define the pin the sensor is connected to
TMP36 temperarureSensor(TMP36_PIN, TMP36_VCC);

// ----------------------------------------------------------------------------------------------- Raindrop Sensor Definitions
#define MAX_RAINDROP_READING 1024
#define MIN_RAINDROP_READING 0

// Raindrop Sensor Connections:
//  - VCC pin of the sensor to 5V on Arduino
//  - GND pin of the sensor to GND on Arduino
//  - AOUT pin of the sensor to A1 on Arduino
#define RS_PIN A5

// ------------------------------------------------------------------------------------------ Soil Moisture Sensor Definitions

// Connections:
//  - VCC pin of the sensor to 3.3V or 5V on Arduino
//  - GND pin of the sensor to GND on Arduino
//  - AOUT pin of the sensor to A2 on Arduino
#define CSMS_PIN A3

// The values of it when the sensor is placed in the air and in the water
#define DRY_MOISTURE 500
#define WET_MOISTURE 200

// -------------------------------------------------------------------------------------------------------------- Main Program

void setup() {
  // Start the serial connection with the computer to view the result open the serial monitor
  Serial.begin(SERIAL_CONNECTION);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) { ; }

  // Attempt to connect to Wi-Fi network
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(SSID);
  status = WiFi.beginAP(SSID, PASSWORD);

  // Check the connection for the Wi-Fi network
  while (status != WL_AP_LISTENING) {
    Serial.println("Still Connecting...");

    // Wait for 1 second for another trail for the connection
    delay(ITERATION_INTERVAL);
    status = WiFi.beginAP(SSID, PASSWORD);
  }

  // Successfully connected
  Serial.println("\nConnected to Wi-Fi network.");

  // Display the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server for the network
  server.begin();
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();

  // Early exit if no client is connected
  if (!client) { return; }

  // When the server is available
  while (client.connected() && client.available()) {
    // Reach the end of the HTTP request
    if (client.read() != END_OF_LINE) { continue; }

    // Send the data from the sensors as the response
    sendHttpResponse(client);
  }

  // Disconnect the server
  client.stop();

  // Demostration for the 'bool onRaining()' and 'void notify(...)' APIs
  if (onRaining()) notify(client, "It is rainning outside!");

  // Wait for 1 second for the next iteration
  delay(ITERATION_INTERVAL);
}

// --------------------------------------------------------------------------------------------------- Function Implementation

void sendHttpResponse(WiFiClient client) {
  // PRIVATE : Read the current analog value from the raindrop sensor
  int __raindropReading__ = analogRead(RS_PIN);

  // PRIVATE : Read the current analog value from the sensor connected to `CSMS_PIN`
  int __moistureReading__ = analogRead(CSMS_PIN);

  // The current temperature in the unit of celsius and in fahrenheit
  float temperatureInCelsius = temperarureSensor.getTempC();
  float temperatureInFahrenheit = temperarureSensor.getTempF();

  // The current raindrop probability percentage
  int raindropReading = convertToPercentage(__raindropReading__, MIN_RAINDROP_READING, MAX_RAINDROP_READING);
  int moistureReading = convertToPercentage(__moistureReading__, WET_MOISTURE, DRY_MOISTURE);

  // Prepare JSON data to send to the server
  String jsonData = "{";
  jsonData += "\"temperatureC\":" + String(temperatureInCelsius, DISPLAY_DIGITS) + ",";
  jsonData += "\"temperatureF\":" + String(temperatureInFahrenheit, DISPLAY_DIGITS) + ",";
  jsonData += "\"moisture\":" + String(moistureReading) + ",";
  jsonData += "\"raindrop\":" + String(raindropReading);
  jsonData += "}";

  // Send HTTP response headers and send the json data
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  client.println(jsonData);
}

template<typename T> int convertToPercentage(T value, T lowerBound, T upperBound) {
  return static_cast<int>((static_cast<double>(value - lowerBound) / (upperBound - lowerBound)) * 99 + 1);
}

template<typename T> bool test(bool onTest, String testTitle, T value) {
  // Display nothing if the test mode is off
  if (!onTest) { return false; }
  
  // Display the given value with its title
  Serial.print(testTitle);
  Serial.print(": ");
  Serial.println(value);
  return true;
}

bool onRaining() { return analogRead(RS_PIN) > 500; }

template<typename T> void notify(WiFiClient client, T content) {
  Serial.println("\n" + String(content));
}
