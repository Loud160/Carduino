/*
  DebounceSwitchSimple

 ***********************************************************************
 **                                                                   **
 ** Strongly suggest looking at examples in DebounceSwitchAdvanced    **
 **       The library it uses greatly simplifies the process          **       
 **       when using more then one switch or button                   **
 **                                                                   **
 ***********************************************************************

  Each time the input pin goes from HIGH to to LOW because of a button was pressed,
  the output pin is switched from LOW to HIGH or HIGH to LOW.  There's a minimum
  delay between toggles to "debounce" the circuit. Try changing this by altering the 
  number listed in the variable "debounceDelay"

  The point of this is to help prevent noise from movement of the button
  that could inadvertently cause your switchh to trigger.

  The circuit:   
   switch/button attached from pin D2 to Ground
   The LED built into the Arduino will be used
*/

// the pin your switch is connected on
int mySwitch = 2;

// the name you give LED
int ledPin =  13;

// the current state of the output pin
int ledState = HIGH;

// the current reading from the input pin
int switchState;

// the previous reading from the input pin
int lastSwitchState = LOW;

// the following variables are uint32's because the time, measured in miliseconds,
// can quickly become a bigger number than can be stored in smaller variables.
long lastDebounceTime = 0;  // the last time the output pin was toggled

// the debounce time; how long the button needs to be held down to turn on or off the LED
long debounceDelay = 250;    

void setup() {
  //Set the input pin and enable the pullup resistor
  pinMode(mySwitch, INPUT_PULLUP);

  // set the output pin
  pinMode(ledPin, OUTPUT);
}

void loop() {

  // read the state of the switch into a local variable
  int reading = digitalRead(mySwitch);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // Check if the switch changed states, was it due to noise or was it swicthed?
  if (reading != lastSwitchState) {

    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    switchState = reading;
  }

  // set the LED using the state of the button:
  digitalWrite(ledPin, switchState);

  // save the reading.  Next time through the loop,
  // it'll be the lastSwitchState:
  lastSwitchState = reading;
  
}
