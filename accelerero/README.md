# Акселерометр_невесомость

Этот проект использует акселерометр **ADXL345** для обнаружения состояния "невесомости". Когда акселерометр фиксирует ускорение по оси **Z** близкое к **0g** (например, при подбрасывании устройства), включается светодиод, сигнализируя о состоянии невесомости.

## Описание

Проект использует **Arduino Nano** и модуль **ADXL345** для измерения ускорения в трех осях: **X**, **Y** и **Z**. При нахождении ускорения по оси **Z** близким к нулю (что может происходить в момент, когда объект кратковременно находится в состоянии невесомости), загорается светодиод.

## Необходимые компоненты

- **Arduino Nano**
- **ADXL345 (акселерометр)** - подключается по I2C
- **Светодиод**
- **Резистор** для светодиода (например, 220 Ом)
- **Провода для соединений**
- **Макетная плата (breadboard)**

## Подключение компонентов

### Схема подключения:

| **ADXL345**  | **Arduino Nano**  | **Назначение**          |
|--------------|-------------------|-------------------------|
| **VCC**      | **5V**          | Питание (5V)          |
| **GND**      | **GND**           | Земля (общий GND)       |
| **SDA**      | **A4**            | Данные I2C (SDA)        |
| **SCL**      | **A5**            | Тактирование I2C (SCL)  |
| **LED**      | **D13**            | Пин для подключения светодиода |
| **Резистор** | Светодиод         | Подключение светодиода с резистором (220 Ом) |

### Подключение светодиода:

Светодиод подключается через резистор к пину **D13**. Не забудьте подключить анод светодиода к пину, а катод — к земле.

## Финал

Загрузите код в вашу Arduino.


