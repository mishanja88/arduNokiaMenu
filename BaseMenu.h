#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "AbstractMenu.h"

class BaseMenu : public AbstractMenu
{
  public:
    const AbstractMenu* processEvents() const override;

  protected:
    constexpr BaseMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next)
      : AbstractMenu(_typeId, _child, _next)
    {
    }
};

#endif // BASE_MENU_H