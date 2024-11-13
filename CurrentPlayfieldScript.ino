#include <FastLED.h> // LED strip library declaration 
#define DATA_PIN 6
#define NUM_LEDS 10 
CRGB leds[NUM_LEDS]; // can change the numbers later if we have to

unsigned long time;

// 2-13, 22-53
unsigned long score = 0;
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
int prevVal1_1 = 0;  // target 1 previous
int prevVal2_1 = 0; // target 2 previous
int prevVal3_1 = 0; // target 3 previous

int prevVal1_2 = 0;  // target 1 previous
int prevVal2_2 = 0; // target 2 previous
int prevVal3_2 = 0; // target 3 previous

int prevVal1_3 = 0;  // target 1 previous
int prevVal2_3 = 0; // target 2 previous
int prevVal3_3 = 0; // target 3 previous

int prevVal1_4 = 0;  // target 1 previous
int prevVal2_4 = 0; // target 2 previous
int prevVal3_4 = 0; // target 3 previous

int prevVal1_5 = 0;  // target 1 previous
int prevVal2_5 = 0; // target 2 previous
int prevVal3_5 = 0; // target 3 previous


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
int rollover10 = 0;

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
enum actionType {IDLE, INPLAY}; // declaration for each of the states for our state machine

actionType action = IDLE; // this is the starting state for our state machine

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
  pinMode(rsc1, INPUT_PULLUP);
  // Rollover Switch 2
  pinMode(rsc2, INPUT_PULLUP);
  // Rollover Switch 3
  pinMode(rsc3, INPUT_PULLUP);
  // Rollover Switch 4
  pinMode(rsc4, INPUT_PULLUP);
  // Rollover Switch 5
  pinMode(rsc5, INPUT_PULLUP);
  // Rollover Switch 6
  pinMode(rsc6, INPUT_PULLUP);

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

  Serial.print("Score: ");
  Serial.println(score);

  if(action == IDLE) { // if we are in an idle state
    if(InPlay == true) { // if boolean InPlay becomes equal to true
      action = INPLAY; // action will change to INPLAY, starting the game
    }
  }

  if(action == INPLAY) { // if the game has started and is now being played
    if(dropTargetCount == 0) { // if the drop target has not been fired at all (has fired 0 times)
      refireDropTarget = true; // fire the drop target
    }
    if(lives == 0) { // if the player is out of lives (The ball has gone in the gutter 3 times)
      action = IDLE; // we return to an idle state and the game is over
      InPlay = false; // in play is reset to false
    }
  }

  Serial.print("Lives: ");
  Serial.println(lives);


  switch(action) {
    case IDLE:
      readStartPin = digitalRead(startPin); // reading value of start pin
      if(readStartPin == 0) { // if start pin is hit (becomes a 0)
        InPlay = true; // In play becomes true, which means we now go into the inplay state, meaning the game starts
      }
      break;
    case INPLAY:
      // Drop Target:
      if(millis() % 1000 == 0){
      val1 = digitalRead(target1);   // read the input pin for drop target 1
      val2 = digitalRead(target2);   // read the input pin for drop target 2
      val3 = digitalRead(target3);   // read the input pin for drop target 3
      val4 = digitalRead(col); // read col pin

      if(val1 == 1 || val2 == 1 || val3 == 1) { // if any of the targets now see a 1
          if(prevVal1_1 == 0 || prevVal2_1 == 0 || prevVal3_1 == 0) { // if the previous value of a drop target was 0, meaning it just got hit
            count += 1; // increase count of how many targets have been hit
            score += 2500; // increment score
          }
        }

      }

      prevVal1_1 = val1;  // target 1 previous value
      prevVal2_1 = val2; // target 2 previous value
      prevVal3_1 = val3; // target 3 previous value

      if(count > 0 && rsTriggered == true) { // if count is more than 0 and the rollover switch has been hit
        refireDropTarget = true; // fire drop target
        count = 0; // return count to 0 because all the targets will now go up
      }

      if(refireDropTarget == true) { // if count is more than 0 meaning a target has been dropped and rollover switch has been hit we can refire the DT
        digitalWrite(dropTargetPin, HIGH); // refire the drop target coil 
        delay(50); // breif pause for coil to fire fully
        digitalWrite(dropTargetPin, LOW); // unfire drop target coil
        if(dropTargetCount == 0) { // if this is the first time the drop target is being fired
          delay(1500); // the first time, we want to delay by a second and a half to consistently read the target (There is some interference at the start)
        }
        refireDropTarget = false; // no longer want to fire again
        rsTriggered = false; // reset this boolean back to false
        count = 0; // reset count to 0 because all targets are now up (repeated for insurance)
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
      if(rollover1 == 1) { // if rollover switch has changed to a 1
        if(prevRoll1 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("one"); // print statement for testing
          score += 250; // increase score by this many points
          rsTriggered = true; // the rollover switch to allow the drop target to fire has been triggered
        }
      }
      prevRoll1 = rollover1; // set previous value to be the last value of the switch

      // Rollover Switch 2
      rollover2 = digitalRead(rsc2); // read rollover switch pin
      if(rollover2 == 1) { // if rollover switch has changed to a 1
        if(prevRoll2 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("two"); // print statement for testing
          score += 250; // increase score by this many points
        }
      }
      prevRoll2 = rollover2; // set previous value to be the last value of the switch

      // Rollover Switch 3
      rollover3 = digitalRead(rsc3); // read rollover switch pin
      if(rollover3 == 1) { // if rollover switch has changed to a 1
        if(prevRoll3 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("three"); // print statement for testing
          score += 250; // increase score by this many points
        }
      }
      prevRoll3 = rollover3; // set previous value to be the last value of the switch

      // Rollover Switch 4
      rollover4 = digitalRead(rsc4); // read rollover switch pin
      if(rollover4 == 1) { // if rollover switch has changed to a 1
        if(prevRoll4 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("four"); // print statement for testing
          score += 250; // increase score by this many points
        }
      }
      prevRoll4 = rollover4; // set previous value to be the last value of the switch

      // Rollover Switch 5
      rollover5 = digitalRead(rsc5); // read rollover switch pin
      if(rollover5 == 1) { // if rollover switch has changed to a 1
        if(prevRoll5 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("five"); // print statement for testing
          score += 250; // increase score by this many points
        }
      }
      prevRoll5 = rollover5; // set previous value to be the last value of the switch

      // Rollover Switch 6
      rollover6 = digitalRead(rsc6); // read rollover switch pin
      if(rollover6 == 1) { // if rollover switch has changed to a 1
        if(prevRoll6 == 0) { // if the previous value was a zero, meaning it has switched from 0 to 1
          Serial.println("six"); // print statement for testing
          lives -= 1; // decrease lives by 1 as the ball has gone in the gutter
        }
      } 
      prevRoll6 = rollover6; // set previous value to be the last value of the switch

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
  }
}
