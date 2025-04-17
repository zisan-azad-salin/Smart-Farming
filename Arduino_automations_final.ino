#include <Servo.h>

#define WATER_SENSOR_PIN A1
#define PUMP_PIN1 8      // Main pump control
#define PUMP_PIN2 10     //  pump
#define LDRPIN A0
#define LEDPIN 5         // LED control
#define SERVO_PIN 9      // Servo motor

Servo myServo;

// Servo schedule variables
unsigned long previousMillis = 0;
const long interval = 10000;  // 10 seconds in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_PIN1, OUTPUT);
  pinMode(PUMP_PIN2, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  
  // Initialize unused pump as OFF
  digitalWrite(PUMP_PIN2, LOW);
}

void loop() {
  // Read water sensor and control pump1
  int waterLevel = analogRead(WATER_SENSOR_PIN);
  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  if (waterLevel < 300) {  // Adjust threshold based on your testing
    digitalWrite(PUMP_PIN1, LOW); // Turn on pump1
  } else {
    digitalWrite(PUMP_PIN1, HIGH);  // Turn off pump1
  }

  // Read LDR and control LED
  int ldrValue = analogRead(LDRPIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < 500) {  // Dark environment detected
    digitalWrite(LEDPIN, LOW);  // Turn LED ON
  } else {
    digitalWrite(LEDPIN, HIGH);   // Turn LED OFF
  }

  // Servo schedule check
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    activateServo();
  }

  delay(1000);  // Main loop delay
}

void activateServo() {
  // Servo sweep routine (0-30 degrees)
  for(int pos = 0; pos <= 30; pos += 1) {
    myServo.write(pos);
    delay(15);
  }
  for(int pos = 30; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
}