/*
  DigitalReadBlink

  The example demonstrates several things, how to read a digital pin when its used as an input pin, how to 
 use digitialRead in a statment and compare it to a know value and how to update the state of a digital pin
 based on the pins current state. 

  You can use any pin number that starts with a D and this will work the same. For this example we will be 
  using pin D2 connect to a switch.

  Connections:
  1) Connect one side of your push button/rocker switch to the digital pin you are using(if you are not using D2).

  2) Connect the other side of your switch to one of the ground connections either on your Mego2560 PRO
    or on one of the ground points of your Carduino.

  3) We are going to use the Arduio's internal pullup resistor to supply power to the digital pin being used
    so the pin will read that it is "High" when the switch is not connected.

  4) Once you have made the switch connections, connect your Arduino to your PC
    using a USB cable and upload the sketch.

  5) You will now notice that the speed of the LED changes based on the state of the pin
*/

// This gives the digital pin being used a name so
// that is easy to reference anywhere it is used in the program
int mySwitch = 2;

// This sets the name for our LED
int myLED = 13;

// Variables used to determine how flast the LED blinks based on the switch state
uint32_t previousMillis = 0;         // will store the last time the LED was updated
int interval = 1000;            // interval at which to blink (in milliseconds)


void setup() {

  // Set the pin mode for the switch and enable the pull up resistor
  pinMode(mySwitch, INPUT_PULLUP);

  // set the LED as an output
  pinMode(myLED, OUTPUT);
}


void loop() {

// Use a timer to control how fast the LED is read and to blink the LED
  if (millis() - previousMillis > interval) {

    // Save the last time the timer was ran
    previousMillis = millis();   

    // read the input pins current state and decide how fast to blink the LED
    if (digitalRead(mySwitch) == 0) {
      interval = 50;
    } else {
      interval = 500;
    }

    // If the LED is off, turn it on and if it's on then turn it off
    digitalWrite(myLED, !digitalRead(myLED));
  }
}