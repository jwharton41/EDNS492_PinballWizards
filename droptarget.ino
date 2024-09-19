int target1 = 2;    // pushbutton connected to digital pin 2
int target2 = 3;
int target3 = 4;
int col = 5;
int bumperPin = 8;
int val1 = 0;      // variable to store the read value
int val2 = 0;
int val3 = 0;
int val4 = 0;
int count = 0;

void setup() {
  pinMode(target1, INPUT);    // sets the digital pin 2 as input
  pinMode(target2, INPUT);    // sets the digital pin 2 as input
  pinMode(target3, INPUT);    // sets the digital pin 2 as input
  pinMode(col, INPUT);
  digitalWrite(col, LOW);
  pinMode(bumperPin, OUTPUT);
  Serial.begin(1200);
}

// col = 0 when all are up. 
// col = 1 when one is down. 


void loop() {
  val1 = digitalRead(target1);   // read the input pin
  val2 = digitalRead(target2);   // read the input pin
  val3 = digitalRead(target3);   // read the input pin
  val4 = digitalRead(col);
  // if(val1 == 0 && val2 == 0 && val3 == 0) {
  //   digitalWrite(col, LOW);
  // }
  if(val1 == 1 || val2 == 1 || val3 == 1) {
    count += 1;
  }
  delay(1000);

  Serial.print(val1);
  Serial.print(" ");
  Serial.print(val2);
  Serial.print(" ");
  Serial.print(val3);
  Serial.print(" ");
  Serial.println(val4);
  Serial.print(" ");
  Serial.println(count);
}