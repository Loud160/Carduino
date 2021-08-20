/* EEPROM Read simple
 *  ****NOTE*** 
 *  Before using this sketch you should first use the EEPROM Write simple example
 *  so there are values in the eeprom to read.If you read the eeprom before writing data 
 *  to it you will read out a value of 255 for every byte
 *  
 * Reads the value of each byte of the EEPROM and displays it on your computer screen
 * The Arduino Mega2560 PRO has 4095 bytes of eeprom space for storage
 */

#include <EEPROM.h>
// start reading from the first byte (address 0) of the EEPROM
unsigned int address = 0;
byte value;

void setup()
{  
  Serial.begin(115200);// initialize serial port  
}

void loop()
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);
  Serial.print("EEPROM Address: ");
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  //increase the eeprom address being read by 1 each time the loop resets
  address = address + 1;

  // reads the eeprom until the end of it is reached 
  if(address == EEPROM.length()){
   Serial.println("The end of the eeprom has been reached");
   while(1){
    // ends the program by going into an inifinite loop  
   }
  } 

  delay(10);
}// end of void loop()
