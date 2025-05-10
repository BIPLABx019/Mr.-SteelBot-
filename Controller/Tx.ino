#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins for the nRF24L01 module
#define CE_PIN 10
#define CSN_PIN 9

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address for communication between transmitter and receiver
const uint64_t address = 0xF0F0F0F0E1LL;
// Variables to store joystick values
int joy1X, joy1Y, joy2X, joy2Y;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize the nRF24L01 module
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // Set power level (MIN, LOW, HIGH, MAX)
  radio.stopListening(); // Set as transmitter
}

void loop() {
  // Read joystick values
  joy1X = analogRead(A0); // Joystick 1 X-axis
  joy1Y = analogRead(A1); // Joystick 1 Y-axis
  joy2X = analogRead(A2); // Joystick 2 X-axis
  joy2Y = analogRead(A3); // Joystick 2 Y-axis

  // Map joystick values to a range of 0-255 for PWM control
  int data[4] = {
    map(joy1X, 0, 1023, 0, 255), // Joystick 1 X-axis
    map(joy1Y, 0, 1023, 0, 255), // Joystick 1 Y-axis
    map(joy2X, 0, 1023, 0, 255), // Joystick 2 X-axis
    map(joy2Y, 0, 1023, 0, 255)  // Joystick 2 Y-axis
  };

  // Send data to the receiver
  radio.write(&data, sizeof(data));

  // Debugging output
  Serial.print("Joystick Values: ");
  Serial.print(data[0]);
  Serial.print(", ");
  Serial.print(data[1]);
  Serial.print(", ");
  Serial.print(data[2]);
  Serial.print(", ");
  Serial.println(data[3]);

  delay(20); // Small delay to avoid flooding the radio
}
