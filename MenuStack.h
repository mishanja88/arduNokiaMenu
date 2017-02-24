#ifndef MENU_STACK_H
#define MENU_STACK_H

#include "AbstractMenu.h"

class MenuStack
{
    class Item
    {
      public:
        Item(const AbstractMenu* _data, Item* _prev);

        const AbstractMenu* data;
        Item* prev;
    };

  public:
    MenuStack();

    void init(const AbstractMenu* _mainMenu);
    void paint() const;
    bool processEvents();
    
    bool isEmpty() const;

    const AbstractMenu* getPrevHelper(const AbstractMenu* parent, const AbstractMenu* child) const;
    
    const AbstractMenu* getPrev() const;
    const AbstractMenu* getNext() const;
    const AbstractMenu* popParent();
    const AbstractMenu* getChild() const;
  
    const AbstractMenu* pop();
    void push(const AbstractMenu* menu);

  protected:
    Item* top;
    const AbstractMenu* curMenu;
};

extern MenuStack g_menuStack;

#endif // MENU_STACK_H
