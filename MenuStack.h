#ifndef MENU_STACK_H
#define MENU_STACK_H

#include "AbstractMenu.h"

class MenuStack
{
  public:
    MenuStack();

    void init(const char* _arrayPtr);
    void paint() const;
    bool processEvents();

    inline const MenuTreeItem* getPrev() const {
      return curUnpackedItem ? curUnpackedItem->prev(arrayPtr) : nullptr;
    }
    inline const MenuTreeItem* getParent() const {
      return curUnpackedItem ? curUnpackedItem->parent(arrayPtr) : nullptr;
    }
    inline const MenuTreeItem* getNext() const {
      return curUnpackedItem ? curUnpackedItem->next(arrayPtr) : nullptr;
    }
    inline const MenuTreeItem* getChild() const {
      return curUnpackedItem ? curUnpackedItem->child(arrayPtr) : nullptr;
    }

  protected:
    const MenuTreeItem* unpackItem(const MenuTreeItem* packedItemPtr) const;
    const AbstractMenu* unpackMenu(const MenuTreeItem* packedItemPtr) const;

    const char* arrayPtr;
    const MenuTreeItem* curPackedItem;

    const MenuTreeItem* curUnpackedItem;
    const AbstractMenu* curUnpackedMenu;

};

extern MenuStack g_menuStack;

#endif // MENU_STACK_H
