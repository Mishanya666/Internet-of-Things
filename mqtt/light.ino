const int ledPin = 13;  
String message = "";

void setup() {
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  if (Serial.available() > 0) {
    message = Serial.readStringUntil('\n');  
    int brightness = message.toInt();  

    if (brightness < 50) {
      digitalWrite(ledPin, HIGH);  
    } else {
      digitalWrite(ledPin, LOW);  
    }
  }
}
