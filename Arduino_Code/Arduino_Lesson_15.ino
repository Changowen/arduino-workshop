#include <SPI.h>
#include <SD.h>
const byte CS_PIN = 10, TEMP_PIN = A0;
unsigned long lastSave = 0;
void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD init failed");
    while (true) { delay(100); }
  }
  if (!SD.exists("DATA.CSV")) {
    File f = SD.open("DATA.CSV", FILE_WRITE);
    if (f) { f.println("time_s,temp_c"); f.close(); }
  }
}
void loop() {
  unsigned long now = millis();
  if (now - lastSave >= 5000UL) {
    lastSave = now;
    int raw = analogRead(TEMP_PIN);
    float tempC = raw * (5.0f / 1023.0f) * 100.0f;
    File f = SD.open("DATA.CSV", FILE_WRITE);
    if (f) {
      f.print(now / 1000.0f, 1); f.print(',');
      f.println(tempC, 1); f.close();
      Serial.println("Saved");
    } else Serial.println("Write failed");
  }
}
