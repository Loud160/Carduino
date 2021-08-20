/**
 * 2019 Vincent Limorté
 * Test and sample using Timer5 lib.
 * Set a PWM pulse, with 1 000 000 microsec period, and 256/1024 payload.
 * Led is on 1/4 second, and off for 3/4 second
 */

#include "TimerFive.h"

void setup()
{
	// PWM pins attached to Timer5 are 44,45 and 46
	// TIMER5_C_PIN is 44
	Timer5.initialize(1000000);
	Timer5.pwm(TIMER5_C_PIN, 256);
}

void loop()
{
	// nothing
}
