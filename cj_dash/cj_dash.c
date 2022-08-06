//////////////////////////////////////////////////////////////////////////////
/// @file cj_dash.c
/// @copy Copyright 2022 William R Cooke
/// @brief Early version of CJ dashboard using NA202 VFD display
//////////////////////////////////////////////////////////////////////////////

// PINS
// D0  -- PB0
// D1  -- PB1
// D2  -- PB2
// D3  -- PB3
// D4  -- PD4
// D5  -- PD5
// D6  -- PD6
// D7  -- PD7
// WR  -- PB4
// RES -- PB5


#define VERSION_YEAR    2022
#define VERSION_MONTH   7
#define VERSION_DATE    7
#define VERSION_MAJOR   0
#define VERSION_MINOR   1
#define VERSION_BUILD   1

#define F_CPU           1000000UL

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define LUMINANCE_SET     (0x04)  // 0x20, 0x40, 0x60, 0xff
#define HIGH_BRIGHT       (0x1f)  // full brightness
#define CURSOR_BLINK_ON   (0x07)
#define BLINK_START       (0x0b)
#define BLINK_END         (0x0c)
#define CURSOR_OFF        (0x0e)
#define CURSOR_ON         (0x0f)
#define SET_CURSOR        (0x1b)
#define RESET             (0x14)
#define CLEAR             (0x15)
#define HOME              (0x16)
#define UNDERLINE         (0x17)
#define UL_UL             (0x44)
#define UL_BL             (0x46)
#define UL_END            (0x45)


void reset(void)
{
  PORTB &= 0xdf;  // clear reset pin
  _delay_ms(5);   // spec is 2 ms, but let's be safe
  PORTB |= 0x20;  // set reset pin
  _delay_ms(2);   // RES to WR is 2 ms, should be fine here
}

void write(uint8_t d)
{
  uint8_t b = PORTB;
  b &= 0xf0;
  b |= (d & 0x0f);
  PORTB = b;
  b = PORTD;
  b &= 0x0f;
  b |= (d & 0xf0);
  PORTD = b;

  PORTB &= 0xef;  // clear WR
  PORTB |= 0x10;  // set WR
  _delay_us(350); // wait
  // _delay_ms(5);
}

void writeString(char* str)
{
  if(str != NULL)
  {
    char ch;
    while((ch = *str) != 0)
    {
      write(ch);
      str++;
    }
  }
}

void cursor(int onoff)
{
  if(onoff != 0)
  {
    write(0x0f);  // turn it on
  }
  else
  {
    write(0x0e);  // turn it off
  }
}

void setCursor(int pt)
{
  if(pt < 40)
  {
    write(0x1b);
    write( (uint8_t)(pt & 0xff) );
  }
}

void clear(void)
{
  write(CLEAR);
}

void writeNumber(int num, int places)
{

}

void writeTach(int rpm)
{
  if(rpm < 0) rpm = 0;
  if(rpm > 7999) rpm = 7999;
  // setCursor(10);
  //writeString("          ");
  setCursor(10);
  uint8_t scale = (uint8_t)(rpm / 100); // scale to 0 to 80
  char ch1 = scale / 10 + '0';
  //if(ch1 == '0') ch1 = ' ';
  char ch2 = scale % 10 + '0';

  scale /= 2;  // now 0 to 40;
  uint8_t full = scale / 5;
  uint8_t part = scale % 5;
  int toWrite = 8;
  for(int i = 0; i < full; i++) write(0x7f);
  toWrite -= full;
  
  char partChar = ' ';
  switch(part)
  {
  case 0:
    partChar = ' ';
    break;
  case 1:
    partChar = 0xf0;
    break;
  case 2:
    partChar = 0xf1;
    break;
  case 3:
    partChar = 0xf2;
    break;
  case 4:
    partChar = 0xf3;
    break;
  default:
    partChar = 0xfe;
    break;
  }
  write(partChar);
  toWrite -= 1;
  for(int i = 0; i < toWrite; i++) write(' ');
  write(ch1);
  write(ch2);
}

void init(void)
{
  DDRB = 0x3f;      // D0-D3 and WR, RES as outputs
  DDRD = 0xf0;      // D4-D7 as outputs
  PORTB = 0xff;     // Prep the objective
  PORTD = 0xff;
  reset();
  clear();
  _delay_ms(100);   // Let things settle
  write(LUMINANCE_SET);
  write(0x20);      // Set low brightness
  cursor(0);        // Turn off cursor
  setCursor(0);
  writeString("v13.6");     // Init display constants
  setCursor(5);
  writeString("t 180");
  setCursor(20);
  writeString("p  60");
  setCursor(25);
  writeString("o 187");
  setCursor(30);
  writeString(" f 38");
  setCursor(35);
  writeString("mp 42");
}

  

int main()
{
  init();

  while(1)
  {
    int rpm;
    for(rpm = 0; rpm < 8000; rpm+=25)
    {
      writeTach(rpm);
       _delay_ms(1);
    }
    for(rpm = 7999; rpm > 0; rpm-=25)
    {
      writeTach(rpm);
       _delay_ms(1);
    }
  }
    
}


  
  
  
  
