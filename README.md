# SOLARM – Smart Irrigation & Motion Detection System

## Overview
**SOLARM** is an ESP8266-based smart irrigation and security system integrated with the **Blynk app**.  
It monitors soil moisture, controls a relay for watering, detects motion with a PIR sensor, and activates a buzzer and continuous rotation servo as a response to motion. The system is fully controllable and monitored remotely via Blynk.

---

## Features
- **Soil Moisture Monitoring:**  
  Reads soil moisture from an analog sensor (A0) and displays it on the Blynk app in real-time.  
- **Automatic Watering:**  
  Controls a relay to turn on a water pump when soil moisture drops below 41%.  
- **Motion Detection:**  
  Detects motion with a PIR sensor and triggers a buzzer and servo motor.  
- **Blynk Integration:**  
  - Real-time sensor updates (soil moisture, motion detection)  
  - Remote relay control  
  - Notifications through virtual pins for watering, motion, and servo activation  
- **Servo Motor Control:**  
  Continuous rotation servo rotates in both directions upon motion detection.  
- **Non-blocking Operation:**  
  Uses timed intervals to read sensors and handle events without blocking other tasks.  

---

## Hardware Requirements
- **ESP8266** (NodeMCU / Wemos D1 Mini)  
- **Soil Moisture Sensor** (Analog)  
- **Relay Module**  
- **PIR Motion Sensor**  
- **Buzzer**  
- **Continuous Rotation Servo**  
- Jumper wires and power supply  

---

## Pin Configuration
| Component                | Pin on ESP8266 |
|---------------------------|----------------|
| Soil Sensor               | A0             |
| Relay                     | D7             |
| PIR Motion Sensor         | D1             |
| Buzzer                    | D5             |
| Continuous Rotation Servo | D6             |

---

## Software Requirements
- **Arduino IDE** (latest version recommended)  
- **Blynk Library** (Classic Blynk)  
- **ESP8266 Board Package** installed via Board Manager  
- **Servo Library** (Arduino built-in)  

---

## Blynk IoT Template Details
Before uploading the code, fill in your **Blynk IoT template credentials**:

```cpp
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxxxxx" // Replace with your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "SOLARM"          // Replace with your Template Name
#define BLYNK_AUTH_TOKEN    "YourAuthToken"   // Replace with your Device Auth Token

char ssid[] = "YOUR_WIFI_SSID";             // Replace with your WiFi SSID
char pass[] = "YOUR_WIFI_PASSWORD";         // Replace with your WiFi password



