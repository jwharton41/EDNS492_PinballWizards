
// 2-13, 22-53

int score;

// Pins for Drop Target
int target1 = 2; // target 1
int target2 = 3; // target 2
int target3 = 4; // target 3
int col = 5; // col pin // col = 0 means the pins switch when a target drops
int dropTargetPin = 6; // pin to tell drop target coil to fire

// variables for drop target
int val1 = 0;  // target 1
int val2 = 0; // target 2
int val3 = 0; // target 3
int val4 = 0; // col pin
int count = 0; // count for refiring drop target
bool refireDropTarget = false;

// Pop Bumpers:

// Pop Bumper 1
int spoon1Pin = 28;    // spoon pin set to pin 28
int bumper1Pin = 29;  // pin to make coil fire set to 29
int pop1 = 0;      // variable to store the read value

// Pop Bumper 2
int spoon2Pin = 30;    // spoon pin set to pin 30
int bumper2Pin = 31;  // pin to make coil fire set to 31
int pop2 = 0;      // variable to store the read value

// Pop Bumper 3
int spoon3Pin = 32;    // spoon pin set to pin 32
int bumper3Pin = 33;  // pin to make coil fire set to 33
int pop3 = 0;      // variable to store the read value

// Pop Bumper 4
int spoon4Pin = 34;    // spoon pin set to pin 34
int bumper4Pin = 35;  // pin to make coil fire set to 35
int pop4 = 0;      // variable to store the read value

// Pop Bumper 5
int spoon5Pin = 36;    // spoon pin set to pin 36
int bumper5Pin = 37;  // pin to make coil fire set to 37
int pop5 = 0;      // variable to store the read value

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

// Rollover Switch 8
int rsc8 = 38;

// Rollover Switch 9
int rsc9 = 39;

// Rollover Switch 10
int rsc10 = 40;

// Rollover Switch 11
int rsc11 = 11;

// Rollover Switch 12
int rsc12 = 12;

// Rollover Switch 13
int rsc13 = 13;

void setup() {
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
  pinMode(rsc8, INPUT);
  // Rollover Switch 9
  pinMode(rsc9, INPUT);
  // Rollover Switch 10
  pinMode(rsc10, INPUT);
  // Rollover Switch 11
  pinMode(rsc11, INPUT);
  // Rollover Switch 12
  pinMode(rsc12, INPUT);
  // Rollover Switch 13
  pinMode(rsc13, INPUT);

  Serial.begin(1200); // serial begin
} 

