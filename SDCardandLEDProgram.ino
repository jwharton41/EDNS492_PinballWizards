// sd card
#include <SPI.h>
#include <SD.h>

//leds
#include <FastLED.h>
#define DATA_PIN     7
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

// sd card
File myFile;
int message;
int premessage;

void setup() {
  // reciver code
  Serial.begin(9600);

  //send code
  Serial.flush();
  Serial.flush();
  /*
  SD card read/write

    This example shows how to read and write data to and from an SD card file
    The circuit:
    SD card attached to SPI bus as follows:
  ** MOSI - pin 11
  ** MISO - pin 12
  ** sck - pin 13
  ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

    created   Nov 2010
    by David A. Mellis
    modified 9 Apr 2012
    by Tom Igoe

    This example code is in the public domain.

  */
  SD.begin(4); 
  
  //leds
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  //reciver code
  if(Serial.available()){
    message = Serial.read(); // read in the message
    if(message == 2){ // this is a kill code such that this ardunio doesn't flood the mega during game play
      delay(1);
    }
    if(message > 2) // the game is over and the score is given to us
      myFile = SD.open("Test.txt");
      if (myFile){ //open sd card and enter loop if succesfull
        while(myFile.available()){ //for all entries in sd
          if(myFile.read() > message ){ // if score is greater than a stored score
            myFile.println(message); // put it in the sd
          }
        }
      }

      // now we are in idle state and should read scores to display from sd
      if (myFile){ // open sd card and enter loop if succesfull
        while(myFile.available()){ // for all entries in sd
          Serial.write(myFile.read()); // send scores
          delay(3000);
        }

      }
    }

  //leds
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
}
