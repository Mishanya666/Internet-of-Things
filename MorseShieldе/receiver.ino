const int pin = 2; // Input pin
const int TU = 200; // Time Unit in ms
volatile unsigned long lastChangeTime = 0;
volatile int signal = HIGH;
String decodedMessage = "";

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), signalChanged, CHANGE);
}

void loop() {
  if (millis() - lastChangeTime > 7 * TU && signal == HIGH) {
    Serial.print("Received message: ");
    Serial.println(decodedMessage);
    decodedMessage = "";
  }
}

void signalChanged() {
  unsigned long duration = millis() - lastChangeTime;
  lastChangeTime = millis();
  
  if (signal == LOW) {
    // HIGH duration
    if (duration >= 7 * TU) {
      decodedMessage += " ";
    } else if (duration >= 3 * TU) {
      decodedMessage += "_";
    }
  } else {
    if (duration < 2 * TU) {
      decodedMessage += ".";
    } else {
      decodedMessage += "-";
    }
  }
  signal = digitalRead(pin);
}
