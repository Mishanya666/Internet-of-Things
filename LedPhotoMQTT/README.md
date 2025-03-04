# LedPhotoMQTT

Этот проект демонстрирует, как можно управлять светодиодом, подключённым к микроконтроллеру ESP8266, на основе данных, полученных от датчика света (фоторезистора) с помощью MQTT. Данные о яркости света передаются через MQTT брокер от одного микроконтроллера, а второй микроконтроллер использует эти данные для управления светодиодом.

### Передача данных с фоторезистора

#### Описание

Микроконтроллер с подключённым датчиком света отправляет данные через MQTT брокер.

#### Схема подключения

- Датчик света подключён к аналоговому пину A0 на микроконтроллере.
- Микроконтроллер подключён к компьютеру через USB.

#### Инструкция

1. Подключите датчик света к микроконтроллеру.
2. Загрузите скетч `photo.ino` на микроконтроллер.

---
### Управление светодиодом

#### Описание

Микроконтроллер управляет светодиодом на основе данных, полученных через MQTT. Светодиод включается при повышении яркости.

#### Схема подключения

- Светодиод подключён к цифровому пину D1 через резистор.
- Микроконтроллер подключён к компьютеру через USB.

#### Инструкция

1. Подключите светодиод к микроконтроллеру согласно схеме.
2. Загрузите скетч `light.ino` на микроконтроллер.

---

### Видео демонстрации

Демонстрация работы проекта доступна по ссылке:

[Видео демонстрация](https://drive.google.com/file/d/1fByb6gSaC43mJ4gfk0KartrI2w0NDWcr/view?usp=sharing)
