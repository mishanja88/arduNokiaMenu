#include "MainMenu.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"
#include "LcdUtil.h"
#include "MenuStack.h"

extern Adafruit_PCD8544 display;

#define D_W 84
#define D_H 48
#define HEADER_H 10
#define VOL_W 10
#define VOL_H 34

void MainMenu::paint() const
{
  if (g_Sys.event.dirtyWidgets == 0xFF)
  {
    display.clearDisplay();
    display.drawFastHLine(0, HEADER_H, D_W, BLACK);
    // display.drawFastHLine(0, D_H - HEADER_H, D_W, BLACK);
  }

  if (g_Sys.event.dirtyWidgets & wMenuBtn)
  {
    display.setCursor(40, D_W - 30);
    printProgmem(PSTR("Menu"));
  }

  if (g_Sys.event.dirtyWidgets & wMainVol)
  {
    display.fillRect(D_W - VOL_W, 2 + HEADER_H, VOL_W, VOL_H, BLACK);
    display.drawFastVLine(1 + D_W - VOL_W, 2 + HEADER_H + 1, VOL_H - 2, WHITE);
    display.drawFastVLine(-2 + D_W, 2 + HEADER_H + 1, VOL_H - 2, WHITE);

    int fixedVol = g_Sys.eq.headVolume >> 3;
    display.fillRect(2 + D_W - VOL_W, 2 + HEADER_H + 1, VOL_W - 4, (VOL_H - 2) - fixedVol, WHITE);

    /* int labelOffset = D_W - 30

     display.setCursor(D_W - 30, D_H >> 1);
     display.println(g_volPos);

     display.setCursor(D_W - 30, D_H >> 1);
     display.println(g_volPos);
    */
    // printProgmem(PSTR("wMainVol"));
    // display.println(g_volPos);
  }

  if (g_Sys.event.dirtyWidgets & wMicVol)
  {
    // printProgmem(PSTR("wMicVol"));
  }

  if (g_Sys.event.dirtyWidgets & wBattery)
  {
    // printProgmem(PSTR("Bat"));
  }

  if (g_Sys.event.dirtyWidgets & wPresetName)
  {
    // printProgmem(PSTR("Preset name"));
  }

  for (int i = 0; i < 3; ++i)
    if (g_Sys.event.dirtyWidgets & (1 << i))
    {
      display.setCursor(i << 3, 20);
      display.println(i);
    }

  //else
  // display.println("done");
}

const MenuTreeItem* MainMenu::processEvents() const
{
  if(g_Sys.event.diffVol)
    g_Sys.event.dirtyWidgets |= wMainVol;

  return BaseMenu::processEvents();
}
