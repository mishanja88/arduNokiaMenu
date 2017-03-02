#ifndef HARDWARESETTINGS_H
#define HARDWARESETTINGS_H

#define EQ_COUNT 5

enum PinMappings
{
//-------- Encoders ---------
  PIN_VOL_DOWN = 0,
  PIN_VOL_UP = 1,

  PIN_SEL_DOWN = 2,
  PIN_SEL_UP = 3,
//---------------------------

  PIN_BTN_CANCEL = 4,
  PIN_BTN_OK = 5,
  
  PIN_BTN_HOLD = 6,

  PIN_RESERVED1 = 7,

  PIN_DISPLAY_DC = 8,
  PIN_DISPLAY_BACKLIGHT = 9,

  PIN_LED_OUT = 10, // A2
  PIN_DISPLAY_RESET = 17 // A3
};

#endif // HARDWARESETTINGS_H

