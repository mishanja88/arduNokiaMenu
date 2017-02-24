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
  const AbstractMenu* parent = top->data;

  const AbstractMenu* prevPtr = nullptr;
  if (!parent)
    return prevPtr;

  // getting first submenu
  const AbstractMenu* nextPtr = (const AbstractMenu*) metaToRam((const char *)parent->child);
  prevPtr = nextPtr;

  // moving further till current menu
  while (nextPtr)
  {
    if (nextPtr->next == curMenu->next && nextPtr->child == curMenu->child)
      break;

    if (prevPtr != nextPtr)
      delete prevPtr; // removing unused
    prevPtr = nextPtr;
    nextPtr = (const AbstractMenu*) metaToRam((const char *)nextPtr->next);
  }

  if (prevPtr != nextPtr)
    delete nextPtr;
  return prevPtr;
}



const AbstractMenu* MenuStack::popParent()
{
  if (top != nullptr)
    return pop();

  return nullptr;
}

const AbstractMenu* MenuStack::getNext() const
{
  if (curMenu && curMenu->next)
    return (const AbstractMenu*) metaToRam((const char*) curMenu->next);

  return nullptr;
}

const AbstractMenu* MenuStack::getChild() const
{
  if (curMenu && curMenu->child)
    return (const AbstractMenu*) metaToRam((const char*) curMenu->child);

  return nullptr;
}

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
  curMenu = (AbstractMenu*) metaToRam((const char*)_mainMenu);
}

void MenuStack::paint() const
{
  curMenu->paint();
}

bool MenuStack::processEvents()
{
  const AbstractMenu* prevMenu = curMenu;

  curMenu = curMenu->processEvents();

  if (curMenu != prevMenu)
  {
    if (prevMenu->child)
    {
      AbstractMenu* pmChild = (AbstractMenu*) metaToRam((const char*)prevMenu->child);

      if ((pmChild->next == curMenu->next) && (pmChild->child == curMenu->child))
        push(prevMenu);
      else
        delete prevMenu;

      delete pmChild;
    }
    else
      delete prevMenu;

    return true;
  }

  return false;
}

