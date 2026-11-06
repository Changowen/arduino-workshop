#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASSWORD";
const byte LIGHT_PIN = 34, LED_PIN = 18;
WebServer server(80);
int sensorValue = 0;
unsigned long lastRead = 0;
void handleData() {
  String json = String("{"light":") + sensorValue + "}";
  server.send(200, "application/json; charset=utf-8", json);
}
void handleHome() {
  server.send(200, "text/html; charset=utf-8",
    "<meta charset='utf-8'><h1>ESP32 Light Station</h1>"
    "<p>Open <a href='/data'>/data</a> to read JSON</p>");
}
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogReadResolution(12);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(300);
  Serial.print("Open http://");
  Serial.println(WiFi.localIP());
  server.on("/", handleHome);
  server.on("/data", handleData);
  server.begin();
}
void loop() {
  server.handleClient();
  if (millis() - lastRead >= 500) {
    lastRead = millis();
    sensorValue = analogRead(LIGHT_PIN);
    digitalWrite(LED_PIN, sensorValue < 1500 ? HIGH : LOW);
  }
}
