#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
//Provide your own WiFi credentials
const char* ssid = "<Your WiFi SSID>";
const char* password = "<Your WiFi Password>";

const char* serverName = "https://api.fingrid.fi/v1/variable/74/event/json";

unsigned long lastTime = 0;

unsigned long timerDelay = 60000;
String luku;
 
 
void setup() {
  
  Serial.begin(115200);
  //Initiate WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
        jsondata = httpGETRequest(serverName);
        Serial.println(luku);
        JSONVar myObject = JSON.parse(luku);

        if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
    }
    lastTime = millis();
}
}
}
String httpGETRequest(const char* serverName)
  WiFiClient client;
  HttpClient;

Http.begin(client, serverName);

