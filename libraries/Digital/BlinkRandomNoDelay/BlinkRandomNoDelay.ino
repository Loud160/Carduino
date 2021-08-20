/*
  Blink without delay

  Turns on and off the built in LED without using the delay() function.
  This means that other code can run at the same time without being 
  interrupted by the LED code.
*/
int thisTime;
int myLED = 13;
long previousMillis = 0;        // will store the last time the LED was updated

void setup() {
    // Set up the built-in LED pin as output:
    pinMode(myLED, OUTPUT);
}

void loop() {  
    // Check to see if it's time to blink the LED using the 
    //difference between the current time and last time we blinked    
    if (millis() - previousMillis > thisTime) {

      //generate a random number and save it into the variable we check for the min time
      thisTime = random(50,500);
        // Save the last the LED was blinked
        previousMillis = millis();

        // If the LED is off, turn it on, and vice versa
        digitalWrite(myLED,!digitalRead(myLED));
    }
}
