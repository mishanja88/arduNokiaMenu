#include "MainMenu.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"

extern Adafruit_PCD8544 display;

void MainMenu::paint() const
{
  if(g_dirtyWidgets & wAll)
  {
    display.clearDisplay();
    display.println("Main menu");
  } 
  else
    display.println("done");
}

AbstractMenu* MainMenu::processEvents()
{
  return this;
}

MainMenu::MainMenu()
{
}
