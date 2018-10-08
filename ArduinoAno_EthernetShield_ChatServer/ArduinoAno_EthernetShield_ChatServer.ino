/*
  Chat Server

  A simple server that distributes any incoming messages to all
  connected clients.  To use, telnet to your device's IP address and type.
  You can see the client's input in the serial monitor as well.
  Using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

*/

#include <SPI.h>
#include <Ethernet2.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0x16, 0xA9
};
IPAddress ip(10, 102, 4, 8);
IPAddress mydns(10, 102, 1, 21);
IPAddress gateway(10, 102, 4, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(10000);
boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip, mydns, gateway, subnet);
  // start listening for clients
  server.begin();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {

  checkForClient();

}

void checkForClient() {
  EthernetClient client = server.available();

  if (client) {
    Serial.println(client);
    client = false;
    Serial.println(client);
    if (!alreadyConnected) {

    } else {

    }

    if (client.available() > 0) {
      client.stop();
    } else {
      client.stop();
    }
  }
}

