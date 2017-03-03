#include "SystemState.h"
#include "Arduino.h"

volatile SystemState g_Sys;

SystemState::SystemState()
{
  memset((void *)&g_Sys, 0, sizeof(SystemState));
  g_Sys.event.dirtyWidgets = 0xFF;
}

bool hasPinEvent(PinMappings pin)
{
  return g_Sys.event.btnEvent & (1 << pin);
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
