#include "CategoryMenu.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"
#include "LcdUtil.h"

extern Adafruit_PCD8544 display;

//static const char prTest[] PROGMEM = "All";
//static const char prTest2[] = "Allkasdjlajdfasdjfk;kklk;k;;;;;;;;;;;klklklklklklklklklklklklklklkl";

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

AbstractMenu* CategoryMenu::processEvents()
{
  if(g_btnEvent)
    g_dirtyWidgets = ~0;
  return (g_btnEvent && prev) ? prev : this;
}

CategoryMenu::CategoryMenu(const char *_label, AbstractMenu* _prev, bool prevIsParent)
: AbstractMenu(_prev, prevIsParent), label(_label)
{
}
