#include <SoftwareSerial.h>

#define RX_PIN 16
#define TX_PIN 17

SoftwareSerial gsmSerial(RX_PIN, TX_PIN);  // RX, TX

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  gsmSerial.begin(9600);  // Initialize GSM Module Serial
}

void loop() {
  // Forward data from GSM module to Serial Monitor
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
  
  // Forward data from Serial Monitor to GSM module
  while (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
}
