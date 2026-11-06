const byte PIR_PIN = 2, BUTTON = 4, LED = 8, BUZZER = 9;
bool armed = false, lastButton = HIGH;
unsigned long lastToggle = 0;
void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}
void loop() {
  bool pressed = digitalRead(BUTTON);
  if (lastButton == HIGH && pressed == LOW &&
      millis() - lastToggle > 200) {
    armed = !armed;
    lastToggle = millis();
  }
  lastButton = pressed;
  bool motion = digitalRead(PIR_PIN) == HIGH;
  bool alarm = armed && motion;
  digitalWrite(LED, alarm ? HIGH : LOW);
  if (alarm) tone(BUZZER, 1000); else noTone(BUZZER);
}
