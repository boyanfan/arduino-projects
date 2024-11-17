/*
 * TMP36_TEST.ino
 *
 * TMP36 Temperature Sensor Test
 *
 * This program demonstrates how to read temperature data from a TMP36 sensor
 * using an Arduino. The sensor provides an analog output that corresponds 
 * to the ambient temperature. The code reads the analog value, converts it 
 * to a voltage, and then calculates the temperature in Celsius and Fahrenheit.
 *
 * Connections:
 * - VCC pin of TMP36 to 5V (could be 3.3V) on Arduino
 * - GND pin of TMP36 to GND on Arduino
 * - OUT pin of TMP36 to A0 (example analog pin) on Arduino
 *
 * Author: Boyan Fan
 * Date: Nov 14, 2024
 *
 */

// Make sure the environment has installed the libaray 'TMP36'
// Example used library version: 1.3.1 or later
#include <TMP36.h>

// Define the analog pin connected to the TMP36 here
#define TMP36_PIN A0

// Define the VCC pin connected to the TMP36 here
#define TMP36_VOLTAGE 5.0

// Create an instance of the TMP36 class named 'temperarureSensor' and define the pin the sensor is connected to
TMP36 temperarureSensor(TMP36_PIN, TMP36_VOLTAGE);

void setup() {
  // Start the serial connection with the computer to view the result open the serial monitor 
  Serial.begin(9600);
}

void loop() {
  // Get the current temperature in the unit of celsius and in fahrenheit
  float celsius = temperarureSensor.getTempC();
  float fahrenheit = temperarureSensor.getTempF();

  // Uncomment the following code to display the readings to the Serial monitor
  // Serial.print("Temperature: ");
  // Serial.print(celsius);
  // Serial.print(" °C / ");
  // Serial.print(fahrenheit);
  // Serial.println(" °F");

  // Wait for 1 second to get next temperature data
  delay(1000);
}
