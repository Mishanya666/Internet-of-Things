#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tenda_05CE60";     
const char* password = "82266851";     
const char* mqtt_server = "test.mosquitto.org"; 

WiFiClient espClient;
PubSubClient client(espClient);

const int photoResistorPin = A0;  
char topic[50]; // сюда сохраняем введённый топик

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

  // Ввод топика через Serial
  Serial.println("Введите топик для публикации:");
  while (Serial.available() == 0) {
    // ждём пока пользователь введёт топик
  }
  Serial.readBytesUntil('\n', topic, sizeof(topic));
  topic[sizeof(topic)-1] = '\0';
  Serial.print("Будем публиковать в: ");
  Serial.println(topic);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("Publisher")) {
      delay(500);
    }
  }

  int lightLevel = analogRead(photoResistorPin);   
  client.publish(topic, String(lightLevel).c_str()); 
  Serial.print("Light level: ");
  Serial.println(lightLevel);
  delay(1000);  
}

