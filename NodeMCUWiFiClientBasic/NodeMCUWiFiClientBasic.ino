/*
    This sketch sends a message to a TCP server

*/
#include <Wire.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Wire.begin(D1, D2);
  delay(10);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("YTMT_Guest", "038627199");

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFi.status() != WL_CONNECTED) {
  //while (WiFiMulti.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}

void loop() {
  delay(100);
  clientConnect();
}

// void loop() {
//   const uint16_t port = 80;
//   const char * host = "portal.ytmt.co.th"; // ip or dns



//   Serial.print("connecting to ");
//   Serial.println(host);

//   // Use WiFiClient class to create TCP connections
//   WiFiClient client;

//   if (!client.connect(host, port)) {
//     Serial.println("connection failed");
//     Serial.println("wait 5 sec...");
//     delay(5000);
//     return;
//   }

//   // This will send the request to the server
//   client.println("Send this data to server");

//   //read back one line from server
//   String line = client.readStringUntil('\r');
//   Serial.println(line);

//   Serial.println("closing connection");
//   client.stop();

//   Serial.println("wait 5 sec...");
//   delay(5000);
// }

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
            const char* tbm = getarray[i]["TBM"].as<char *>();
            const char* art_no = getarray[i]["ART_NO"].as<char *>();
            String _art = art_no;
            // Serial.println(getarray[i]["GT_STOCK"].as<char *>());
            const char* GTStock = getarray[i]["GT_STOCK"].as<char *>();
            String _gt = GTStock;
            
            Wire.beginTransmission(8);
            Wire.write(tbm);
            Serial.println(tbm);
            //SoftSerial1.print(art_no);
            Wire.endTransmission();
            delay(10000);

            Wire.beginTransmission(8);
            Wire.write(art_no);
            Serial.println(art_no);
            //SoftSerial1.print(art_no);
            Wire.endTransmission();
            delay(10000);

            Wire.beginTransmission(8);
            Wire.write(GTStock);
            Serial.println(GTStock);
            //SoftSerial1.print(art_no);
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