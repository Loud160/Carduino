# Carduino

Carduino is the first Arduino based expansion board that has been designed specfically for use in automotive applactions. When you look at Arduino shields they all have one thing in common, they sit on top of your Arduino. What makes Carduino diffrent, is then rather then plugging a shield into your Arduino, you are now plugging your Arduino into an expansion board. This expansion board is designed to accomidate multiple Arduino shields simultaneously while also incorporating a number of smaller expansion modules that can be used in conjunction with existing shields to greatly expand the possibiltys of what your able to create.The Carduino has also included quite a bit of room on it that allow you to build a number of your own circuits with out the need for a bread board once your project is complete. The Carduino is a lot more then just an expansion board, a number of Arduino libaries has been rewritten to work with the altered pinout Carduino uses to make this as simple as possible to get started with. 

  


# Table of contents
* [Supported Arduino](#supported-Arduino)
* [Recommended Bootloader](#Recommended-Bootloader)
* [Bootloader Features](#Bootloader-Features)
* [EEPROM retain option](#eeprom-option)
* [Link time optimization / LTO](#link-time-optimization--lto)
* [Printf support](#printf-support)
* [Pin macros](#pin-macros)
* [PROGMEM with flash sizes greater than 64kB](#progmem-with-flash-sizes-greater-than-64kb)
* [Write to own flash](#write-to-own-flash)
* [Programmers](#programmers)
* **[How to install](#how-to-install)**
  - [Boards Manager Installation](#boards-manager-installation)
  - [Manual Installation](#manual-installation)
  - [PlatformIO](#platformio)
* **[Getting started with MegaCore](#getting-started-with-megacore)**
* [Wiring reference](#wiring-reference)
* **[Pinout](#pinout)**
* **[Minimal setup](#minimal-setup)**


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
When you pruchased your Carduino you were given the option also purchase either a MEGA 2650 Pro(Embed) or a MEGA 2650 Promini. If you purchased your Arduino from us then you will already be using the recommended bootloader. If you have chosen to supply your own, it is strongly suggested you install the bootloder provided in this library. With out this boot loader a number of the examples will not work correctly with your Arduino and you will be lacking a number of improvments made compared to the 'normal' Arduino bootloader. <BR><BR>

The Carduino bootloader is derived from the Arduino [Megacore bootloader](https://github.com/MCUdude/MegaCore), that is based on the [Optiboot Bootloader](https://github.com/Optiboot/optiboot). The bootloaders have had substantial changes made that improve speed, functionality and cold start boot time <BR><BR>

Some of the key benfites and changes made by these bootloaders can be found below. If you would like to learn more about the specfics of each bootloader you can find complete details on their Github pags linked below:<br>
[Megacore On Github](https://github.com/MCUdude/MegaCore)<br>
[Optiboot On Github](https://github.com/Optiboot/optiboot)
<br><br>
  **Note - To change some specfic settings you will need to use an ISP programmer and hit **Burn bootloader** for the new settings to be applied. <BR><BR>
  
 
## Bootloader Features<br>
  **BOD option**<br>
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br>

|  BOD Options    | 
|-----------------|
| 4.3V            |
| 2.7V            |
| 1.8V            |
|**Disabled**     |

<BR><BR>


 **Printf support**<br>
Unlike official Arduino core, Carduino has native support for printf with out any additional libraries. If you're not familiar with printf you can read more about it [HERE](https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm). Printf has been added to the Print class and will work with any library that inherit Print. Printf is a standard C function that lets you display formated text much easier than using Arduino's built-in print and println. <br>
  *Note - The included printf support does NOT support the use of floats or doubles. <br>This is a limitation of the avr-libc printf implementation on AVR microcontrollers.<br><br>

To display formated information, simply use `Serial.printf("Time since start: %ld\n", millis());`. The printf function makes is easy to display information on most types of LED and OLED displays. A few of the libraries it works well using the printf function are the LiquidCrystal LCD library and the U8G2 graphical LCD library.
  <br><br>
  
  **Write To Flash While Running**
The Carduino bootloader is able to provide several new benfits taken from the Optiboot bootloader core, one of these notable benfits is the ability to write to your boards flash memory while a program is running on your Arduino. This works very similar to how the eeprom works however the flash memory is far more durable and can with stand thousands of writes with out any signs of were like an eeprom would be. <br><br>
  
This means that values from a sensor for example can be stored in the flash memory directly and will persist even with out power. There are several examples of how to impliment this type of functionality that can be found in the examples directory. This function is a bit more advanced then working with Arduino's eeprom but the examples will clearly show you how to impliment the methods into your existing code. <br><br>

  
  **EEPROM option**<br>
If you want the EEPROM to be erased every time you burn the bootloader or upload using a programmer, you can turn off this option. You'll have to connect an ISP programmer and hit "Burn bootloader" to enable or disable EEPROM retain. Note that when uploading using a bootloader, the EEPROM will always be retained.<br><br>
  
**Link time optimization(LTO)**<br>
After Arduino IDE 1.6.11 where released, there have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 and older will return an error.
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!
  
  
**Wiring reference**
Thanks to some changes made by Megacore several missing Wireing functions that are missing from the Arduino core have been added and extend this core's functionality a bit further. A list for several of the missing Wiring functions used in the ATMega2560 chip can be found below. These functions can be used as "regular" Arduino functions, there's no need to include an external library.<br><BR>

**Function list**
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()
* disablePower() 









## Pin macros
Note that you don't have to use the digital pin numbers to refer to the pins. You can also use some predefined macros that maps "Arduino pins" to the port and port number:

```c++
// Use PIN_PE0 macro to refer to pin PE0 (Arduino pin 0)
digitalWrite(PIN_PE0, HIGH);

// Results in the exact same compiled code
digitalWrite(0, HIGH);

```

## PROGMEM with flash sizes greater than 64kB
The usual `PROGMEM` attribute stores constant data such as string arrays to flash and is great if you want to preserve the precious RAM. However, PROGMEM will only store content in the lower section, from 0 and up to 64kB. If you want to store data in other sections, you can use `PROGMEM1` (64 - 128kB), `PROGMEM2` (128 - 192kB), or `PROGMEM3` (192 - 256kB), depending on the chip you're using.
Accessing this data is not as straight forward as with `PROGMEM`, but it's still doable:

```c
const char far_away[] PROGMEM1 = "Hello from far away!\n"; // (64  - 128kB)
const char far_far_away[] PROGMEM2 = "Hello from far, far away!\n"; // (128 - 192kB)
const char far_far_far_away[] PROGMEM3 = "Hello from far, far, far away!\n"; // (192 - 256kB)

void print_progmem()
{
  uint8_t i;
  char c;

  // Print out far_away
  for(i = 0; i < sizeof(far_away); i++)
  {
    c = pgm_read_byte_far(pgm_get_far_address(far_away) + i);
    Serial.write(c);
  }

  // Print out far_far_away
  for(i = 0; i < sizeof(far_far_away); i++)
  {
    c = pgm_read_byte_far(pgm_get_far_address(far_far_away) + i);
    Serial.write(c);
  }
  // Print out far_far_far_away
  for(i = 0; i < sizeof(far_far_far_away); i++)
  {
    c = pgm_read_byte_far(pgm_get_far_address(far_far_far_away) + i);
    Serial.write(c);
  }
}

```


## Write to own flash
MegaCore uses Optiboot Flash, a bootloader that supports flash writing within the running application, thanks to the work of [@majekw](https://github.com/majekw).
This means that content from e.g. a sensor can be stored in the flash memory directly without the need of external memory. Flash memory is much faster than EEPROM, and can handle at least 10 000 write cycles before wear becomes an issue.
For more information on how it works and how you can use this in you own application, check out the [Serial_read_write](https://github.com/MCUdude/MegaCore/blob/master/avr/libraries/Optiboot_flasher/examples/Serial_read_write/Serial_read_write.ino) for a simple proof-of-concept demo, and
[Flash_put_get](https://github.com/MCUdude/MegaCore/blob/master/avr/libraries/Optiboot_flasher/examples/Flash_put_get/Flash_put_get.ino) + [Flash_iterate](https://github.com/MCUdude/MegaCore/blob/master/avr/libraries/Optiboot_flasher/examples/Flash_iterate/Flash_iterate.ino) for useful examples on how you can store strings, structs and variables to flash and retrieve then afterwards.
The [Read_write_without_buffer](https://github.com/MCUdude/MegaCore/blob/master/avr/libraries/Optiboot_flasher/examples/Read_write_without_buffer/Read_write_without_buffer.ino) example demonstrate how you can read and write to the flash memory on a lower level without using a RAM buffer.


## Programmers
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external oscillator is recommended.


## How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://mcudude.github.io/MegaCore/package_MCUdude_MegaCore_index.json`
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MegaCore** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation
Click on the "Download ZIP" button in the upper right corner. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MegaCore" will show up.

#### PlatformIO
[PlatformIO](http://platformio.org) is an open source ecosystem for IoT development and supports MegaCore.

**See [PlatformIO.md](https://github.com/MCUdude/MegaCore/blob/master/PlatformIO.md) for more information.**


## Getting started with MegaCore
Ok, so you're downloaded and installed MegaCore, but how to get started? Here's a quick start guide:
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
  - If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted.
* Open the **Tools > Board** menu item, and select **ATmega64**, **ATmega128**, **ATmega1281**, **ATmega2561**, **ATmega640**, **ATmega1280**, **ATmega2560**, **AT90CAN32**, **AT90CAN64** or **AT90CAN128**.
* Select your preferred clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* Hit **Burn Bootloader**. If an LED is connected to pin PB5/PB7, it should flash twice every second.
* Now that the correct fuse settings is sat and the bootloader burnt, you can upload your code in two ways:
  - Disconnect your programmer tool, and connect a USB to serial adapter to the microcontroller, like shown in the [pinout diagram](#pinout). Then select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting some kind of timeout error, it means your RX and TX pins are swapped, or your auto reset circuity isn't working properly (the 100 nF capacitor on the reset line).
  - Keep your programmer connected, and hold down the `shift` button while clicking **Upload**. This will erase the bootloader and upload your code using the programmer tool.

Your code should now be running on the microcontroller!

## Wiring reference
To extend this core's functionality a bit further, I've added a few missing Wiring functions to this hardware package. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isn't active. These functions is used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful, because they really are!

### Function list
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()
* disablePower()

### For further information please view the [Wiring reference page](https://github.com/MCUdude/MegaCore/blob/master/Wiring_reference.md)!






### ATmega640/1280/2560
Beside including the original Arduino Mega pinout for the ATmega640/1280/2560, I've also added an *AVR style pinout*, which is a more straight forward and logical pinout if you're not working with the Arduino Mega board. For the default Arduino Mega pinout, the standard LED pin is assigned to Arduino pin 13, and for the AVR pin it's assigned to pin 22.
<b>Click to enlarge:</b> <br/>
<img src="https://i.imgur.com/sweRJs3.jpg" width="280"> <img src="https://i.imgur.com/O7WtWAj.jpg" width="280"> <img src="http://i.imgur.com/DfR7arD.jpg" width="280">



