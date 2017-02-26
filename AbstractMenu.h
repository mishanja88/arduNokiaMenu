#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include "Arduino.h"
#include "TypeId.h"
#include "TreeItem.h"

class AbstractMenu;
typedef TreeItem<const AbstractMenu> MenuTreeItem;

class AbstractMenu : public TypeIdClass
{
  public:
    virtual void paint() const = 0;
    virtual const MenuTreeItem* processEvents() const = 0;

  protected:
    constexpr AbstractMenu(const int _typeSize)
      : TypeIdClass(_typeSize)
    {
    }

};

#endif // ABSTRACT_MENU_H
