#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

class AbstractMenu
{
  public:
    virtual void paint() const = 0;
    virtual const AbstractMenu* processEvents() const = 0;
  
    AbstractMenu(const AbstractMenu* _child, const AbstractMenu* _next);

    const AbstractMenu* child;
    const AbstractMenu* next;
};

#endif // ABSTRACT_MENU_H
