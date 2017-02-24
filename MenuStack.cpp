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

const AbstractMenu* MenuStack::getPrevFor(const AbstractMenu* ptr) const
{
  if (top)
    for (const AbstractMenu* it = top->data->child; it != ptr; it = it->next)
      if (it->next == ptr)
        return it;

  return ptr;
}


const AbstractMenu* MenuStack::getNextFor(const AbstractMenu* ptr) const
{
  if (top)
    for (const AbstractMenu* it = top->data->child; it != ptr; it = it->next)
      if (it->next == ptr)
        return it;

  return ptr;
}

const AbstractMenu* MenuStack::getParentFor(const AbstractMenu* ptr) const
{
  if (top)
    for (const AbstractMenu* it = top->data->child; it != ptr; it = it->next)
      if (it->next == ptr)
        return it;

  return ptr;
}


const AbstractMenu* MenuStack::getChildFor(const AbstractMenu* ptr) const
{
  if (top)
    for (const AbstractMenu* it = top->data->child; it != ptr; it = it->next)
      if (it->next == ptr)
        return it;

  return ptr;
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
    top = new Item(menu, top);
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
    delete prevMenu;
  }
  
  return false;
}

