#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "BaseMenu.h"

class MainMenu : public BaseMenu
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

    TYPEID_CLASS(MainMenu) (const AbstractMenu* _child)
      : TYPEID_PARENT(BaseMenu) _child, nullptr)
    {
    }
    
    void paint() const override;
    const AbstractMenu* processEvents() const override;
};

#endif // MAIN_MENU_H
