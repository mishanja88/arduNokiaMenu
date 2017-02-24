#include "MenuStack.h"

MenuStack g_menuStack;

MenuStack::Item::Item(const AbstractMenu* _data, Item* _prev)
  : data(_data), prev(_prev)
{
}

MenuStack::MenuStack()
  : top(nullptr)
{
}

bool MenuStack::isEmpty() const
{
  return top;
}

const AbstractMenu* MenuStack::getPrev() const
{
  if (!top)
    return nullptr;

  // getting parent menu
  const AbstractMenu* parent = (const AbstractMenu*) metaToRam((const char *)top->data);

  // getting first submenu
  const AbstractMenu* nextPtr = parent->child;

  // returning packed result!
  const AbstractMenu* result = parent->child;
  delete parent;

  // moving further till current menu
  while (nextPtr != curMenu)
  {
    result = nextPtr;
    nextPtr = (const AbstractMenu*) metaToRam((const char *)nextPtr);
    const AbstractMenu *prevPtr = nextPtr;
    nextPtr = nextPtr->next;
    delete prevPtr; // removing unused
  }
  
  return result;
}



const AbstractMenu* MenuStack::popParent()
{
  if (top != nullptr)
    return pop();

  return nullptr;
}

/*
const AbstractMenu* MenuStack::getNext() const
{
  if (curMenu && curMenu->next)
    return curMenu->next; //(const AbstractMenu*) metaToRam((const char*) curMenu->next);

  return nullptr;
}

const AbstractMenu* MenuStack::getChild() const
{
  if (curMenu && curMenu->child)
    return curMenu->child; //(const AbstractMenu*) metaToRam((const char*) curMenu->child);

  return nullptr;
}
*/

const AbstractMenu* MenuStack::pop()
{
  if (!top)
    return nullptr;

  const AbstractMenu* result = top->data;
  Item* prevTop = top;
  top = top->prev;
  delete prevTop;

  return result;
}

void MenuStack::push(const AbstractMenu* menu)
{
  if (menu)
  {
    Item* prevTop = top;
    top = new Item(menu, prevTop);
  }
}


void MenuStack::init(const AbstractMenu* _mainMenu)
{
  curMenu = _mainMenu; // (AbstractMenu*) metaToRam((const char*)_mainMenu);
}

void MenuStack::paint() const
{
  const AbstractMenu* unpackedMenu = (const AbstractMenu*) metaToRam((const char*)curMenu);
  unpackedMenu->paint();
  delete unpackedMenu;
}

bool MenuStack::processEvents()
{
  bool result = false;

  const AbstractMenu* prevMenu = curMenu;
  const AbstractMenu* unpackedPrev = (AbstractMenu*) metaToRam((const char*)prevMenu);

  curMenu = unpackedPrev->processEvents();

  if ((!curMenu) || curMenu == unpackedPrev)
  {
    curMenu = prevMenu;
  }
  else
  {
    if (unpackedPrev->child == curMenu)
        push(prevMenu);

    result = true;
  }

  delete unpackedPrev;
  return result;
}

