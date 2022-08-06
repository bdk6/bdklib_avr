//////////////////////////////////////////////////////////////////////////////
/// @file blinkie.c
/// @copy Copyright 2022 William R Cooke
/// @brief Tools test: blinks LED on PC5 of atmega8
/////////////////////////////////////////////////////////////////////////////

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRC = 0xff;   // set portc as outputs

  while(1)
  {
    PORTC = 0x20;  // on
    _delay_ms(250);  // wait
    PORTC = 0;     // off
    _delay_ms(250);  // wait
  }

  return 0;
}
