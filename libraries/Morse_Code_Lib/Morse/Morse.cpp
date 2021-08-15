#include "Arduino.h"
#include <HardwareSerial.h>
#include <Math.h>
#include <stdarg.h>
#include "Morse.h"

Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void CCD::init(HardwareSerial* serial) {
	this->ccdBus = serial;
	this->ccdBus->begin(this->ccdBaud);
}


void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}