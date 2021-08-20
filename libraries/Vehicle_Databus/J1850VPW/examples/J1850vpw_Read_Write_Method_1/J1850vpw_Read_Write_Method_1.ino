/*Reading and Writing messages to your J1850VPW transceiver  using method 1
 * 
 * This method is optimized to allow reading and writing messages with your J1850VPW transceiver using simple methods
 * that mimimize the amount of code needed while keeping a simmple format to work with. This method is very versitial 
 * and can be utilized in a number of diffrent ways. Below you will find several of the ways your able to read, alter and rewrite data
 * 
 * Commands Used:
 * 
 * .Start(x) - this starts the serial port for your transceiver on x Serial port. Carduinos J1850VPW transceiver is on Serial3 by default
 * 
 * .Debug(0) - this starts the serial port for displaying messages on screen using x Serial Port. This can be used in place of Serial.begin()
 * 
 * .checkReceive(x) - This returns a boolean responce and can be used anywhere in your code, if there is a new message it will also store that 
 *    new message in .msgBuffer[], x is the ammount of time that will be waited to determine if there is a new mmessage waiting to be read. 
 *    This is be passed using a variable or nummber.
 * 
 * .msgSize - When a new message is found, the size of the message is stored here and can be used anywhere in your code.
 * 
 * .msgBuffer[] - This array is able to hold up to 255 bytes of data and can be used any where in your code, it will only 
 *    store a new message after .checkReceive(x) returns with a true responce. 
 *    
 * .showFrame(yourMessage) - This allows you to display the message your sending to the transceiver over any serial port for debugging purposes. 
 * 
 * .sendMsg(yourMessage) - This will send your formated message array to the transceiver.
 */



#include "VPW.h"

// the name you will use to reference your J1850-vpw data bus
J1850VPW myBus; // The J1850VPW Trancivier and Debug Serial messages use 115,200 baud

// How long will J1850VPW messages be waited for if there is not a message waiting to be read from the Serial port
uint8_t searchTime = 10;

// Create an empty array to read new messages into
uint8_t storeMSG[] = {};

// Array structure is setup at: Size of message is 2 bytes, the message is 0x4D 0x1E
uint8_t vpwMSG1[] = {0x02, 0x4D, 0x1E};

// Array structure is setup at: Size of message is 8 bytes, the message is 0x8A 0x10 0xF0 etc
uint8_t vpwMSG2[] = { 0x08, 0x8A, 0x10, 0xF0, 0x22, 0x4A, 0x01, 0x10, 0xAB};



void setup() {
  // initialize the serial port you will be using to write messages to the J1850-VPW transceiver
  myBus.Start(0);// the name of your J1850-VPW data bus and what Serial port it will use(Carduino uses Serial 3 by default)

  myBus.Debug(0);// enable display of J1850-VPW messages as HEX data on this serial port. USB is on Serial 0

}

void loop() {
  if (myBus.checkReceive(searchTime)) // Checks if there is a new message, set maximum search time for complete message
  {
    readMSG();// Calls the function where you read the data into your buffer
  }

  // Even when delays or blocking functions are used, you are still able to store incoming messages in the serial ports buffer.
  delay(1000);
  myBus.sendMsg(vpwMSG1);
  delay(1000);
  myBus.sendMsg(vpwMSG2);
}


void readMSG() {
  for (uint16_t i = 0; i < myBus.msgSize; i++)
  {
    // saves the current message that has been read into an example array
    storeMSG[i] = myBus.msgBuffer[i];
  }

  // You can pass indivgual bytes read into your formated message array and perform math operations at the same time
  vpwMSG1[2] = storeMSG[3] + 1;

  // You can also pass values that have been read directly from the serial buffer into formated message array and perform math operations at the same time
  vpwMSG2[3] = myBus.msgBuffer[4] + 2;

  //Display the bytes read in a readable format over USB
  myBus.showFrame(storeMSG);

  //write an array to the J1850VPW data bus
  myBus.sendMsg(storeMSG);
}
