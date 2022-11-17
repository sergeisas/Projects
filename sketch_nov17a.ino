
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

String response = "";
DynamicJsonDocument doc(2048);



void setup(){

WiFi.begin(ssid, password);
  Serial.begin(11520);
  Serial.println("Connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connect");
  Serial.println(WiFi.localIP());
}
  void loop(){
HTTPClient http;
String request = "https://api.spot-hinta.fi/JustNow";
http.begin(request);

http.GET();

response = http.getString();
DeserializationError error = deserializeJson(doc, response);
  if(error) {
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     return;

Serial.println(doc["PriceNoTax"].as<char*>());
http.end();

delay(600000);
  }
  }