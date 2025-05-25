#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64, &Wire, OLED_ADDRESS);

const char* ssid = "iphone";        
const char* password = "qwertyui"; 

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(28, 20);
  display.println("Connecting...");
  display.display();

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  display.clearDisplay();
  display.setCursor(20, 20);
  display.println("Connected!");
  display.setCursor(20, 40);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);


  display.clearDisplay();

  displayEmotion();
}

void loop() {
 
}

void displayEmotion() {

  int randomNum = random(1, 6);  

  if (randomNum == 1) {
    regEyes();
  } else if (randomNum == 2) {
    heart();
  } else if (randomNum == 3) {
    carrotEyes();
  } else if (randomNum == 4) {
    sideEye();
  } else if (randomNum == 5) {
    sideEye();  
  }
}

void regEyes() {
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);
  display.display();
  delay(2000);
}

void heart() {
  display.clearDisplay();
  int x1 = 44;
  int y1 = 27;
  int radius1 = 10;
  display.fillTriangle(x1 - radius1, y1, x1, y1 + radius1, x1 + radius1, y1, WHITE);
  display.fillCircle(x1 - 5, y1, 5.5, WHITE);
  display.fillCircle(x1 + 5, y1, 5.5, WHITE);
  
  int x2 = 84;
  int y2 = 27;
  int radius2 = 10;
  display.fillTriangle(x2 - radius2, y2, x2, y2 + radius2, x2 + radius2, y2, WHITE);
  display.fillCircle(x2 - 5, y2, 5.5, WHITE);
  display.fillCircle(x2 + 5, y2, 5.5, WHITE);
  
  display.fillCircle(64, 50, 12, WHITE);
  display.fillRect(0, 38, 128, 12, BLACK);  
  display.display();
  delay(2000);
}

void carrotEyes() {
  display.clearDisplay();
  int centerX = 42;
  int centerY = 32;
  int lineLength = 10;
  display.drawLine(centerX - lineLength, centerY + lineLength, centerX, centerY - lineLength, WHITE);
  display.drawLine(centerX, centerY - lineLength, centerX + lineLength, centerY + lineLength, WHITE);

  int centerXl = 90;
  int centerYl = 32;
  display.drawLine(centerXl - lineLength, centerYl + lineLength, centerXl, centerYl - lineLength, WHITE);
  display.drawLine(centerXl, centerYl - lineLength, centerXl + lineLength, centerYl + lineLength, WHITE);
  
  display.fillCircle(64, 50, 12, WHITE);
  display.fillRect(0, 38, 128, 12, BLACK);
  display.display();
  delay(2000);
}



void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(28, 20);
  display.println("STRAZZ");
  display.setCursor(35, 40);
  display.println("TUNED");
  display.display();
  delay(2000);
  display.clearDisplay();
  sleep();
  wakeUp();
}


void sleep() {
  display.clearDisplay();
  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 45, 32, 8, WHITE);
  display.fillCircle(48, 48, 3, WHITE);
  display.fillCircle(80, 48, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();


  //yawn
  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  display.fillCircle(64, 50, 8, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 45, 32, 8, WHITE);
  display.fillCircle(48, 48, 3, WHITE);
  display.fillCircle(80, 48, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();
  //yawn
  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  display.fillCircle(64, 50, 8, WHITE);
  display.display();
  delay(2000);
}

void wakeUp() {
  display.clearDisplay();
  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //left wink
  display.fillCircle(46, 32, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(2000);
  display.clearDisplay();

  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(1000);
  display.clearDisplay();

  //right wink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);


  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

  //blink
  display.fillRect(36, 28, 20, 8, WHITE);
  display.fillRect(76, 28, 20, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(1000);
  display.clearDisplay();

  // eyes
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //blink
  display.fillRect(36, 28, 20, 4, WHITE);
  display.fillRect(76, 28, 20, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(50);

// eyes
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(1000);
  display.clearDisplay();


  //blink
  display.fillRect(44, 28, 10, 4, WHITE);
  display.fillRect(76, 28, 10, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(50);
}

void regEyes() {  
  // eyes
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //blink
  display.fillRect(44, 28, 10, 4, WHITE);
  display.fillRect(76, 28, 10, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(100);

  //open
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  //blink
  display.fillRect(44, 28, 10, 4, WHITE);
  display.fillRect(76, 28, 10, 4, WHITE);
  display.display();
  delay(100);
}

void sideEye() {
  // eyes
  display.clearDisplay();
  display.fillCircle(48, 32, 8, WHITE);
  display.fillCircle(80, 32, 8, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();
  //blink
  display.fillRect(32, 28, 10, 4, WHITE);
  display.fillRect(96, 28, 10, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(100);
  display.clearDisplay();

  //side eye
  display.fillCircle(32, 32, 8, WHITE);
  display.fillCircle(96, 32, 8, WHITE);

  //mouth
  display.fillRect(32, 55, 64, 8, WHITE);
  display.fillCircle(32, 58, 3, WHITE);
  display.fillCircle(96, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //blink
  display.fillRect(32, 28, 10, 4, WHITE);
  display.fillRect(96, 28, 10, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(100);
  display.clearDisplay();

  //side eye
  display.fillCircle(32, 32, 8, WHITE);
  display.fillCircle(96, 32, 8, WHITE);

  //mouth
  display.fillRect(32, 55, 64, 8, WHITE);
  display.fillCircle(32, 58, 3, WHITE);
  display.fillCircle(96, 58, 3, WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();

  //blink
  display.fillRect(32, 28, 10, 4, WHITE);
  display.fillRect(96, 28, 10, 4, WHITE);

  //small mouth
  display.fillRect(48, 55, 32, 8, WHITE);
  display.fillCircle(48, 58, 3, WHITE);
  display.fillCircle(80, 58, 3, WHITE);

  display.display();
  delay(100);
  display.clearDisplay();
}


