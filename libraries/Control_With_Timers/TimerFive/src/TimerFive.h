/*
 *  Interrupt and PWM utilities for 16 bit Timer5 on ATmega2560
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified April 2012 by Paul Stoffregen - portable to other AVR chips, use inline functions
 *  Modified again, June 2014 by Paul Stoffregen - support Teensy 3.1 & even more AVR chips
 *  Modified February 2016 by Vincent Limorté, porting Timer3 to Timer5 for ATmega2560. Removed teensy support, as i don't own it to test
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */

#ifndef TimerFive_h_
#define TimerFive_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "config/timer_five_pins.h"

#define TIMER5_RESOLUTION 65536UL  // Timer5 is 16 bit


// Placing nearly all the code in this .h file allows the functions to be
// inlined by the compiler.  In the very common case with constant values
// the compiler will perform all calculations and simply write constants
// to the hardware registers (for example, setPeriod).


class TimerFive
{


#if defined(__AVR__)
  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	TCCR5B = _BV(WGM53);        // set mode as phase and frequency correct pwm, stop the timer
	TCCR5A = 0;                 // clear control register A
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
    	/* WGM53 mode goes from BOTTOM to TOP (ICR5) then from TOP to BOTTOM, then from BOTTOM to TOP.
    	 * OVF interrupt is triggered on TOP, thus the period covers 2*ICR5 counts.
    	 * Max period is 8'388'480 µs
    	 */
    	const unsigned long cycles = (F_CPU / 2000000) * microseconds;
	if (cycles < TIMER5_RESOLUTION) {
		clockSelectBits = _BV(CS50);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER5_RESOLUTION * 8) {
		clockSelectBits = _BV(CS51);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER5_RESOLUTION * 64) {
		clockSelectBits = _BV(CS51) | _BV(CS50);
		pwmPeriod = cycles / 64;
	} else
	if (cycles < TIMER5_RESOLUTION * 256) {
		clockSelectBits = _BV(CS52);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER5_RESOLUTION * 1024) {
		clockSelectBits = _BV(CS52) | _BV(CS50);
		pwmPeriod = cycles / 1024;
	} else {
		clockSelectBits = _BV(CS52) | _BV(CS50);
		pwmPeriod = TIMER5_RESOLUTION - 1;
	}
	ICR5 = pwmPeriod;
	TCCR5B = _BV(WGM53) | clockSelectBits;
    }

    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	TCCR5B = 0;
	TCNT5 = 0;		// TODO: does this cause an undesired interrupt?
	resume();
    }
    void stop() __attribute__((always_inline)) {
	TCCR5B = _BV(WGM53);
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	TCCR5B = _BV(WGM53) | clockSelectBits;
    }

    //****************************
    //  PWM outputs
    //****************************
    /*
     * Duty goes from 0 to 1023.
     */
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	if (pin == TIMER5_A_PIN) OCR5A = dutyCycle;
	#ifdef TIMER5_B_PIN
	else if (pin == TIMER5_B_PIN) OCR5B = dutyCycle;
	#endif
	#ifdef TIMER5_C_PIN
	else if (pin == TIMER5_C_PIN) OCR5C = dutyCycle;
	#endif
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	if (pin == TIMER5_A_PIN) { pinMode(TIMER5_A_PIN, OUTPUT); TCCR5A |= _BV(COM5A1); }
	#ifdef TIMER5_B_PIN
	else if (pin == TIMER5_B_PIN) { pinMode(TIMER5_B_PIN, OUTPUT); TCCR5A |= _BV(COM5B1); }
	#endif
	#ifdef TIMER5_C_PIN
	else if (pin == TIMER5_C_PIN) { pinMode(TIMER5_C_PIN, OUTPUT); TCCR5A |= _BV(COM5C1); }
	#endif
	setPwmDuty(pin, duty);
	TCCR5B = _BV(WGM53) | clockSelectBits;
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER5_A_PIN) TCCR5A &= ~_BV(COM5A1);
	#ifdef TIMER5_B_PIN
	else if (pin == TIMER5_B_PIN) TCCR5A &= ~_BV(COM5B1);
	#endif
	#ifdef TIMER5_C_PIN
	else if (pin == TIMER5_C_PIN) TCCR5A &= ~_BV(COM5C1);
	#endif
    }

    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	TIMSK5 = _BV(TOIE5);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	TIMSK5 = 0;
    }
    static void (*isrCallback)();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;

#endif
};

extern TimerFive Timer5;

#endif

