/* Reading an Analog Input without Delay
 This example demonstrates the use of analog input by reading an analog voltage with analog pin 0(A0) and
 turning on and off a light emitting diode(LED) that is built into your Carduino. 
 Your Carduino has built in LED's on channels D36 and D38. 
 To turn these LED's ON you must set the respective output pins as LOW.
 
 To visulazie changes in voltage value being read, the LED will turn on and off based on the value read by analogRead(). 
 The higher the voltage, the longer the LED will stay on for.
 
 Required Parts:
 1) Two 3 terminal potentiometer, any value between 1k and 10,000k will work fine.
 We will use this to simulate a sensor.

 2) 6 Jumper wires
 
 The circuit:
 *Perform the following steps for both potentiometers*
 * Connect the center terminal of one potentiometer to analog input A0 and the center terminal of the second one to A1
 * Connect the left side of both potentiometers to ground.
 * Connect the right side of both potentiometer to a 5V.

*/

//constants won't change. Used here to set pin numbers:
// Pin  36: Carduino LED 1
// Pin 38: Carduino LED 2
const int ledONE =  36;      // the number of the LED pin
const int ledTWO =  38; 
const int sensorONE = A0;    // select the input pin for the potentiometer
const int sensorTWO = A1;

// Variables that will change:
int ledONE_State = HIGH;   // Set the state of LED 1 to OFF. 
int ledTWO_State = HIGH;   // Set the state of LED 2 to OFF. 
int sensorONE_Value = 0;  // Set a starting value of 0
int sensorTWO_Value = 0;  // Set a starting value of 0

// the follow variables is set as a uint32_t, because the time, measured in miliseconds(1/1000th of a second),
// will quickly become a very large number and we do not want the variable to over flow,
//When a variable overflows it means the size of the number being stored was larger then the variable type was able to hold.
// For example, uint32_t will take 49.71 days before it reachers a number large enough to cause the variable to overflow
uint32_t previousMillis_ONE = 0;// store last time the time was active
uint32_t previousMillis_TWO = 0;// store last time the time was active
void setup() {
  // set the digital pin as output:
  pinMode(ledONE, OUTPUT);
  pinMode(ledTWO, OUTPUT);
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

//Timer used for LED ONE
  if (currentMillis - previousMillis_ONE > sensorONE_Value) {

    // save the millis count when the timer activated.
    previousMillis_ONE = currentMillis;

    // Read the analog input pin and save the value
    sensorONE_Value = analogRead(sensorONE);

    if (ledONE_State == LOW)// if it's not LOW then we know it has to be HIGH
      ledONE_State = HIGH;
    else
      ledONE_State = LOW;
       digitalWrite(ledONE, ledONE_State);
    
  }
  
 //Timer used for LED TWO
  if (currentMillis - previousMillis_TWO > sensorTWO_Value) {

    // save the millis count for the second timer when activated.
    previousMillis_TWO = currentMillis;

    // Read the second analog input pin and save the value
    sensorTWO_Value = analogRead(sensorTWO);

    if (ledTWO_State == LOW)// if it's not LOW then we know it has to be HIGH
      ledTWO_State = HIGH;
    else
      ledTWO_State = LOW;
    digitalWrite(ledTWO, ledTWO_State);
    
  }

  
}// End Void Loop()