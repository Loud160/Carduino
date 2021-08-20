**************************************** NOTE **********************************************
Carduino MEGA2560 PRO Version 1.0 uses an altered pin mapping from another other Arduino board.
Currently the boards internal pin mapping has NOT been altered but may be changed at some point
in the future so it is important to note what version Carduino board you are currently using. 

********************************** PINOUT CHANGE EXPLANATION *******************************
In order to maximuis the potential of the Carduino design, how each pin was assigned needed
to be changed. Not just to make creation of the Carduino board less expencive, but also to 
make the best possible use of all the avaible pins on the Arduino Mega processor. Many times
when stacking multi Uno shields you will encounter sitations where shield pins over lap making
the shields incompatible. To fix this issue, the way the pins were laid out needed to be altered.
Moving the pins around exactly simple, since each pin on the Arduino has multiple functions it 
can be used for. 

The changes below are how the NEW pinout compares to a standared Arduino UNO shield. The pinson the
inside of the example diagram are the default(normal) pins as they are assinged and laid outon the
Arduino UNO. The pin mapping on the outside of the example are how the pins have been assigned on 
your Carduino. It was impossible to keep every pin fucntion idential, since many of the pins on the Mega 
do not have the same fucntions as the UNO. However the pin fucntions we felt were the most important 
have been placed in a manner that makes each pin capabality nearly equivlant to pin fucntions of the Uno.

The pins that are capable of PWM have been placed so that they are able to function in thhe equivlant manner as 
you would find when using an UNO, that is to say, all the pins on an UNO that have PWM are in the same physcial 
place on the Carduino but they will be using difrent pin names then what you would with the UNO. 

*************************************** Carduino Shield and Expansion Moudle Pin out views ***************************************
LED 0(Built into Mega) = D13
LED 1 = D36 Set LOW to activate LED
LED 2 = D38 Set LOW to activate LED

CS/SS for SPI Uno Shield A = D12
CS/SS for SPI Uno Shield B = D46
CS/SS for SPI External(Under Uno Sheild B) = D34

I2C Pullup resistor breakouts under Uno Shield A(near I2C connections)
DS18 Tempeture Sensors have built in 4.7K pullups already Sensor 1 = D28, Sensor 2 = D29
(DS18 Temp Sensor circuits can support two sensors per input channel)


Buzzer(Optional) = D39 Set HIGH to activate buzzer



                   Carduinos "UNO Shield A"            
            +-------------------------------------+
            |***Inside Pins Match UNO Shileds***  |
            |*Outside Pins Match Carduino Pin Map*|
            |                                     |
            |                                   O |
            | O                                 []| SCL - IC2 lines are shared
            |                                   []| SDA - between both sheilds
            |                                   []| AREF
            |                                   []| GND                  ** Alternative SPI Connenctions**
            |                                [D13]| D35         |SCK  | If you look on the back of your Carduino, you will 
            |[IOREF]                         [D12]| DD37        |MISO |noitce under shield A that there are 12 solder
      RESET |[Reset]                         [D11]| D09 - PWM   |MOSI |pads. You can cut the traces between the outer pads
        3V3 |[3v3]                           [D10]| D12 - PWM         | and then bridge it to the pad next to it in order to move 
         5V |[5V]                             [D9]| D11 - PWM         |SPI back on to pins 11-13 if you have a shield that is not 
        GND |[GND]                            [D8]| D24               |using the ISP header for SPI. 
        GND |[GND]                                |
         NA |[VIN                             [D7]| D23
            |                                 [D6]| D13 - PWM 
         A0 |[A0]                             [D5]| D4  - PWM 
         A1 |[A1]                             [D4]| D33
         A2 |[A2]                             [D3]| D10 - PWM 
         A3 |[A3]                             [D2]| D2  - PWM
         A4 |[A4](SDA)                        [D1]| D18 - Serial 1 TX
         A5 |[A5](SCL)        ISP             [D0]| D19 - Serial 1 RX
           +-+              [o-o-o]      +--------+
              \ O           [o-o-o]   O /
               +-----------------------+




                    Carduinos "UNO Shield B"            
            +-------------------------------------+
            |***Inside Pins Match UNO Shileds***  |
            |*Outside Pins Match Carduino Pin Map*|
            |                                     |
            |                                   O |
            | O                                 []| SCL - IC2 lines are shared
            |                                   []| SDA - between both sheilds
            |                                   []| AREF
            |                                   []| GND       
            |                                [D13]| D40       
            |[IOREF]                         [D12]| D43       
      RESET |[Reset]                         [D11]| D44 - PWM 
        3V3 |[3v3]                           [D10]| D46 - PWM 
         5V |[5V]                             [D9]| D45 - PWM 
        GND |[GND]                            [D8]| D26       
        GND |[GND]                                |
         NA |[VIN                             [D7]| D25
            |                                 [D6]| D8  - PWM 
         A6 |[A0]                             [D5]| D7  - PWM 
         A7 |[A1]                             [D4]| D27
         A8 |[A2]                             [D3]| D6  - PWM 
         A9 |[A3]                             [D2]| D3  - PWM                 *** NOTE ****
        A10 |[A4](SDA)                        [D1]| D18 - Serial 2 TX| Serial 2 is also shared with the 
        A11 |[A5](SCL)        ISP             [D0]| D19 - Serial 2 RX| optional GPS module. This means that 
           +-+              [o-o-o]      +--------+                  | D16/D17 will be unavaible when a GPS 
              \ O           [o-o-o]   O /                            | expansion module is also being used. 
               +-----------------------+



   ***** J1850VPW Mini Expansion Module ****
  (when viewed looking down at your Carduino)
          +--------------------------+
          |         O O O O O        |      1) J1850VPW Signal Data line
          |         1 2 3 4 5        |      2) J1850VPW 8V Ref line
          |                          |      3) Ground
          |                          |      4) 5V Supply
          |                          |      5) 12V Supply
          |                          |      6) Ground
          |                          |      7) Resistor(do not connect here)
          |                          |      8) D41 - J1850VPW Reset Circuit
          |            10 9 8 7 6    |      9) Serial 3 RX D15 (PWM Capable if not using J1850 VPW module)
          |             O O O O O    |     10) Serial 3 TX D14 (PWM Capable if not using J1850 VPW module)
          +--------------------------+




     ***** CAN BUS Expansion Module(not shield) ****
      (when viewed looking down at your Carduino)
          +--------------------------+
          |                O O O O O |      1) CS/SS - D26
          |                1 2 3 4 5 |      2) MISO
          |                          |      3) MOSI
          |                          |      4) CAN Recv.Interupt - D53
          |                          |      5) SCK
          |                          |      6) Reset(pull low to reset) - D43
          |                          |      7) Ground
          |                          |      8) CAN HIGH
          |    10 9 8 7 6            |      9) CAN LOW
          |     O O O O O            |     10) 5V Power
          +--------------------------+




  ***** Accelerometer Expansion Module(not shield) ****
      (when viewed looking down at your Carduino)
          +----------------------------+
          |      O O O O O O O O       |      1) SLC
          |      1 2 3 4 5 6 7 8       |      2) SDA
          |                            |      3) Ground
          |                            |      4) NC
          |                            |      5) NC
          |                            |      6) Select - D31
          |                            |      7) 5V Power
          |                            |      8) Ground
          +----------------------------+




     ***** Exh Probe Module(K-type probe) ****
