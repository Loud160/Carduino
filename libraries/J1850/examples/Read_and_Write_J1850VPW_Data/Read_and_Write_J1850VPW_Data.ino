#include "timer.h"
#include "timerManager.h"
#include "VPW.h"

// the name you will use to reference your J1850-vpw data bus
J1850VPW myBus;

// How long will J1850VPW messages be waited for if there is not a message waiting to be read from the Serial port
uint8_t searchTime = 10;

//In this sketch, there are 2 seperate examples using diffrent methods to read and write to the J1850 VPW tranciver
int tryMethod = 1; // Set this to 2 in order to try the second method of reading and writing to the data bus


// Array used in method 1, array structure is setup at: Size of message is 2 bytes, the message is 0x4D 0x1E
uint8_t Vpw_MSG_1[] = {0x02, 0x4D, 0x1E};

// using method 2 the size of the array is not included in the array
uint8_t Vpw_MSG_2[] = { 0x8A, 0x10, 0xF0, 0x22, 0x4A, 0x01, 0x10, 0xAB};
//Example 2 also demonstrats using an undefined array
uint8_t exampleMSG[] = {};

// variables used to store new messages read using method 2
uint8_t Buf_Len;
uint8_t rx_Buf[255];


// Name and create individual timers for each VPW message to send and how often to send the message
// sends a message using method 1 on a timer
Timer Timer_1_Name;
long Timer_1_Name_interval = 510;
// sends a message using method 2 on a timer
Timer Timer_2_Name;
long Timer_2_Name_interval = 831;


void setup() {
  // initialize the serial port you will be using to write messages to the J1850-VPW transceiver
  myBus.Start(0);// the name of your J1850-VPW data bus and what Serial port it will use(Carduino uses Serial 3 by default)

  //myBus.Debug(0);// enable display of J1850-VPW messages as HEX data on this serial port. USB is on Serial 0

  //initialize each timer that will be sending messages to the J1850-VPW tranciver
  Timer_1_Name.setInterval(Timer_1_Name_interval);
  Timer_2_Name.setInterval(Timer_2_Name_interval);

  // Sets the function each timer will call when it activates
  Timer_1_Name.setCallback(writeVPW_1);
  Timer_2_Name.setCallback(writeVPW_2);

  // Starts the timer to automatically send J1850-VPW messages at preset intervals
  TimerManager::instance().timerStart();

}// ends setup()

// add back into script commander
//00 17 73 65 74 76 69 6e 31 4a 34 46 41 32 39 31 39 36 50 37 34 30 34 34 35
void loop() {
  // checks if its time to write a messages to the J1850-VPW data bus yet
  TimerManager::instance().update();

  if (tryMethod == 1) {
    // this method returns a true or flase if there is a new mesasge that was read
    if (myBus.checkReceive(searchTime)) // Checks if there is a new message, set maximum search time for complete message
    {
      readMethod1();
    }
  } else {
    // this method uses error handling for messagea that are not read correctly
    readMethod2();
  }




}// end void loop()



void readMethod1() { 
  for (uint16_t i = 0; i < myBus.msgSize; i++)
  {
    // saves the current message that has been read into an example array
    exampleMSG[i] = myBus.msgBuffer[i];
  }

  //Display the bytes read in a readable format
  myBus.showFrame(exampleMSG);

  //write an array
  myBus.sendMsg(exampleMSG);
}// ends readMethod1()


void readMethod2() {
  int msgResponce = myBus.readMsg(searchTime, &Buf_Len, rx_Buf);
  if (msgResponce == 1) {
    Serial.println("Msg Found");
    for (uint16_t i = 0; i < Buf_Len; i++)
    {
      // saves the rx_buf into an array
      exampleMSG[i] = rx_Buf[i];
    }
    myBus.printFrame(exampleMSG, Buf_Len);
    myBus.writeMsg(exampleMSG, Buf_Len);
  }
  else if (msgResponce == 0) {
    // no message was read
  }
  else if (msgResponce == 2) {
    // message size was shorted then it should have been
    Serial.println("Msg Was Shorted Then Expected");
  }
  else if (msgResponce == 3) {
    // message size was longer then it should have been
    Serial.println("Msg Was Larger Then Expected");
  }
}// ends readMethod2()



// These Fucntions are called when the timer fires for a timer by name
void writeVPW_1() {
  // write this messages over serial to your J1850-VPW tranciver using method 1
  myBus.sendMsg(Vpw_MSG_1);
}


void writeVPW_2() {
   // write this messages over serial to your J1850-VPW tranciver using method 1
   myBus.writeMsg(Vpw_MSG_2, sizeof(Vpw_MSG_2));
 // myBus.sendMsg(Vpw_MSG_2);
}
