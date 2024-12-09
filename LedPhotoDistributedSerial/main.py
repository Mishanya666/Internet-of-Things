import serial
import time

PORT_LED = "COM9"
PORT_SENSOR = "COM6"
BAUDRATE = 9600
LIGHT_THRESHOLD = 800

CMD_READ_SENSOR = 'p'
CMD_LED_ON = 'u'
CMD_LED_OFF = 'd'

led_conn = serial.Serial(PORT_LED, baudrate=BAUDRATE, timeout=1)
sensor_conn = serial.Serial(PORT_SENSOR, baudrate=BAUDRATE, timeout=1)

def send_command(connection, command, response_length=0):
    connection.write(command.encode())
    if response_length > 0:
        return connection.read(response_length)
    return None

def main():
    try:
        while True:
            sensor_value_bytes = send_command(sensor_conn, CMD_READ_SENSOR, 1)
            if sensor_value_bytes:
                sensor_value = int.from_bytes(sensor_value_bytes, byteorder='little') * 4
                print(f"Sensor value: {sensor_value}")

                if sensor_value > LIGHT_THRESHOLD:
                    send_command(led_conn, CMD_LED_ON)
                else:
                    send_command(led_conn, CMD_LED_OFF)
            time.sleep(0.1)  
    except KeyboardInterrupt:
        print("Программа завершена.")
    finally:
        led_conn.close()
        sensor_conn.close()

if __name__ == "__main__":
    main()
