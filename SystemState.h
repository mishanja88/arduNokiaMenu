#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "HardwareSettings.h"

// Button event mask
#define EVENT_BTN_MASK 0xF0

// Encoder event mask
#define EVENT_VOL_MASK 0x03
#define EVENT_SEL_MASK 0x0C

bool hasPinEvent(PinMappings pin);
void blinkDebug(int n);

struct EqState
{
  int headVolume;
  int lineVolume;
  int micVolume;
  int curPreset[EQ_COUNT];
};

struct DisplayState
{
  int brightness;
  int contrast;
  int timeout;
};

struct EventState
{
    //TODO: remove---------------
    // volatile int g_selPos;
    // volatile int g_volPos;
    //---------------------------

    // Each bit corresponds to screen widget
    unsigned char dirtyWidgets;

    int diffSel;
    int diffVol;

    unsigned char btnEvent;
    unsigned char oldPORTD;
};

class SystemState
{
public:
    SystemState();
  
    EqState eq;
    DisplayState disp;
    EventState event;
};

extern volatile SystemState g_Sys;

#endif // SYSTEM_STATE_H
