#include <FastLED.h> // LED strip library declaration 
#define DATA_PIN 6
#define NUM_LEDS 10 
CRGB leds[NUM_LEDS]; // can change the numbers later if we have to

// 2-13, 22-53
int score = 0;
bool InPlay = false; // boolean if the game is in progress
int lives = 3;
// not sure where to put these booleans quite yet

// pin for start button
int startPin = 8;
int readStartPin = 0;

// Pins for Drop Target
int target1 = 2; // target 1
int target2 = 3; // target 2
int target3 = 4; // target 3
int col = 5; // col pin // col = 0 means the pins switch when a target drops
int dropTargetPin = 6; // pin to tell drop target coil to fire

// variables for drop target
int dropTargetCount = 0; // keep track of how many times drop target fires
int prevVal1.1 = 0;  // target 1 previous
int prevVal2.1 = 0; // target 2 previous
int prevVal3.1 = 0; // target 3 previous

int prevVal1.2 = 0;  // target 1 previous
int prevVal2.2 = 0; // target 2 previous
int prevVal3.2 = 0; // target 3 previous

int prevVal1.3 = 0;  // target 1 previous
int prevVal2.3 = 0; // target 2 previous
int prevVal3.3 = 0; // target 3 previous

int prevVal1.4 = 0;  // target 1 previous
int prevVal2.4 = 0; // target 2 previous
int prevVal3.4 = 0; // target 3 previous

int prevVal1.5 = 0;  // target 1 previous
int prevVal2.5 = 0; // target 2 previous
int prevVal3.5 = 0; // target 3 previous


int val1 = 0;  // target 1
int val2 = 0; // target 2
int val3 = 0; // target 3
int val4 = 0; // col pin

int count = 0; // count for refiring drop target

bool rsTriggered = false;
bool refireDropTarget = false;

// Pop Bumpers:
// Pop Bumper 1
int spoon1Pin = 28;    // spoon pin set to pin 28
int bumper1Pin = 29;  // pin to make coil fire set to 29
int pop1 = 50;      // variable to store the read value

// Pop Bumper 2
int spoon2Pin = 30;    // spoon pin set to pin 30
int bumper2Pin = 31;  // pin to make coil fire set to 31
int pop2 = 50;      // variable to store the read value

// Pop Bumper 3
int spoon3Pin = 32;    // spoon pin set to pin 32
int bumper3Pin = 33;  // pin to make coil fire set to 33
int pop3 = 50;      // variable to store the read value

// Pop Bumper 4
int spoon4Pin = 34;    // spoon pin set to pin 34
int bumper4Pin = 35;  // pin to make coil fire set to 35
int pop4 = 50;      // variable to store the read value

// Pop Bumper 5
int spoon5Pin = 36;    // spoon pin set to pin 36
int bumper5Pin = 37;  // pin to make coil fire set to 37
int pop5 = 50;      // variable to store the read value

// Rollover Switches:
// Rollover Switch 1
int rsc1 = 22;

// Rollover Switch 2
int rsc2 = 23;

// Rollover Switch 3
int rsc3 = 24;

// Rollover Switch 4
int rsc4 = 25;

// Rollover Switch 5
int rsc5 = 26;

// Rollover Switch 6
int rsc6 = 27;

// Rollover Switch 7
int rsc7 = 53;
// this switch is unique in that it resets the drop target and doesn't give any points

// Rollover Switch 10
int rsc10 = 40;

int rollover1 = 0;
int prevRoll1 = 0;
int rollover2 = 0;
int prevRoll2 = 0;
int rollover3 = 0;
int prevRoll3 = 0;
int rollover4 = 0;
int prevRoll4 = 0;
int rollover5 = 0;
int prevRoll5 = 0;
int rollover6 = 0;
int prevRoll6 = 0;
int rollover7 = 0;
int prevRoll7 = 0;
int rollover10 = 0;
int prevRoll10 = 0;

// Slingshots:
// Slingshot 1 

