#include "Config.h"

#define LEFT_DIRECTION 3
#define LEFT_SPEED 9
#define RIGHT_SPEED 10
#define RIGHT_DIRECTION 2

#define LEFT_SIDE_FORWARD LOW
#define RIGHT_SIDE_FORWARD HIGH

#define LEFT_SIDE_BACKWARD HIGH
#define RIGHT_SIDE_BACKWARD LOW

#define FORWARD_TRIG A0
#define FORWARD_ECHO A1

#define RIGHT_TRIG A2
#define RIGHT_ECHO A3

int forward_distance, right_distance, value;
int speed_left = 170;
int speed_right = 170;
int ratio = 0.6;

void setup() {
    Serial.begin(115200);
    for (int i = 2; i <= 3; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }

    pinMode(FORWARD_TRIG, OUTPUT);
    pinMode(FORWARD_ECHO, INPUT);
    pinMode(RIGHT_TRIG, OUTPUT);
    pinMode(RIGHT_ECHO, INPUT);
}

int getDistance(bool isForward) {
    int result;

    if (isForward) {
        digitalWrite(FORWARD_TRIG, LOW);
        delayMicroseconds(2);
        digitalWrite(FORWARD_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(FORWARD_TRIG, LOW);

        result = pulseIn(FORWARD_ECHO, HIGH) * 0.034 / 2;
    } else {
        digitalWrite(RIGHT_TRIG, LOW);
        delayMicroseconds(2);
        digitalWrite(RIGHT_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(RIGHT_TRIG, LOW);

        result = pulseIn(RIGHT_ECHO, HIGH) * 0.034 / 2;
    }

    return result > 0 ? result : 0;
}

void move(bool dir_left, int speed_left, bool dir_right, int speed_right) {
    speed_left = constrain(speed_left, 0, 255);
    speed_right = constrain(speed_right, 0, 255);

    digitalWrite(LEFT_DIRECTION, dir_left);
    analogWrite(LEFT_SPEED, speed_left);
    digitalWrite(RIGHT_DIRECTION, dir_right);
    analogWrite(RIGHT_SPEED, speed_right);
}

void move_only_right() {
    move(false, 0, false, 200);
}

void move_only_left() {
    move(false, 200, false, 0);
}

void go_forward() {
    move(LEFT_SIDE_FORWARD, speed_left, RIGHT_SIDE_FORWARD, speed_right);
}

void go_backward() {
    move(LEFT_SIDE_BACKWARD, speed_left, RIGHT_SIDE_BACKWARD, speed_right);
}

void turn_left(float ratio) {
    move(LEFT_SIDE_FORWARD, int(speed_left * ratio), RIGHT_SIDE_FORWARD, speed_right);
}

void turn_right(float ratio) {
    move(LEFT_SIDE_FORWARD, speed_left, RIGHT_SIDE_FORWARD, int(speed_right * ratio));
}

void turn_left_onspot() {
    move(LEFT_SIDE_BACKWARD, speed_left, RIGHT_SIDE_FORWARD, speed_right);
}

void turn_right_onspot() {
    move(LEFT_SIDE_FORWARD, speed_left, RIGHT_SIDE_BACKWARD, speed_right);
}

void stop() {
    move(0, 0, 0, 0);
}

void loop() {
    forward_distance = getDistance(true);
    Serial.print(forward_distance);

    right_distance = getDistance(false);
    Serial.print(" ");
    Serial.println(right_distance);

    if (forward_distance < STOP_DISTANCE) {
        turn_left_onspot();
        delay(1400);
    }
    if (forward_distance > STOP_DISTANCE) {
        if (right_distance <= RIGHT_CORRIDOR) {
            turn_left_onspot();
            delay(120);
        } else if (right_distance >= LEFT_CORRIDOR && right_distance < 180) {
            turn_right(ratio);
        }

        if (right_distance > 180) {
            turn_right(ratio);
        } else {
            go_forward();
        }
    }
}

