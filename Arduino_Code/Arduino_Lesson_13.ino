#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;) { delay(100); }
  }
}
void loop() {
  int raw = analogRead(A0);
  int width = map(raw, 0, 1023, 0, 116);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0); oled.println(F("Arduino UNO"));
  oled.setCursor(0, 20); oled.print(F("A0 = "));
  oled.println(raw);
  oled.drawRect(5, 44, 118, 13, SSD1306_WHITE);
  oled.fillRect(6, 45, width, 11, SSD1306_WHITE);
  oled.display();
  delay(100);
}
