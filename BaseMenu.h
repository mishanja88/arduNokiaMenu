#ifndef BASE_MENU_H
#define BASE_MENU_H

#include "AbstractMenu.h"

class BaseMenu : public AbstractMenu
{
  public:
    const AbstractMenu* processEvents() const override;

  protected:
    BaseMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next);
};

#endif // BASE_MENU_H
