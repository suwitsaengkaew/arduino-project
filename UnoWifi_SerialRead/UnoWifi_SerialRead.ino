#include <SoftwareSerial.h>
#include <Wire.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include "Arial14.h"


#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
// String inputString = "";
// SoftwareSerial SoftSerial1(2 ,3);
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup() {
  Wire.begin(9);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  // Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */


  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  
}

void loop() {
  delay(100);
  // String inputString = "";
  // if (SoftSerial1.available()) {
  //   inputString = SoftSerial1.readString();
  //   // Serial.println(inputString);
  //   DisplayLed(inputString);
  // }
  ledonoff();
}

void ledonoff() {
  Serial.println("Yokohama oop");
  delay(1000);
}

void DisplayLed(String a) {
  Serial.println(a + ", " + a.length());
  int howMany = a.length() + 1;
  char buf[howMany];
  a.toCharArray(buf, howMany);
  Serial.println(buf);
  dmd.clearScreen( true );
  dmd.selectFont(Arial_Black_16);
  dmd.drawString( 1, 1, buf, howMany, GRAPHICS_NORMAL );
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  String inputString = "";
  //while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);
    inputString += c;  
    // b[row] = c;
    // row++;
  //}
  // Serial.println(SoftSerial1.read());
  // while (0 < SoftSerial1.available()) {
    //char c = Wire.read();      /* receive byte as a character */
    // Serial.write(SoftSerial1.read());
    // inputString += c;  
    // b[row] = c;
    // row++;
  // }
  // Serial.println("Serial print: " + inputString);
  // int buff = inputString.length() + 1;
  // char b[buff]; int row = 0;
  // inputString.toCharArray(b, buff);
  // dmd.clearScreen( true );
  // dmd.selectFont(Arial_Black_16);
  // dmd.drawString( 1, 1, b, buff, GRAPHICS_NORMAL );
  // inputString = "";
  Serial.println("Yokohama");
  Serial.println(howMany);            
  //Serial.println("Row: " + row);
}

