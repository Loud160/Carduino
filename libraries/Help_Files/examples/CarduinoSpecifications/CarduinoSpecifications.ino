Carduino Hardware Specifications

********************************************Power Supply **********************************************
Carduino 12v Power Taps: 2A MAX
Carduino Board Power Input: 9-18V(20v max)
Carduino on-board 5v power supply:
using Carduinos main connector: 1 amp continuous (at 13.8 volts) **self reseting fuse will trip at 1.2 amps**
using Carduino USB input: 500mA peak, suggested to keep current draw under 250mA
using Arduino MEGA2560 PRO(EMDED) USB: Carduino should never be powered by the Arduinos onboard USB connector if present

********************************************MEGA2560 PRO I/O Pins **************************************
Analog Input Pins: 16, 8 of these support pcintCarduino
Digital I/O Pins: 54 digital pins, 8 of these support hardware interupts, 15 support PWM output
DC voltage supplied by any I/O Pin: 0-5V
Maximum DC voltage applied to any I/O Pin: 5V
Maximum DC Current supplied per I/O Pin: 20 mA(30mA peak)

*******************************************MEGA2560PRO Processor************************************
Total Number Of Serial Ports: 4(3 usable, serial 0 is tied to Carduinos USB)
Flash Memory:  256 KB total(8 KB used by bootloader)
Processor RAM: 8 KB
Builtin EEPROM:4 KB
Clock Speed: 16 MHz(can be increased to 20mhz with crystal change)

*********************************************Carduino Hardware Limiations********************************
Maximum Operating Temperature Range: -50 to +120 degrees celsius 
Preferred Operating Temperature Range:  -23 to 100 degrees celsius 
Voltage on any pin(execpt Reset): -0.5 to Vcc +.5
Maximum DC Current for all I/O pins Combined: 600mA
Carduino 12 pin connectors: 3 amps per terminal(9 amps max per plug)
Carduino 12 pin connector type: Molex Mini-Fit Dual Row
https://www.molex.com/molex/products/family/minifit_power_connector_solutions
