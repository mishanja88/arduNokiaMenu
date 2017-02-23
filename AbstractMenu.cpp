#include "AbstractMenu.h"

AbstractMenu::AbstractMenu(const AbstractMenu* _child, const AbstractMenu* _next)
  : child(_child), next(_next)
{
}

