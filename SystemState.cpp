#include "SystemState.h"

int selPos = 0;
int volPos = 0;

volatile int g_diffSel = 0;
volatile int g_diffVol = 0;

volatile int g_btnEvent = 0;
volatile int g_oldPORTD = 0;

bool hasPinEvent(PinMappings pin)
{
  if(pin >= PIN_BTN_CANCEL)
    return g_btnEvent & (1 << pin);
  
  switch(pin)
  {
    case PIN_VOL_DOWN: return g_diffVol < 0; break;
    case PIN_VOL_UP: return g_diffVol > 0; break;
    case PIN_SEL_DOWN: return g_diffSel < 0; break;
    case PIN_SEL_UP: return g_diffSel > 0; break;
  }
  return false;
}

