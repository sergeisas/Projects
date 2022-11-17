#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "korvaa ssid";
const char* password = "password";

String  FinGridApi = "190dc6b44f7dc55965da6468dad72204";
String my_city = "Lahore";
String my_country_code = "PK";






unsigned long lastTime = 0;
unsigned long timerDelay = 600000;

String json_array;
void setup(){

WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("First set of readings will appear after 10 seconds");
}
void loop(){
    String server = "http://api.openweathermap.org/data/2.5/weather?q=" + my_city + "," + my_country_code + "&APPID" + FinGridApi; 
    json_array = GET_Request(server.c_str());
    Serial.println(json_array);
    JSONVar my_obj = JSON.parse(json_array);

    Serial.println(my_obj);
}
String GET_Request(const char*server){
    WiFiClient client;
    HttpClient;
    http.begin(server);
    int httpResponseCode = Http.get();

    String payload = "{}";

    if (httpResponseCode>0) {
            Serial.print("HTTP code");
            Serial.println(httpResponseCode);
            payload = http.getString();
    }
    else {
        Serial.print("Error");
        Serial.println(httpResponseCode);
    }
    http.end();
    return payload;
}


