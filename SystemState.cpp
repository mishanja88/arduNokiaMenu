#include "SystemState.h"
#include "Arduino.h"

SystemState g_Sys;

SystemState::SystemState()
{
  memset((void *)&g_Sys, 0, sizeof(SystemState));
  widgetsDirty();
}

void SystemState::buttonsClear()
{
  event.diffSel = 0;
  event.diffVol = 0;
  event.btnEvent = 0;
}

void SystemState::widgetsClear()
{
  event.dirtyWidgets = 0;
}

void SystemState::widgetsDirty()
{
  event.dirtyWidgets = ~0;
}

bool SystemState::hasButtons() const
{
  return event.btnEvent;
}

bool SystemState::hasWidgets() const
{
  return event.dirtyWidgets;
}

bool SystemState::hasPin(PinMappings pin) const
{
  return event.btnEvent & (1 << pin);
}

void blinkDebug(int n)
{
  for (int i = 0; i < n; ++i)
  {
    for (int bright = 256; bright >= 0; --bright)
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
