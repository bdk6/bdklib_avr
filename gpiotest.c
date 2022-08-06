#include <stdint.h>
#include "gpio.h"

int main(int argc, char** argv)
{
  for(uint16_t p = 0; p < 80; p++)
  {
    GPIO_makeInput(p);
    GPIO_makeOutput(p);
    GPIO_setDirection(p, GPIO_INPUT);
    GPIO_setDirection(p, GPIO_OUTPUT);
    GPIO_writePin(p, GPIO_HIGH);
    uint8_t r = GPIO_readPin(p);
  }
  return 0;
}
