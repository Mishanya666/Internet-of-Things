#include <Wire.h>

#define SLAVE_ADDRESS 9  
String incomingMessage = "";
bool hasMessage = false;

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.print("Enter recipient (0-2 or 99 for reply): ");
    while (!Serial.available()); 
    int receiver = Serial.parseInt();

    incomingMessage = String(receiver) + msg;
    hasMessage = true;
  }
}

void receiveEvent(int howMany) {
  if (howMany == 1) {
    char request = Wire.read();
    if (request == 'R') { 
      Wire.write(hasMessage ? incomingMessage.length() : 0);
    }
  } else {
    int senderAddr = Wire.read(); 
    incomingMessage = "";
    while (Wire.available()) {
      incomingMessage += (char)Wire.read();
    }
    Serial.print("Message from ");
    Serial.print(senderAddr);
    Serial.print(": ");
    Serial.println(incomingMessage);
  }
}

void requestEvent() {
  if (hasMessage) {
    Wire.write(incomingMessage.c_str());
    hasMessage = false;
  }
}
