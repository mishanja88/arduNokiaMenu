#include "MenuStack.h"

MenuStack g_menuStack;

MenuStack::MenuStack()
  : arrayPtr(nullptr), curPackedItem(nullptr), curUnpackedItem(nullptr), curUnpackedMenu(nullptr)
{
}

const MenuTreeItem* MenuStack::unpackItem(const MenuTreeItem* packedItemPtr) const
{
  return copyToRam<const MenuTreeItem>(packedItemPtr);
}

const AbstractMenu* MenuStack::unpackMenu(const MenuTreeItem* unpackedItemPtr) const
{
  return (const AbstractMenu*) metaToRam((const char *) unpackedItemPtr->data);
}

void MenuStack::init(const char* _arrayPtr)
{
  arrayPtr = _arrayPtr;
  curPackedItem = (const MenuTreeItem*) pgm_read_word(_arrayPtr);
  curUnpackedItem = unpackItem(curPackedItem);
  curUnpackedMenu = unpackMenu(curUnpackedItem);
}

void MenuStack::paint() const
{
  curUnpackedMenu->paint();
}

void MenuStack::processEvents()
{
  const MenuTreeItem* nextItem = curUnpackedMenu->processEvents();

  if (nextItem && nextItem != curPackedItem)
  {
    curPackedItem = nextItem;

    delete curUnpackedItem;
    delete curUnpackedMenu;
    
    curUnpackedItem = unpackItem(nextItem);
    curUnpackedMenu = unpackMenu(curUnpackedItem);
  }
}