int slingshotSpoonPin1 = 48;   
int slingshotBumperPin1 = 49;
int slingshot1val = 0;      // variable to store the read valu0e
int slingshot1val2 = 0;

// Slingshot 2

int slingshotSpoonPin2 = 50;
int slingshotBumperPin2 = 51;
int slingshot2val = 0;      // variable to store the read valu0e
int slingshot2val2 = 0;

// state machine
enum actionType {IDLE, INPLAY, INGUTTER};
// declaration for each of the states for our state machine

actionType action = IDLE; // this is the starting state for our state machine

// enum dropTargetState {IDLETARGET, CANFIRE, FIRE}

// dropTargetState dtState = IDLETARGET;


void setup() {

  // setup for start button
  pinMode(startPin, INPUT_PULLUP);

  // setup for Drop Target
  pinMode(target1, INPUT); // target 1
  pinMode(target2, INPUT); // target 2
  pinMode(target3, INPUT); // target 3
  pinMode(col, INPUT); // col pin
  digitalWrite(col, LOW); // setting col to low so we read when a target falls
  pinMode(dropTargetPin, OUTPUT); // pin to tell coil to fire set as output

  // setup for Pop Bumpers
  // setup for Pop Bumper 1
  pinMode(spoon1Pin, INPUT_PULLUP);    // sets the digital pin 28 as input
  pinMode(bumper1Pin, OUTPUT); // sets digital pin 29 as output

  // setup for Pop Bumper 2
  pinMode(spoon2Pin, INPUT_PULLUP);    // sets the digital pin 30 as input
  pinMode(bumper2Pin, OUTPUT); // sets digital pin 31 as output

  // setup for Pop Bumper 3
  pinMode(spoon3Pin, INPUT_PULLUP);    // sets the digital pin 32 as input
  pinMode(bumper3Pin, OUTPUT); // sets digital pin 33 as output

  // setup for Pop Bumper 4
  pinMode(spoon4Pin, INPUT_PULLUP);    // sets the digital pin 34 as input
  pinMode(bumper4Pin, OUTPUT); // sets digital pin 35 as output

  // setup for Pop Bumper 5
  pinMode(spoon5Pin, INPUT_PULLUP);    // sets the digital pin 36 as input
  pinMode(bumper5Pin, OUTPUT); // sets digital pin 37 as output

  // Setup for Rollover Switches
  // Rollover Switch 1
  pinMode(rsc1, INPUT);
  // Rollover Switch 2
  pinMode(rsc2, INPUT);
  // Rollover Switch 3
  pinMode(rsc3, INPUT);
  // Rollover Switch 4
  pinMode(rsc4, INPUT);
  // Rollover Switch 5
  pinMode(rsc5, INPUT);
  // Rollover Switch 6
  pinMode(rsc6, INPUT);
  // Rollover Switch 7
  pinMode(rsc7, INPUT);
  // Rollover Switch 10
  pinMode(rsc10, INPUT);

  // Setup for Slingshots
  // Slingshot 1
  pinMode(slingshotSpoonPin1, INPUT_PULLUP);    
  pinMode(slingshotBumperPin1, OUTPUT);

  // Slingshot 2
  pinMode(slingshotSpoonPin2, INPUT_PULLUP);    
  pinMode(slingshotBumperPin2, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // setup for the LED strip

  Serial.begin(9600); // serial begin with the necessary baud rate
} 

void loop() {

  Serial.println(score);

  if(action == IDLE) {
    if(InPlay == true) {
      action = INPLAY;
    }
  }

  if(action == INPLAY) {
    if(dropTargetCount == 0) {
      refireDropTarget = true;
    }
    if(rsc10 == 1) {
      action = INGUTTER;
    }
  }

  if(action == INGUTTER) {
    lives -= 1;
    if(lives == 0) {
      action = IDLE;
    }
    else if(lives > 0) {
      if(rsc6 == 1) {
        action = INPLAY;
      }
    }
  }

  switch(action) {
    case IDLE:
      readStartPin = digitalRead(startPin); // reading value of start pin
      if(readStartPin == 0) { // if start pin is hit (becomes a 1)
        InPlay = true; // In play becomes true, which means we now go into the inplay state, meaning the game starts
      }
      break;
    case INPLAY:
      // Drop Target:
      
      val1 = digitalRead(target1);   // read the input pin for drop target 1
      val2 = digitalRead(target2);   // read the input pin for drop target 2
      val3 = digitalRead(target3);   // read the input pin for drop target 3
      val4 = digitalRead(col); // read col pin

      Serial.println(val1);

      if(val1 == 1 || val2 == 1 || val3 == 1) { // if any of the targets get dropped
        if(prevVal1.1 == 1 || prevVal2.1 == 1 || prevVal3.1 == 1) { // if the previous value of a drop target was 0, meaning it just got dropped
          if(prevVal1.2 == 1 || prevVal2.2 == 1 || prevVal3.2 == 1) { // if the previous value of a drop target was 0, meaning it just got dropped
            if(prevVal1.3 == 1 || prevVal2.3 == 1 || prevVal3.3 == 1) { // if the previous value of a drop target was 0, meaning it just got dropped
              if(prevVal1.4 == 1 || prevVal2.4 == 1 || prevVal3.4 == 1) { // if the previous value of a drop target was 0, meaning it just got dropped
                if(prevVal1.5 == 0 || prevVal2.5 == 0 || prevVal3.5 == 0) { // if the previous value of a drop target was 0, meaning it just got dropped
                  count += 1; // increase count
                  score += 2500; // increment score
                  Serial.println("Drop");
                }
              }
            }
          }
        }
      }

      prevVal1.5 = prevVal1.4;  // target 1 previous
      prevVal2.5 = prevVal2.4; // target 2 previous
      prevVal3.5 = prevVal3.4; // target 3 previous

      prevVal1.4 = prevVal1.3;  // target 1 previous
      prevVal2.4 = prevVal2.3; // target 2 previous
      prevVal3.4 = prevVal3.3; // target 3 previous

      prevVal1.3 = prevVal1.2;  // target 1 previous
      prevVal2.3 = prevVal2.2; // target 2 previous
      prevVal3.3 = prevVal3.2; // target 3 previous

      prevVal1.2 = prevVal1.1;
      prevVal2.2 = prevVal2.1;
      prevVal3.2 = prevVal3.1;

      prevVal1.1 = val1;  // target 1 previous
      prevVal2.1 = val2; // target 2 previous
      prevVal3.1 = val3; // target 3 previous

      if(count > 0 && rsTriggered == true) { // if count is more than 0 and the rollover switch has been hit
        refireDropTarget = true; // fire drop target
      }

      if(refireDropTarget == true) { // if count is more than 0 meaning a target has been dropped and rollover switch has been hit we can refire the DT
        digitalWrite(dropTargetPin, HIGH); // refire the drop target coil 
        delay(50);
        digitalWrite(dropTargetPin, LOW); // unfire drop target coil
        refireDropTarget = false; // no longer want to fire again
        count = 0; // reset count to 0 because all targets are now up
        dropTargetCount += 1; // the drop target has been fired this many times
      }
      
      // Pop Bumpers: 

      // Pop Bumper 1
      pop1 = digitalRead(spoon1Pin);   // read pop bumper spoon pin
      if(pop1 == LOW){ // if spoon pin is low
        digitalWrite(bumper1Pin, HIGH); // fire pop bumper coil
        delay(100);
        digitalWrite(bumper1Pin, LOW); // unfire pop bumper coil
        score += 500; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 2
      pop2 = digitalRead(spoon2Pin);   // read the spoon pin
      if(pop2 == LOW){ // if spoon pin value is low
        digitalWrite(bumper2Pin, HIGH); // fire pop bumper coil
        delay(100);
        digitalWrite(bumper2Pin, LOW); // unfire pop bumper coil
        score += 500; // increase score by this much
      }  

      // Pop Bumper 3
      pop3 = digitalRead(spoon3Pin);   // read the spoon pin
      if(pop3 == LOW){ // if spoon pin is low
        digitalWrite(bumper3Pin, HIGH); // fire pop bumper coil
        delay(100);
        digitalWrite(bumper3Pin, LOW); // unfire pop bumper coil
        score += 500; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 4
      pop4 = digitalRead(spoon4Pin);   // read the spoon pin
      if(pop4 == LOW){ // if spoon pin is low
        digitalWrite(bumper4Pin, HIGH); // fire pop bumper coil
        delay(100);
        digitalWrite(bumper4Pin, LOW); // unfire pop bumper coil
        score += 500; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 5
      pop5 = digitalRead(spoon5Pin);   // read the input pin
      if(pop5 == LOW){ // if spoon pin is low
        digitalWrite(bumper5Pin, HIGH); // fire pop bumper coil
        delay(100);
        digitalWrite(bumper5Pin, LOW); // unfire pop bumper coil
        score += 500; // increase score by this much
      }  // sets the LED to the button's value

      // Rollover Switches:

      // Rollover Switch 1
      rollover1 = digitalRead(rsc1); // read rollover switch pin
      if(rollover1 == 1) {
        if(prevRoll1 == 0) {
          Serial.println("one");
          score += 250;
        }
      }

      // Rollover Switch 2
      rollover2 = digitalRead(rsc2); // read rollover switch pin
      if(rollover2 == 1) {
        if(prevRoll2 == 0) {
          Serial.println("two");
          score += 250;
        }
      }

      // Rollover Switch 3
      rollover3 = digitalRead(rsc3);
      if(rollover3 == 1) {
        if(prevRoll3 == 0) {
          Serial.println("three");
          score += 250;
        }
      }

      // Rollover Switch 4
      rollover4 = digitalRead(rsc4);
      if(rollover4 == 1) {
        if(prevRoll4 == 0) {
          Serial.println("four");
          score += 250;
        }
      }

      // Rollover Switch 5
      rollover5 = digitalRead(rsc5);
      if(rollover5 == 1) {
        if(prevRoll5 == 0) {
          Serial.println("five");
          score += 250;
        }
      }


      // Rollover Switch 6
      rollover6 = digitalRead(rsc6);
      if(rollover6 == 1) {
        if(prevRoll6 == 0) {
          Serial.println("six");
          score += 250;
        }
      }

      // Rollover Switch 7
      rollover7 = digitalRead(rsc7);
      if(rollover7 == 1) {
        if(prevRoll7 == 0)
          Serial.println("seven");
          rsTriggered = true;
        }
      }

      // Rollover Switch 10
      rollover10 = digitalRead(rsc10);
      if(rollover10 == 1) {
        if(prevRoll10 == 0) {
          Serial.println("ten");
          score += 250;
        }
      }


      // Slingshots:

      // Slingshot1
      slingshot1val = digitalRead(slingshotSpoonPin1);   // read the input pin
      if(slingshot1val == LOW){
        digitalWrite(slingshotBumperPin1, HIGH);
        val2 = digitalRead(slingshotBumperPin1);
        delay(100);
        digitalWrite(slingshotBumperPin1, LOW);
        val2 = digitalRead(slingshotBumperPin1);
        score += 500; // increase score by this much
      }  

      // Slingshot2
      slingshot2val = digitalRead(slingshotSpoonPin2);   // read the input pin
      if(slingshot2val == LOW){
        digitalWrite(slingshotBumperPin2, HIGH);
        val2 = digitalRead(slingshotBumperPin2);
        delay(100);
        digitalWrite(slingshotBumperPin2, LOW);
        val2 = digitalRead(slingshotBumperPin2);
        score += 500; // increase score by this much
      }  
      break;

    case INGUTTER:
      // do cervo motor things
      int x = 1;
      break;

  }
}