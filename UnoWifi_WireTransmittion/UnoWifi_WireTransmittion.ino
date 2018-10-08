#include <Arial14.h>
#include <Arial_black_16.h>
#include <Arial_Black_16_ISO_8859_1.h>
#include <DMD.h>
#include <SystemFont5x7.h>

#include <TimerOne.h>
#include <Wire.h>

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */

  Timer1.initialize(5000);
  Timer1.attachInterrupt( ScanDMD );

  dmd.clearScreen(true);
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  String inString;
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    // Serial.print(c);
    inString += c;
  }
  Serial.println(inString);            /* to newline */
  // Serial.println(howMany);
  int buff = howMany + 1;
  char msg[buff];
  inString.toCharArray(msg, buff);
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  dmd.drawString(1, 1, msg, buff, GRAPHICS_NORMAL);
  //dmd.clearScreen(false);
  inString = String();
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write("Hello NodeMCU");  /*send string on request */

}
