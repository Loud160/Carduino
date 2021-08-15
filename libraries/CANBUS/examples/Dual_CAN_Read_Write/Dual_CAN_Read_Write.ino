/* Read and Write from 2 CAN sheilds with each bus using it's own bufffer
   This example demonstrates how to read and write messages using 2 CAN Shields with each CAN having its own set of buffers so data is not over lapped between busses.
   
   The code is setup using loopback mode so you do NOT need to connect your Carduino to a CAN network or to another CAN BUS shield to see how this example works. To enable communaction with live data buses you simply need to uncomment two line of code that can be found near the bottom of void setup()
  
  CAN0.setMode(MCP_NORMAL); //Remove comment makers to Enable CAN0
  CAN1.setMode(MCP_NORMAL); //Remove comment makers to Enable CAN1
   

   The following code has been seperated to keep CAN0 and CAN1 variables seperate so it is easyier to to see how each variable is created and also how they are then used.  
*/

#include <mcp_can.h> // the CAN BUS Libary needed for this to work
#include <SPI.h> // You will be using SPI to communicate with the CAN hardware so this libary must be included

// Variables used for CAN0
//CAN1 will use it's own set of variables and has it's own buffer so messages are not over writting each other between buses
long TX_Rate0 = 1500; // the time between messages that will be sent
uint32_t lastTX0 = 0;//This the variable that stores when the last message was sent
uint32_t rxId_0;// stores the header a message was read from
uint8_t len_0;// stores the size of a message read, this is handled using sizeof(message)
uint8_t rxBuf_0[8];// the buffer a message is read into
char canMSG_0[128];// stores a formated message using sprintf that is able to display CAN frames in a simple manner
uint8_t data0[] = {0xEE, 0x1A, 0x0D, 0x21, 0x7B, 0x12, 0xF1, 0x56};  // Example of an 8 byte CAN message as an array


//Variables used for CAN1
long TX_Rate1 = 3200;
uint32_t lastTX1 = 0;
uint32_t rxId_1;
uint8_t len_1;
uint8_t rxBuf_1[8];
char canMSG_1[128];
uint8_t data1[] = {0xAA, 0xEE, 0x0D, 0x21, 0x7B, 0x12, 0xF1, 0x56};

MCP_CAN CAN0(10);                               // Set CS to pin 10
MCP_CAN CAN1(9);

void setup()
{
  // CAN is running at 500kbps, our baudrate is running at 115,200Bps. The serial speed here is very slow in comparsion.
  // It is also important to remember that displaying data on screen in string formats are also slowing things down a great deal.
  // When your code is complete you should NEVER leave any Serial.print messages active as they will greatly slow down your program
  // You may find it helpful to use the #if defined() structure to allow an easy way to enable or disable screen print messages for debugging
  Serial.begin(115200);

  // Initialize the CAN Shield or expansion module. If your using a shield make sure it uses a 16MHz crystal clock
  //If your board is not running at 16mhz, you will need to set the speed to your crystals speed below
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) { // Message format: CAN being used,(set CAN format as 11 or 29 bit or allow both
    /*
      The current CAN being Initialized and will use the settings listed after it
        CAN0.begin is the CAN being Initialized
      MCP_ANY is the frame format, valid entries are:
        MCP_ANY and disables filters/masks allowing every messasge to be read
        MCP_STD uses 11 bit filters/masks
        MCP_EXT uses 29 bit filters/masks
        MCP_STDEXT uses mixed 11 and 29 bit filters/masks
      CAN_500KBPS is the CAN bus speed, set this using the same format to match your bus. Valid speeds are:
        CAN_4K096BPS
        CAN_5KBPS
        CAN_10KBPS
        CAN_20KBPS
        CAN_31K25BPS
        CAN_33K3BPS
        CAN_40KBPS
        CAN_50KBPS
        CAN_80KBPS
        CAN_100KBPS
        CAN_125KBPS
        CAN_200KBPS
        CAN_250KBPS
        CAN_500KBPS
        CAN_1000KBPS
      MCP_16MHZ is the speed the CAN Transceiver is running at, valid speeds are 20mhx, 16,mhz and 8mhz. Note - 8mhz clocks may not support higher baud rates very well
      CAN_OK this tells us if the CAN was Initialized correctly or if there was an error

    */
    Serial.println("CAN Shield Was Initialized Successfully!");
  }
  else {
    Serial.println("There Was An Error Initializing The CAN Shield");
    while (1) {} // Create an infinite loop that stops the program since the CAN Shield did not initialize correctly
  }// ends CAN0.begin


  if (CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {    
    Serial.println("CAN Shield 2 Was Initialized Successfully!");
  }
  else {
    Serial.println("There Was An Error Initializing CAN Shield 2");
    while (1) {} 
  }

  
// to enable normal CAN communaction with another device this line would need to be uncommneted added
// When this line is commented out the CAN chip is using loop back mode to read what was written to it. 
  //CAN0.setMode(MCP_NORMAL); //Enables CAN0
  //CAN1.setMode(MCP_NORMAL); //Enables CAN1

}// ends void setup()

