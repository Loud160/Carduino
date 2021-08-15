/*Calling a function Using multiple Timers
 * 
 * The example demonstrates how to use multiple timers, each timer is using varraying intervuls 
 * and eachh timer will call a unique fucntion when the timer period is reached. There are methods for
 * the timers to run in constant loops were it will continue to call the fucntion each timeout, or
 * a function can be called for a specfic number of illerations.  
 * 
 * For example, in this example timers 1-3 are only run once and timers 4-8 run in a constant loop. 
 * However timer 8 has been configured to restart timer 1 periodically to demonstrate how to make a  
 * timer interact with another timer for more advanced use.
 * 
 * While the timers can be used at very low time periods, for the sake of demonstration the timers
 * have been configured to run slowly so you can watch how they work in the serial monitor. 
  
*/

#include "timer.h"
#include "timerManager.h"

Timer Timer_1_Name;
long Timer_1_Name_time = 3210;

Timer Timer_2_Name;
long Timer_2_Name_time = 1531;

Timer Timer_3_Name;
long Timer_3_Name_time = 2312;

Timer Timer_4_Name;
long Timer_4_Name_time = 6923;

Timer Timer_5_Name;
long Timer_5_Name_time = 7316;

Timer Timer_6_Name;
long Timer_6_Name_time = 5367;

Timer Timer_7_Name;
long Timer_7_Name_time = 6121;

Timer Timer_8_Name;
long Timer_8_Name_time = 9798;

void sayHello1() {
  Serial.println("Hello from the timer 1");
}

void sayHello2() {
  Serial.println("Hello from the timer 2");
}

void sayHello3() {
  Serial.println("Hello from the timer 3");
}

void sayHello4() {
  Serial.println("Hello from the timer 4");
}

void sayHello5() {
  Serial.println("Hello from the timer 5");
}

void sayHello6() {
  Serial.println("Hello from the timer 6");
}

void sayHello7() {
  if (Timer_8_Name.isPaused()) {
    Serial.println("Timer 7 is restarting Timer 8");
    Timer_8_Name.start();
  }
  else {    
    Serial.println("Timer 7 is pausing Timer 8");
    Timer_8_Name.pause();
  }
}

void sayHello8() {
  Serial.println("Timer 8 is restarting Timer 1");
  if (Timer_1_Name.isRunning() == false) {
    Timer_1_Name.start();
  }

}

void setup() {
  Serial.begin(115200);

  // setTimeout means it will only be run once unless you call name.start() to use it again.
  // if you call name.reset() while the timer is still running it will resart the timer
  // if you pause the timer, when you call name.start() the timer will pick up where it left off
  Timer_1_Name.setTimeout(Timer_1_Name_time);
  Timer_2_Name.setTimeout(Timer_2_Name_time);
  Timer_3_Name.setTimeout(Timer_3_Name_time);

  //setInterval is a timer that runs in a constant loop. Each time it is called it restarts the timer
  // name.start(), name.stop(), name.pause() will still work on these timers
  Timer_4_Name.setInterval(Timer_4_Name_time);
  Timer_5_Name.setInterval(Timer_5_Name_time);
  Timer_6_Name.setInterval(Timer_6_Name_time);
  Timer_7_Name.setInterval(Timer_7_Name_time);
  Timer_8_Name.setInterval(Timer_8_Name_time);

  //Set the function each timer will call when it activates 
  Timer_1_Name.setCallback(sayHello1);
  Timer_2_Name.setCallback(sayHello2);
  Timer_3_Name.setCallback(sayHello3);
  Timer_4_Name.setCallback(sayHello4);
  Timer_5_Name.setCallback(sayHello5);
  Timer_6_Name.setCallback(sayHello6);
  Timer_7_Name.setCallback(sayHello7);
  Timer_8_Name.setCallback(sayHello8);


  //Start all the timers
  TimerManager::instance().start();
}

void loop()
{
  //Update all the timers at once
  TimerManager::instance().update();

}