/* CAN Send Only example
 *  This example allows you to send a messages on an active data bus or to another CAN Shield
 *  This example does NOT look for any messages
 *  You will need to have your CAN sheild connected to an active data bus or to another shield
 *  that is setup to read incoming messages
*/

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10
uint8_t data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
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
  // send data:  ID = 0x101, Standard CAN Frame, message length = 8 bytes, 'data' is the array being sent
  byte sndStat = CAN0.sendMsgBuf(0x101, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
   // send data per 100ms
  delay(100);
  // Since we are NOT doing anything other then sending a single message
  //using a delay here works fine. A timer would have no advange in this situation 
}
