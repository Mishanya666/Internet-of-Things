#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tenda_05CE60";     // Имя Wi-Fi сети (вставьте свое имя сети)
const char* password = "82266851";     // Пароль Wi-Fi сети (вставьте свой пароль)
const char* mqtt_server = "test.mosquitto.org"; // Адрес MQTT брокера

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = 5; // Пин для светодиода (D1) (смотрите GPIO вашей платы Arduino)
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

void callback(char* receivedTopic, byte* payload, unsigned int length) {
  payload[length] = '\0'; 
  String message = String((char*)payload);
  Serial.print("Message received: ");
  Serial.println(message);

  int brightness = message.toInt(); 
  brightness = map(brightness, 0, 1023, 0, 1023); 
  analogWrite(ledPin, brightness); // Управление светодиодом
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  if (client.connect("Subscriber")) {
    client.subscribe(topic);
    Serial.println("Subscribed to topic: " + String(topic));
  }
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("Subscriber")) {
      delay(500);
    }
    client.subscribe(topic);
  }
  client.loop();
}
