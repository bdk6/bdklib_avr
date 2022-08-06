//////////////////////////////////////////////////////////////////////////////
/// @file gpio.c
/// @copy William R Cooke 2022
/// @brief Implementtion of GPIO library functions
//////////////////////////////////////////////////////////////////////////////

#include "gpio.h"

//////////////////////////////////////////////////////////////////////////////
/// @fn GPIO_makeInput
/// @brief Sets a GPIO pin number as input.
/// @param[in] gpio_pin Pin number to affect.
//////////////////////////////////////////////////////////////////////////////
void GPIO_makeInput(uint16_t gpio_pin)
{
  uint8_t pinMask = ~(uint8_t)(1 << (gpio_pin & 0x07));
  uint16_t port = gpio_pin >> 3;
  switch(port)
  {
    #ifdef DDRA
  case 0:
    DDRA &= pinMask;
    break;
    #endif

    #ifdef DDRB
  case 1:
    DDRB &= pinMask;
    break;
    #endif

    #ifdef DDRC
  case 2:
    DDRC &= pinMask;
    break;
    #endif

    #ifdef DDRD
  case 3:
    DDRD &= pinMask;
    break;
    #endif

    #ifdef DDRE
  case 4:
    DDRE &= pinMask;
    break;
    #endif

    #ifdef DDRF
  case 5:
    DDRF &= pinMask;
    break;
    #endif

    #ifdef DDRG
  case 6:
    DDRG &= pinMask;
    break;
    #endif

    #ifdef DDRH
  case 7:
    DDRH &= pinMask;
    break;
    #endif

    #ifdef DDRJ
  case 8:
    DDRJ &= pinMask;
    break;
    #endif

    #ifdef DDRK
  case 9:
    DDRK &= pinMask;
    break;
    #endif

    #ifdef DDRL
  case 10:
    DDRL &= pinMask;
    break;
    #endif

    
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
/// @fn GPIO_makeOutput
/// @brief Sets a GPIO pin number as output.
/// @param[in] gpio_pin Pin number to affect.
//////////////////////////////////////////////////////////////////////////////
void GPIO_makeOutput(uint16_t gpio_pin)
{
  uint8_t pinMask = (uint8_t) (1 << (gpio_pin & 0x07));
  uint16_t port = gpio_pin >> 3;
  switch(port)
  {
    #ifdef DDRA
  case 0:
    DDRA |= pinMask;
    break;
    #endif

    #ifdef DDRB
  case 1:
    DDRB |= pinMask;
    break;
    #endif

    #ifdef DDRC
  case 2:
    DDRC |= pinMask;
    break;
    #endif

    #ifdef DDRD
  case 3:
    DDRD |= pinMask;
    break;
    #endif

    #ifdef DDRE
  case 4:
    DDRE |= pinMask;
    break;
    #endif

    #ifdef DDRF
  case 5:
    DDRF |= pinMask;
    break;
    #endif

    #ifdef DDRG
  case 6:
    DDRG |= pinMask;
    break;
    #endif

    #ifdef DDRH
  case 7:
    DDRH |= pinMask;
    break;
    #endif

    #ifdef DDRJ
  case 8:
    DDRJ |= pinMask;
    break;
    #endif

    #ifdef DDRK
  case 9:
    DDRK |= pinMask;
    break;
    #endif

    #ifdef DDRL
  case 10:
    DDRL |= pinMask;
    break;
    #endif
    
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
/// @fn GPIO_setDirection
/// @brief Sets the direction (in or out) of a GPIO pin.
/// @param[in] gpio_pin Pin number to affect.
/// @param[in] dir 0 for INPUT other for OUTPUT.
//////////////////////////////////////////////////////////////////////////////
void GPIO_setDirection(uint16_t gpio_pin, int dir)
{
  if(dir != 0)
  {
    GPIO_makeOutput(gpio_pin);
  }
  else
  {
    GPIO_makeInput(gpio_pin);
  }
}

//////////////////////////////////////////////////////////////////////////////
/// @fn GPIO_writePin
/// @brief Writes a value to a GPIO pin number.
/// @param[in] gpio_pin Pin number to affect.
/// @param[in] val Value to write: 0 = LOW, other = HIGH.
//////////////////////////////////////////////////////////////////////////////
void GPIO_writePin(uint16_t gpio_pin, int val)
{
  uint16_t port = gpio_pin >> 3;
  uint8_t pinMask = (uint8_t)(1 << (uint8_t)(gpio_pin & 0x07));
  if(val != 0)   // Write 1
  {
    switch(port)
    {
      #ifdef PORTA
    case 0:
      PORTA |= pinMask;
      break;
      #endif

      #ifdef PORTB
    case 1:
      PORTB |= pinMask;
      break;
      #endif

      #ifdef PORTC
    case 2:
      PORTC |= pinMask;
      break;
      #endif

      #ifdef PORTD
    case 3:
      PORTD |= pinMask;
      break;
      #endif

      #ifdef PORTE
    case 4:
      PORTE |= pinMask;
      break;
      #endif

      #ifdef PORTF
    case 5:
      PORTF |= pinMask;
      break;
      #endif

      #ifdef PORTG
    case 6:
      PORTG |= pinMask;
      break;
      #endif

      #ifdef PORTH
    case 7:
      PORTH |= pinMask;
      break;
      #endif

      #ifdef PORTJ
    case 8:
      PORTJ |= pinMask;
      break;
      #endif

      #ifdef PORTK
    case 9:
      PORTK |= pinMask;
      break;
      #endif

      #ifdef PORTL
    case 10:
      PORTL |= pinMask;
      break;
      #endif

    default:
      break;
    }
  }
  else  // Write 0
  {
    pinMask = ~pinMask;  // 00001000 -> 11110111
    switch(port)
    {
      #ifdef PORTA
    case 0:
      PORTA &= pinMask;
      break;
      #endif

      #ifdef PORTB
    case 1:
      PORTB &= pinMask;
      break;
      #endif

      #ifdef PORTC
    case 2:
      PORTC &= pinMask;
      break;
      #endif

      #ifdef PORTD
    case 3:
      PORTD &= pinMask;
      break;
      #endif

      #ifdef PORTE
    case 4:
      PORTE &= pinMask;
      break;
      #endif

      #ifdef PORTF
    case 5:
      PORTF &= pinMask;
      break;
      #endif

      #ifdef PORTG
    case 6:
      PORTG &= pinMask;
      break;
      #endif

      #ifdef PORTH
    case 7:
      PORTH &= pinMask;
      break;
      #endif

      #ifdef PORTJ
    case 8:
      PORTJ &= pinMask;
      break;
      #endif

      #ifdef PORTK
    case 9:
      PORTK &= pinMask;
      break;
      #endif

      #ifdef PORTL
    case 10:
      PORTL &= pinMask;
      break;
      #endif

    default:
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
/// @fn GPIO_readPin
/// @brief Reads state of GPIO input pin.
/// @param[in] gpio_pin Pin number to read.
/// @return 1 if input is HIGH, 0 if it is LOW.
//////////////////////////////////////////////////////////////////////////////
uint8_t GPIO_readPin(uint16_t gpio_pin)
{
  uint8_t rtn = 0;
  uint16_t port = gpio_pin >> 3;
  uint8_t pinMask = (uint8_t)(1 << (uint8_t)(gpio_pin & 0x07));

  switch(port)
  {
    #ifdef PINA
  case 0:
    rtn = PINA;
    break;
    #endif

    #ifdef PINB
  case 1:
    rtn = PINB;
    break;
    #endif

    #ifdef PINC
  case 2:
    rtn = PINC;
    break;
    #endif

    #ifdef PIND
  case 3:
    rtn = PIND;
    break;
    #endif

    #ifdef PINE
  case 4:
    rtn = PINE;
    break;
    #endif

    #ifdef PINF
  case 5:
    rtn = PINF;
    break;
    #endif

    #ifdef PING
  case 6:
    rtn = PING;
    break;
    #endif

    #ifdef PINH
  case 7:
    rtn = PINH;
    break;
    #endif

    #ifdef PINJ
  case 8:
    rtn = PINJ;
    break;
    #endif

    #ifdef PINK
  case 9:
    rtn = PINK;
    break;
    #endif

    #ifdef PINL
  case 10:
    rtn = PINL;
    break;
    #endif

  default:
    break;
  }

  rtn &= pinMask;
  if(rtn != 0) rtn = 1;

  return rtn;
}

  
