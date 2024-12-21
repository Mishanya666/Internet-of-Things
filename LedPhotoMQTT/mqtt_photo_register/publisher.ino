#include "Config.h"
#include "WIFI.h"
#include "MQTT.h"

const int sensorPin = A0; 
const char* sensorTopic = "esp8266/light_sensor"; 

void setup() {
  Serial.begin(115200);
  WIFI_init(false);
  MQTT_init();
  mqtt_cli.publish("esp8266/state", "Sensor ready");
}

void loop() {
  mqtt_cli.loop();

  int lightLevel = analogRead(sensorPin); 
  String lightData = String(lightLevel);
  mqtt_cli.publish(sensorTopic, lightData.c_str()); 

  Serial.println("Light Level: " + lightData);
  delay(2000);
}
