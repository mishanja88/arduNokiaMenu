#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include "TypeId.h"

class AbstractMenu
{
  public:
    virtual void paint() const = 0;
    virtual const AbstractMenu* processEvents() const = 0;

    const TypeId typeId;
    const AbstractMenu* child;
    const AbstractMenu* next;

  protected:
    AbstractMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next);

};

#endif // ABSTRACT_MENU_H