void loop() {
  // Drop Target: 
  val1 = digitalRead(target1);   // read the input pin for drop target 1
  val2 = digitalRead(target2);   // read the input pin for drop target 2
  val3 = digitalRead(target3);   // read the input pin for drop target 3
  val4 = digitalRead(col); // read col pin
  if(val1 == 1 || val2 == 1 || val3 == 1) { // if a target gets dropped
    count += 1; // count goes up by 1
    score += 150;
  }
  delay(1000); // delay 
  // looking at all the drop target pins
  Serial.print(val1);
  Serial.print(" ");
  Serial.print(val2);
  Serial.print(" ");
  Serial.print(val3);
  Serial.print(" ");
  Serial.println(val4);
  Serial.print(" ");
  Serial.println(count);

  if(count > 0 && score >= 2000) { // if count is more than 0 and we've reached a certain score
    refireDropTarget = true;
  }

  if(refireDropTarget == true) { // if count is more than 0 and we've reached a certain score
    digitalWrite(dropTargetPin, HIGH); // refire the drop target coil 
    delay(50);
    digitalWrite(dropTargetPin, LOW);
    refireDropTarget = false;
    count = 0;
  }
  
  // Pop Bumpers: 

  // Pop Bumper 1
  pop1 = digitalRead(spoon1Pin);   // read the input pin
  if(pop1 == LOW){
    digitalWrite(bumper1Pin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumper1Pin, LOW);
    score += 1000;
  }  // sets the LED to the button's value
  Serial.println(pop1);

  // Pop Bumper 2
  pop2 = digitalRead(spoon2Pin);   // read the input pin
  if(pop2 == LOW){
    digitalWrite(bumper2Pin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumper2Pin, LOW);
    score += 1000;
  }  // sets the LED to the button's value
  Serial.println(pop2);

  // Pop Bumper 3
  pop3 = digitalRead(spoon3Pin);   // read the input pin
  if(pop3 == LOW){
    digitalWrite(bumper3Pin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumper3Pin, LOW);
    score += 1000;
  }  // sets the LED to the button's value
  Serial.println(pop3);

  // Pop Bumper 4
  pop4 = digitalRead(spoon4Pin);   // read the input pin
  if(pop4 == LOW){
    digitalWrite(bumper4Pin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumper4Pin, LOW);
    score += 1000;
  }  // sets the LED to the button's value
  Serial.println(pop4);

  // Pop Bumper 3
  pop5 = digitalRead(spoon5Pin);   // read the input pin
  if(pop5 == LOW){
    digitalWrite(bumper5Pin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumper5Pin, LOW);
    score += 1000;
  }  // sets the LED to the button's value
  Serial.println(pop5);

  // Rollover Switches:

  // Rollover Switch 1
  int rollover1 = digitalRead(rsc1);
  Serial.print(rollover1);
  Serial.print("\n");
  if(rsc1 == 1) {
    score += 250;
  }

  // Rollover Switch 2
  int rollover2 = digitalRead(rsc2);
  Serial.print(rollover2);
  Serial.print("\n");
  if(rsc2 == 1) {
    score += 250;
  }

  // Rollover Switch 3
  int rollover3 = digitalRead(rsc3);
  Serial.print(rollover3);
  Serial.print("\n");
  if(rsc3 == 1) {
    score += 250;
  }

  // Rollover Switch 4
  int rollover4 = digitalRead(rsc4);
  Serial.print(rollover4);
  Serial.print("\n");
  if(rsc4 == 1) {
    score += 250;
  }

  // Rollover Switch 5
  int rollover5 = digitalRead(rsc5);
  Serial.print(rollover5);
  Serial.print("\n");
  if(rsc5 == 1) {
    score += 250;
  }

  // Rollover Switch 6
  int rollover6 = digitalRead(rsc6);
  Serial.print(rollover6);
  Serial.print("\n");
  if(rsc6 == 1) {
    score += 250;
  }

  // Rollover Switch 7
  int rollover7 = digitalRead(rsc7);
  Serial.print(rollover7);
  Serial.print("\n");
  if(rsc7 == 1) {
    score += 250;
    refireDropTarget = true;
  }

  // Rollover Switch 8
  int rollover8 = digitalRead(rsc8);
  Serial.print(rollove8);
  Serial.print("\n");
  if(rsc8 == 1) {
    score += 250;
  }

  // Rollover Switch 9
  int rollover9 = digitalRead(rsc9);
  Serial.print(rollover9);
  Serial.print("\n");
  if(rsc9 == 1) {
    score += 250;
  }

  // Rollover Switch 10
  int rollover10 = digitalRead(rsc10);
  Serial.print(rollover10);
  Serial.print("\n");
  if(rsc10 == 1) {
    score += 250;
  }

  // Rollover Switch 11
  int rollover11 = digitalRead(rsc11);
  Serial.print(rollover11);
  Serial.print("\n");
  if(rsc11 == 1) {
    score += 250;
  }

  // Rollover Switch 12
  int rollover12 = digitalRead(rsc12);
  Serial.print(rollover12);
  Serial.print("\n");
  if(rsc12 == 1) {
    score += 250;
  }

  // Rollover Switch 13
  int rollover13 = digitalRead(rsc13);
  Serial.print(rollover13);
  Serial.print("\n");
  if(rsc13 == 1) {
    score += 250;
  }

}
