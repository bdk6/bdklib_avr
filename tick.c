//////////////////////////////////////////////////////////////////////////////
/// @file tick.c
/// @copy Copyright 2022 William R Cooke
/// @brief Implements timer ticks.
//////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "tick.h"

// Number of callbacks allowed
#define MAX_CALLBACKS       4


// ///////////////////////////////////////////////////////////////////////////
//  There are several different names for timer 0 overflow interrupt:
//  TIM0_OVF_vect     (tn13, tn43u, tn24, tn44, tn84, tn45, tn25, tn85)
//  TIMER0_OVF0_vect  (s2313, s2323, s2343, tn22, tn26)
//  TIMER0_OVF_vect   (s1200, s2333, s4414, s4433, s4434, s8515, s8535, pwm216
//      pwm2B, pwm316, pwm3b, pwm3, pwm2, pwm1, can128, can32, can64, m103,
//      m128, m1284p, m16, m161, m162, m163, m165, m165p, m168p, m169, m169p,
//      m32, m323, m325, m3250, m3250p, m328p, m329, m3290, m3290p, m32hvb,
//      m48p, m64, m645, m6450, m649, m6490, m8, m8515, m8535, m88p, m168, m48,
//      m88, m640, m1280, m1281, m2560, m2561, m324p, m164p, m644p, m644,
//      m16hva, tn11, tn12, tn15, tn2313, tn28, tn48, tn261, tn461, tn861,
//      usb162, usb82, usb1287, usb1286, usb647, usb646
//  
//  We need some common ground

#if defined (TIM0_OVF_vect)
#define TICK_VECT       TIM0_OVF_vect

#elif defined (TIMER0_OVF0_vect)
#define TICK_VECT       TIMER0_OVF0_vect

#elif defined (TIMER0_OVF_vect)
#define TICK_VECT       TIMER0_OVF_vect

#else
#error  The timer 0 overflow vector is not defined
#endif


// Get the timer control register names
#if defined TCCR0
#define TCCR TCCR0



#elif define 



// Keep track of how many ticks have happened
static volatile uint32_t ticks;

// Store the callback functions
callback callbacks[MAX_CALLBACKS];
uint16_t cb_delays[MAX_CALLBACKS];
uint16_t cb_counts[MAX_CALLBACKS];

// Timer 0 atmega8
// TCNT0   [ T7 | ... | T0 ]
//         Timer count register
// TCCR0   [ - | - | - | - | - | CS02 | CS01 | CS00 ]
//         CS02, CS01, CS00 -- Clock Select
//         000 -- No clock, stopped
//         001 -- CLKIO  / 1
//         010 -- CLKIO  / 8
//         011 -- CLKIO  / 64
//         100 -- CLKIO  / 256
//         101 -- CLKIO  / 1024
//         110 -- EXT on T0 pin falling edge
//         111 -- EXT on T0 pin rising edge
//
// TIFR   Timer Interrupt Flag Register
//        [ OCF2 | TOV2 | ICF1 | OCF1A | OCF1B | TOV1 | - | TOV0 ]
//        TOV0 -- Timer 0 Overflow Flag -- 1 on overflow
//             Cleared by H/W when processing interrupt
//             Can be cleared by writing 1 to bit
//        
// TIMSK  [ OCIE2 | TOIE2 | TICIE1 | OCIE1 | TOIE1 | - | TOIE0 ]
//        TOIE0  -- Timer 0 overflow interrupt enable
//        
// GIFR
// GIMSK
//

void Tick_init(int source)
{
  // enable the timer PRTIM0 = 0;
  // NOt in atmega8 (88,168,328) PRR &= 0xcf;  // Clear PRTIM0 bit (5)
  // use "normal" mode = 0 (counts 0 to 255, overflows to 0
  //
  // Set clock source and prescaler
  if(source > TICK_SOURCE_T0_RISING || source < TICK_SOURCE_NONE)
  {
    source = TICK_SOURCE_DIV_1024;   // default to slow
  }
  
  uint8_t tccr0 = TCCR0 & 0xf8;
  tccr0 |= source;
  TCCR0 = tccr0;

  // Enable the interrupt
  TIMSK |= 1;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn Tick_enable
/// @brief (Re) enables the timer tick and callbacks.
//////////////////////////////////////////////////////////////////////////////
void Tick_enable(void)
{
  TIMSK |= _BV(TOIE0); // 1;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn Tick_disable
/// @brief Disables the timer interrupt stopping all ticks and callbacks.
//////////////////////////////////////////////////////////////////////////////
void Tick_disable(void)
{
  TIMSK &= ~(_BV(TOIE0)); // 1;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn Tick_registerCallback
/// @brief Registers a function to call very dly timer ticks.
/// @param[in] cb A pointer to the parameterless function to call.
/// @param[in] dly The number of ticks between calls of this function.
/// @return The index (for removing) of this callback, -1 if no room.
//////////////////////////////////////////////////////////////////////////////
int Tick_registerCallback(callback cb, uint16_t dly)
{
  int rtn = -1;
  int i = 0;
  while(i < MAX_CALLBACKS)
  {
    if(callbacks[i] == 0) // NULL pointer, no callback
    {
      rtn = i;
      callbacks[i] = cb;
      cb_delays[i] = dly;
      cb_counts[i] = dly;
      break;
    }
    i++;
  }
  
  return rtn;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn Tick_removeCallback
/// @brief Removes a callback function from callback list.
/// @param[in] index The index of callback to remove
//////////////////////////////////////////////////////////////////////////////
void Tick_removeCallback(uint16_t index)
{
  if(index < MAX_CALLBACKS)
  {
    callbacks[index] = 0;  // Set to NULL
  }
}

//////////////////////////////////////////////////////////////////////////////
/// @fn Tick_getTicks
/// @brief Gets current number of timer ticks
/// @return The current number of ticks
//////////////////////////////////////////////////////////////////////////////
uint32_t Tick_getTicks(void)
{
  return ticks;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn TICK_VECT
/// @brief Timer 0 overflow ISR increments tick counter, calls callbacks
//////////////////////////////////////////////////////////////////////////////
ISR(TICK_VECT) 
{
  ticks++;
  for(int i = 0; i < MAX_CALLBACKS; i++)
  {
    if(callbacks[i] != 0)
    {
      callbacks[i]();
    }
  }
}

/////////////////////////////////////////////////////////////////
///   For development only
///   TODO: remove
/////////////////////////////////////////////////////////////////
void fn(void)
{
  ticks--;
}

int main(int argc, char** argv)
{
  Tick_init(TICK_SOURCE_DIV_64);
  Tick_registerCallback(fn, 10);
  while(1)
  {
    uint32_t t = ticks;
    if(ticks == 1000) ticks += 2000;
  }
  return 0;
}

  
  
