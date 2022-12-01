#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>


#define DATA_PIN 4 // led valo
#define NUM_LEDS 8
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
int MyArray[8] = {0, 1, 2, 3, 4, 5, 6, 7}; //mnotako led valoa nauhassa on
CRGB leds[NUM_LEDS];

int mySDA = 21; // lcd näytön toimivuus
int mySCL = 22;
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
int pin = 4; //lcs näytön toimivuus

const char* ssid = "HHWLAN";    //wifi tunnus ja salasana
const char* password = "HHWLAN12345";

String response = "";  // koko API/JSON tiedosto tallennus

DynamicJsonDocument doc(2048); // API/JSON tiedosto
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //lcd näyttö
  pinMode(pin, INPUT);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password); // wifi yhteys
  Serial.println("Connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connect");
  Serial.println(WiFi.localIP());

  Serial.println ("Started."); // lcd näyttö
  lcd.setCursor(0, 0);
  lcd.print("Started.");
  delay(1000);

}




void dataHaku(void) {
  //Initiate HTTP client
  HTTPClient http; // tässä haetaan API/JSON
  //The API URL
  String request = "https://api.spot-hinta.fi/JustNow";
  //Start the request
  http.begin(request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response); // jotta voidaan käyttää JSON tiedostoa
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
  float  PriceWithTax = doc["PriceWithTax"]; // hinta haettuna JSON tiedostosta, joka haettiin yläpuolella olevassa koodissa
  int Value = PriceWithTax * 100; // hinta sentteinä
  int Arvo = doc["Rank"];

  Serial.println(Value);
  Serial.println(Arvo);
  Serial.println("testi");

  // hinnan tulostus LCD näyttöön
  bool isDetected = digitalRead(pin); 

  if (isDetected) {
    lcd.setCursor(0, 0);
    lcd.print(String("hinta ") + Value + " snt");
    lcd.setCursor(0, 1);
    lcd.print(&timeinfo, "%H");

  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(String("hinta ") + Value + " snt");
    lcd.setCursor(0, 1);
    lcd.print(&timeinfo, "%H");
    //hinnan tulostus LCD näyttöön
  }
  delay(5000);
  //LED valon muuttaminen riippuen hinnasta
  int a = Arvo;
  switch (a) {
    case 1:
    case 2:
    case 3:
    case 4: // pienimmät hinnat
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
    case 24: // suurimmat hinnat
      Serial.println("testi6");
      for (int i = 0; i < 8; i++) {
        leds[i] = CRGB(255, 0, 0);
        FastLED.show();
      }
      break;

  }

}
