void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10000);                       // wait for a second
  digitalWrite(D5, LOW);    // turn the LED off by making the voltage LOW
  delay(300);                       // wait for a second
}
