#define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "SOLARM"
#define BLYNK_AUTH_TOKEN    "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// ====================
// Blynk and WiFi Settings
// ====================
char auth[] = "YOUR_BLYNK_AUTH_TOKEN"; // Blynk Auth Token
char ssid[] = "YOUR_WIFI_SSID";        // WiFi SSID
char pass[] = "YOUR_WIFI_PASSWORD";    // WiFi Password

// ====================
// Pin Definitions
// ====================
const int SOIL_PIN    = A0;
const int RELAY_PIN   = 13;
const int PIR_PIN     = 5;
const int BUZZER_PIN  = 14;
const int SERVO_PIN   = 4;

Servo myServo;

// ====================
// Variables
// ====================
bool lowMoistureNotified = false;
bool motorNotified = false;
unsigned long lastSensorUpdate = 0;
unsigned long lastMotionTime = 0;
const unsigned long SENSOR_INTERVAL = 1000;
const unsigned long SERVO_DURATION  = 1000;

// ====================
// Blynk Terminal
// ====================
WidgetTerminal terminal(V10); // Terminal widget on V10

// ====================
// Blynk Relay Control
// ====================
BLYNK_WRITE(V3) {
  int relayCmd = param.asInt(); // 1=ON, 0=OFF
  digitalWrite(RELAY_PIN, relayCmd);
  terminal.println(String("Relay manually set to: ") + relayCmd);
  terminal.flush();
}

// ====================
// Setup
// ====================
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(PIR_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(90); // stop continuous rotation

  Serial.println("=== SOLARM ===");
  terminal.println("=== SOLARM ===");
  Serial.println("System Starting...");
  terminal.println("System Starting...");
  terminal.flush();

  Blynk.begin(auth, ssid, pass);
}

// ====================
// Loop
// ====================
void loop() {
  Blynk.run();

  unsigned long currentMillis = millis();

  // --- Soil Moisture Reading ---
  if (currentMillis - lastSensorUpdate >= SENSOR_INTERVAL) {
    lastSensorUpdate = currentMillis;

    int sensorValue = analogRead(SOIL_PIN);
    int moisturePercent = map(sensorValue, 1023, 0, 0, 100);

    String msg = "Moisture: " + String(moisturePercent) + "%";
    Serial.println(msg);
    terminal.println(msg);
    terminal.flush();

    Blynk.virtualWrite(V0, moisturePercent);

    // Relay control based on moisture
    if (moisturePercent < 41) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay ON - Watering");
      terminal.println("Relay ON - Watering");
      terminal.flush();
      Blynk.virtualWrite(V1, 1);

      if (!lowMoistureNotified) {
        Blynk.virtualWrite(V4, 1);
        Blynk.virtualWrite(V4, 0);
        lowMoistureNotified = true;
        terminal.println("Notification: Low soil moisture");
        terminal.flush();
      }
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay OFF");
      terminal.println("Relay OFF");
      terminal.flush();
      Blynk.virtualWrite(V1, 0);
      lowMoistureNotified = false;
    }
  }

  // --- PIR Motion Detection ---
  int motionDetected = digitalRead(PIR_PIN);

  if (motionDetected == HIGH && currentMillis - lastMotionTime >= 3000) {
    lastMotionTime = currentMillis;

    Serial.println("Motion Detected!");
    terminal.println("Motion Detected!");
    terminal.flush();

    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V5, 1);
    Blynk.virtualWrite(V5, 0);

    if (!motorNotified) {
      Blynk.virtualWrite(V6, 1);
      Blynk.virtualWrite(V6, 0);
      motorNotified = true;
      terminal.println("Servo Activated!");
      terminal.flush();
    }

    digitalWrite(BUZZER_PIN, HIGH);
    myServo.write(0);   // CW
    delay(SERVO_DURATION);
    myServo.write(180); // CCW
    delay(SERVO_DURATION);
    myServo.write(90);  // Stop
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (motionDetected == LOW) {
    Blynk.virtualWrite(V2, 0);
    motorNotified = false;
  }
}
