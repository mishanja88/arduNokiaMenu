#include "CategoryMenu.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"
#include "LcdUtil.h"
#include "MenuStack.h"

extern Adafruit_PCD8544 display;

void CategoryMenu::paint() const
{
  if (g_Sys.event.dirtyWidgets == 0xFF)
  {
    display.clearDisplay();
    printProgmem(label);
  }

  if (g_Sys.event.dirtyWidgets & wMenuBtn)
  {
    printProgmem(PSTR("Menu"));
    display.println();
  }

  if (g_Sys.event.dirtyWidgets & wMainVol)
  {
    printProgmem(PSTR("wMainVol"));
  }

  if (g_Sys.event.dirtyWidgets & wMicVol)
  {
    printProgmem(PSTR("wMicVol"));
  }

  if (g_Sys.event.dirtyWidgets & wBattery)
  {
    printProgmem(PSTR("Bat"));
  }

  if (g_Sys.event.dirtyWidgets & wPresetName)
  {
    printProgmem(PSTR("Preset name"));
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

const MenuTreeItem* CategoryMenu::processEvents() const
{
  BaseMenu::processEvents();

  if (g_Sys.hasPinEvent(PIN_BTN_CANCEL))
    return g_menuStack.getParent();

  if (g_Sys.hasPinEvent(PIN_BTN_OK))
    return g_menuStack.getChild();

  if (g_Sys.hasPinEvent(PIN_SEL_DOWN))
    return g_menuStack.getNext();

  if (g_Sys.hasPinEvent(PIN_SEL_UP))
    return g_menuStack.getPrev();

  return nullptr;
}

