#include <Arduino.h>

// Standard ESP32 Serial2 Pins
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200); // USB connection to PC
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // F-Bus connection to Nokia

  // Send 128 'U' (0x55) bytes to synchronize the Nokia's UART baud rate
  for(int i = 0; i < 128; i++) {
    Serial2.write(0x55);
  }
  delay(50);
  
  Serial.println("ESP32 F-Bus Bridge Ready.");
  Serial.println("Waiting for hex frames from PC...");
}

void loop() {
  // Transparent Bridge: Pass bytes from PC to Nokia
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }
  
  // Transparent Bridge: Pass bytes from Nokia to PC
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}
