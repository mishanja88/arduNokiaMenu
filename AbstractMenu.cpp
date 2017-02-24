#include "AbstractMenu.h"

AbstractMenu::AbstractMenu(const TypeId _typeId, const AbstractMenu* _child, const AbstractMenu* _next)
: child(_child), next(_next), typeId(_typeId)
{
}

