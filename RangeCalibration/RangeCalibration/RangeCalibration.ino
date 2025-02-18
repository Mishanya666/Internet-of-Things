const int trigPin = 4;
const int echoPin = 3;
long duration;
float distance;
const int irSensorPin = A0;
int irValue;
const int ledPin = 13;  // Встроенный светодиод на пине 13

// Переменные для отслеживания состояния калибровки
int dataCount = 0;
int maxDataCount = 50;  // Максимальное количество данных для калибровки

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);  // Настроим светодиод на вывод

  digitalWrite(ledPin, LOW);  // Начальный статус светодиода (выключен)
}

void loop() {
  // Получаем данные с ультразвукового сенсора
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2; // Расстояние в см

  // Получаем данные с инфракрасного сенсора
  irValue = analogRead(irSensorPin);

  // Отправляем данные на ПК
  Serial.print(distance);
  Serial.print(",");
  Serial.println(irValue);

  // Увеличиваем количество собранных данных
  dataCount++;

  // Проверяем, достигли ли мы нужного количества данных
  if (dataCount >= maxDataCount) {
    // Если данные собраны, мигаем светодиодом
    blinkLED();
    dataCount = 0;  // Сбрасываем счетчик для нового сбора данных
  }

  delay(100);
}

// Функция для мигания светодиода
void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);  // Включаем светодиод
    delay(200);  // Задержка 200 мс
    digitalWrite(ledPin, LOW);   // Выключаем светодиод
    delay(200);  // Задержка 200 мс
  }
}
