/*
 * CSMS_TEST.ino
 * 
 * Capacitive Soil Moisture Sensor v1.2 Test
 *
 * This program demonstrates how to interface the Capacitive Soil Moisture Sensor v1.2 with an Arduino.
 * It reads the analog output from the sensor, converts it to a moisture percentage, and displays the
 * value on the Serial Monitor.
 *
 * Connections:
 * - VCC pin of the sensor to 3.3V or 5V on Arduino
 * - GND pin of the sensor to GND on Arduino
 * - AOUT pin of the sensor to A0 (example analog pin) on Arduino
 *
 * Author: Boyan Fan
 * Date: Nov 14, 2024
 *
 */

// Define the analog pin connected to the CSMS here
#define CSMS_PIN A0

// For the following value 'DRY_MOISTURE', connect the board and call the function 'getBoundMoisture()' 
// to get the value of it when the sensor is placed in the air
#define DRY_MOISTURE 100

// For the following value 'WET_MOISTURE', connect the board and call the function 'getBoundMoisture()' 
// to get the value of it when the sensor is placed in the water
#define WET_MOISTURE 1

// The maximum percentage value for soil moisture, representing the driest condition of the soil
#define MAX_PERCENTAGE 100

// The minimum percentage value for soil moisture, representing the wettest condition of the soil
#define MIN_PERCENTAGE 1

/*
 * Function:
 *  int getMoistureRange()
 *
 * Description:
 *  This function is used to determine the sensor's moisture boundaries in different environmental conditions.
 *  Specifically, it returns the highest or lowest possible readings based on the current placement of the sensor.
 *
 * Usage:
 *  1. Place the sensor in a dry environment (e.g., air) and call `getMoistureRange()`. 
 *     The function will return the maximum value that represents the dry condition.
 *  2. Place the sensor in a wet environment (e.g., water) and call `getMoistureRange()`. 
 *     The function will return the minimum value that represents the wet condition.
 *
 * Parameters:
 *  - pin (int): The analog pin number to which the sensor is connected.
 *
 * Return:
 * - An integer value corresponding to the moisture reading in the current environment.
 *
 * Note:
 *  - Use the returned values to set `DRY_MOISTURE` and `WET_MOISTURE` constants for calibration.
 *  - Keyword 'static' is used to prevents other '.ino' files from accessing it.
 *
 */
static int getMoistureBound(int pin);

void setup() {
  // Start the serial connection with the computer to view the result open the serial monitor 
  Serial.begin(9600);
}

void loop() {
  // Uncomment the following code to call 'getMoistureBound()' to set `DRY_MOISTURE` and `WET_MOISTURE`
  // int rawSensorReading = getMoistureBound(CSMS_PIN);
  // Serial.print(rawSensorReading);

  // Reads the current analog value from the sensor connected to `CSMS_PIN`
  int sensorReading = analogRead(CSMS_PIN);

  // Maps the raw sensor reading to a percentage value
  int percentageReading = map(sensorReading, WET_MOISTURE, DRY_MOISTURE, MAX_PERCENTAGE, MIN_PERCENTAGE);

  // Uncomment the following code to display the readings to the Serial monitor
  // Serial.print(percentageReading);
  // Serial.println("%");

  // Wait for 1 second to get next temperature data
  delay(1000);
}

static int getMoistureBound(int pin) { return analogRead(pin); }
