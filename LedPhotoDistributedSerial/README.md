# **LedPhotoDistributedSerial**
---
**Описание**  
Программа управляет освещением, используя данные от датчика освещенности. Микроконтроллеры для светодиода и датчика работают независимо, обмениваясь данными через ПК. ПК принимает решения о включении или выключении светодиода на основе показаний датчика освещенности.

**Ссылка на видео с демонстрацией работы:**
https://drive.google.com/file/d/11yrALaXOpBnSX-uT215-scJ62RjiczGw/view?usp=sharing


### **Возможности**
1. **Получение данных освещенности:**  
   Программа непрерывно считывает данные с датчика освещенности в реальном времени.
   
2. **Управление светодиодом:**  
   - **Включение:** Если уровень освещенности ниже заданного порога.  
   - **Выключение:** Если уровень освещенности превышает заданный порог.  

3. **Оптимизированная передача данных:**  
   Считываемое значение делится на 4 и отправляется как байт для экономии трафика.

   ### Используемые команды  

- `'p'` — Запрос значения освещённости с микроконтроллера-датчика.  
- `'u'` — Включение светодиода.  
- `'d'` — Выключение светодиода.  
- `'b'` — Включение мигания светодиода (используется только в `led_bub.ino`).  

### Основная логика работы системы  

1. **Микроконтроллер с датчиком освещённости** (`photo_sensor.ino`):  
   - Принимает команду `'p'` и возвращает текущее значение освещённости (сжатое до 1 байта).  

2. **Скрипт Python** (`main.py`):  
   - Читает значение освещённости с микроконтроллера.  
   - Сравнивает его с порогом освещённости.  
   - Отправляет команды на другой микроконтроллер для управления светодиодом.  

3. **Микроконтроллер со светодиодом** (`led_bub.ino`):  
   - Принимает команды `'u'` и `'d'`, чтобы включить или выключить светодиод.  

### **Описание прошивки для Arduino**

#### **Функционал:**
1. **Датчик освещенности:**
   - Команда `'p'` заставляет микроконтроллер считать данные с аналогового пина (A0).  
   - Считываемое значение делится на 4 и передается как байт.  

2. **Светодиод:**
   - Команда `'u'` включает светодиод (пин 13).  
   - Команда `'d'` выключает светодиод.

#### **Функционал:**
1. **Получение данных освещенности:**  
   - Отправляет команду `'p'` микроконтроллеру с датчиком.  
   - Полученные данные преобразуются обратно в значение (умножаются на 4).  

2. **Управление светодиодом:**  
   - Если значение освещенности ниже порога, отправляется команда `'u'`.  
   - Если значение выше порога, отправляется команда `'d'`.

### **Аппаратная конфигурация**  
- **Светодиод:**  
  - Подключен к пину 13 на Arduino.  
  - Катод подключен к GND через резистор (5 кОм).  

- **Датчик освещенности (фоторезистор):**  
  - Подключен к пину A0 на Arduino.  
  - Соединен с GND через резистор (5 кОм).  

### **Работа программы:**
1. Программа устанавливает связь через COM-порты с микроконтроллерами.  
2. В цикле считываются данные с датчика освещенности.  
3. Данные сравниваются с пороговым значением.  
4. Отправляются команды для управления светодиодом.  

---

### **Использование**
1. Подключите светодиод и датчик освещенности к Arduino.  
2. Загрузите соответствующие прошивки.  
3. Запустите Python-скрипт с указанием правильных COM-портов.  
 

---

### Файл `led_bub.ino` — управление светодиодом  

Этот файл отвечает за управление светодиодом на основе команд, полученных по последовательному порту.  

#### Описание функций:  

- **`update_state()`**:  
  - Считывает команды из последовательного порта (Serial) и обновляет текущее состояние.  
  - Поддерживаемые команды:  
    - `'u'` — Включить светодиод.  
    - `'d'` — Выключить светодиод.  
    - `'b'` — Включить мигание светодиода.  

- **`process_state()`**:  
  - Выполняет действия в зависимости от текущего состояния:  
    - Включает светодиод (`STATE_LED_ON`).  
    - Выключает светодиод (`STATE_LED_OFF`).  
    - Организует мигание светодиода (`STATE_LED_BLINK`) с интервалом, заданным `BLINK_INTERVAL`.  

- **`setup()`**:  
  - Инициализирует последовательный порт (Serial) и задаёт пин светодиода как выходной.  

- **`loop()`**:  
  - Основной цикл программы:  
    - Сначала обновляет состояние на основе входящих команд (`update_state`).  
    - Затем выполняет соответствующее действие на основе состояния (`process_state`).  

#### Некоторые моменты по коду:  
- Используются три состояния: включение, выключение и мигание светодиода.  
- Включение/выключение реализуется с использованием функций `digitalWrite` и соответствующих значений HIGH/LOW.  
- Для мигания используется функция `millis()`, чтобы обеспечить стабильные временные интервалы.  

---

### Файл `photo_sensor.ino` — считывание данных с датчика освещённости  

Этот файл управляет датчиком освещённости и отправляет данные в сжатом виде по последовательному порту.  

#### Описание функций:  

- **`setup()`**:  
  - Инициализирует последовательный порт (Serial).  
  - Настраивает пин датчика освещённости как входной.  

- **`loop()`**:  
  - Проверяет, есть ли команда на чтение (`'p'`) в последовательном порту.  
  - Считывает значение с аналогового пина.  
  - Делит значение на 4, чтобы привести диапазон к 0–255 (1 байт).  
  - Отправляет сжатое значение обратно через `Serial.write()`.  

---

### Файл `main.py` — управляющий скрипт  

Этот скрипт обрабатывает данные от датчика освещённости и управляет светодиодом, подключённым к другому микроконтроллеру.  

#### Описание функций:  

- **`send_command(connection, command, response_length=0)`**:  
  - Отправляет команду по последовательному порту.  
  - Возвращает ответ, если указан `response_length` (например, для команды `'p'`).  

- **`main()`**:  
  - Основной цикл:  
    1. Отправляет команду `'p'` микроконтроллеру с датчиком, чтобы получить данные освещённости.  
    2. Преобразует полученное значение из байта в диапазон 0–1023 (умножением на 4).  
    3. Сравнивает значение с порогом `LIGHT_THRESHOLD`:  
       - Если значение превышает порог, отправляет команду `'u'` (включение светодиода).  
       - Если значение ниже порога, отправляет команду `'d'` (выключение светодиода).  
    4. Добавляет задержку 0.1 секунды для стабильной работы.  
  - Обрабатывает исключение `KeyboardInterrupt` для корректного завершения программы.  

#### Некоторые моменты по коду:  
- Использует библиотеку `pyserial` для работы с последовательным портом.  
- Подключается к двум разным COM-портам для взаимодействия с микроконтроллерами.  
- Реализует логику управления светодиодом на основе данных освещённости.  

---


