#include "MenuStack.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "LcdUtil.h"

extern Adafruit_PCD8544 display;

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

void MenuStack::init(const void* _arrayPtr)
{
  arrayPtr = (const MenuTreeItem**)_arrayPtr;
  curPackedItem = (const MenuTreeItem*) pgm_read_word(_arrayPtr);
  curUnpackedItem = unpackItem(curPackedItem);
  curUnpackedMenu = unpackMenu(curUnpackedItem);
}

void MenuStack::paint() const
{
  curUnpackedMenu->paint();
}

bool MenuStack::processEvents()
{
  const MenuTreeItem* nextItem = curUnpackedMenu->processEvents();

  display.clearDisplay();
  printRaw((const char*)curPackedItem, sizeof(MenuTreeItem), PSTR("CurPacked"));
  display.display();
  delay(3000);

  if (nextItem && nextItem != curPackedItem)
  {
    printRaw((const char*)nextItem, sizeof(MenuTreeItem), PSTR("nextItem"));
    display.display();
    delay(3000);
    
    delete curUnpackedItem;
    delete curUnpackedMenu;

    curUnpackedItem = unpackItem(nextItem);

//    printRaw((const char*)curUnpackedItem, sizeof(MenuTreeItem), PSTR("nextItem"));
//    display.display();
//    delay(3000);
    
    curUnpackedMenu = unpackMenu(curUnpackedItem);

    return true;
  }

  return false;
}

