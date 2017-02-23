#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "AbstractMenu.h"

class BaseMenu : public AbstractMenu
{
  public:
    AbstractMenu* processEvents() override;

  protected:
    BaseMenu(AbstractMenu* _prev = nullptr, bool prevIsParent = false);
};

#endif // BASE_MENU_H
