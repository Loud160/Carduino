/*  EEPROM Write Simple
 *   ***NOTE***
 *   This example should be used in conjuction with the EEPROM READ Simple example.
 *   Use this sketch first to store data in the eeprom and then use the read example to 
 *   view the data that was stored. 
 *   
 *   
 *Using a potentiometry connected to A0 this example will read the ADC counter value
 *from the pot and store the values into your Carduino's EEPROM. 
 *
 *The values stored will remain in the EEPROM even after the Carduino has been disconnected 
 *You can then read these values back out at a later point in time and they will have remained unchanged
 */

#include <EEPROM.h>

/** the current address being used in the EEPROM **/
unsigned int addr = 0;
//give the analog pin being read a name and set what input its using 
#define Potentiometry A0
//when the eeprom is full the LED will turn on and the program stops reading input values
#define LED 13 

void setup(){ 
 pinMode(LED,OUTPUT);
 digitalWrite(LED, LOW);
  }

void loop()
{
  /***
    Need to divide by 4 because analog inputs ranges from
    0 to 1023 and each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/

  int val = analogRead(Potentiometry) / 4;

  /***
    Write the value to the appropriate address currently being used for the EEPROM.
    these values will remain there when the board is
    turned off or disconnected.
  ***/
  EEPROM.write(addr, val);

  // increase the address for the next write by 1
  addr = addr + 1;
  if(addr == EEPROM.length()){
    addr = 0;
    digitalWrite(LED, HIGH);
  } 


  delay(1);
}// end of void loop()
