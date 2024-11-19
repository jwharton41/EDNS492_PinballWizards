//#include <PBWire.h>
#include <FastLED.h>
#include <Wire.h>
#define DATA_PIN 13
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];
/*

 * The arduino takes   receives a number over I2C and displays
 * it on the pinScore 7 digit display.
   * 
 * Wiring connections
 * ------------------
 * With the pinscore display   facing you and '20' on the left
 * with 'J1' on the right, pin 1 is the leftmost   pin
 * 
 * Pin    Arduino Connection
 * 1      +5V
 * 2      8           |    A 4 bit message is sent via this
 * 3      9           |   connection so need   to use port
 * 4      10          |   manipulation to set the output
 * 5       11          |   simultaneously
 * 6      12
 * 7      No Pin
 * 8       Gnd
 * 9      Not Connected
 * 10     A0
 * 11     Not Connected
   * 12     2
 * 13     3
 * 14     4
 * 15     5
 * 16     6
 * 17      7
 * 18     Not Connected
 * 19     Not Connected
 * 20     Not Connected
   * 
 * I2C - arduino needs A4 & A5 connected to the same pins
 * on master   arduino
 * 
 */

//structure to map a pin to a digit for display
struct   pinScore {
  int8_t pin;
  int8_t digit;
};

//array to hold the   7 pins and digits
pinScore scoreMap[9];
  
void setup() {
  Serial.begin(9600);
  
  //Map the   pins to the digits on the pinscore
  scoreMap[0].pin = 7;//Analogue pin for highest   order digit
  scoreMap[1].pin = 6;
  scoreMap[2].pin = 5;
  scoreMap[3].pin   = 4;
  scoreMap[4].pin = 3;
  scoreMap[5].pin = 2;
  scoreMap[6].pin =   14;
  
  //set the pins to output
  for(int x = 0; x <7; x++){
    pinMode(scoreMap[x].pin,   OUTPUT);
    scoreMap[x].digit = 2;//initialise the score to 1234567
  }
     
  //set port B pins to output
  DDRB = B00111111 | DDRB; //set to output   apart from osc pins

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 

  for(int x = 0; x <7; x++){
    pinMode(scoreMap[x].pin,   OUTPUT);
    scoreMap[x].digit = x;//initialise the score to 1234567
  }
  /*cycles to constantly refresh   the pinscore using the current
  score saved in scoreMap*/
  
  for(int   x = 0; x < 7; x++){
    //set all the digit id pins to low
    for(int y =   0; y < 7; y++){
      digitalWrite(scoreMap[y].pin,LOW);
    }
    //set   the pin for the current digit to high
    digitalWrite(scoreMap[x].pin,HIGH);
     //send the 4 bit integer to pinscore
    PORTB = scoreMap[x].digit;
    //write   high to set the message
    digitalWrite(12,HIGH);
    //delay
   }
  
  /*if(counter == 9999999L){
    counter = 0;
  }else{
    counter++;
   }
  mapScore(counter);
  */  

    // Set all LEDs to red
  /*fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  // Set all LEDs to green
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  // Set all LEDs to blue
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
*/
}

//takes in an unsigned long over   I2C and populates the scoring array 
//with the new number.
/*void mapScore(unsigned   long score){
  unsigned long sumScore=0;
  //extract the digits from the number   and populate the scoring array
  for(int x = 0; x < 7; x++){
    if(score>0){
       int mod;
      mod = score % 10; // take the lowest order digit
      scoreMap[x].digit   = mod; //copy it to the map
      score = (score-mod)/10; //move all the digits   1 to the left
    }else{
      scoreMap[x].digit = 15;//will display nothing
     }
  }
}
*/



