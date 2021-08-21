/*Timer Class Method
 * 
 * Create a method and class to use the timer control
*/

#include "timer.h"

//Create our class (FooLed, got it ?)
class FooLed {
public:
  FooLed(byte led_pin) {
    this->led_pin = led_pin;
    pinMode(led_pin, OUTPUT);
    led_is_on = false;
  }

  //blink method
  void blink() {
    if(led_is_on) {
        digitalWrite(led_pin, HIGH);
      } else {
        digitalWrite(led_pin, LOW);
      }

      //Change led state
      led_is_on = !led_is_on;
  }

private:
  byte led_pin;
  byte led_is_on;
};


//FooLed object
FooLed led(13);

//TimerForMethods object
TimerForMethods<FooLed> timer(&led, &FooLed::blink);

void setup()
{
  //Set the interval in milliseconds we want the led to blink
  timer.setInterval(1000);

  //Start the timer
  timer.start();
}

void loop()
{
  //Update the timer
  timer.update();
}
