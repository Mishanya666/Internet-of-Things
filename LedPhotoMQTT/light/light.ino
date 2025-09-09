#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tenda_05CE60";     
const char* password = "82266851";     
const char* mqtt_server = "test.mosquitto.org"; 

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = 5; // D1
char topic[50];       // сюда будем сохранять введённый топик

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
  analogWrite(ledPin, brightness); 
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  // Ввод топика через Serial
  Serial.println("Введите топик для подписки:");
  while (Serial.available() == 0) {
    // ждём ввода
  }
  Serial.readBytesUntil('\n', topic, sizeof(topic));
  topic[sizeof(topic)-1] = '\0'; // защита
  Serial.print("Подписываемся на: ");
  Serial.println(topic);

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
