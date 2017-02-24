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



  if (!top)
  {
    printProgmem(PSTR("gPtop(NULL),"));
    display.display();
    delay(1000);
    return prevPtr;
  }

  // getting parent menu
  const AbstractMenu* parent = top->data;
  return getPrevHelper(parent, curMenu);
}

const AbstractMenu* MenuStack::getPrevHelper(const AbstractMenu* parent, const AbstractMenu* child) const
{
  const AbstractMenu* prevPtr = nullptr;
  if (!parent)
  {
    printProgmem(PSTR("gpPar(NULL),"));
    display.display();
    delay(1000);

    return prevPtr;
  }

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
  {
    return pop(); // top->data; // already in heap!
  }

  display.clearDisplay();
  printProgmem(PSTR("NO TO,"));
  display.display();
  delay(1000);

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

  display.clearDisplay();
  printProgmem(PSTR("POP POP"));
  display.display();
  delay(1000);

  const AbstractMenu* result = top->data;
  Item* prevTop = top;
  top = top->prev;
  delete prevTop;

  return result;
}

void MenuStack::push(const AbstractMenu* menu)
{
  display.clearDisplay();
  printProgmem(PSTR("PUSH"));
  display.display();
  delay(1000);

  if (menu)
  {
    Item* prevTop = top;
    // top = (Item*) malloc(sizeof(Item));
    // top->data = menu;
    // top->prev = prevTop;

    top = new Item(menu, prevTop);

    if (!top)
    {
      printProgmem(PSTR("top(NULL),"));
      display.display();
      delay(1000);
    }
  }
  else
  {
    printProgmem(PSTR("menu(NULL),"));
    display.display();
    delay(1000);
  }

  if (!top)
  {
    printProgmem(PSTR("top(NULL),"));
    display.display();
    delay(1000);
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

  printDebugMem(PSTR("Before process"));

  curMenu = curMenu->processEvents();

  printDebugMem(PSTR("After process"));


  if (curMenu != prevMenu)
  {
    if (prevMenu->child)
    {
      printDebugMem(PSTR("Child1"));

      AbstractMenu* pmChild = (AbstractMenu*) metaToRam((const char*)prevMenu->child);

      if ((pmChild->next == curMenu->next) && (pmChild->child == curMenu->child))
      {
        printDebugMem(PSTR("Child1-push"));
        push(prevMenu);
      }
      else
        delete prevMenu;

      delete pmChild;
    }
    else
    {
      delete prevMenu;
      printDebugMem(PSTR("Child1-deleted"));
    }

    return true;
  }

  return false;
}

