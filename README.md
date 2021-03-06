# Carduino

Carduino is the first Arduino based expansion board that has been designed specfically for use in automotive applactions. When you look at Arduino shields they all have one thing in common, they sit on top of your Arduino. What makes Carduino diffrent, is then rather then plugging a shield into your Arduino, you are now plugging your Arduino into an expansion board. This expansion board is designed to accomidate multiple Arduino shields simultaneously while also incorporating a number of smaller expansion modules that can be used in conjunction with existing shields to greatly expand the possibiltys of what your able to create.The Carduino has also included quite a bit of room on it that allow you to build a number of your own circuits with out the need for a bread board once your project is complete. The Carduino is a lot more then just an expansion board, a number of Arduino libaries has been rewritten to work with the altered pinout Carduino uses to make this as simple as possible to get started with. 

  


# Table of contents
* [Supported Arduino](#supported-Arduino)
* [Recommended Bootloader](#Recommended-Bootloader)
* [Bootloader Features](#Bootloader-Features)
  - [BOD option](#BOD-option)
  - [Printf support](#Printf-support)
  - [Write To Flash While Running](#Write-to-Flash-While-Running)
  - [EEPROM option](#EEPROM-option)
  - [Link time optimization](#Link-time-optimization)
  - [Wiring Reference(wiring.h)](#Wiring-Reference(wiring.h))
  - [Pin Macros](#Pin-Macros)
* **[How to install](#how-to-install)**
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
* [Getting started with Carduino](#Getting-started-with-Carduino)



## Supported Arduino
Carduino is designed to work with the Arduino 'MEGA 2650 Pro' & 'Mega 2560 Promini'.
These boards are considerbally smaller then an Arduino UNO and also provide a great deal 
more functionality then the Uno. The Pro and Promini have all the advantages of the 
full size Arduino Mega 2560 but with a much smaller footprint so it takes up less space.
<br/> <br/>
The MEGA 2650 Pro/MEGA 2650 Promini both feature the ATmega2560-16AU processor. 

|               | Mega2560 |   UNO    |
|-------------- |----------|----------|
| **Flash**     | 256kB    | 32kb     |
| **RAM**       | 8kB      | 2kB      |
| **EEPROM**    | 4kB      | 1kB      |
| **IO pins**   | 70       | 23       |
| **PWM pins**  | 15       | 6        |
|**Analog pins**| 16       | 6        |
| **Interrupts**| 6        | 2        |
| **Serials**   | 4        | 1        |
| **Timers**    | 6        | 3        |






## Recommended Bootloader
When you purchased your Carduino you were given the option also purchase either a MEGA 2650 Pro(Embed) or a MEGA 2650 Promini. If you purchased your Arduino from us then you will already be using the recommended bootloader. If you have chosen to supply your own, it is strongly suggested you install the bootloder provided in this library. With out this boot loader a number of the examples will not work correctly with your Arduino and you will be lacking a number of improvments made compared to the 'normal' Arduino bootloader. <BR><BR>

The Carduino bootloader is derived from the Arduino [Megacore bootloader](https://github.com/MCUdude/MegaCore), that is based on the [Optiboot Bootloader](https://github.com/Optiboot/optiboot). The bootloaders have had substantial changes made that improve speed, functionality and cold start boot time <BR><BR>

Some of the key benfites and changes made by these bootloaders can be found below. If you would like to learn more about the specfics of each bootloader you can find complete details on their Github pags linked below:<br>
[Megacore On Github](https://github.com/MCUdude/MegaCore)<br>
[Optiboot On Github](https://github.com/Optiboot/optiboot)
<br><br>
  **Note - To change some specfic settings you will need to use an ISP programmer and hit **Burn bootloader** for the new settings to be applied. <BR><BR>
  
 
## Bootloader Features<br>
#### BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available choices:
<br>

|  BOD Options    | 
|-----------------|
| 4.3V            |
| 2.7V            |
| 1.8V            |
|**Disabled**     |

<BR><BR>


#### Printf support
Unlike official Arduino core, Carduino has native support for printf with out any additional libraries. If you're not familiar with printf you can read more about it [HERE](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). Printf has been added to the Print class and will work with any library that inherit Print. Printf is a standard C function that lets you display formated text much easier than using Arduino's built-in print and println. <br>
  *Note - The included printf support does NOT support the use of floats or doubles. <br>This is a limitation of the avr-libc printf implementation on AVR microcontrollers.<br><br>

To display formated information, simply use `Serial.printf("Time since start: %ld\n", millis());`. The printf function makes is easy to display information on most types of LED and OLED displays. A few of the libraries it works well using the printf function are the LiquidCrystal LCD library and the U8G2 graphical LCD library.
  <br><br>
  
#### Write To Flash While Running
The Carduino bootloader is able to provide several new benfits taken from the Optiboot bootloader core, one of these notable benfits is the ability to write to your boards flash memory while a program is running on your Arduino. This works very similar to how the eeprom works however the flash memory is far more durable and can with stand thousands of writes with out any signs of were like an eeprom would be. <br><br>
  
This means that values from a sensor for example can be stored in the flash memory directly and will persist even with out power. There are several examples of how to impliment this type of functionality that can be found in the examples directory. This function is a bit more advanced then working with Arduino's eeprom but the examples will clearly show you how to impliment the methods into your existing code. <br><br>

  
#### EEPROM option
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect an ISP programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.<br><br>
  
#### Link time optimization
After Arduino IDE 1.6.11 where released, there have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 and older will return an error.
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!
  
  
#### Wiring Reference(wiring.h)
Thanks to improvments made by Megacore several Wiring functions that are missing from the Arduino core have been added to enhance this core's functionality a bit further. These functions can be used as "regular" Arduino functions, there's no need to include an external library. A list for the missing Wiring functions used in the ATMega2560 chip can be found below. <br><BR>
**Function Added**
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()
* disablePower() <BR>
 **Note - More information reguarding how to use these functions can be found [HERE](https://github.com/Loud160/Carduino/blob/main/Wiring_reference.md)** 
<BR><BR><BR>


#### Pin Macros
You don't have to use the digital pin numbers to reference each of your Arduinos pins. You can also use predefined macros that maps "Arduino pins" to the port and port number:<BR>
```c++
// Use PIN_PE0 macro to refer to pin PE0 (Arduino pin 0)
digitalWrite(PIN_PE0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);

```


## How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://raw.githubusercontent.com/Loud160/Carduino/main/package_Carduino_index.json`
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **Carduino** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button in the upper right corner. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "Carduino" will show up.


## Getting started with Carduino
Ok, so you're downloaded and installed Carduino, but how to get started? Here's a quick start guide:
* Plug your Arduino board into the Carduino so the processor on the Arduino is facing up. 
* Connect a USB cable between your PC and the Carduino's USB C connector..(If your using a MEGA2560 Pro(embed) you can also connect a USB directly to the Arduino)
* In the strip menu at the top of your Arduino IDE, seledt **Tools > Board** menu item, and select the Carduino board you are using
* Select In the tools menu you will also need to  select what com port your Carduino is connected to
* In the strip menu at the top of your Arduino IDE, select **File >Example>** Scroll down and find the Carduino board listing then select **Basic Code Examples>Carduino Blink**
* The example code for the Carduino blink example will be loaded
* In the strip menu at the top of your Arduino IDE, seledt **Tools >Upload** and click on Upload
* The two center LED's on your Carduino board are now be blinking!

