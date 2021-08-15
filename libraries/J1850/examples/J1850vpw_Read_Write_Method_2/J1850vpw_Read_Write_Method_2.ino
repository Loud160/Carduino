/*Reading and Writing messages to your J1850VPW transceiver  using method 2

   This method is designed to allow direct control of the messages when they are read and being written by using a size variable with the message array.
   This also has responce codes that indicate how a message was read. This allows for creation of methods to deal with message read errors.


   Commands Used:

   .Start(x) - this starts the serial port for your transceiver on x Serial port. Carduinos J1850VPW transceiver is on Serial3 by default

   .Debug(0) - this starts the serial port for displaying messages on screen using x Serial Port. This can be used in place of Serial.begin()

   .readMsg(searchTime, &Buf_Len, rx_Buf); - Buf_Len and rx_Buf are declaired as variables in your sketch. When a new message is read they are
      store into these variable.This will also return a value that tells you something about the message, 0 is no new message read,
      1 is new message read, 2 is message shorted then expected(incomplete), 3 is message to large(may have read into part off the next message)
      Using the responce codes you are able to impliment error handing when a message is not read correctly..

   you will be creating 2 variables that are used to hold the messages read and the size of what was read.
   In this example they are (uint8_t Buf_Len) and (uint8_t rx_Buf[255]). The transceiver has a fixed buffer size of 255 bytes so trying to
   read and write messages larger then this will cause errors.

   .printFrame(yourMessage,size) - This allows you to display the message your sending to the transceiver over any serial port for debugging purposes.

   .writeMsg(yourMessage, size) - This will send your message array to the transceiver and write the number of bytes listed in size..
*/



#include "VPW.h"

// the name you will use to reference your J1850-vpw data bus
J1850VPW myBus; // The J1850VPW Trancivier and Debug Serial messages use 115,200 baud

// How long will J1850VPW messages be waited for if there is not a message waiting to be read from the Serial port
uint8_t searchTime = 10;

// variables used to store new messages
uint8_t Buf_Len;
uint8_t rx_Buf[255];

// Array structure is formated as the messages raw bytes. You do NOT need to set the message size as your first byte like in method 1
uint8_t vpwMSG1[] = {0x4D, 0x1E};

// Array structure is formated as the messages raw bytes. You do NOT need to set the message size as your first byte like in method
uint8_t vpwMSG2[] = {0x8A, 0x10, 0xF0, 0x22, 0x4A, 0x01, 0x10, 0xAB};



void setup() {
  // initialize the serial port you will be using to write messages to the J1850-VPW transceiver
  myBus.Start(0);// the name of your J1850-VPW data bus and what Serial port it will use(Carduino uses Serial 3 by default)

  myBus.Debug(0);// enable display of J1850-VPW messages as HEX data on this serial port. USB is on Serial 0

}

void loop() {

  readMSG();// Calls the function used to check for new messages and process message replies


  // Even when delays or blocking functions are used, you are still able to store incoming messages in the serial ports buffer.
  delay(1000);
  myBus.writeMsg(vpwMSG1, sizeof(vpwMSG1));
  delay(1000);
  myBus.writeMsg(vpwMSG2, sizeof(vpwMSG2));
}


void readMSG() {

  int msgResponce = myBus.readMsg(searchTime, &Buf_Len, rx_Buf);

  // The msgResponce numbers should be checked in the order you would expect to see them for the purpose speed.
  //We are not expecting erros so check for those last
  if (msgResponce == 1) { // a valid message has been found

    // You can pass individual bytes read into your message array and perform math operations at the same time
    vpwMSG2[2] = rx_Buf[3] + 1;

    //Display the bytes read in a readable format over USB, you must set the message and the size of the message that will be shown
    myBus.printFrame(rx_Buf, Buf_Len);

    //write an array to the J1850VPW data bus, you must set the message and the size of the message that will be written
    myBus.writeMsg(rx_Buf, Buf_Len);

  }
  else if (msgResponce == 0) {
    // no message was read
  }
  else if (msgResponce == 2) {
    // message size was shorter then it should have been
    Serial.println("Msg Was Shorted Then Expected");
  }
  else if (msgResponce == 3) {
    // message size was longer then it should have been
    Serial.println("Msg Was Larger Then Expected");
  }
}
