/*
  DigitalReadSerial

  The example demonstrates two things, how to read a digital pin when its used as an input and also how to display the state of the pin over USB so it can be viewed in the Serial Monitor. 
  
  You can use and pin number that starts with a D and this will work the same. For this example we will be using pin D2 to connect a switch to. 

 Connections:
 1) Connect one side of your push button/rocker switch to the digital pin you are using(if you are not using D2). 
 
 2) Connect the other side of your switch to one of the ground connections either on your Mego2560 PRO 
    or on one of the ground points of your Carduino. 
 
 3) We are going to use the Arduio's internal pullup resistor to supply power to the digital pin being used  
    so the pin will read that it is "High" when the switch is not connected. 
 
 4) Once you have made the switch connections, connect your Arduino to your PC
    using a USB cable and upload the sketch. 
 
 5) Open your Serial monitor in Arduino and make sure your 
    baud rate is set at 115200.

 
*/

// This gives the digital pin being used a name so 
// that is easy to reference anywhere it is used in the program
int mySwitch = 2;

// Create a variable to store the value that's been read into
int switchState;

// create a variable to hold the last state of the switch 
int lastSwitchState;


void setup() {
  
  // initialize serial port at 115200 baud
  Serial.begin(115200);
  
  // Set the pin mode for the switch and enable the pull up resistor
  pinMode(mySwitch, INPUT_PULLUP);
}


void loop() {
  // read the input pins current state  and save it into a variable 
   switchState = digitalRead(mySwitch);   
   
   //Compare the state that was just read with the last known state to see if its changed
   if (switchState != lastSwitchState) {
     
    // If the button state changed update the last know value variable with the current state 
      lastSwitchState = switchState;
    
          //Now determine what state the switch is in and display a message accordingly 
      if (lastSwitchState == 0){
        Serial.println("Button is ON");       
      }else{
        Serial.println("Button is OFF");  
      } 
  } 
  
   
  // adding this delay in between reads for stability
  delay(1);
}