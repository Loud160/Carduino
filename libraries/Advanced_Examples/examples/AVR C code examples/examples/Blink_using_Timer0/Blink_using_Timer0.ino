/*************************************************************
 This sketch makes the pin PB5 or PB7 toggle every second
 if you run the microcontroller at 16 MHz. It uses Timer0
 or Timer0B, and divide the clock frequency by 1024.
 The divided frequencys period is multiplied with the
 number og counts Timer0/Timer0b can take before it overflows.
 The number is then multiplied by 61, and gives approximately
 1 second.

 16MHz / 1024 = 15625 hz        We divide the 16 MHz clock by 1024
 1/15625 = 0.000064s            Period time
 256 * 0.000064 = 0.016384
 0.016384 * 61 = 0.999424 ≈ 1s
 X = 0.999424 / 0.016384 where X is approximately 61
**************************************************************/


#include <avr/io.h>

uint8_t ledPin = 0;
uint16_t timeCount = 0;


int main (void)
{
  #if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
    DDRB |= _BV(PB5); // Set PB5 as output, ignore the rest
    ledPin = _BV(PB5);
    TCCR0 = 0x07;     // clock frequency / 1024
    OCR0 = 0x00;      // Output compare
    TCNT0 = 0;        // Start to count from zero
    TIMSK = 0x01;     // Enable overflow interrupt

  #elif defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__)
    DDRB |= _BV(PB5); // Set PB5 as output, ignore the rest
    ledPin = _BV(PB5);
    TCCR0A = 0x05;    // clock frequency / 1024
    OCR0A = 0x00;     // Output compare
    TCNT0 = 0;        // Start to count from zero
    TIMSK0 = 0x01;    // Enable overflow interrupt

  #elif defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2561__)
    DDRB |= _BV(PB5); // Set PB5 as output, ignore the rest
    ledPin = _BV(PB5);
    TCCR0B = 0x05;    // clock frequency / 1024
    OCR0B = 0x00;     // Output compare
    TCNT0 = 0;        // Start to counter 0 to zero
    TIMSK0 = 0x01;    // Enable overflow interrupt

  #elif defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    DDRB |= _BV(PB7); // Set PB7 as output, ignore the rest
    ledPin = _BV(PB7);
    TCCR0B = 0x05;    // clock frequency / 1024
    OCR0B = 0x00;     // Output compare
    TCNT0 = 0;        // Start to counter 0 to zero
    TIMSK0 = 0x01;    // Enable overflow interrupt
  #endif

  sei(); // Enable global interrupts

  while(1); // Infinite loop
}


// Timer 0 overflow vector - this run every time timer0 overflows
ISR(TIMER0_OVF_vect)
{
  timeCount++;
  if(timeCount == 61) // Timer overflown for the 61th time
  {
    PORTB ^= ledPin;  // Toggle the LED
    timeCount = 0;    // Reset overflow counter
  }
}
