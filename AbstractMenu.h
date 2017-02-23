#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

class Adafruit_PCD8544;

class AbstractMenu
{
  public:
    AbstractMenu(AbstractMenu* _prev = nullptr, bool prevIsParent = false);

    void setChild(AbstractMenu* ptr);
    void setNext(AbstractMenu* ptr);

    bool hasParent() const;

    virtual void paint(Adafruit_PCD8544* display) const = 0;
    virtual AbstractMenu* processEvents() = 0;
  
  protected:
    AbstractMenu* prev;
    AbstractMenu* child;
    AbstractMenu* next;
};

#endif // ABSTRACT_MENU_H
