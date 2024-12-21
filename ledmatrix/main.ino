#define PIN_LED_3 3 
#define PIN_LED_5 5 
#define PIN_LED_6 6 
#define PIN_LED_9 9 

String inputText; 
String ledState; 

void pause(unsigned long duration) { 
  unsigned long previousMillis = millis(); 
  while (millis() - previousMillis < duration) { 
 
  } 
}

void parser(String ledState) { 
  String val1 = ledState.substring(0, 4); 
  String val2 = ledState.substring(4, 8);

  Serial.print("S1: "); 
  Serial.println(val1); 
  Serial.print("S2: "); 
  Serial.println(val2); 

  digitalWrite(PIN_LED_3, (val1[0] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_5, (val1[1] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_6, (val1[2] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_9, (val1[3] == '1') ? HIGH : LOW); 
  pause(500); 

  digitalWrite(PIN_LED_3, (val2[0] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_5, (val2[1] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_6, (val2[2] == '1') ? HIGH : LOW); 
  digitalWrite(PIN_LED_9, (val2[3] == '1') ? HIGH : LOW); 
  pause(500); 
}

String getBinaryState(String input) { 
  if (input == "off") return "00000000"; 
  if (input == "on") return "11111111";
  if (input == "1") return "10010000"; 
  if (input == "2") return "10100000"; 
  if (input == "3") return "01010000"; 
  if (input == "4") return "01100000"; 
  if (input == "1,2") return "10000000"; 
  if (input == "2,4") return "11100000"; 
  if (input == "3,4") return "01000000"; 
  if (input == "1,3") return "11010000"; 
  if (input == "1,4") return "10010110"; 
  if (input == "2,3") return "10100101"; 
  if (input == "1,2,4") return "10000110"; 
  if (input == "2,3,4") return "10100100"; 
  if (input == "1,3,4") return "01001001"; 
  if (input == "1,2,3") return "10000101"; 

  // Обрабатываем сложные комбинации, такие как "4,1,2"
  String binaryState = "00000000"; 
  if (input.indexOf("1") >= 0) binaryState[0] = '1'; 
  if (input.indexOf("2") >= 0) binaryState[1] = '1'; 
  if (input.indexOf("3") >= 0) binaryState[2] = '1';
  if (input.indexOf("4") >= 0) binaryState[3] = '1'; 
  
  return binaryState;  
}

void setup() { 
  Serial.begin(9600); 
  Serial.println("Введите, какие пины необходимо включить (например, 1,3,4):"); 

  pinMode(PIN_LED_3, OUTPUT); 
  pinMode(PIN_LED_5, OUTPUT); 
  pinMode(PIN_LED_6, OUTPUT); 
  pinMode(PIN_LED_9, OUTPUT); 
}

void loop() { 
  if (Serial.available() > 0) { 
    inputText = Serial.readStringUntil('\n'); 
    ledState = getBinaryState(inputText); 

    Serial.print("Получен ввод: "); 
    Serial.println(inputText); 
    Serial.print("Бинарное состояние: "); 
    Serial.println(ledState);

    if (ledState != "") { 
      parser(ledState); 
    } else { 
      Serial.println("Ошибка: Неверный ввод."); 
    } 
  } 
}
