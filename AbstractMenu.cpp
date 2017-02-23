#include "AbstractMenu.h"

AbstractMenu::AbstractMenu(AbstractMenu* _prev, bool prevIsParent)
  : prev(_prev), child(nullptr), next(nullptr)
{
  if (prev)
  {
    if (prevIsParent)
      prev->setChild(this);
    else
      prev->setNext(this);
  }
}

bool AbstractMenu::hasParent() const
{
  return prev && prev->child == this;
}


void AbstractMenu::setChild(AbstractMenu* ptr)
{
  child = ptr;
}

void AbstractMenu::setNext(AbstractMenu* ptr)
{
  next = ptr;
}

