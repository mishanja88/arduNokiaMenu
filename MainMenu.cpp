#include "MainMenu.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SystemState.h"

extern Adafruit_PCD8544 display;

void MainMenu::paint() const
{
  if(g_dirtyWidgets)// & wAll)
  {
    display.println("Main menu");
    display.display();
    
    digitalWrite(PIN_LED_OUT, LOW);
    delay(750);
    digitalWrite(PIN_LED_OUT, HIGH);
    delay(750);
    digitalWrite(PIN_LED_OUT, LOW);
    delay(750);

    ///display.clearDisplay();
  } 
  //else
    // display.println("done");
}

AbstractMenu* MainMenu::processEvents()
{
  return this;
}

MainMenu::MainMenu()
{
}
