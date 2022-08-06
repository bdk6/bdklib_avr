//////////////////////////////////////////////////////////////////////////////
/// @file tick.h
/// @copy Copyright 2022 William R Cooke
/// @brief Defines interface for timer ticks.
//////////////////////////////////////////////////////////////////////////////

#ifndef _TICK_H_
#define _TICK_H_

enum
{
  TICK_SOURCE_NONE       = 0,
  TICK_SOURCE_DIV_1      = 1,
  TICK_SOURCE_DIV_8      = 2,
  TICK_SOURCE_DIV_64     = 3,
  TICK_SOURCE_DIV_256    = 4,
  TICK_SOURCE_DIV_1024   = 5,
  TICK_SOURCE_T0_FALLING = 6,
  TICK_SOURCE_T0_RISING  = 7
};

typedef void (*callback)(void);

void Tick_init(int source); 
void Tick_enable(void);
void Tick_disable(void);
int Tick_registerCallback(callback cb, uint16_t dly);
void Tick_removeCallback(uint16_t index);
uint32_t Tick_getTicks(void);


#ifdef TIMER0_OVF_vect
//#error atmega 8
#endif


#endif

