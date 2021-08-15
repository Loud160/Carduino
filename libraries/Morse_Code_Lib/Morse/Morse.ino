#include "Morse.h"

//Morse morse(13);
//Morse J1850(Serial1);
CCD ccdBus;
void setup()
{
 ccdBus.init(&Serial21);
}

void loop()
{
//  morse.dot(); morse.dot(); morse.dot();
//  morse.dash(); morse.dash(); morse.dash();
//  morse.dot(); morse.dot(); morse.dot();
//  delay(3000);
}
