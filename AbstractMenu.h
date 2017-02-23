#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

class AbstractMenu
{
  public:
    void setChild(AbstractMenu* ptr);
    void setNext(AbstractMenu* ptr);

    bool hasParent() const;

    virtual void paint() const = 0;
    virtual AbstractMenu* processEvents() = 0;
  
    AbstractMenu(AbstractMenu* _prev = nullptr, bool prevIsParent = false);

    AbstractMenu* prev;
    AbstractMenu* child;
    AbstractMenu* next;
};

#endif // ABSTRACT_MENU_H
