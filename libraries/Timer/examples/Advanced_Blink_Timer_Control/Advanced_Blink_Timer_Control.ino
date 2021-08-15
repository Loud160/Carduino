/*Advanced Blink Timer Control
 * 
 * This example demonstrates the use of a simplified timer control to call a function.  
*/

#include "timer.h"

int led_pin = 13;  //Set our led pin
bool led_is_on = false;  //Holds if the led is on

//Timer name
Timer myTimer;

//blink led function called when timer is triggered 
void blinkLed() {
  if(led_is_on) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }

  //Change our led state
  led_is_on = !led_is_on;
}

void setup()
{
  pinMode(led_pin, OUTPUT);

  //Set the interval in milliseconds we want the led to blink
  myTimer.setInterval(1000);

  //Set our callback function
  myTimer.setCallback(blinkLed);

  //Start the timer
  myTimer.start();
}

void loop()
{
  //Update the timer
  myTimer.update();
}
