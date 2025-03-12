#define MOTOR_IN1  7  
#define MOTOR_IN2  8  

void setup() {
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
}

void controlMotor(int speed, bool direction) {
    if (direction) {
        digitalWrite(MOTOR_IN1, HIGH);
        digitalWrite(MOTOR_IN2, LOW);
    } else {
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, HIGH);
    }
    if (speed > 0) {
        digitalWrite(MOTOR_IN1, HIGH);  
    } else {
        digitalWrite(MOTOR_IN1, LOW);  
    }
}

void loop() {
    controlMotor(150, true);  
    delay(2000);
    controlMotor(255, true);  
    delay(2000);
    controlMotor(150, false); 
    delay(2000);
    controlMotor(0, true);    
    delay(2000);
}
