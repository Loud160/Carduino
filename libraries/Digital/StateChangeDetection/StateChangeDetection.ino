/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the
  time, but you just need to know when the input changes from one state
  to another.  For example, you want to know when a button goes from
  OFF to ON.  This is called state change detection, or edge detection.

  This example shows how to detect when a button or switch changes
  from off to on and on to off.

  To use this example, connect to Carduino or Arduino Mega2560 PRO to the
  USB serial port. Then push the button a few times and see what happens.

*/
// set the input pin that will be checked
int myButton = 2;

//set the name of the LED
int myLED = 13;

// counter for the number of button presses
int buttonPushCounter = 0;

// How many button presses before it should reset
int countUntil = 4;

// current state of the button
int buttonState = 0;

// previous state of the button
int lastButtonState = 0;

void setup() {
  // Serial port is used to display the state change
  Serial.begin(115200);

  // initialize myButton as an input, enable the pullup resistor to keep the pin from floating
  pinMode(myButton, INPUT_PULLUP);

  // initialize the LED as an output
  pinMode(myLED, OUTPUT);
}

void loop() {
  // read the pushbutton input pin
  buttonState = digitalRead(myButton);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {

    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;

    // check what the current button state is
    if (buttonState == LOW) {

      // if the current state is HIGH, then the button went from off to on
      Serial.println("Input Pin LOW, Button Pressed Down");

      // Increase the counter by 1
      buttonPushCounter++;
    } else {

      // if the current state is LOW, then the button went from on to off:
      Serial.println("Input Pin HIGH");
    }

    //Display the current button count
    Serial.print("number of button pushes:  ");
    Serial.println(buttonPushCounter);

    //Check if we have reached the max count
    if (buttonPushCounter >=  countUntil) {
      digitalWrite(myLED, !digitalRead(myLED));
      buttonPushCounter = 0;
      Serial.println("Button Counter Reset");
    }
  }

// added to stabilize the input reading
  delay(1);

}
