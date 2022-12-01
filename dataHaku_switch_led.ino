#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>


#define DATA_PIN 4 // muuta
#define NUM_LEDS 8
#define BRIGHTNESS  64
#define LED_TYPE    WS2811 // muuta ehkä
#define COLOR_ORDER GRB
int MyArray[8] = {0, 1, 2, 3, 4, 5, 6, 7};
CRGB leds[NUM_LEDS];

int mySDA = 21;
int mySCL = 22;
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
int pin = 4;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

const char* ssid = "HHWLAN";
const char* password = "HHWLAN12345";

String response = "";

DynamicJsonDocument doc(2048);
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(pin, INPUT);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connect");
  Serial.println(WiFi.localIP());

  Serial.println ("Started.");
  lcd.setCursor(0, 0);
  lcd.print("Started.");
  delay(1000);
  
}




void dataHaku(void) {
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
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  //Close connection
  http.end();
  //Wait two seconds for data
  delay(60000);
}
void loop(void) {
  dataHaku();
  float  PriceWithTax = doc["PriceWithTax"];
  int Value = PriceWithTax * 100;
  int Arvo = doc["Rank"];

  Serial.println(Value);
  Serial.println(Arvo);
  Serial.println("testi");
  
  bool isDetected = digitalRead(pin);
  
  if (isDetected) {
    lcd.setCursor(0, 0);
    lcd.print(String("hinta ") + Value + " snt");
    lcd.setCursor(0,1);
    lcd.print(&timeinfo, "%H");

  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(String("hinta ") + Value + " snt");
    lcd.setCursor(0,1);
    lcd.print(&timeinfo, "%H");

  }
  delay(5000);
  int a = Arvo;
  switch (a) {
    case 1:
    case 2:
    case 3:
    case 4:
      Serial.println("testi1");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(0, 255, 0);
        FastLED.show();
      }
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      Serial.println("testi2");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(145, 233, 0);
        FastLED.show();
      }
      break;
    case 9:
    case 10:
    case 11:
    case 12:
      Serial.println("testi3");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(196, 186, 0);
        FastLED.show();
      }
      break;
    case 13:
    case 14:
    case 15:
    case 16:
      Serial.println("testi4");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(229, 145, 0);
        FastLED.show();
      }
      break;
    case 17:
    case 18:
    case 19:
    case 20:
      Serial.println("testi5");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(249, 96, 0);
        FastLED.show();
      }
      break;
    case 21:
    case 22:
    case 23:
    case 24:
      Serial.println("testi6");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(255, 0, 0);
        FastLED.show();
      }
      break;

  }

}
