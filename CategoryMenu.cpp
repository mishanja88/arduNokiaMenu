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
    return g_menuStack.pop();

  if (hasPinEvent(PIN_BTN_OK) && child)
    return child;

  if (hasPinEvent(PIN_SEL_DOWN) && next)
    return next;

  if (hasPinEvent(PIN_SEL_UP))
    return g_menuStack.getPrevFor(this);

  return this;
}

CategoryMenu::CategoryMenu(const char *_label, const AbstractMenu* _child, const AbstractMenu* _next)
  : BaseMenu(_child, _next), label(_label)
{
}
