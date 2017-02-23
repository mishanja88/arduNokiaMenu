#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

// Button event mask
#define EVENT_BTN_MASK 0xF0

// Encoder event mask
#define EVENT_SEL_MASK 0x03
#define EVENT_VOL_MASK 0x0C

enum PinMappings
{
//-------- Encoders ---------
  PIN_SEL_DOWN = 0,
  PIN_SEL_UP = 1,

  PIN_VOL_DOWN = 2,
  PIN_VOL_UP = 3,
//---------------------------

  PIN_BTN_OK = 4,
  PIN_BTN_CANCEL = 4,

  PIN_BTN_HOLD = 6,

  PIN_RESERVED1 = 7,

  PIN_DISPLAY_DC = 8,
  PIN_DISPLAY_BACKLIGHT = 9,

  PIN_LED_OUT = 16, // A2
  PIN_DISPLAY_RESET = 17 // A3
};

extern int volPos;
extern int selPos;

extern volatile int g_diffVol;
extern volatile int g_diffSel;

extern volatile int g_btnEvent;
extern volatile int g_oldPORTD;

#endif
