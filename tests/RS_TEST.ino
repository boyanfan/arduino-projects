/*
 * RS_TEST.ino
 *
 * Rain Sensor Test
 *
 * This program demonstrates how to interface a rain sensor with an Arduino board.
 * It reads the sensor's output to detect rainfall and displays the status on the Serial Monitor.
 *
 * Connections:
 * - VCC pin of the sensor to 5V on Arduino
 * - GND pin of the sensor to GND on Arduino
 * - AOUT pin of the sensor to A0 (example analog pin) on Arduino
 *
 * Author: Boyan Fan
 * Date: Nov 14, 2024
 */

// Define the analog pin connected to the RS here
#define RS_PIN A0

void setup() {
  // Start the serial connection with the computer to view the result open the serial monitor 
  Serial.begin(9600);
}

void loop() {
  // Reads the current analog value from the sensor connected to `RS_PIN`
  int sensorReading = analogRead(RS_PIN);

  // Uncomment the following code to display the readings to the Serial monitor
  // Serial.print(percentageReading);
  // Serial.println(" / 1023");

  // Wait for 1 second to get next temperature data
  delay(1000);
}
