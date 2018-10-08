#include <Arial14.h>
#include <Arial16.h>
#include <ArialBold16.h>
#include <Arial_black_16.h>
#include <Arial_Black_16_ISO_8859_1.h>
#include <DMD.h>
#include <SystemFont5x7.h>

#include <TimerOne.h>
#include <Wire.h>

DMD dmd(2, 1);

void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Serial.begin(9600);           /* start serial for debug */
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
}

void loop() {
  delay(100);
  //Serial.println("YOKOHAMA");
  //  int buff = dis.length() + 1;
  //  char msg[buff];
  //  dis.toCharArray(msg, buff);
  //  dmd.clearScreen(true);
  //  dmd.selectFont(Arial_Black_16);
  //  dmd.drawString(1, 1, msg, buff, GRAPHICS_NORMAL);
  //  delay(5000);
}
// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  String textInput;
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    textInput += c;
  }
  Timer1.initialize(5000);
  Timer1.attachInterrupt( ScanDMD );
  delay(1000);
  dmd.clearScreen(true);
  int buff = howMany + 1;
  char msg[buff];
  textInput.toCharArray(msg, buff);
  dmd.clearScreen(true);
  dmd.selectFont(ArialBold_16);
//  dmd.drawChar(  1,  1, msg[0], GRAPHICS_NORMAL );
//  dmd.drawChar(  12,  1, msg[1], GRAPHICS_NORMAL );
//  dmd.drawChar(  23,  1, msg[2], GRAPHICS_NORMAL );
//  dmd.drawChar(  34,  1, msg[3], GRAPHICS_NORMAL );
//  dmd.drawChar(  45,  1, msg[4], GRAPHICS_NORMAL );
//  dmd.drawChar(  56,  1, msg[5], GRAPHICS_NORMAL );
//  
//  dmd.drawChar(  65,  1, msg[0], GRAPHICS_NORMAL );
//  dmd.drawChar(  76,  1, msg[1], GRAPHICS_NORMAL );
//  dmd.drawChar(  87,  1, msg[2], GRAPHICS_NORMAL );
//  dmd.drawChar(  98,  1, msg[3], GRAPHICS_NORMAL );
//  dmd.drawChar(  109,  1, msg[4], GRAPHICS_NORMAL );
//  dmd.drawChar(  110,  1, msg[5], GRAPHICS_NORMAL );
//  dmd.drawChar( 17,  1, '4', GRAPHICS_NORMAL );
//  dmd.drawChar( 25,  1, '5', GRAPHICS_NORMAL );
  //  dmd.selectFont(Arial_Black_16);
  dmd.drawString(1, 1, msg, buff, GRAPHICS_NORMAL);
  Serial.println(textInput);
  Serial.println(buff);
  //textInput = String();
}

// function that executes whenever data is requested from master
//void requestEvent() {
//  Wire.write("Hello NodeMCU");  /*send string on request */
//}

//void display() {
//  Serial.println("Display: " + textInput);
//  int buff = textInput.length() + 1;
//  char msg[buff];
//  textInput.toCharArray(msg, buff);
//  dmd.clearScreen(true);
//  dmd.selectFont(Arial_Black_16);
//  dmd.drawString(1, 1, msg, buff, GRAPHICS_NORMAL);
//  delay(5000);
//}

