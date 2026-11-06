const byte BUTTON_PIN = 2;
volatile unsigned long pressCount = 0;
volatile unsigned long lastEdgeUs = 0;
const unsigned long DEBOUNCE_US = 50000UL;
unsigned long lastPrinted = 0;
void onPress() {
  unsigned long now = micros();
  if (now - lastEdgeUs >= DEBOUNCE_US) {
    pressCount++;
    lastEdgeUs = now;
  }
}
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onPress, FALLING);
}
void loop() {
  if (millis() - lastPrinted >= 250) {
    lastPrinted = millis();
    noInterrupts();
    unsigned long countCopy = pressCount;
    interrupts();
    Serial.print("Presses: ");
    Serial.println(countCopy);
  }
}