(when viewed looking down at your Carduino from the back)
          +--------------------------+
          |  O O O O O               |      1) SCK
          |  1 2 3 4 5               |      2) CS/SS - D25
          |                          |      3) MISO
          |                          |      4) 5V Power
          |    (larger holes)        |      5) Ground
          |         O  O             |      6) EXH Probe +
          |         6  7             |      7) EXH Probe -
          |                          |     
          +--------------------------+


    ***** GPS Expansion Module(not shield) ****
(when viewed looking down at your Carduino from the back)
          +--------------------------+
          |         O O O O O        |      1) 5V Power
          |         1 2 3 4 5        |      2) Ground
          |                          |      3) TX From Arduino on Serial 2
          |                          |      4) RX From Arduino on Serial 2
          |                          |      5) PPS - Pin broken out but not connected
          |                          |     
          |                          |     
          |                          |     
          +--------------------------+


     ***** 1 Wire Temp Sensor Circuit(prebuilt) ****
   (when viewed looking down at your Carduino from the back)
          +-----------------------+    1) A14
          | 1 Wire Temp Sensor    |    2) A15
          |       O     O         |    These circuits use a 5V pull up resistor combined with a voltage divider to read thermistor 
          | ||    1     2   ||    |    type sensors. The circuits have filtering capacitors on the input side and Analog channel
          | ---            ---    |    side of the pullup circuit to reduce noise and stablize the readings. These circuits are
          +-----------------------+    suitable to read most ground type restiance based circuits used in Automoitve temp sensors.
             ****NOTE*** Applying any voltage greater then  5V will damage your Arduino and Carduino*****



      ***** 1 Wire Temp Sensor Circuit(prebuilt) ****
   (when viewed looking down at your Carduino from the back)
          +-----------------------+  1) A12
          | 1 Wire Temp Sensor    |  2) A13
          |       O     O         |  These circuits use a grounded voltage divider to read automotive sensors that use a
          | ||    1     2   ||    |  0.5v - 4.5v range such as TPS sensors, Oil Pressure sensors, MAP Sensors etc. You MUST 
          | ---            ---    |  supply the sensor both a 5V power AND ground ref from the Carduino for these circuits to  
          +-----------------------+  read sensors correctly, You should NOT attempt to "piggy back" readings off vehicle sensors.
             ****NOTE*** Applying any voltage greater then  5V will damage your Arduino and Carduino*****             



  ***** SD Card Expansion Module(not shield) ****
(when viewed looking down at your Carduino from the back)
           +-------------------------+
           |O O O O O O O O O O O O O|      1) 5V Power
           |O O O O O O O O O O O O O|      2) N/A
           |    MEGA HEADER PINS     |      3) Ground
           |                         |      4) SCK
           |                         |      5) MISO
           |                         |      6) MOSI
           |     O O O O O O O O     |      7) SS/CS - D32
           |     1 2 3 4 5 6 7 8     |      8) Card Detect - D34
          +--------------------------+



     ***** Solder Pads on Back for SPI ****
     (Moves SPI to D11-13 on Uno Shield A)
(when viewed looking down at your Carduino from the back)
          +--------------------------+
          |  ☐--☐ || ☐--☐          |      To move SPI from the ISP header to D11,D12 and D13 you will need
          |  1   2 || 3   4          |      cut 6 traces in the 2 small boxes on the back of the Carduino board.
          |        ||                |      Cut the traces between pads 1/2 and 3/4. Then solder a bridge between 
          |  ☐--☐ || ☐--☐          |      pads 2 & 3 to move the connection. Cut Traces 5/6 & 7/8 and then 
          |  5   6 || 7   8          |      again between 9/10 & 11/12. Next join pads between 6/7 and then 
          |        ||                |      also join the pads between 10/11. This will move MISO, MOSI and SCK
          |  ☐--☐ || ☐--☐          |      into the normal place on the Arduino header for D11-13. However after
          |  9  10 || 11 12          |      after this is done, there will no longer be any Digital pins available
          +--------------------------+      on D11,12 or 13. These will become permanent ISP/SPI header pins. 




          
               
