# Mr Steelbot - Transmitter & Receiver Code

This repository contains the Arduino code for the wireless control system of **Mr Steelbot**, a combat-ready robot built for RoboWar, RoboSoccer, and RoboSumo competitions.

The system uses **NRF24L01 2.4GHz RF modules** for wireless communication between the transmitter and receiver. Dual joysticks on the transmitter allow manual control of motor speed and direction, enabling precise movements in battle or on the field.

---

## 🔧 Hardware Components

### Transmitter:
- Arduino Nano
- 2x Joystick modules
- NRF24L01 module
- Pushbuttons (optional)

### Receiver:
- Arduino Uno/Nano
- NRF24L01 module
- BTS7960 motor drivers
- 4x Gear motors (2 per side)
- Power supply (LiPo or Li-ion battery)

---

## 📡 Communication

- **Protocol:** NRF24L01 with RF24 library
- **Frequency:** 2.4GHz
- **Method:** SPI-based data transmission of joystick positions (X/Y) and button states
- **Payload:** Struct-based control data sent from transmitter to receiver every few milliseconds

---
