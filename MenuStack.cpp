#include "MenuStack.h"
#include "LcdUtil.h"


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
extern Adafruit_PCD8544 display;

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
  const AbstractMenu* prevPtr = nullptr;

  // getting parent menu
  const AbstractMenu* parent = getParent();
  if (!parent)
    return prevPtr;

  // getting first submenu
  const AbstractMenu* nextPtr = (const AbstractMenu*) metaToRam((const char *)parent->child);
  delete parent; // removing unused

  // moving further till current menu
  while (nextPtr)
  {
    if (nextPtr->next == curMenu->next && nextPtr->child == curMenu->child)
      return prevPtr;

    delete prevPtr; // removing unused
    prevPtr = nextPtr;
    nextPtr = (const AbstractMenu*) metaToRam((const char *)nextPtr->next);
  }

  return nullptr;
}

const AbstractMenu* MenuStack::getParent() const
{
  if (top)
    return (const AbstractMenu*) metaToRam((const char *)top->data);

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
  printProgmem(PSTR("pch"));
  display.display();
  delay(1000);

  if (curMenu && curMenu->child)
  {
    printProgmem(PSTR(",pch2"));
    display.display();
    delay(1000);
    const AbstractMenu* result = (const AbstractMenu*) metaToRam((const char*) curMenu->child);
    if (result)
      printProgmem(PSTR(",pchOK"));
    else
      printProgmem(PSTR(",pchNULL"));
    display.display();
    delay(1000);
    return result;
  }

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
    printProgmem(PSTR("point1"));
    display.display();
    delay(1000);

    if (curMenu->child && curMenu->child->next == prevMenu->next && curMenu->child->child == prevMenu->child)
      pop();

    if (prevMenu->child && prevMenu->child->next == curMenu->next && prevMenu->child->child == curMenu->child)
      push(prevMenu);
    else
      delete prevMenu;

    return true;
  }

  return false;
}

