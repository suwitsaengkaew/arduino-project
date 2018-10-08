#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
// SoftwareSerial SoftSerial1(0 ,2);
const char *ssid = "YTMT_Guest";
const char *password = "038627199";

String url = "http://portal.ytmt.co.th/productionService/ProService.asmx/GreenStockPC?mc=P130";

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  // SoftSerial1.begin(115200);
  delay(100);
  Wire.begin(D1, D2);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop()
{
  delay(100);
  //++value;
  clientConnect();
}

void clientConnect()
{

  if ((WiFiMulti.run() == WL_CONNECTED))
  {

    HTTPClient http;
    http.begin("http://portal.ytmt.co.th/productionService/ProService.asmx/GreenStockPC?mc=P130"); //HTTP

    int httpCode = http.GET();
    if (httpCode > 0)
    {

      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        const size_t bufferSize = payload.length();

        if (payload.length() > 0)
        {
          DynamicJsonBuffer buff(bufferSize);
          JsonArray &getarray = buff.parseArray(payload);
          const int arraySize = getarray.size();
          for (int i = 0; i < arraySize; i++)
          {
            // Serial.println(getarray[i]["TBM"].as<char *>());
            const char *tbm = getarray[i]["TBM"].as<char *>();
            const char *art_no = getarray[i]["ART_NO"].as<char *>();
            String _art = art_no;
            // Serial.println(getarray[i]["GT_STOCK"].as<char *>());
            const char *GTStock = getarray[i]["GT_STOCK"].as<char *>();
            String _gt = GTStock;

            Wire.beginTransmission(8);
            Wire.write(tbm);
            Serial.println(tbm);
            Wire.endTransmission();
            Wire.beginTransmission(9);
            Wire.write(tbm);
            Serial.println(tbm);
            Wire.endTransmission();
            delay(10000);
            
            Wire.beginTransmission(8);
            Wire.write(art_no);
            Serial.println(art_no);
            Wire.endTransmission();
            Wire.beginTransmission(9);
            Wire.write(art_no);
            Serial.println(art_no);
            Wire.endTransmission();
            delay(10000);
            
            Wire.beginTransmission(8);
            Wire.write(GTStock);
            Serial.println(GTStock);
            Wire.endTransmission();
            Wire.beginTransmission(9);
            Wire.write(GTStock);
            Serial.println(GTStock);
            Wire.endTransmission();
            delay(10000);
            
          }
        }
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}