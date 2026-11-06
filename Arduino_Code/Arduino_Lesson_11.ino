const byte LED_PIN = LED_BUILTIN;
const unsigned long blinkInterval = 300;
const unsigned long reportInterval = 1000;
unsigned long lastBlink = 0, lastReport = 0;
bool ledOn = false;
unsigned long loopCount = 0;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  unsigned long now = millis();
  loopCount++;
  if (now - lastBlink >= blinkInterval) {
    lastBlink = now;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn);
  }
  if (now - lastReport >= reportInterval) {
    lastReport = now;
    Serial.print("loops per second ~ ");
    Serial.println(loopCount);
    loopCount = 0;
  }
}
