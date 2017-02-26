#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "AbstractMenu.h"

class BaseMenu : public AbstractMenu
{
  public:
    const MenuTreeItem* processEvents() const override;

  protected:
    constexpr BaseMenu(const int _typeSize)
      : AbstractMenu(_typeSize)
    {
    }
};

#endif // BASE_MENU_H
