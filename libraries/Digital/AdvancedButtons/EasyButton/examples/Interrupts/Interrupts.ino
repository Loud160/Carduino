/*
Interrupts example
This example to demostrate how to use hardware interrupts in order to improve performance in your main loop with buttons.
The only time the button is read is when it changes states and there is no code that needs to be added into the main loop
*/

#include <Arduino.h>
#include <EasyButton.h>

// Arduino pin where the buttons are connected to.
#define BUTTON_PIN 2

#define BAUDRATE 115200

// Instance of the button.
EasyButton button(BUTTON_PIN);

void buttonStateChanged()
{
  Serial.println("Button pressed");
}

void sequenceEllapsed()
{
  Serial.println("Double click");
}

void buttonISR()
{
  /*
    When button is being used through external interrupts, 
    parameter INTERRUPT must be passed to read() function
   */
  button.read();
}

void setup()
{

  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);
  Serial.println(">>> EasyButton interrupts example <<<");

  // Initialize the button.
  button.begin();

// this is trigggered when the button is pressed 
  button.onPressed(buttonStateChanged);  

// check it the button has been clicked twice in the last 1.5 seconds 
  button.onSequence(2, 1500, sequenceEllapsed);

//check if the pin being used supports a hardware interupt
  if (button.supportsInterrupt())
  {
    button.enableInterrupt(buttonISR);
    Serial.println("The selected pin supports hardware interrupts");
  }else{
     Serial.println("This input pin does not support");
     Serial.println("interrupts and can not be used");
     while(1){
      // go into an endless loop and do nothing
     }
  }
}

void loop()
{
  // it's so easy you don't even need to add any code into your main loop!
}
