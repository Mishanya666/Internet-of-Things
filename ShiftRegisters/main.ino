int latch = 5;       
int clk = 3;         
int data = 7;        

bool patterns[10][8] = {
  {0, 0, 1, 0, 0, 0, 1, 0},  // 0
  {1, 0, 1, 0, 1, 1, 1, 1},  // 1
  {0, 0, 1, 1, 0, 0, 0, 1},  // 2
  {0, 0, 1, 0, 0, 1, 0, 1},  // 3
  {1, 0, 1, 0, 1, 1, 0, 0},  // 4
  {0, 1, 0, 0, 0, 1, 0, 0},  // 5
  {0, 1, 0, 0, 0, 0, 0, 0},  // 6
  {0, 0, 1, 0, 1, 1, 1, 1},  // 7
  {0, 0, 1, 0, 0, 0, 0, 0},  // 8
  {0, 0, 1, 0, 0, 1, 0, 0}   // 9
};

int timeCounter = 0;

void initializePins() {
  pinMode(latch, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  Serial.begin(9600);
}

void updateDisplay(int number) {
  if (number < 0 || number > 9) return;
  digitalWrite(latch, LOW);
  for (int bit = 7; bit >= 0; bit--) {
    digitalWrite(clk, LOW);
    digitalWrite(data, patterns[number][bit]);
    digitalWrite(clk, HIGH);
  }
  digitalWrite(latch, HIGH);
}

void setup() {
  initializePins();
}

void loop() {
  updateDisplay(timeCounter / 10);
  delay(600); 
  updateDisplay(timeCounter % 10);
  delay(600);

  timeCounter = (timeCounter + 1) % 60;

  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input >= '0' && input <= '9') {
      timeCounter = input - '0';
    }
  }
}
