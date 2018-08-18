#include <ESP8266WiFi.h>

const char* ssid = "teste";
const char* password = "12345670";
void setup() {
    Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

}

void loop() {
  // put your main code here, to run repeatedly:

}
