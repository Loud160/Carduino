# Arduino core files for Carduino core

This repo contains the Arduino corefiles used with **Carduino**.


## Supported devices

* ATmega2560


## Supported clock frequencies

External Clock speeds that produce accurate timing for (millis,
micros, delay, delayMicroseconds)
* 20 MHz
* 16 MHz
* 12 MHz
* 8 MHz
* 4 MHz
* 1 MHz


### Exactness of `delayMicroseconds()`

The `delayMicroseconds(unsigned int us)` implementation is exact up to a few
cycles for the frequencies listed above.

The maximum input parameter to work reliably is 10000 for 10 milliseconds.
Its result is affected by interrupts occurring, which may prolong the delay.


### Exactness of `micros()` and `delay()`

For the clock speeds listed above, `micros()` is corrected to zero drift.
Even for very long run times, the `micros()` function will precisely follow the
oscillator used.

Frequencies not listed above are either exact or corrected to below 60 ppm drift
and in exact sync with `millis()`.

Note that the result of `micros()` may jump up by several microseconds between
consecutive calls and rolls over after one hour and eleven minutes.

The `delay()` function uses `micros()` internally and inherits its drift accuracy
with slight variations due to function call overhead and processing.
It is immune to interrupts and thus long-term accurate.


### Exactness of `millis()`

For the clock speeds listed above, `millis()` is corrected to zero drift.
Even for very long run times, the `millis()` function will precisely follow the
oscillator used.

Frequencies not listed above are either exact or corrected to below 60 ppm drift
and in exact sync with `micros()` and `delay()`.

We do not register the rollover of the `unsigned long` millis counter that
occurs every 49.7 days; such would have to be done in the user's program.
Often this is not necessary:  The code

    if (millis() - millis_old >= interval) {
      /* do something */
      millis_old += interval;
    }

is long-term accurate even when rolling over provided `millis_old` is of type
`unsigned long`.

For clock speeds of 16 MHz and below, the return value of `millis()`
occasionally jumps up by more than one (notwithstanding low/zero drift).
