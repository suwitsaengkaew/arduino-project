/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/
#include <ArduinoJson.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup()
{

  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("YTMT_Guest", "038627199");
}

void loop()
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED))
  {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://portal.ytmt.co.th/productionService/ProService.asmx/GreenStockPC?mc=P010"); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        const size_t bufferSize = payload.length();

        if (payload.length() > 0)
        {
          // StaticJsonBuffer<bufferSize> buff;
          DynamicJsonBuffer buff(bufferSize);
          // Create an empty array
          // JsonArray& array1 = buff.createArray();

          // Parse a JSON array
          JsonArray &getarray = buff.parseArray(payload);
          const int arraySize = getarray.size();
          for (int i = 0; i < arraySize; i++)
          {
            Serial.println(getarray[i]["TBM"].as<char *>());
            Serial.println(getarray[i]["ART_NO"].as<char *>());
            // Serial.println(getarray[i]["GT_STOCK"].as<char *>());
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

  delay(10000);
}
