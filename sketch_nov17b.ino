


#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>



const char* ssid = "DNA-WIFI-1E39";
const char* password = "gA5S38yC";



String response = "";

DynamicJsonDocument doc(2048);
void setup(){

WiFi.begin(ssid, password);
  Serial.begin(115200);
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










  void loop(void) {
  //Initiate HTTP client
  HTTPClient http;
  //The API URL
  String request = "https://api.spot-hinta.fi/JustNow";
  //Start the request
  http.begin(request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  if(error) {
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.f_str());
     return;
  }
  //Print parsed value on Serial Monitor
  Serial.println(doc["PriceNoTax"].as<double>());
  //Close connection  
  http.end();
  //Wait two seconds for next joke
  delay(2000);
}

 
 
