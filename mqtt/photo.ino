const int sensorPin = A0;  

void setup() {
  Serial.begin(9600);  
}

void loop() {
  int lightLevel = analogRead(sensorPin);  
  int normalizedLight = map(lightLevel, 0, 1023, 0, 100); 

  Serial.println(normalizedLight);  
  delay(1000); 
}
