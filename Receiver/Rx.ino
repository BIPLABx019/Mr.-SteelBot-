#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins for the nRF24L01 module
#define CE_PIN 7
#define CSN_PIN 8

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address for communication
const uint64_t address = 0xF0F0F0F0E1LL;

// Variables to store recei0ved data
int data[4];

// Motor driver pins for BTS7960 #1 (Left Side)
#define RPWM_LEFT 6
#define LPWM_LEFT 5
#define R_EN_LEFT 4
#define L_EN_LEFT 3

// Motor driver pins for BTS7960 #2 (Right Side)
#define RPWM_RIGHT 10
#define LPWM_RIGHT 9
#define R_EN_RIGHT 2
#define L_EN_RIGHT 0

void setup() {
  Serial.begin(9600);
  
  // Initialize the nRF24L01 module
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // Set as receiver

  // Set motor driver pins as outputs
  pinMode(RPWM_LEFT, OUTPUT);
  pinMode(LPWM_LEFT, OUTPUT);
  pinMode(R_EN_LEFT, OUTPUT);
  pinMode(L_EN_LEFT, OUTPUT);

  pinMode(RPWM_RIGHT, OUTPUT);
  pinMode(LPWM_RIGHT, OUTPUT);
  pinMode(R_EN_RIGHT, OUTPUT);
  pinMode(L_EN_RIGHT, OUTPUT);

  // Enable both channels of BTS7960 drivers
  digitalWrite(R_EN_LEFT, HIGH);
  digitalWrite(L_EN_LEFT, HIGH);
  digitalWrite(R_EN_RIGHT, HIGH);
  digitalWrite(L_EN_RIGHT, HIGH);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));

    int forward = map(data[3], 0, 255, -130, 130);
    int turn = map(data[0], 0, 255, -130, 130);

    int leftSpeed = constrain(forward - turn, -130, 130);
    int rightSpeed = constrain(forward + turn, -130, 130);

    if (abs(leftSpeed) < 50) leftSpeed = 0;
    if (abs(rightSpeed) < 50) rightSpeed = 0;

    if (leftSpeed > 0) {
      analogWrite(RPWM_LEFT, leftSpeed);
      analogWrite(LPWM_LEFT, 0);
    } else {
      analogWrite(RPWM_LEFT, 0);
      analogWrite(LPWM_LEFT, -leftSpeed);
    }

    if (rightSpeed > 0) {
      analogWrite(RPWM_RIGHT, rightSpeed);
      analogWrite(LPWM_RIGHT, 0);
    } else {
      analogWrite(RPWM_RIGHT, 0);
      analogWrite(LPWM_RIGHT, -rightSpeed);
    }
    Serial.print(leftSpeed); Serial.print(", ");
    Serial.println(rightSpeed);
  }   

}
