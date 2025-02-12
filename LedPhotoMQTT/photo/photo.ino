#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tenda_05CE60";     // Имя Wi-Fi сети (вставьте свое имя сети)
const char* password = "82266851";     // Пароль Wi-Fi сети (вставьте свой пароль)
const char* mqtt_server = "test.mosquitto.org"; // Адрес MQTT брокера (можете выбрать любой)

WiFiClient espClient;
PubSubClient client(espClient);

const int photoResistorPin = A0;  // Пин фоторезистора
const char* topic = "sensor/light"; 

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("Publisher")) {
      delay(500);
    }
  }

  int lightLevel = analogRead(photoResistorPin);   // Считывание с датчика
  client.publish(topic, String(lightLevel).c_str()); // Отправка данных в MQTT
  Serial.print("Light level: ");
  Serial.println(lightLevel);
  delay(1000);  
}
