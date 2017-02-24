#include "LcdUtil.h"
#include <MemoryFree.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"

extern Adafruit_PCD8544 display;

void printDebugMem(const char *label)
{
    display.fillRect(0, 30, 20, 20, WHITE);
    display.setCursor(0, 30);
    display.println(freeMemory());
    if(label)
      printProgmem(label);
      
    display.setCursor(0, 0);
    display.display();
//    delay(3000);
}

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
    display.print(len);
    printProgmem(PSTR(":"));
  }
  for (int i = 0; i < len; ++i)
  {
    display.print(pgm_read_byte(mem++), HEX);
    printProgmem(PSTR("|"));
  }
  display.println();
}

