#ifndef VPW_H
#define VPW_H

class J1850VPW {

  public:
    J1850VPW(); //initializer - you could pass the serial parameter here also if updated for it
    void Start(int SelectSerial); //pass serial wanted as a pointer to the function VPWStart(This is then saved to the private VPW variable below)
    void sendMsg(uint8_t *TempBuf); //send data command
    void Debug(int debugSerial);
    bool WaitForSerial(uint16_t waitTime);
    bool checkReceive(uint16_t timeout);
    uint8_t msgSize;
    uint8_t msgBuffer[255];
    int readMsg(uint16_t timeout, uint8_t *len, uint8_t *buf);               // Read message from receive buffer
    void writeMsg(uint8_t *TempBuf, uint8_t bufSize);
    int checkMsgSize(uint8_t sizeRead, uint8_t SizeCounted);
    void printFrame(volatile uint8_t* msg, int len);
    void showFrame(volatile uint8_t *msg);

  private:
    HardwareSerial *thisPort;
    HardwareSerial *thisSerial;
    uint32_t  thisBaud = 115200; //baud rate private variable
};

#endif