void loop()
{
  //check the read receive buffers to see if there is a new message
  checkCan0_MSG();// check CAN0 for messages
  checkCAN1_MSG();// check CAN1 for messages
  SendCAN();// Send CAN frames using a timer. 
}// End of void loop()




//This function is used to read new messages with as they are found
// checkCan1_MSG() does the same thing as this function but is uesed to read CAN1 and does not have comment
void checkCan0_MSG() {
  if (CAN0.checkReceive() == CAN_MSGAVAIL) {

    // If there was a new message avaible then we call the function that is used to read the message from the CAN tranciver
    CAN0.readMsgBuf(&rxId_0, &len_0, rxBuf_0);

    // Determine if the message ID is standard (11 bit) or extended (29 bit) format
    if ((rxId_0 & 0x80000000) == 0x80000000) {

      // The serial prints shown below are formated using sprintf to join multiple parts of the messages into a single message that can be displayed much easier then formating each part seperatly.
      // If the message is using an 29 bit header the line is formatted to fit this format
      sprintf(canMSG_0, "CAN0 Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId_0 & 0x1FFFFFFF), len_0);
    }
    else {
      // If the message is using an 11 bit header the line is formatted to fit this format
      sprintf(canMSG_0, "CAN0 Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId_0, len_0);
    }

    // This is where we display the data that was formated using sprintf
    Serial.print(canMSG_0);

    // This line is used to Determine if message is a remote request frame
    if ((rxId_0 & 0x40000000) == 0x40000000) {
      sprintf(canMSG_0, "CAN0 REMOTE REQUEST FRAME");
      Serial.print(canMSG_0);
    } else {
      // If we are working with a normal CAN frame, we read the message from the RX message buffer while formating it to display on screen using sprintf
      for (byte i = 0; i < len_0; i++) {
        sprintf(canMSG_0, " 0x%.2X", rxBuf_0[i]);
        Serial.print(canMSG_0);
      }
    }
    // Now that the frame has been saved into the buffer and displayed on screen we need to start a new line to keep things simple to view
    Serial.println();
    }

}// End void checkCan0_MSG

void checkCAN1_MSG() {
  if (CAN1.checkReceive() == CAN_MSGAVAIL) {
    CAN1.readMsgBuf(&rxId_1, &len_1, rxBuf_1);
    if ((rxId_1 & 0x80000000) == 0x80000000) {
      sprintf(canMSG_1, "CAN1 Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId_1 & 0x1FFFFFFF), len_1);
    }
    else {
      sprintf(canMSG_1, "CAN1 Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId_1, len_1);
    }
    Serial.print(canMSG_1);
    if ((rxId_1 & 0x40000000) == 0x40000000) {
      sprintf(canMSG_1, "CAN1 REMOTE REQUEST FRAME");
      Serial.print(canMSG_1);
    } else {
      for (byte i = 0; i < len_1; i++) {
        sprintf(canMSG_1, " 0x%.2X", rxBuf_1[i]);
        Serial.print(canMSG_1);
      }
    }
    Serial.println();
  }
}// End void checkCAN1_MSG


// This is a fucntion using a timer to send CAN messages at fixed intervuls 
void SendCAN() {

 //This timer is controlling messages sent on CAN0 and has been commented, the timer used for CAN1 is the same but with out comments
  if (millis() - lastTX0 >= TX_Rate0) {
    lastTX0 = millis();
      // Sends the message and makes sure it sent correctly
    if (CAN0.sendMsgBuf(0x100, sizeof(data0), data0) != CAN_OK) {
      // if the message was not sent correctly this block would be used to address the issue
      Serial.println("Error Sending Message On CAN0");
    }
    //the else block can be ommited and is only here for this example.
    //If the CAN frame sent with out issue you can move along with your code and not worry about it. 
    else {
      // This has only been added for clarity 
      Serial.println("Message Sent On CAN0");
    }
  }// ends the timer controlling the rate messages are sent on CAN0

  //
  if (millis() - lastTX1 >= TX_Rate1) {
    lastTX1 = millis();
    if (CAN1.sendMsgBuf(0x101, sizeof(data1), data1) != CAN_OK) {
     //Do something about the error here 
     Serial.println("Error Sending Message On CAN1");
    }
  }


}// end void SendCAN
