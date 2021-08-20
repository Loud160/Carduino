Ok, so you're downloaded and installed Carduino, if you are supplying your own MEGE2560 Pro you will want to replace the 
stock bootloader to get the most out of your Carduino.

1)To burn the bootloader you will need an ISP Programmer or another Arduino. You will NOT be able to plug the 
ISP programmer directly into your MEGA2560PRO unless you have installed a pass-through header. You will need to use suitable 
jumper wires to make the 6 connections from the ISP header to the programmers 6 pin header.

2)While you do not need to use the Carduino bootloader, it is strongly suggest since it boots considerably faster then the 
default Arduino bootloader does(around 1/3 the time to start). The bootloader Carduino uses also adds a number of features
that are not found in the default Arduino bootloaders such as printf support, write to flash, improved eeprom functions and
the ability to jump to the bootloader from within a running program. If you are not using the Carduino bootloader you will
not be able to use any of the provided examples for these features. 

3)If you are unable to burn the bootloader using your ISP Programmer from within Arduino, you can also use "AVRDUDESS portable"
https://github.com/zkemble/AVRDUDESS/releases
This is a graphical version with a pretty simple GUI that greatly simplifies using AVRDUDE. So if you have troubles getting 
the bootloader burned using Arduino and you've double checked your connections you might consider giving this a try. 
You can find the Carduino bootloaders in your Arduino's board profiles. To find where they are stored, in Arduino
select FILE->PREFERENCES and near the bottom of the popup window you will see a link to open this location. It will typically 
be something line C:\Users\YourName\AppData\Local\Arduino15

4)There are several options in the Carduino boards menu that DO require using an ISP Programmer to change but these are not 
things you probably won't need to set more than once, so for the most part these settings are not something you need to be
concerned with. The option to change your Mega2560's clock frequency has been added with 16mhz being the default value. 
There are cases when a faster or slower clock speed may be needed, but these are going to be limited use cases that generally
involve connections to an external device using SPI or perhaps to get a little more processing speed if your main loop is 
running slow and you have already optimized your code as much as possible.
