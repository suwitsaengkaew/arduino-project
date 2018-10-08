//CREATED BY TZ

#include <SPI.h>
#include <Ethernet.h>

int led = 4;
int led2 = 3;
int led3 = 5;
int led4 = 6; 


int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 10, 102, 4, 251 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 10, 102, 4, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        if (readString.length() < 100) {
          
          readString += c;
          
         }

         
         if (c == '\n') {          
           Serial.println(readString); 
           //html file 
           client.println("HTTP/1.1 200 OK"); 
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<TITLE>TZ Projects</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>TZ</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>MY_ARDUINO_ROOM_1</H2>");
           client.println("<br />");  
           //BUTTON FOR FIRST LED
           client.println("<a href=\"/?button1on\"\">Turn On LED1</a>");
           client.println("<a href=\"/?button1off\"\">Turn Off LED1</a><br />");   
           //SPACES
           client.println("<br />");     
           client.println("<br />"); 
            //BUTTON SECOND LED
           client.println("<a href=\"/?button2on\"\">Turn On LED2</a>");
           client.println("<a href=\"/?button2off\"\">Turn Off LED2</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           //BUTTON THIRD LED
           client.println("<a href=\"/?button3on\"\">Turn On LED3</a>");
           client.println("<a href=\"/?button3off\"\">Turn Off LED3</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           //BUTTON FOURTH LED
           client.println("<a href=\"/?button4on\"\">Turn On LED4</a>");
           client.println("<a href=\"/?button4off\"\">Turn Off LED4</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
            
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, LOW);
           }



          if (readString.indexOf("?button2on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(led, LOW);
           }





            if (readString.indexOf("?button3on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(led, LOW);
           }





            if (readString.indexOf("?button4on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(led, LOW);
           }


           
            //clearing string for next read
            readString="";  
           
         }
       }
    }
}
}

