/*Timer Control Via Serial Commands 
 * 
 * The example lets you use several of the timer commands over the serial monitor to better understand 
 * how the timer control works.  
 * There are 4 commands that can be used:
 * S = start the timer 
 * T = stops the timer
 * P = pause the timer
 * R = reset the timer
*/

#include "timer.h"

//Set the name for the timer
Timer thisTimer;

//command that is read over serial 
char command = ' ';

void printElapsedTime() {
  Serial.print("Elapsed time = ");
  Serial.print(thisTimer.getElapsedTime());
  Serial.println(" ms");
}

void setup()
{
  Serial.begin(115200);

  //Set the time interval in milliseconds to blink the LED
  thisTimer.setInterval(1000);

  //Set the function the timer will call when its triggered 
  thisTimer.setCallback(printElapsedTime);

  //Start the timer
  thisTimer.start();
}

void loop()
{
  if(Serial.available()) {
    command = Serial.read();

    if(command == 's') {
      thisTimer.start();
      Serial.println("Started");
    } else if(command == 't') {
      thisTimer.stop();
      Serial.println("Stopped");
    } else if(command == 'p') {
      thisTimer.pause();
      Serial.println("Paused");
    } else if(command == 'r') {
      thisTimer.reset();
      Serial.println("Reset Timer");
    }
  }
  
  //Update the timer
  thisTimer.update();
}
