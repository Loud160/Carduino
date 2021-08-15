/*
Analog Input converted to PWM Output
Read a 0-5v input value from A0 and convert the reading into a PWM value 
that we can use to control the brightness of the onboard LED of the Arduino Mega2650 PRO.


Example Requires:
1) A 3 wire potentiometry(1k to 10K value pot will work fine)
2) 3 Jumper wires

Connections:
Connect the center terminal of your potentiometry to A0
Connnect the Left side terminal of the potentiometry to ground
connect the right side terminal of the potentiometry to 5v

***NOTE***
Your Arduino Mega2560 PRO requires specfic channels to use PWM with. 
Digital pins 2&3, 5-12,and 44-46 all support PWM at up to 490Hz
Digital pins 4 and 13 support PWM at 980Hz
These frequices can be changed using advanced examples for direct port control 


*/


int ledPin = 13;      // Use the onboard LED of your Arduino
int analogPin = A0;   // potentiometer connected to analog pin 0
int val = 0;         // variable to store the read value

void setup() {
  pinMode(ledPin, OUTPUT);  // sets the pin as output
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  analogWrite(ledPin, val / 4); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}