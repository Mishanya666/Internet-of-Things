import time
import paho.mqtt.client as mqtt_client
import serial
import hashlib
from uuid import getnode as get_mac

broker = "test.mosquitto.org" // Адрес MQTT брокера (можете выбрать любой)

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
print(f"Generated pub_id: {pub_id}") 

ser = serial.Serial('COM5', 9600)  

client = mqtt_client.Client()
client.connect(broker)
client.loop_start()

def read_sensor_data():
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').strip()
        normalized_data = min(100, max(0, int(data)))  
        return normalized_data
    return None

def publish_data():
    while True:
        data = read_sensor_data()
        if data is not None:
            client.publish(f"lab/{pub_id}/photo/instant", data)
            print(f"Sent: {data}")
        time.sleep(1)  

publish_data()
