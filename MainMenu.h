#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "AbstractMenu.h"

class MainMenu : public AbstractMenu
{
  public:
  enum Widgets
  {
    wEqLow = (1 << 0),
    wEqMid = (1 << 1),
    qEqHigh = (1 << 2),
    
    wPresetName = (1 << 3),
    wBattery = (1 << 4),
    wMainVol = (1 << 5),
    wMicVol = (1 << 6),
    wMenuBtn = (1 << 7)
  };
    
  MainMenu();
  
  void paint() const override;
  AbstractMenu* processEvents() override;
};

#endif // MAIN_MENU_H
