#define BUTTON_PIN 2 
#define BOUNCE_TIME 50
#define PRESSED HIGH


volatile long int press_time = 0;
volatile bool pressed_candidate = false;
volatile long int hold_time = 0;
volatile int press_count = 0;
volatile bool report_to_user = false;
bool button_pressed = false;


void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), process_button_click, RISING);
}

void loop() {
  if (report_to_user) {
    Serial.println("Press candidate");
    report_to_user = false;
  }

  if (pressed_candidate && (millis() - press_time) > BOUNCE_TIME) {
    if (digitalRead(BUTTON_PIN) == PRESSED) {
      press_count++;
      Serial.print("Real press detected. Press count: ");
      Serial.println(press_count);

      long int start_hold_time = millis();
      while (digitalRead(BUTTON_PIN) == PRESSED) {

      }
      hold_time = millis() - press_time;
      Serial.print("Button held for: ");
      Serial.print(hold_time);
      Serial.println(" ms");

      pressed_candidate = false; 
    } else {

      pressed_candidate = false;
    }
  }
}

void process_button_click() {
  if (!pressed_candidate) {
    press_time = millis();
    pressed_candidate = true;
    report_to_user = true;
  }
}
