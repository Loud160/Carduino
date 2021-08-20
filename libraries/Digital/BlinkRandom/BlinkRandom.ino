/*
  Blink
  Read the state of the LED pin and change it to the opposite state then
  generate a random number to use as the time to delay for.
*/

//give the LED a variable name
int myLED = 13;
void setup() {
  // initialize digital pin myLED as an output.
  pinMode(myLED, OUTPUT);
}
void loop() {
  //Read the current state of the LED and change it
  digitalWrite(myLED, !digitalRead(myLED));

  // generate a random number between 10 and 350, use this number as the delay in mS(x/1000th of a second)
  delay(random(10, 350));
}
