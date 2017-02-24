#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include "Arduino.h"
#include "TypeId.h"

class AbstractMenu : public TypeIdClass
{
  public:
    virtual void paint() const = 0;
    virtual const AbstractMenu* processEvents() const = 0;

    const PROGMEM AbstractMenu* child;
    const PROGMEM AbstractMenu* next;

  protected:
    constexpr AbstractMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next)
      : TypeIdClass(_typeId), child(_child), next(_next)
    {
    }

};

#endif // ABSTRACT_MENU_H
