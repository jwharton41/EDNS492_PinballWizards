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
int prevVal1 = 0;  // target 1 previous
int prevVal2 = 0; // target 2 previous
int prevVal3 = 0; // target 3 previous
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

// // Rollover Switch 8
// int rsc8 = 38;

// // Rollover Switch 9
// int rsc9 = 39;

// Rollover Switch 10
int rsc10 = 40;

// // Rollover Switch 11
// int rsc11 = 11;

// // Rollover Switch 12
// int rsc12 = 12;

// // Rollover Switch 13
// int rsc13 = 13;


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
  // Rollover Switch 8
  // pinMode(rsc8, INPUT);
  // // Rollover Switch 9
  // pinMode(rsc9, INPUT);
  // Rollover Switch 10
  pinMode(rsc10, INPUT);
  // Rollover Switch 11
  // pinMode(rsc11, INPUT);
  // // Rollover Switch 12
  // pinMode(rsc12, INPUT);
  // // Rollover Switch 13
  // pinMode(rsc13, INPUT);

  // Setup for Slingshots
  // Slingshot 1
  pinMode(slingshotSpoonPin1, INPUT_PULLUP);    
  pinMode(slingshotBumperPin1, OUTPUT);

  // Slingshot 2
  pinMode(slingshotSpoonPin2, INPUT_PULLUP);    
  pinMode(slingshotBumperPin2, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // setup for the LED strip

  Serial.begin(115200); // serial begin with the necessary baud rate
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
      if(readStartPin == 1) { // if start pin is hit (becomes a 1)
        InPlay = true; // In play becomes true, which means we now go into the inplay state, meaning the game starts
      }
      break;
    case INPLAY:
      // Drop Target:
      //readStartPin = 0; 
      val1 = digitalRead(target1);   // read the input pin for drop target 1
      val2 = digitalRead(target2);   // read the input pin for drop target 2
      val3 = digitalRead(target3);   // read the input pin for drop target 3
      val4 = digitalRead(col); // read col pin

      if(val1 == 1 || val2 == 1 || val3 == 1) { // if any of the targets get dropped
        count += 1; // increase count
        if(prevVal1 == 0 || prevVal2 == 0 || prevVal3 == 0) { // if the previous value of a drop target was 0, meaning it just got dropped
          score += 2500; // increment score
        }
      }

      prevVal1 = val1; // reset previous values
      prevVal2 = val2;
      prevVal3 - val3;

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

      // backup for drop target stuff
      // switch(dtState) {
      //   if(dtState == IDLETARGET) {
      //     if(rsTriggered == true) {
      //       dtState = CANFIRE;
      //     }
      //   }
      //   if(dtState == CANFIRE) {
      //     if(count > 0) {
      //       dtState = FIRE;
      //     }
      //     else {
      //       dtState = IDLETARGET;
      //     }
      //   }
      //   if(dtState == FIRE) {
      //     if(hasFired == true) {
      //       dtState = IDLETARGET;
      //     }
      //     else {
      //       dtState = FIRE;
      //     }
      //   }

      //   case IDLETARGET:
      //     if(rsc7 == 1) {
      //       rsTriggered = true;
      //     }
      //     if(val1 == 1 || val2 == 1 || val3 == 1) { // if any of the targets get dropped
      //       count += 1;
      //       if(prevVal1 == 0 || prevVal2 == 0 || prevVal3 == 0) {
      //         score += 2500; // increment score
      //       }
      //     }
      //     break;
      //   case CANFIRE:
      //     if(count > 0 && rsTriggered == true) { // if count is more than 0 and we've reached a certain score
      //       refireDropTarget = true;
      //     }
      //     break;
      //   case FIRE:
      //     if(refireDropTarget == true) { // if count is more than 0 and we've reached a certain score
      //       digitalWrite(dropTargetPin, HIGH); // refire the drop target coil 
      //       delay(50);
      //       digitalWrite(dropTargetPin, LOW);
      //       refireDropTarget = false;
      //       count = 0;
      //     } 
      //     break;

      // }
      
      // Pop Bumpers: 

      // Pop Bumper 1
      pop1 = digitalRead(spoon1Pin);   // read pop bumper spoon pin
      if(pop1 == LOW){ // if spoon pin is low
        digitalWrite(bumper1Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper1Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 2
      pop2 = digitalRead(spoon2Pin);   // read the spoon pin
      if(pop2 == LOW){ // if spoon pin value is low
        digitalWrite(bumper2Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper2Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  

      // Pop Bumper 3
      pop3 = digitalRead(spoon3Pin);   // read the spoon pin
      if(pop3 == LOW){ // if spoon pin is low
        digitalWrite(bumper3Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper3Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 4
      pop4 = digitalRead(spoon4Pin);   // read the spoon pin
      if(pop4 == LOW){ // if spoon pin is low
        digitalWrite(bumper4Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper4Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  // sets the LED to the button's value

      // Pop Bumper 5
      pop5 = digitalRead(spoon5Pin);   // read the input pin
      if(pop5 == LOW){ // if spoon pin is low
        digitalWrite(bumper5Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper5Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  // sets the LED to the button's value

      // Rollover Switches:

      // Rollover Switch 1
      int rollover1 = digitalRead(rsc1); // read rollover switch pin
      if(rsc1 == 1) {
        score += 250;
      }

      // Rollover Switch 2
      int rollover2 = digitalRead(rsc2); // read rollover switch pin
      if(rsc2 == 1) { 
        score += 250;
      }

      // Rollover Switch 3
      int rollover3 = digitalRead(rsc3);
      if(rsc3 == 1) {
        score += 250;
      }

      // Rollover Switch 4
      int rollover4 = digitalRead(rsc4);
      if(rsc4 == 1) {
        score += 250;
      }

      // Rollover Switch 5
      int rollover5 = digitalRead(rsc5);
      if(rsc5 == 1) {
        score += 250;
      }

      // Rollover Switch 6
      int rollover6 = digitalRead(rsc6);
      if(rsc6 == 1) {
        score += 250;
      }

      // Rollover Switch 7
      int rollover7 = digitalRead(rsc7);
      if(rsc7 == 1) {
        rsTriggered = true;
      }

      // Rollover Switch 10
      int rollover10 = digitalRead(rsc10);
      if(rsc10 == 1) {
        score += 250;
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
      }  // sets the LED to the button's value

      // Slingshot2
      slingshot2val = digitalRead(slingshotSpoonPin2);   // read the input pin
      if(slingshot2val == LOW){
        digitalWrite(slingshotBumperPin2, HIGH);
        val2 = digitalRead(slingshotBumperPin2);
        delay(100);
        digitalWrite(slingshotBumperPin2, LOW);
        val2 = digitalRead(slingshotBumperPin2);
      }  // sets the LED to the button's value
      break;

    case INGUTTER:
      // do cervo motor things
      int x = 1;
      break;

  }
}
