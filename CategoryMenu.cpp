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
  if (g_dirtyWidgets == 0xFF)
  {
    display.clearDisplay();
    printProgmem(label);
  }

  if (g_dirtyWidgets & wMenuBtn)
  {
    printProgmem(PSTR("Menu"));
    display.println();
  }

  if (g_dirtyWidgets & wMainVol)
  {
    printProgmem(PSTR("wMainVol"));
  }

  if (g_dirtyWidgets & wMicVol)
  {
    printProgmem(PSTR("wMicVol"));
  }

  if (g_dirtyWidgets & wBattery)
  {
    printProgmem(PSTR("Bat"));
  }

  if (g_dirtyWidgets & wPresetName)
  {
    printProgmem(PSTR("Preset name"));
  }

  for (int i = 0; i < 3; ++i)
    if (g_dirtyWidgets & (1 << i))
    {
      display.setCursor(i << 3, 20);
      display.println(i);
    }

  //else
  // display.println("done");
}

const AbstractMenu* CategoryMenu::processEvents() const
{
  BaseMenu::processEvents();

  if (hasPinEvent(PIN_BTN_CANCEL))
  {
    display.clearDisplay();

    printProgmem(PSTR("bgGP,"));
    display.display();
    delay(1000);

    
    const AbstractMenu* result = g_menuStack.getParent();

    if (result == nullptr)
      printProgmem(PSTR("ret(NULL),"));
    else
      printProgmem(PSTR("ret(OK),"));

    display.display();
    delay(1000);


    return result;
  }

  if (hasPinEvent(PIN_BTN_OK) && child)
    return g_menuStack.getChild();

  if (hasPinEvent(PIN_SEL_DOWN) && next)
    return g_menuStack.getNext();

  if (hasPinEvent(PIN_SEL_UP))
    return g_menuStack.getPrev();

  return this;
}

