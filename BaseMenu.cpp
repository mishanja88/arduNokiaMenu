#include "BaseMenu.h"
#include "SystemState.h"


const MenuTreeItem* BaseMenu::processEvents() const
{
    // g_selPos += g_diffSel / 2;
        
    g_Sys.eq.headVolume += g_Sys.event.diffVol;
    
    if(g_Sys.eq.headVolume < 0)
      g_Sys.eq.headVolume = 0;
    else if(g_Sys.eq.headVolume > 0xFF)
      g_Sys.eq.headVolume = 0xFF;
    
    return nullptr;
}

