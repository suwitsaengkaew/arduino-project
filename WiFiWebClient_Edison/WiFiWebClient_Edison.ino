
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>

char ssid[] = "YTMT_Guest"; // Editable
char pass[] = "038627199"; // Editable
int keyIndex = 0; // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char server[] = "localhost.localdomain"; //Editable

WiFiClient client;

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue:
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0")
    Serial.println("Please upgrade the firmware");
  // -----------------------------------------------------------------
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println(F("Connected to wifi"));
  printWifiStatus();
  // ----------------------------------------------------------------

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
}

void loop()
{
  clientConnect("/api/test");
  delay(5000);
  client.stop();
  
}

void clientConnect(String url)
{
  Serial.println(url);
  if (client.connect(server, 8080))
  {
    Serial.println("connected to server");
    // Make a HTTP request:
    // client.println("GET /search?q=arduino HTTP/1.1");
    // client.println("Host: www.google.com");
    Serial.println("GET " + url + " HTTP/1.1");
    client.println("GET " + url + " HTTP/1.1"); //Editable
    client.println("Host: localhost.localdomain"); //Editable
    client.println("Connection: close");
    // client.println();
    if (client.println() == 0)
    {
      Serial.println(F("Failed to send request"));
      return;
    }

    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0)
    {
      Serial.print(F("Unexpected response: "));
      Serial.println(status);
      return;
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders))
    {
      Serial.println(F("Invalid response"));
      return;
    }

    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(10) + 60;
    DynamicJsonBuffer jsonBuffer(capacity);

    // Parse JSON object
    JsonObject &root = jsonBuffer.parseObject(client);
    if (!root.success())
    {
      Serial.println(F("Parsing failed!"));
      return;
    }

    // Extract values
    Serial.println(F("Response:"));
    Serial.println(root["motor1"].as<char *>());
    Serial.println(root["motor2"].as<char *>());
    // Serial.println(root["time"].as<char *>());
    // Serial.println(root["data"][0].as<char *>());
    // Serial.println(root["data"][1].as<char *>());
    motor2 = root["motor2"].as<char *>();

    // Disconnect
    // client.stop();
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
