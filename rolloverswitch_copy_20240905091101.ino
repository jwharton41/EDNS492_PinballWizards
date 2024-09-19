int rollsw = 8;
int rsc = 9;

void setup() {
  pinMode(rollsw, INPUT);
  pinMode(rsc, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val2 = digitalRead(rsc);
  Serial.print(val2);
  Serial.print("\n");
}
