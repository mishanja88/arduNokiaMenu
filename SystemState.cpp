#include "SystemState.h"
#include "Arduino.h"

volatile int g_selPos = 0;
volatile int g_volPos = 0;

volatile int g_diffSel = 0;
volatile int g_diffVol = 0;

volatile unsigned char g_btnEvent = 0;
volatile unsigned char g_oldPORTD = 0;

volatile unsigned char g_dirtyWidgets = 0xFF;

bool hasPinEvent(PinMappings pin)
{
  return g_btnEvent & (1 << pin);
}

void blinkDebug(int n)
{
  for (int i = 0; i < n; ++i)
  {
    for(int bright = 256; bright >= 0; --bright)
    {
      analogWrite(PIN_LED_OUT, bright);
      delay(1);
    }
    //digitalWrite(PIN_LED_OUT, HIGH);
    //delay(50);
    //digitalWrite(PIN_LED_OUT, LOW);
    //delay(50);
  }
}
