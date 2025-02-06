#define NROWS 3
#define NCOLS 3
#define SCAN_INTERVAL 10  

const int row_pins[NROWS] = {2, 3, 4};
const int col_pins[NCOLS] = {5, 6, 7};
bool btn_state[NROWS][NCOLS] = {false};
bool prev_btn_state[NROWS][NCOLS] = {false};
unsigned long press_start[NROWS][NCOLS] = {0};

unsigned long last_scan_time = 0;
int current_row = 0;

void check_buttons();
void report_button_states();

void setup() {
  for (int i = 0; i < NROWS; i++) {
    pinMode(row_pins[i], OUTPUT);
    digitalWrite(row_pins[i], HIGH);
  }
  for (int i = 0; i < NCOLS; i++) {
    pinMode(col_pins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - last_scan_time >= SCAN_INTERVAL) {
    last_scan_time = current_time;
    digitalWrite(row_pins[current_row], HIGH);
    current_row = (current_row + 1) % NROWS;
    digitalWrite(row_pins[current_row], LOW);
    check_buttons();
  }
}

void check_buttons() {
  for (int i = 0; i < NCOLS; i++) {
    btn_state[current_row][i] = !digitalRead(col_pins[i]);
    if (btn_state[current_row][i] != prev_btn_state[current_row][i]) {
      if (btn_state[current_row][i]) {
        press_start[current_row][i] = millis();
      } else {
        unsigned long press_duration = millis() - press_start[current_row][i];
        Serial.print("Button ");
        Serial.print(1 + i + NCOLS * current_row);
        Serial.print(" released, duration: ");
        Serial.print(press_duration);
        Serial.print(" ms, started at: ");
        Serial.println(press_start[current_row][i]);
      }
      prev_btn_state[current_row][i] = btn_state[current_row][i];
      report_button_states();
    }
  }
}

void report_button_states() {
  Serial.print("Pressed buttons: ");
  bool first = true;
  for (int r = 0; r < NROWS; r++) {
    for (int c = 0; c < NCOLS; c++) {
      if (btn_state[r][c]) {
        if (!first) Serial.print(", ");
        Serial.print(1 + c + NCOLS * r);
        first = false;
      }
    }
  }
  Serial.println();
}
