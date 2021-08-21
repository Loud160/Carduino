/* * Inherited Timer Class
 * 
 * The example demonstrates how the timer class can be inherited by overwriting the call method  
*/

#include "timer.h"

//Create our class and inherit the Timer class
class FooLed: public Timer {
public:
  FooLed(byte led_pin) {

    this->led_pin = led_pin;
    pinMode(led_pin, OUTPUT);
    led_is_on = false;

    //Set our interval
    this->setInterval(1000);

    //Start the timer
    this->start();
  }

  // blink method
  void blink() {
    if(led_is_on) {
        digitalWrite(led_pin, HIGH);
      } else {
        digitalWrite(led_pin, LOW);
      }

      //Change led state
      led_is_on = !led_is_on;
  }

  //Overwrites the call method
  void call() {
    blink();
  }

private:
  byte led_pin;
  byte led_is_on;
};


//FooLed object
FooLed led(13);

void setup()
{
}

void loop()
{
  //Update the led
  led.update();
}
