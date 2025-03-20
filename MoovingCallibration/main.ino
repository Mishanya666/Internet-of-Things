#include <SoftwareSerial.h>

// Пины моторов
const int DIR1 = 4, SPEED1 = 5, SPEED2 = 6, DIR2 = 7;

SoftwareSerial BTSerial(10, 11); // RX, TX

// Переменные калибровки
int dir1State = LOW, dir2State = LOW;
int speedLeft = 150, speedRight = 150;
int turn90Time = 500, turn180Time = 1000, turn270Time = 1500, turn360Time = 2000;

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
        case '^': 
            moveForward();
            break;
        case 'v': 
            moveBackward();
            break;
        case '<':
            turnLeft();
            break;
        case '>': 
            turnRight();
            break;
        case 'X': 
            speedLeft = min(255, speedLeft + 10);
            break;
        case 'B': 
            speedLeft = max(0, speedLeft - 10);
            break;
        case 'A': 
            speedRight = min(255, speedRight + 10);
            break;
        case 'Y': 
            speedRight = max(0, speedRight - 10);
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
    delay(turn90Time);
}

void turnRight() {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(SPEED1, speedLeft);
    analogWrite(SPEED2, speedRight);
    delay(turn90Time);
}
