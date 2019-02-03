/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: Common-Cathode RGB LED wired like so:
  - red anode: digital pin 3
  - green anode: digital pin 5
  - blue anode: digital pin 6
  - cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi

  This example code is in the public domain.
*/
#include <SoftwareSerial.h>

SoftwareSerial swSer(5, 4 );
// pins for the LEDs:
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  swSer.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt();
    // do it again:
    int green = Serial.parseInt();
    // do it again:
    int blue = Serial.parseInt();

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      /*  red = 255 - constrain(red, 0, 255);
        green = 255 - constrain(green, 0, 255);
        blue = 255 - constrain(blue, 0, 255);*/
      constrain(red, 0, 255);

      // fade the red, green, and blue legs of the LED:
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      // print the three numbers in one string as hexadecimal:
      
      Serial.print(red);
      Serial.print(",");
      Serial.print(green);
      Serial.print(",");
      Serial.println(blue);
      swSer.write(254);
      swSer.write(128);

      // clear display by sending spaces
      swSer.write("                ");
      swSer.write("                ");

      // move cursor to beginning of first line
      swSer.write(254);
      swSer.write(128);

      swSer.write(" Connecting to  Dark Sky ");
      delay(200);

      swSer.write(254);
      swSer.write(128);

      // clear display by sending spaces
      swSer.write("                ");
      swSer.write("                ");

      // move cursor to beginning of first line
      swSer.write(254);
      swSer.write(128);
      swSer.write("temp= ");
      swSer.print(red);
      swSer.write(" , ");
      swSer.write(254);
      swSer.write(192);
      swSer.write("humidity=");
      swSer.print(blue);
      swSer.print("  ");     
      swSer.print(green);

    }
  }
}
