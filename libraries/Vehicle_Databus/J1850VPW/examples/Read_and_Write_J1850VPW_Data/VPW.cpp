#include <Arduino.h>
#include <HardwareSerial.h>
#include <Math.h>
#include <stdarg.h>
#include "VPW.h"


J1850VPW::J1850VPW() {

}
uint16_t msgSize;
uint8_t msgBuffer[255];

/*
   Initialize serial bus and other necessary information.

   @access  public
   @param object  HardwareSerial reference - Typically Serial1 on Arduino and Teensy
   @return  void
*/
void J1850VPW::Start(int SelectSerial) {
  //save passed serial to our private variable so it can be called whenever
  if (SelectSerial == 0)
  {
    thisPort = &Serial;
  }
  else if (SelectSerial == 1)
  {   
    thisPort = &Serial1;
  }
  else if (SelectSerial == 2)
  {   
    thisPort = &Serial2;
  } else if (SelectSerial == 3)
  {  
    thisPort = &Serial3;
  }
  thisPort->begin(thisBaud);//start serial at the private baud rate 115200
}


void J1850VPW::Debug(int debugSerial) {
 
   if (debugSerial == 0)
  {
    thisSerial = &Serial;
  }
  else if (debugSerial == 1)
  {   
    thisSerial = &Serial1;
  }
  else if (debugSerial == 2)
  {   
    thisSerial = &Serial2;
  } 
  else if (debugSerial == 3)
  {  
    thisSerial = &Serial3;
  }
  thisSerial->begin(thisBaud);//start serial at the private baud rate 115200
    thisSerial->println("J1850VPW Debug Enabled");  
}



bool J1850VPW::WaitForSerial(uint16_t waitTime)
{
  uint32_t StartMil = millis();
  while ((millis() - StartMil) < waitTime)
  {
    if (thisPort->available() > 0) {
      return true;
    }
  }
  return false;
}

bool J1850VPW::checkReceive(uint16_t timeout) {
  if (thisPort->available() > 0)
  {
    msgSize = 0x00;
    int  zeroByte = thisPort->read();
    if (WaitForSerial(timeout) == false) {
      return false;
    }
    uint8_t thisSize =   thisPort->read();
    msgSize = thisSize + 1;
    msgBuffer[0] = thisSize;
    uint8_t chkSize = 0;
    for (uint16_t i = 1; i < thisSize + 1 ; i++)
    {
      if (WaitForSerial(timeout) == false) {
        if (checkMsgSize(thisSize, chkSize) == 1) {
          return true;
        } else {
          return false;
        }
      }
      msgBuffer[i] = thisPort->read();// create offset to incluse message size
      chkSize++;
    }
    return true;
  }
  return false;
}



int J1850VPW::readMsg( uint16_t timeout, uint8_t *len, uint8_t buf[])
{
  if (thisPort->available() > 0)
  {
    msgSize = 0x00;
    int  zeroByte = thisPort->read();
    if (WaitForSerial(timeout) == false) {
      return 0;
    }
    uint8_t thisSize =   thisPort->read();
    *len = thisSize;
    uint8_t chkSize = 0;
    for (uint16_t i = 0; i < thisSize ; i++)
    {
      if (WaitForSerial(timeout) == false) {
        return checkMsgSize(thisSize, chkSize);
      }
      buf[i] = thisPort->read();
      chkSize++;
    }
    return 1;
  }
  return 0;
}


int J1850VPW::checkMsgSize(uint8_t sizeRead, uint8_t SizeCounted) {
  if (SizeCounted > sizeRead) {
    //message read was larger then it should have been
    return 3;
  }
  if (SizeCounted < sizeRead) {
    //message read was incomplete
    return 2;
  }
  if (SizeCounted == sizeRead) {
    //message read is complete
    return 1;
  }
}





void J1850VPW::sendMsg(uint8_t *TempBuf) {
  uint8_t thisSize = TempBuf[0];
  while (  thisPort->availableForWrite() == 0) {}
  thisPort->write(0x00);
  thisPort->write(thisSize);
  for (uint16_t i = 1; i < thisSize + 1; ++i) {
    while (  thisPort->availableForWrite() == 0) {}
    thisPort->write(TempBuf[i]);
  }


  //  int len = TempBuf[0] + 2; // the message uses a leading 0x00 followed by the message size, the message size does NOT include the null byte or the size byte making it message size + 2 every time.
  //  uint8_t newBuf[len];
  //  newBuf[0] = 0x00;
  //  for (uint16_t i = 0; i < len; ++i) {
  //    newBuf[i + 1] = TempBuf[i];
  //  }
  //
  //
  //  for (uint16_t i = 0; i < len; ++i) { //loop mc loopy
  //    while (  VPW->availableForWrite() == 0) {} //do fuckall while no bytes free to write with
  //    //  uint8_t tempbyte = newBuf[i];
  //    VPW->write(newBuf[i]); //write bitch
  //  }


}



void J1850VPW::writeMsg(uint8_t *TempBuf, uint8_t bufSize) {
  while (  thisPort->availableForWrite() == 0) {}
  thisPort->write(0x00);
  thisPort->write((bufSize));
  for (uint16_t i = 0; i < bufSize; ++i) {
    while (  thisPort->availableForWrite() == 0) {}
    thisPort->write(TempBuf[i]);
  }
}

void J1850VPW::showFrame(volatile uint8_t *msg)
{
  uint8_t thisSize = msg[0];
  thisSerial->print("Msg Size[");
  thisSerial->print(thisSize, HEX);
  thisSerial->print("] ");
  thisSerial->print(",  Message: ");
  for (uint16_t i = 1; i < thisSize + 1; i++)
  {
    thisSerial->print(msg[i], HEX);
    thisSerial->print(",");
  }
  thisSerial->println("");
}


void J1850VPW::printFrame(volatile uint8_t *msg, int len)
{
  thisSerial->print("Msg Size[");
  thisSerial->print(len, HEX);
  thisSerial->print("] ");
  thisSerial->print(",  Message: ");
  for (uint16_t i = 0; i < len; i++)
  {
    thisSerial->print(msg[i], HEX);
    thisSerial->print(",");
  }
  thisSerial->println("");
}
