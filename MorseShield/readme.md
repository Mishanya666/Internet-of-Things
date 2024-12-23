# Morse Code Communication System with Arduino UNO

## Подключение и схема собранной цепи

### Как подключить:
- **Передатчик:**
  * Пин 9 подключен к линии связи.
  * Используется внешний резистор для подтяжки линии к HIGH.

- **Приемник:**
  * Пин 2 подключен к линии связи.
  * Используется встроенный `INPUT_PULLUP` для подтяжки линии к HIGH.

- **Переключение режимов (передатчик/приемник):**
  * Реализовано через перемычку или ползунковый переключатель.
  * Переключатель управляет ролью микроконтроллера, меняя обработку данных.

- **Отладка:**
  * Линия связи дополнительно соединена со светодиодами через резисторы.
  * Светодиоды визуализируют смену состояний сигнала (HIGH/LOW).

---

## Видео демонстрация работы
На видео представлена работа системы, включая отправку и прием сообщений.

[Посмотреть видео](https://drive.google.com/)

---

## Управление

### В режиме передатчика:
Передатчик автоматически отправляет запрограммированное сообщение. Пример сообщения — `AZ`.
- **Кодировка символов:**
  * `A (.-)`
  * `Z (--..)`

- **Интервалы сигналов (в TU):**
  * Точка (`.`) — 1 TU (LOW).
  * Тире (`-`) — 3 TU (LOW).
  * Интервал между точками/тире — 1 TU (HIGH).
  * Интервал между буквами — 3 TU (HIGH).
  * Интервал между словами — 7 TU (HIGH).

### В режиме приемника:
Приемник декодирует сигнал и отображает буквы через последовательный порт.
- **Обработка сигналов:**
  * Распознавание символов на основе длительности LOW.
  * Распознавание интервалов между буквами и словами по длительности HIGH.
  * Ожидание завершения передачи при состоянии HIGH > 7 TU.

---

## Как реализован код
- **Передатчик:**
```
const int pin = 9;
const int TU = 200; 
const String message = "AZ"; 

void setup() {
  pinMode(pin, OUTPUT);
}

void dot() {
  digitalWrite(pin, LOW);
  delay(TU);
  digitalWrite(pin, HIGH);
  delay(TU);
}

void dash() {
  digitalWrite(pin, LOW);
  delay(3 * TU);
  digitalWrite(pin, HIGH);
  delay(TU);
}

void sendLetter(char letter) {
  if (letter == 'A') {
    dot();
    dash();
  } else if (letter == 'Z') {
    dash();
    dash();
    dot();
    dot();
  }
}

void sendMessage(const String &msg) {
  for (int i = 0; i < msg.length(); i++) {
    if (msg[i] == ' ') {
      delay(7 * TU);
    } else {
      sendLetter(msg[i]);
      if (i < msg.length() - 1 && msg[i + 1] != ' ') {
        delay(3 * TU); 
      }
    }
  }
}

void loop() {
  sendMessage(message);
  delay(7 * TU);
}
```

- **Приемник:**
```
const int pin = 2; // Input pin
const int TU = 200; // Time Unit in ms
volatile unsigned long lastChangeTime = 0;
volatile int signal = HIGH;
String decodedMessage = "";

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), signalChanged, CHANGE);
}

void loop() {
  if (millis() - lastChangeTime > 7 * TU && signal == HIGH) {
    Serial.print("Received message: ");
    Serial.println(decodedMessage);
    decodedMessage = "";
  }
}

void signalChanged() {
  unsigned long duration = millis() - lastChangeTime;
  lastChangeTime = millis();
  
  if (signal == LOW) {
    // HIGH duration
    if (duration >= 7 * TU) {
      decodedMessage += " ";
    } else if (duration >= 3 * TU) {
      decodedMessage += "_";
    }
  } else {
    if (duration < 2 * TU) {
      decodedMessage += ".";
    } else {
      decodedMessage += "-";
    }
  }
  signal = digitalRead(pin);
}
```

### Функции

#### Transmitter (передатчик)
1. **setup()** — настраивает пин передачи и готовит программу к отправке сообщений.
2. **dot() и dash()** — реализуют длительность сигналов для точки и тире.
3. **sendLetter()** — формирует сигнал для определенной буквы.
4. **sendMessage()** — отправляет строку сообщения.

#### Receiver (приемник)
1. **setup()** — настраивает входной пин и прерывание для обработки сигналов.
2. **loop()** — проверяет завершение передачи, выводит сообщение через Serial.
3. **signalChanged()** — обработка изменения сигналов (HIGH/LOW) для декодирования.


## Режимы работы
1. **Автоматический:**
   Передача заранее заданного сообщения с фиксированными интервалами.

2. **Ручной (опционально):**
   Сигналы можно передавать вручную через кнопку, подключенную к линии.


## Печатная плата (PCB)

### Особенности:
- **Размер:** 4x6 см (стандартная плата для прототипирования).
- **Компоненты:**
  * Ножки для подключения к Arduino UNO.
  * Светодиоды для отладки сигналов.
  * Переключатель для смены режимов.
  * Семисегментный индикатор для отображения сообщений.
  * Потенциометр для регулировки скорости передачи.
  * Сдвиговый регистр или драйвер индикатора для упрощения управления.
  * Контакты для ручной передачи сигналов.

### Схема расположения:


