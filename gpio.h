//////////////////////////////////////////////////////////////////////////////
/// @file gpio.h
/// @copy William R Cooke 2022
/// @brief Header for GPIO library functions
//////////////////////////////////////////////////////////////////////////////

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

#define GPIO_VERSION_MAJOR    0
#define GPIO_VERSION_MINOR    1
#define GPIO_VERSION_BUILD    1
#define GPIO_VERSION_DATE     (20220701L)

#define GPIO_INPUT           0
#define GPIO_OUTPUT          1
#define GPIO_HIGH            1
#define GPIO_LOW             0


void GPIO_makeInput(uint16_t gpio_pin);
void GPIO_makeOutput(uint16_t gpio_pin);
void GPIO_setDirection(uint16_t gpio_pin, int dir);
void GPIO_writePin(uint16_t gpio_pin, int val);
uint8_t GPIO_readPin(uint16_t gpio_pin);

#endif

