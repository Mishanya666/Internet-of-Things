import serial
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
import time


ser = serial.Serial('COM4', 9600)  # Замените 'COM PORT' на ваш порт
time.sleep(2)


def collect_data():
    distances = []
    ir_values = []

    while True:
        data = ser.readline().decode('utf-8').strip()
        if data:
            distance, ir_value = map(float, data.split(','))
            distances.append(distance)
            ir_values.append(ir_value)


            if len(distances) >= 50:
                print("Данные собраны.")
                break

    return np.array(distances), np.array(ir_values)


print("Сбор данных...")
distances, ir_values = collect_data()

poly = PolynomialFeatures(degree=3)
X_poly = poly.fit_transform(ir_values.reshape(-1, 1))

model = LinearRegression()
model.fit(X_poly, distances)

predicted_distances = model.predict(X_poly)

plt.figure(figsize=(8, 6))
plt.scatter(ir_values, distances, color='red', label='Измеренные данные')
plt.plot(ir_values, predicted_distances, color='blue', label='Аппроксимация модели', linewidth=2)

plt.xlabel('Значение с инфракрасного сенсора')
plt.ylabel('Расстояние (см)')
plt.title('')

plt.legend()

plt.grid(True)
plt.tight_layout()
plt.show()


def convert_to_centimeters(ir_value):
    transformed = poly.transform(np.array([[ir_value]]))
    return model.predict(transformed)[0]


ir_value_example = 500
distance_in_cm = convert_to_centimeters(ir_value_example)
print(f"Расстояние для значения {ir_value_example} с инфракрасного сенсора: {distance_in_cm:.2f} см")
