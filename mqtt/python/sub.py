import time
import paho.mqtt.client as mqtt_client
import serial

broker = "test.mosquitto.org"  // Адрес MQTT брокера (можете выбрать любой)
pub_id = "вставьте айди из паблишера"  

ser = serial.Serial('COM10', 9600)  // COM выбирайте взависимости от того какой он у платы

client = mqtt_client.Client()
client.connect(broker)
client.loop_start()

def on_message(client, userdata, message):
    data = message.payload.decode('utf-8')  
    print(f"Received from MQTT: {data}")

    ser.write(f"{data}\n".encode())
    print(f"Sent to Arduino: {data}")

client.on_message = on_message
client.subscribe(f"lab/{pub_id}/photo/instant")
print(f"Subscribed to topic: lab/{pub_id}/photo/instant")

try:
    while True:
        time.sleep(1)  
except KeyboardInterrupt:
    client.disconnect()
    client.loop_stop()
