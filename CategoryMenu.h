#ifndef CATEGORY_MENU_H
#define CATEGORY_MENU_H

#include "BaseMenu.h"

class CategoryMenu : public BaseMenu
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
    
  CategoryMenu(const char *_label, AbstractMenu* _prev = nullptr, bool prevIsParent = false);
  
  void paint() const override;
  AbstractMenu* processEvents() override;

  protected:
    const char *label;
};

#endif // CATEGORY_MENU_H
