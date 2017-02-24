#include "BaseMenu.h"
#include "SystemState.h"


const AbstractMenu* BaseMenu::processEvents() const
{
    g_selPos += g_diffSel / 2;
        
    g_volPos += g_diffVol;
    
    if(g_volPos < 0)
      g_volPos = 0;
    else if(g_volPos > 0xFF)
      g_volPos = 0xFF;
    
    return this;
}

