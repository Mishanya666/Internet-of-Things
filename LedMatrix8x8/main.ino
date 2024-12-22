#define ROW_PIN_1 2  
#define ROW_PIN_2 3
#define ROW_PIN_3 4
#define ROW_PIN_4 5

#define COL_PIN_1 6 
#define COL_PIN_2 7
#define COL_PIN_3 8
#define COL_PIN_4 9

String ledMatrix[4][4] = {
    {"1", "0", "0", "1"},
    {"0", "1", "1", "0"},
    {"0", "1", "1", "0"},
    {"1", "0", "0", "1"}
};

unsigned long lastUpdateTime = 0;
int activeRow = 0;

void setup() {
  pinMode(ROW_PIN_1, OUTPUT);
  pinMode(ROW_PIN_2, OUTPUT);
  pinMode(ROW_PIN_3, OUTPUT);
  pinMode(ROW_PIN_4, OUTPUT);

  pinMode(COL_PIN_1, OUTPUT);
  pinMode(COL_PIN_2, OUTPUT);
  pinMode(COL_PIN_3, OUTPUT);
  pinMode(COL_PIN_4, OUTPUT);
}

void driveRow(String rowPattern, int rowIndex) {

  digitalWrite(ROW_PIN_1, rowIndex == 0 ? HIGH : LOW);
  digitalWrite(ROW_PIN_2, rowIndex == 1 ? HIGH : LOW);
  digitalWrite(ROW_PIN_3, rowIndex == 2 ? HIGH : LOW);
  digitalWrite(ROW_PIN_4, rowIndex == 3 ? HIGH : LOW);

  digitalWrite(COL_PIN_1, rowPattern[0] == '1' ? LOW : HIGH);
  digitalWrite(COL_PIN_2, rowPattern[1] == '1' ? LOW : HIGH);
  digitalWrite(COL_PIN_3, rowPattern[2] == '1' ? LOW : HIGH);
  digitalWrite(COL_PIN_4, rowPattern[3] == '1' ? LOW : HIGH);
}

void loop() {
  if (millis() - lastUpdateTime > 2) {
    String rowState = "";
    for (int i = 0; i < 4; i++) {
      rowState += ledMatrix[activeRow][i];
    }
    driveRow(rowState, activeRow); 
    activeRow = (activeRow + 1) % 4; 
    lastUpdateTime = millis();
  }
}

