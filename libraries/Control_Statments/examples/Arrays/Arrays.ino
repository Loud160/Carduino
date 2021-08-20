/*
  Storeing digital pin numbers in Arrays

  The example demonstrates how to use an array to hold pin numbers and
  loop though them sequence.  For example, you can turn on multiple LEDs in
  sequence, then turn them back off in the same order or reverse the order. 

  By using an array to store the pin number, the pins used to not 
  have to be in order, you can use any combanation of pins and set the order they are used..
*/

int delayTime = 100;      // The higher the number, the slower the timing.
int ledPins[] = {2,7,4,6,5,3}; // Create an array of pin numbers to use

int thisPin; // the pin currently be used
int pinCount = 6;        // The number of pins (i.e. the length of the array)

void setup() {
    
     // Use a for loop to initialize each pin as an output:
    for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
        pinMode(ledPins[thisPin], OUTPUT);
    }
}

void loop() {
  // Loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    // Turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);
    delay(delayTime);
    // Turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);
  }

  // Loop from the highest pin to the lowest:
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    // Turn the pin on:
    digitalWrite(ledPins[thisPin], HIGH);
    delay(delayTime);
    // Turn the pin off:
    digitalWrite(ledPins[thisPin], LOW);
  }
}
