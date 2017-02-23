#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "AbstractMenu.h"

class MainMenu : public AbstractMenu
{
  public:
  MainMenu();
  
  void paint() const override;
  AbstractMenu* processEvents() override;
};

class Test : public MainMenu
{
  public:
  Test()
  {}
};

#endif // MAIN_MENU_H
