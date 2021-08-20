/* Read Analog Inputs With a Loop
  This example impliments the use of a simple timer and a new function that is used to read multiple sensors into an array using a for loop.
  The array size is determined dynamically, so as you add or remove sensors being read from the array nothing else in the program needs to be changed.

  Required Parts:
  1) Two or more 3 terminal potentiometer, any value between 1k and 10,000k will work fine.
  We will use these to simulate multiple sensors.

  2) Jumper wires

  The circuit:
  Perform the following steps for all potentiometers
   Connect the center terminal of each potentiometer to analog input pin between A0 and A11
   Connect the left side of each potentiometers to ground.
   Connect the right side of each potentiometer to a 5V.

*/


int Sensors[] = {A0, A2, A7, A10}; //creates an array of analong pins to read.
int sensorValue[sizeof(Sensors)]; // Initilze the size of the sensor value array, based on the number of sensors listed in the Sensors array.
long interval = 3000; // the amount of time between sensor readings
//uint32_t will take 49.71 days before it reachers a number large enough to cause the variable to overflow
uint32_t previousMillis = 0;// store last time the time was active
long Counter = 0; //cycler through the ADC values that are stored in the array.

void setup() {
  // Begin a serial port that will display data over USB
  Serial.begin(115200);// Set the baudrate used to 115200, setting this slower will affect program performance
}

void loop()
{

  // this is declaired as a local value and is updated every time the loop restarts
  uint32_t currentMillis = millis();

  //This is just a basic Timer, but we can use it to control how offten we are reading our sensor values.
  if (currentMillis - previousMillis > interval) {
    // save the current time isn millis when the timer activated.
    previousMillis = currentMillis;

    // Tells use were starting a new read
    Serial.println("Start New Sensor Reading:");

    // Calls the function found after void loop() near the bottom of this example
    ReadSensors();


    Serial.print("Sensor Read took ");

    // Do some math, we know what time we entered this timer so we can compare that with the
    // current millis time reading to see how long it took to complete the  ReadSensors() function.
    long readTime = millis() - previousMillis;
    //display the time we just caluclated
    Serial.print(readTime);// displays the time diffrences between the current time and when this timer was entered
    Serial.println("/1000th of a second to complete");// 1 millis is equal to 1 millisecond.

    // Now this is an example of reading a sensor value directly from the arry using a number rather then [i].
    Serial.print("Sensor ");
    Serial.print(Counter);// You can enter a number here that matches a sensor used in your array. For example if you read 4 analong pins you can enter any number between 0 and 3(since 0 is a sensor it counts)

    // Simple formula that turns the value read by the ADC into a voltage value.
    float voltage = sensorValue[Counter] * (5.0 / 1023.0);
    Serial.print(", Voltage: ");
    Serial.print(voltage);
    //add some blank space before we take the next reading
    Serial.println();//
    Serial.println();

    // increase the counter number by 1
    Counter++;
    // If the counter has gone higher then the number of sensors being read, reset the counter back to 0
    if (Counter >= (sizeof(Sensors)) / sizeof(int)) {
      Counter = 0;
    }// This is the end of the Counter

  }// This is the end of the timer




}// End Void Loop()

void ReadSensors() {
  // We use a simple for loop  to loop though all the pins in our sensor array.
  //We also use sizeof(array) so that we can change the number of sensors being read with out having to change any of this code.
  for (int i = 0; i < (sizeof(Sensors)) / sizeof(int); i++) {
    // value of the reading is saved to an array that can be accessed anywhere in the program simply by inserting the sensor placment in the array you want to use
    sensorValue[i] = analogRead(Sensors[i]);
    //****************** Try commenting out the 5 lines below and see how it impacts the amount of time it takes to read the sensors *********************
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" ADC: ");
    Serial.print(sensorValue[i]);
    Serial.print(",  ");
    //***************Stop removing lines here ********
  }
  Serial.println();
}// End Void ReadSensors()