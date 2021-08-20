/* Reading an Analog Input without Delay
 This example demonstrates the use of analog input by reading an analog voltage with analog pin 0(A0) and
 turning on and off a light emitting diode(LED) that is built into your Carduino. 
 Your Carduino has built in LED's on channels D36 and D38. 
 To turn these LED's ON you must set the respective output pins as LOW.
 
 To visulazie changes in voltage value being read, the LED will turn on and off based on the value read by analogRead(). 
 The higher the voltage, the longer the LED will stay on for.
 
 Required Parts:
 1) 3 terminal potentiometer, any value between 1k and 10,000k will work fine. We will use this to simulate a sensor.
 2) 3 Jumper wires
 
 The circuit:
 * Connect the potentiometer center pin to analog input A0.
 * Connect the left side of the potentiometer to ground tap connection.
 * Connect the right side of the potentiometer to a 5V+ power tap.

*/

//constants won't change. Used here to set pin numbers:
// Pin  36: Carduino LED 1
// Pin 38: Carduino LED 2
const int ledPin =  13;      // the number of the LED pin
const int sensorPin = A0;    // select the input pin for the potentiometer

// Variables that will change:
int ledState = HIGH;   // ledState used to set the LED
int sensorValue = 0;  // Set a starting value of 0
long interval = 1000;  // this variable will change based on the value read for the potentiometer

// the follow variables is set as a uint32_t, because the time, measured in miliseconds(1/1000th of a second),
// will quickly become a very large number and we do not want the variable to over flow,
//When a variable overflows it means the size of the number being stored was larger then the variable type was able to hold.
// For example, uint32_t will take 49.71 days before it reachers a number large enough to cause the variable to overflow
uint32_t previousMillis = 0;// store last time the time was active

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

void loop()
{ /*
    This code runs in a continues loop and constantly checks to see if it's time to read the current value
    of the sensor. The time between reads is based on the sensors ADC counter value
    that will be between 0 and 1023.

    Each time the timer becomes active the sensors value is read and updates the intervul time
    between reads to match the ADC count value.

    The LED state is also changed each time the timer becomes active
    so you can visually see the changes in the time between sensor reads.
  */

  // this is declaired as a local value and is updated every time the loop restarts
  uint32_t currentMillis = millis();

  if (currentMillis - previousMillis > interval) {

    // save the millis count when the timer activated.
    previousMillis = currentMillis;

    // Read the analog input pin and save the value
    sensorValue = analogRead(sensorPin);

    //This is a redundant step but shown for clarity.
    interval =  sensorValue;
    //Now, we can also save the analogRead value directly to the interval value by doing:
    // interval = analogRead(sensorPin);
    //This would allow removing 1 variable and 2 lines of code
    //making the program both smaller and faster.

    // Digital pins only have 2 state and can be treated similar to a true or false statments.
    // We only need to know ONE of the states to turn it on or off.
    if (ledState == LOW)// if it's not LOW then we know it has to be HIGH
      ledState = HIGH;
    else
      ledState = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    // By using this method we only need to use a single digitalWrite to control both the
    //ON and OFF states of the LED. The conventional method for doing this would use similar code to below:
    //    if (ledState == LOW) {
    //      digitalWrite(led, HIGH);
    //    }
    //    else if (ledState == HIGH) {
    //      digitalWrite(led, LOW);
    //    }
  }

  
}// End Void Loop()