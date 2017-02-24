#include "LcdUtil.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"

extern Adafruit_PCD8544 display;

void printProgmem(const char *data)
{
    char buf[] = "0";
    while ((buf[0] = pgm_read_byte(data++)) != 0x00)
      display.print(buf);
}

void printRaw(const char* mem, int len, const char* title = 0)
{
  if (title)
  {
    printProgmem(title);
    display.println();
  }
  for (int i = 0; i < len; ++i)
    display.print(pgm_read_byte(mem + i), HEX);
  display.println();
}

