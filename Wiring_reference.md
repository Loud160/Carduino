# Wiring reference
To extend this core's functionality a bit further, a few missing Wiring functions have been added. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isn't active. These functions are used as "regular" Arduino functions, and there's no need to include an external library.

## Content
* [portMode](#portmode)()
* [portRead](#portread)()
* [portWrite](#portwrite)()
* [sleepMode](#sleepmode)()
* [sleep](#sleep)()
* [noSleep](#disablesleep)()
* [enablePower](#enablepower)()
* [disablepower](#disablePower)()

## portMode()
The <b>portMode()</b> method sets a specified digital I/O port as INPUT or OUTPUT. A digital I/O port is a group of 8 pins. By writing 0 to a port it will set individually each of the 8 pins to 0 (LOW). Possible values range from 0 to 255. It possible to read or write a value of a digital I/O port by using the <b>[portRead()](#portread)</b> and <b>[portWrite()](#portwrite)</b> methods.

### Syntax
``` c++
portMode(portNumber, value)
```

#### Parameters
`portNumber` - <i>byte/uint8_t</i> <br/>
`value` - <i>byte/uint8_t</i>

| PortNumber  | Physical port |
|-------------|---------------|
| 0           | PORTA         |
| 1           | PORTB         |
| 2           | PORTC         |
| 3           | PORTD         |

#### Returns
`none`
<br/>

### Example
``` c++
byte portNumber = 1; // Use port B
byte val = 0;

void setup() {
  portMode(portNumber, OUTPUT);
}

void loop() {
  portWrite(portNumber, val);
  val = val + 1;
  if (val > 255)
    val = 0;
}
```



## portRead()
The <b>portRead()</b> method reads the value of the digital input port specified.

### Syntax
``` c++
portRead(portNumber)
```

#### Parameters
`portNumber` - <i>byte/uint8_t</i> <br/>

| PortNumber  | Physical port |
|-------------|---------------|
| 0           | PORTA         |
| 1           | PORTB         |
| 2           | PORTC         |
| 3           | PORTD         |

#### Returns
`byte/uint8_t`
<br/>

### Example
``` c++
byte inport = 1;
byte val = 0;

void setup() {
  portMode(PortNumber, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = portRead(PortNumber);
  Serial.print(val);
}
```



## portWrite()
The <b>portWrite()</b> method writes a value to the digital output port specified.

### Syntax
``` c++
portWrite(portNumber, value)
```

#### Parameters
`portNumber` - <i>byte/uint8_t</i> <br/>
`value` - <i>byte/uint8_t</i>

| PortNumber  | Physical port |
|-------------|---------------|
| 0           | PORTA         |
| 1           | PORTB         |
| 2           | PORTC         |
| 3           | PORTD         |

#### Returns
`none`
<br/>

### Example
``` c++
byte outport = 1;
byte val = 0;

void setup() {
  portMode(PortNumber, OUTPUT);
}

void loop() {
  portWrite(PortNumber, val);
  val = val + 1;
  if (val > 255)
    val = 0;
}
```



## sleepMode()
Sleep modes enable the application to shut down unused modules in the microcontroller, thereby saving power. The default mode is SLEEP_IDLE. Different AVR devices provides various sleep modes allowing the user to tailor the power consumption to the application's requirements. There are six sleep modes set by the sleepMode() command. <br/>
<b>SLEEP_IDLE:</b> makes the MCU enter Idle mode, stopping the CPU but allowing the SPI, Serial, Analog Comparator, ADC, Wire, Timer/Counters and the interrupt system to continue operating. This mode enables the microcontroller to wake up from external triggered interrupts as well as internal ones like the Timer Overflow and Serial Transmit Complete interrupts.
SLEEP_ADC: makes the microcontroller enter ADC Noise Reduction mode, stopping the CPU but allowing the ADC, the external interrupts, Wire Serial Interface address match and Timer/Counter2. This improves the noise environment for the ADC, enabling higher resolution measurements. If the ADC is enabled, a conversion starts automatically when this mode is entered. Only an External Reset, a Wire serial interface interrupt, a Timer/Counter2 interrupt, an SPM/EEPROM ready interrupt, an external level interrupt on INT7:4 or a pin change interrupt can wakeup the microcontroller from ADC Noise Reduction mode.<br/>
<b>SLEEP_POWER_DOWN:</b> In this mode, the external Oscillator is stopped, while the external interrupts, and the Wire Serial Interface continue operating. Only an External Reset, Wire Serial Interface address match, an external level interrupt on INT7:4, an external interrupt on INT3:0, or a pin change interrupt can wake up the microcontroller. This sleep mode basically halts all generated clocks, allowing operation of asynchronous modules only. <br/>
<b>SLEEP_POWER_SAVE:</b> This mode is identical to SLEEP_POWER_DOWN, with one exception: If Timer/Counter2 is enabled, it will keep running during sleep. The device can wake up from either Timer Overflow or Output Compare event from Timer/Counter2 if the corresponding Timer/Counter2 interrupt enable bits are set, and the Global Interrupts are enable. If Timer/Counter2 is not running, SLEEP_POWER_DOWN mode is recommended instead of SLEEP_POWER_SAVE mode. The Timer/Counter2 can be clocked both synchronously and asynchronously in SLEEP_POWER_SAVE mode. If the Timer/Counter2 is not using the asynchronous clock, the Timer/Counter Oscillator is stopped during sleep. If the Timer/Counter2 is not using the synchronous clock, the clock source is stopped during sleep. Note that even if the synchronous clock is running in SLEEP_POWER_SAVE, this clock is only available for the Timer/Counter2.<br/>
<b>SLEEP_STANDBY:</b> This mode is identical to SLEEP_POWER_SAVE mode with the exception that the Oscillator is kept running.<br/>
<b>SLEEP_EXTENDED_STANDBY:</b> This mode is identical to SLEEP_POWER_SAVE mode with the exception that the Oscillator is kept running. From SLEEP_EXTENDED_STANDBY mode, the device wakes up in six clock cycles.<br/>

### Syntax
``` c++
sleepMode(mode)
```

#### Parameters
`mode` - <i>byte/uint8_t</i> <br/>

| mode                   |
|------------------------|
| SLEEP_IDLE             |
| SLEEP_ADC              |
| SLEEP_POWER_DOWN       |
| SLEEP_POWER_SAVE       |
| SLEEP_STANDBY          |
| SLEEP_EXTENDED_STANDBY |

#### Returns
`none`
<br/>

### Example
``` c++
// ...

// Set the sleep mode to SLEEP_IDLE
sleepMode(SLEEP_IDLE);
sleep(); // Go to sleep

if(some_condition)
  noSleep(); // Wakes up


// ...
```

## sleep()
the <b>sleep()</b> command can allow an application to reduce its power consumption considerably. Sleep modes enable the application to shut down unused modules in the microcontroller, thereby saving power. The default mode is SLEEP_IDLE. Different AVR devices provides various sleep modes allowing the user to tailor the power consumption to the application's requirements. There are six sleep modes set by the [sleepMode()](#sleepmode) command.

### Syntax
``` c++
sleep()
```

#### Returns
`none`

### Example
``` c++
// ...

// Set the sleep mode to SLEEP_IDLE
sleepMode(SLEEP_IDLE);
sleep(); // Go to sleep

if(some_condition)
  noSleep(); // Wakes up


// ...
```



## noSleep()
the <b>noSleep()</b> command wakes up the microcontroller from a previous [sleep()](#sleep). Sleep modes enable the application to shut down unused modules in the microcontroller, thereby saving power. The default mode is SLEEP_IDLE. Different AVR devices provides various sleep modes allowing the user to tailor the power consumption to the application's requirements. There are six sleep modes set by the [sleepMode()](#sleepmode) command.

### Syntax
``` c++
noSleep()
```

#### Returns
`none`

### Example
``` c++
// ...

// Set the sleep mode to SLEEP_IDLE
sleepMode(SLEEP_IDLE);
sleep(); // Go to sleep

if(some_condition)
  noSleep(); // Wakes up


// ...
```
