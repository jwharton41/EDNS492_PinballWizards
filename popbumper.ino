int spoonPin = 2;    // pushbutton connected to digital pin 7
int bumperPin = 8;
int val = 0;      // variable to store the read value

void setup() {
  pinMode(spoonPin, INPUT_PULLUP);    // sets the digital pin 7 as input
  pinMode(bumperPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(spoonPin);   // read the input pin
  if(val == LOW){
    digitalWrite(bumperPin, HIGH);
    Serial.println("Ballin");
    delay(50);
    digitalWrite(bumperPin, LOW);
  }  // sets the LED to the button's value
  Serial.println(val);
}