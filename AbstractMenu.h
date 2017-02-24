#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include "Arduino.h"
#include "TypeId.h"

class AbstractMenu
{
  public:
    virtual void paint() const = 0;
    virtual const AbstractMenu* processEvents() const = 0;

    const PROGMEM TypeId typeId;
    const PROGMEM AbstractMenu* child;
    const PROGMEM AbstractMenu* next;

  protected:
    constexpr AbstractMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next)
      : child(_child), next(_next), typeId(_typeId)
    {
    }

};

#endif // ABSTRACT_MENU_H
