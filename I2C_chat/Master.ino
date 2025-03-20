#include <Wire.h>

#define NUM_SLAVES 3

const int slaveAddresses[NUM_SLAVES] = {9, 10, 11};

char lastSender = -1; 

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Master I2C
}

void loop() {
  for (int i = 0; i < NUM_SLAVES; i++) {
    int slaveAddr = slaveAddresses[i];

    Wire.beginTransmission(slaveAddr);
    Wire.write("READY?"); 
    Wire.endTransmission();

    delay(100);
    
    Wire.requestFrom(slaveAddr, 1);
    if (Wire.available()) {
      int dataSize = Wire.read();
      if (dataSize > 0) {
        lastSender = slaveAddr; 

        Serial.print("Receiving from Slave ");
        Serial.print(slaveAddr);
        Serial.print(": ");

        Wire.requestFrom(slaveAddr, dataSize); 
        String message = "";
        while (Wire.available()) {
          char c = Wire.read();
          message += c;
        }

        Serial.println(message);

        int receiver = message[0] - '0'; 
        message.remove(0, 1); 
        
        sendMessage(receiver, message, slaveAddr);
      }
    }
  }
  delay(1000);
}

void sendMessage(int receiver, String message, int senderAddr) {
  if (receiver == 99) {
    receiver = lastSender;
  }

  Serial.print("Forwarding to Slave ");
  Serial.print(receiver);
  Serial.print(": ");
  Serial.println(message);

  Wire.beginTransmission(receiver);
  Wire.write(senderAddr); 
  Wire.write(message.c_str()); 
  Wire.endTransmission();
}
