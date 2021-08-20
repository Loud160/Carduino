/* CAN Loopback Self Test
 * This example is used to send a message every 1000ms and then reads back the message it sent using loopback mode
 * You do NOT need to be connected to a data bus for this example.  
 * This code will simply test for functionality between your Arduino and the CAN hardware. 
 */

#include <mcp_can.h>
#include <SPI.h>

// CAN TX Variables
uint32_t prevTX = 0;     // Variable to store last execution time
long invlTX = 1000;      // One second interval constant
uint8_t  data[] = {0x01, 0xFA, 0x10, 0xAE, 0xFF, 0xE3, 0xD7, 0x9A};  // Example CAN message to write

// CAN RX Variables
uint32_t rxId;
uint8_t len;
uint8_t rxBuf[8];

// Serial Output String Buffer
char msgString[128];

//Set the name of your CAN bus and what Slave Select(Chip Select)pin is being used
MCP_CAN CAN0(10);// Set CS to pin 10


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

  
// to enable normal CAN communaction with another device this line would need to be uncommneted added
// When this line is commented out the CAN chip is using loop back mode to read what was written to it. 
  //CAN0.setMode(MCP_NORMAL); //Enables CAN0
}

void loop()
{
if (CAN0.checkReceive() == CAN_MSGAVAIL)              // Is there is a new message on CAN0
  {
    //Read the new message and save it into the buffers
    CAN0.readMsgBuf(&rxId, &len, rxBuf);// Read data: len = data length, buf = data byte(s)
     
     // Determine if ID is standard (11 bits) or extended (29 bits)
    if((rxId & 0x80000000) == 0x80000000)             // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);

   // Determine if message is a remote request frame.
    if((rxId & 0x40000000) == 0x40000000){           
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }        
    Serial.println();
  }

 // Now send a message at a one second intervals. 
  if(millis() - prevTX >= invlTX){                   
    prevTX = millis();
    byte sndStat = CAN0.sendMsgBuf(0x7FF, 8, data);//writes the message to the data bus
    if(sndStat == CAN_OK)//Now check if the message was sent correctly
      Serial.println("Message Sent Successfully!");
    else
      Serial.println("Error Sending Message...");
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/