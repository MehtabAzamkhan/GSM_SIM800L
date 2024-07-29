#include <SoftwareSerial.h>

#define RX_PIN 16
#define TX_PIN 17

SoftwareSerial gsmSerial(RX_PIN, TX_PIN);  // RX, TX

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  gsmSerial.begin(9600);  // Initialize GSM Module Serial
  
  delay(3000); // Allow time for the GSM module to initialize

  Serial.println("Initializing GSM module...");

  // Check network registration
  checkNetworkRegistration();
  
  // Initialize GPRS
  initializeGPRS();
  
  // Wait a bit to ensure GPRS is initialized
  delay(5000);
  
  // Try to activate GPRS
  activateGPRS();
  
  // Retrieve IP address
  retrieveIPAddress();
}

void loop() {
  updateSerial();
}

void checkNetworkRegistration() {
  Serial.println("Checking network registration...");
  gsmSerial.println("AT+CREG?");
  delay(2000);
  updateSerial();
}

void initializeGPRS() {
  Serial.println("Initializing GPRS...");
  
  // Attach to GPRS service
  gsmSerial.println("AT+CGATT=1");  
  delay(2000);
  updateSerial();
  
  // Set APN for Ufone
  Serial.println("Setting APN...");
  gsmSerial.println("AT+CGDCONT=1,\"IP\",\"ufone.pinternet\"");
  delay(2000);
  updateSerial();

  // Verify APN setting
  Serial.println("Verifying APN...");
  gsmSerial.println("AT+CGDCONT?");
  delay(2000);
  updateSerial();
}

void activateGPRS() {
  Serial.println("Activating GPRS...");
  gsmSerial.println("AT+CGACT=1,1");  // Activate GPRS context (CID 1)
  delay(2000);  // Wait for the command to process
  updateSerial();
}

void retrieveIPAddress() {
  Serial.println("Retrieving IP address...");
  gsmSerial.println("AT+CGPADDR=1");
  delay(2000);
  updateSerial();
}

void updateSerial() {
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read()); // Forward GSM module output to Serial Monitor
  }
  while (Serial.available()) {
    gsmSerial.write(Serial.read()); // Forward Serial input to GSM module
  }
}
