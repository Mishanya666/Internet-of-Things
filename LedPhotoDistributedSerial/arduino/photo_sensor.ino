#define PHOTO_SENSOR_PIN A0
#define CMD_READ_SENSOR 'p'

void setup() {
    Serial.begin(9600);
    pinMode(PHOTO_SENSOR_PIN, INPUT);
}

void loop() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();
        if (cmd == CMD_READ_SENSOR) {
            int sensor_value = analogRead(PHOTO_SENSOR_PIN) / 4; 
            Serial.write(sensor_value); 
        }
    }
}
