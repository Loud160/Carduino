A graphical breakdown and description of the altered pinouts used for the Uno shield sheilds can be found under
About Carduino/CarduinoShieldPinDiagram in this subsection. 

*************************** Pins used for specfic fucntions with Carduino ****************
LED 0(Built into Mega) = D13
LED 1 = D36 Set LOW to activate LED
LED 2 = D38 Set LOW to activate LED

******************** SPI CS/SS ****************************
CS/SS for SPI Uno Shield A = D12
CS/SS for SPI Uno Shield B = D46
CS/SS for SPI External(Under Uno Sheild B) = D34

******************** I2C ****************************
I2C Pullup resistor breakouts under Uno Shield A(near I2C connections)
2 external I2C circuits are provided for expansion, there is one under each Uno shield near the I2C pins

************** DS18 Temp ***********************
**DS18 Tempeture Sensor Circuits have built in 4.7K pullups** 
Sensor 1 = D28
Sensor 2 = D29
(DS18 Temp Sensor circuits can support two sensors per input channel)

************** J1850VPW Expansion module ***********************
**J1850VPW Data line connection is found near the upper left corner of module**
This Moudule uses Serial 3 to read and write messages from the MEGA2560 PRO
Modules Reset is on D41, pull LOW to reset module


************** CAN BUS Expansion module ***********************
CS/SS is on D26
Interupt(on read) is on D53(this is a pcint pin)
CAN Reset is on D43, pull LOW to reset module 

************** 1 Wire Temp Sensors ***********************
**circuit uses a 5v pullup** Do not apply power to circuits **
**This is used to read 1 wire automotive thermistor sensors **
Sensor 1 is A14
Sensor 2 is A15


************** 5V Automotive Sensors ***********************
**5V Ref and Ground MUST be supplied from Carduino **
**Do NOT apply external power to these circuits or attempt to "piggyback" vehcile sensors **
Sensor 1 is A12
Sensor 2 is A13


************** Accelerometer Expansion module **************
CS/SS Pin is on D31


************** GPS Expansion module ************************
** NOTE Uno Shield B & GPS Share a Serial2 **
**When GPS is used Uno shield B 0/1(Mega D16/D17) are unavaible)**
GPS Moudle uses Serial 2 for sending and reading Data


************** Exh Probe module ************************
** Use K-Type thermocoupler **
CS/SS Pin is on D25

************** SD CARD module ************************
CS/SS Pin is on D32
SD Card Detect is on Pin D34

Buzzer(Optional) = D39 Set HIGH to activate buzzer
