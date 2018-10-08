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

EthernetClient clients;

boolean alreadyConnected = false;

void setup() {
  // initialize the Ethernet device
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
  // wait for a new client:
  EthernetClient client = server.available();
  
  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      client.println("reply from arduino");
 
      client.flush();  
      clients.stop();  
    }
  }
}
