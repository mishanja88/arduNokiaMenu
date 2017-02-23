#include "BaseMenu.h"
#include "SystemState.h"

BaseMenu::BaseMenu(AbstractMenu* _prev, bool prevIsParent)
: AbstractMenu(_prev, prevIsParent)
{
}

AbstractMenu* BaseMenu::processEvents()
{
    g_selPos += g_diffSel;
        
    g_volPos += g_diffVol;
    
    if(g_volPos < 0)
      g_volPos = 0;
    else if(g_volPos > 0xFF)
      g_volPos = 0xFF;
    
    return this;
}

