#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "HardwareSettings.h"

// Button event mask
#define EVENT_BTN_MASK 0xF0

// Encoder event mask
#define EVENT_VOL_MASK 0x03
#define EVENT_SEL_MASK 0x0C

//TODO: remove---------------
extern int selPos;
extern int volPos;
//---------------------------

// Each bit corresponds to screen widget
extern int g_dirtyWidgets;

extern volatile int g_diffSel;
extern volatile int g_diffVol;

extern volatile int g_btnEvent;
extern volatile int g_oldPORTD;

bool hasPinEvent(PinMappings pin);

#endif // SYSTEM_STATE_H
