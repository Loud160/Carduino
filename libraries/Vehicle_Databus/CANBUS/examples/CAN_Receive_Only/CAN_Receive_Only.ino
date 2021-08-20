/* CAN Receive Only example
 *  This example allows yoo to listen to messages on an active data bus or from another CAN Shield
 *  This example does NOT send any messages, its just listing for them
 *  You will need to have your CAN sheild connected to an active data bus or to another shield
 *  that is being used to send messages.  
*/

#include <mcp_can.h>
#include <SPI.h>

uint32_t rxId;// ID or headers of frame that was read
uint8_t len = 0;//number of bytes in the message
uint8_t rxBuf[8];// Bufffer to hold the bytes read
char msgString[128];// Buffer to store the formated serial string
MCP_CAN CAN0(10);// Set CS to pin 10

void setup()
{
  Serial.begin(115200);  
  // Initialize CAN Shield at 16MHz with a data bus baudrate of 500kb/s, masks and filters disabled
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("CAN Initialized Successfully!");
  else
    Serial.println("Error Initializing CAN...");
  
  CAN0.setMode(MCP_NORMAL);// Set CAN Shield to normal operation mode  
  Serial.println("CAN Receive Example...");
}

void loop()
{
  if (CAN0.checkReceive() == CAN_MSGAVAIL)    // Check for a new message on CAN0
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
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
}

/