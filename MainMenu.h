#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "AbstractMenu.h"

class MainMenu : public AbstractMenu
{
  public:
  enum Widgets
  {   
    wPresetName = (1 << 11),
    wBattery = (1 << 12),
    wVolume = (1 << 13),
    wMenuBtn = (1 << 14),
    wAll = (1 << 15), 
  };
  
  MainMenu();
  
  void paint(Adafruit_PCD8544* display) const override;
  AbstractMenu* processEvents() override;
};

class Test : public MainMenu
{
  public:
  Test()
  {}
};

#endif // MAIN_MENU_H
