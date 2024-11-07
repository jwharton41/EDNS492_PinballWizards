int score = 0;
bool InPlay = false;
int lives = 3;
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

// Pop Bumper:
int spoon1Pin = 28;    // spoon pin set to pin 28
int bumper1Pin = 29;  // pin to make coil fire set to 29
int pop1 = 50;      // variable to store the read value

/* ... */

// Rollover Switch:
int rsc1 = 22;
// talk about how one rollover switch makes the state become INGUTTER

/* ... */

// Slingshot:
int slingshotSpoonPin1 = 48;   
int slingshotBumperPin1 = 49;
int slingshot1val = 0;      // variable to store the read valu0e
int slingshot1val2 = 0;

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
  /* ... */
  pinMode(col, INPUT); // col pin
  digitalWrite(col, LOW); // setting col to low so we read when a target falls
  pinMode(dropTargetPin, OUTPUT); // pin to tell coil to fire set as output

  // setup for Pop Bumper
  pinMode(spoon1Pin, INPUT_PULLUP);    // sets the digital pin 28 as input
  pinMode(bumper1Pin, OUTPUT); // sets digital pin 29 as output
  /* ... */
 
  // Setup for Rollover Switch
  pinMode(rsc1, INPUT);
  /* ... */
  
  // Setup for Slingshot
  pinMode(slingshotSpoonPin1, INPUT_PULLUP);    
  pinMode(slingshotBumperPin1, OUTPUT);
  /* ... */

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
      /* ... */

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
      
      // Pop Bumper
      pop1 = digitalRead(spoon1Pin);   // read pop bumper spoon pin
      if(pop1 == LOW){ // if spoon pin is low
        digitalWrite(bumper1Pin, HIGH); // fire pop bumper coil
        delay(50);
        digitalWrite(bumper1Pin, LOW); // unfire pop bumper coil
        score += 1000; // increase score by this much
      }  // sets the LED to the button's value

      /* ... */

      // Rollover Switch (Standard)
      int rollover1 = digitalRead(rsc1); // read rollover switch pin
      if(rsc1 == 1) {
        score += 250;
      }

      // Rollover Switch (State Change)
      int rollover7 = digitalRead(rsc7);
      if(rsc7 == 1) {
        rsTriggered = true;
      }

      // Slingshot
      slingshot1val = digitalRead(slingshotSpoonPin1);   // read the input pin
      if(slingshot1val == LOW){
        digitalWrite(slingshotBumperPin1, HIGH);
        val2 = digitalRead(slingshotBumperPin1);
        delay(100);
        digitalWrite(slingshotBumperPin1, LOW);
        val2 = digitalRead(slingshotBumperPin1);
      }  // sets the LED to the button's value
      /* ... */
      break;

    case INGUTTER:
      // do servo motor things
      int x = 1;
      break;
  }
}
