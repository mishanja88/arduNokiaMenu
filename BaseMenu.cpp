#include "BaseMenu.h"
#include "SystemState.h"
#include "MenuStack.h"

const MenuTreeItem* BaseMenu::processEvents() const
{
  // g_selPos += g_diffSel / 2;

  g_Sys.eq.headVolume += g_Sys.event.diffVol;

  if (g_Sys.eq.headVolume < 0)
    g_Sys.eq.headVolume = 0;
  else if (g_Sys.eq.headVolume > 0xFF)
    g_Sys.eq.headVolume = 0xFF;

  if (g_Sys.event.btnEvent & ~0x3)
    g_Sys.widgetsDirty();

  if (g_Sys.hasPin(PIN_BTN_CANCEL))
    return g_menuStack.getParent();

  if (g_Sys.hasPin(PIN_BTN_OK))
    return g_menuStack.getChild();

  if (g_Sys.hasPin(PIN_SEL_DOWN))
    return g_menuStack.getNext();

  if (g_Sys.hasPin(PIN_SEL_UP))
    return g_menuStack.getPrev();

  return nullptr;
}

