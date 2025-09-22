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
const int SOIL_PIN    = A0;   // Soil sensor connected to A0
const int RELAY_PIN   = D7;   // Relay connected to D7
const int PIR_PIN     = D1;   // PIR motion sensor
const int BUZZER_PIN  = D5;   // Buzzer
const int SERVO_PIN   = D6;   // Continuous rotation servo

Servo myServo;

// ====================
// Variables
// ====================
bool lowMoistureNotified = false; // prevent repeated low moisture notifications
bool motorNotified = false;       // prevent repeated motor notifications
unsigned long lastSensorUpdate = 0; // for non-blocking timing
unsigned long lastMotionTime = 0;
const unsigned long SENSOR_INTERVAL = 1000; // update every 1 second
const unsigned long SERVO_DURATION  = 1000; // 1 second per rotation

// ====================
// Blynk Relay Control
// ====================
BLYNK_WRITE(V3) {
  int relayCmd = param.asInt(); // 1=ON, 0=OFF
  digitalWrite(RELAY_PIN, relayCmd);
}

// ====================
// Setup
// ====================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== SOLARM ===");
  Serial.println("System Starting...");

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(PIR_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(90); // stop continuous rotation

  Serial.println("Relay, PIR, Buzzer, Servo, and Soil Sensor Ready");
  Serial.println("=========================");

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

    int sensorValue = analogRead(SOIL_PIN); // raw ADC 0-1023
    int moisturePercent = map(sensorValue, 1023, 0, 0, 100);

    Serial.print("Moisture: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    Blynk.virtualWrite(V0, moisturePercent); // send moisture to Blynk

    // Relay control based on moisture
    if (moisturePercent < 41) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay ON - Watering");
      Blynk.virtualWrite(V1, 1);

      if (!lowMoistureNotified) {
        Blynk.virtualWrite(V4, 1); // trigger notification in Blynk app
        Blynk.virtualWrite(V4, 0); // reset
        lowMoistureNotified = true;
      }
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay OFF");
      Blynk.virtualWrite(V1, 0);
      lowMoistureNotified = false;
    }
  }

  // --- PIR Motion Detection ---
  int motionDetected = digitalRead(PIR_PIN);

  if (motionDetected == HIGH && currentMillis - lastMotionTime >= 3000) { // avoid repeated events
    lastMotionTime = currentMillis;
    Serial.println("Motion Detected!");
    Blynk.virtualWrite(V2, 1);

    // Trigger Blynk notification via virtual pin
    Blynk.virtualWrite(V5, 1); // Motion detected
    Blynk.virtualWrite(V5, 0); // reset

    // Servo motor notification
    if (!motorNotified) {
      Blynk.virtualWrite(V6, 1); // Servo activated
      Blynk.virtualWrite(V6, 0);
      motorNotified = true;
    }

    // Activate buzzer
    digitalWrite(BUZZER_PIN, HIGH);

    // Rotate servo forward
    myServo.write(0);   // full speed CW
    delay(SERVO_DURATION);

    // Rotate servo backward
    myServo.write(180); // full speed CCW
    delay(SERVO_DURATION);

    // Stop servo
    myServo.write(90);
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (motionDetected == LOW) {
    Blynk.virtualWrite(V2, 0);
    motorNotified = false; // reset motor notification
  }
}
