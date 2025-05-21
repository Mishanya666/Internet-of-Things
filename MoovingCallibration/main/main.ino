#include <SoftwareSerial.h>

const int DIR1 = 4, SPEED1 = 5, SPEED2 = 6, DIR2 = 7;
SoftwareSerial BTSerial(10, 11); 
int speedLeft = 150, speedRight = 150;

void setup() {
    pinMode(DIR1, OUTPUT);
    pinMode(SPEED1, OUTPUT);
    pinMode(SPEED2, OUTPUT);
    pinMode(DIR2, OUTPUT);
    
    BTSerial.begin(9600);
    Serial.begin(9600);
}

void loop() {
    if (BTSerial.available()) {
        char command = BTSerial.read();
        Serial.print("Received: ");
        Serial.println(command);
        processCommand(command);
    }
}

void processCommand(char command) {
    switch (command) {
        case 'L': 
            moveForward();
            break;
        case 'R': 
            moveBackward();
            break;
        case 'F':
            turnLeft();
            break;
        case 'B': 
            turnRight();
            break;
        case '0':  
            stopMotors();
            break;
    }
}

void moveForward() {
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    analogWrite(SPEED1, speedLeft);
    analogWrite(SPEED2, speedRight);
}

void moveBackward() {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    analogWrite(SPEED1, speedLeft);
    analogWrite(SPEED2, speedRight);
}

void turnLeft() {
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(SPEED1, speedLeft);
    analogWrite(SPEED2, speedRight);
}

void turnRight() {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(SPEED1, speedLeft);
    analogWrite(SPEED2, speedRight);
}

void stopMotors() {
    analogWrite(SPEED1, 0);
    analogWrite(SPEED2, 0);
}
