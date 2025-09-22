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

## Installation Instructions

### 1. Install Arduino IDE
Download and install the Arduino IDE from [Arduino.cc](https://www.arduino.cc/en/software).

### 2. Add ESP8266 Board Package
1. Open Arduino IDE → **File → Preferences → Additional Board Manager URLs**  
2. Add the following URL:  
http://arduino.esp8266.com/stable/package_esp8266com_index.json

3. Go to **Tools → Board → Boards Manager**, search for **ESP8266**, and click **Install**.

### 3. Install Required Libraries
1. In Arduino IDE, go to **Sketch → Include Library → Manage Libraries**.  
2. Search and install the following libraries:  
- **Blynk**  
- **Servo** (usually built-in)

### 4. Connect Hardware
- Follow the **Pin Configuration** table in this README.  

### 5. Configure the Sketch
- Open `sketch_sep22a.ino` in Arduino IDE.  
- Replace placeholders with your WiFi and Blynk credentials:  
```cpp
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "SOLARM"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"
```

### 6. Select Board and Port
- Go to **Tools → Board** and select your ESP8266 model.  
- Go to **Tools → Port** and select the correct COM port.

### 7. Upload the Sketch
- Click **Upload** in Arduino IDE.  
- Wait for compilation and flashing to complete.

### 8. Set Up Blynk App Project
1. Create a project in the Blynk app using your template.  
2. Add widgets for virtual pins:  
   - **V0** → Soil Moisture Display  
   - **V1** → Relay Status LED  
   - **V2** → Motion Detection LED  
   - **V3** → Relay Control Button  
   - **V4** → Watering Notification  
   - **V5** → Motion Notification  
   - **V6** → Servo Activation Notification

### 9. Power Up and Test
- The ESP8266 will automatically connect to WiFi and Blynk.  
- Verify that the relay, motion detection, and notifications are working as expected.


---




