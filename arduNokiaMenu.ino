#include <avr/sleep.h>
#include <avr/power.h>
#include <MemoryFree.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "MainMenu.h"
#include "CategoryMenu.h"
#include "SystemState.h"
#include "LcdUtil.h"
#include "MenuStack.h"
#include "TreeItem.h"

#define TI_TOP_ITEM 0, -1

#define TI_1_TOP 0, 7
#define TI_1_ITEM 1, 7

#define treeArrItem(x) const char catName##x[] PROGMEM = "Test" #x; \
  CategoryMenu const PROGMEM pmCat##x(catName##x); \
  const MenuTreeItem PROGMEM gTreeArrayItem##x((const AbstractMenu*)&pmCat##x

MainMenu const pmMain PROGMEM; // &pmCatA);
const MenuTreeItem PROGMEM gTreeArrayItem0((const AbstractMenu*)&pmMain, 0, -1, 1, TI_ROOT); // id0, no parent, child is 1, no prev, no next

treeArrItem(1), 1, TI_1_TOP, TI_BEGIN);
treeArrItem(2), 2, TI_TOP_ITEM, TI_MID);
treeArrItem(3), 3, TI_TOP_ITEM, TI_MID);
treeArrItem(4), 4, TI_TOP_ITEM, TI_MID);
treeArrItem(5), 5, TI_TOP_ITEM, TI_MID);
treeArrItem(6), 6, TI_TOP_ITEM, TI_END);

treeArrItem(1_1), 7, TI_1_ITEM, TI_BEGIN);
treeArrItem(1_2), 8, TI_1_ITEM, TI_MID);
treeArrItem(1_3), 9, TI_1_ITEM, TI_MID);
treeArrItem(1_4), 10, TI_1_ITEM, TI_MID);
treeArrItem(1_5), 11, TI_1_ITEM, TI_MID);
treeArrItem(1_6), 12, TI_1_ITEM, TI_END);

const MenuTreeItem* const gTreeArray[] PROGMEM = {
  &gTreeArrayItem0,
  &gTreeArrayItem1,
  &gTreeArrayItem2,
  &gTreeArrayItem3,
  &gTreeArrayItem4,
  &gTreeArrayItem5,
  &gTreeArrayItem6,
  &gTreeArrayItem1_1,
  &gTreeArrayItem1_2,
  &gTreeArrayItem1_3,
  &gTreeArrayItem1_4,
  &gTreeArrayItem1_5,
  &gTreeArrayItem1_6,
};

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 8 - Data/Command select (D/C)
// LCD chip select (CS) - to ground (single display)
// pin 17 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_DISPLAY_DC, 0, PIN_DISPLAY_RESET);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

static const int cBtnHoldFlag = (1 << PIN_BTN_HOLD);

volatile int f_wdt = 1;

ISR(WDT_vect)
{
  float result = analogRead(0);

  for(int i=0; i<10;++i)
  {
    delay(10);
    result = (result + analogRead(0)) / 2;
  }

  static const float adc3v3 = 510.7;
  static const float adc5v = 781.875;

  static const float ka = (5.08 - 3.32) / ( adc5v - adc3v3);
  static const float kb = 5.08 - ka * adc5v;

  float voltage = ka * result + kb;

  display.clearDisplay();
  
  printProgmem(PSTR("ADC result:"));
  display.println();
  display.println(result);

  printProgmem(PSTR("Voltage:"));
  display.println();
  display.println(voltage);

  display.display();

  for (int i = 0; i < 100; ++i)
    delay(1000);

  g_Sys.widgetsDirty();

  if (f_wdt == 0)
  {
    f_wdt = 1;
  }
  else
  {
    asm volatile ("  jmp 0");
  }
}

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  power_all_enable();
}

ISR (PCINT2_vect)
{
  static int g_btnPush = 0;
  static int g_encoderCheck = 0;
  static int g_curPORTD = 0;
  static int g_vol = 0;
  static int g_Sel = 0;

  g_curPORTD = PIND;
  g_btnPush = g_Sys.event.oldPORTD ^ g_curPORTD;

  // Checking hold on press
  if (cBtnHoldFlag & ~g_curPORTD)
  {
    if ((g_btnPush & cBtnHoldFlag))
    {
      g_Sys.event.btnEvent = cBtnHoldFlag;
    }
    return;
  }

  // Event set only on button release
  g_Sys.event.btnEvent |= (g_btnPush & ~g_curPORTD);
  g_Sys.event.btnEvent &= EVENT_BTN_MASK;


  // Checking encoder rotation
  if (g_btnPush & EVENT_VOL_MASK)
  {
    bool ta = !(g_btnPush & 0x1);
    bool a = g_curPORTD & 0x1;
    bool b = g_curPORTD & 0x2;

    if (ta ^ (a == b))
    {
      g_Sys.event.diffVol--;
    }
    else
    {
      g_Sys.event.diffVol++;
    }
  }

  if (g_btnPush & EVENT_SEL_MASK)
  {
    bool ta = !(g_btnPush & 0x4);
    bool a = g_curPORTD & 0x4;
    bool b = g_curPORTD & 0x8;

    if (ta ^ (a == b))
      g_Sys.event.diffSel--;
    else
      g_Sys.event.diffSel++;
  }

  if (g_Sys.event.diffVol < 0)
    g_Sys.event.btnEvent |= 1 << PIN_VOL_DOWN;
  else if (g_Sys.event.diffVol)
    g_Sys.event.btnEvent |= 1 << PIN_VOL_UP;

  if (g_Sys.event.diffSel < 0)
    g_Sys.event.btnEvent |= 1 << PIN_SEL_DOWN;
  else if (g_Sys.event.diffSel)
    g_Sys.event.btnEvent |= 1 << PIN_SEL_UP;

  g_Sys.event.oldPORTD = g_curPORTD;
}  // end of PCINT2_vect

void setup() {
  analogWrite(PIN_DISPLAY_BACKLIGHT, 0);

  // Initializing all ports 0 - 7
  // (serial is not used)
  for (int i = 0; i <= PIN_DISPLAY_DC; ++i)
    pinMode(i, INPUT_PULLUP);
  g_Sys.event.oldPORTD = PORTD;

  // Display init
  display.begin();

  pinMode(PIN_LED_OUT, OUTPUT);
  digitalWrite(PIN_LED_OUT, HIGH);

  //  display.setRotation(2);
  display.setContrast(60);

  display.clearDisplay();
  display.setCursor(0, 0);

  /*
    printProgmem(PSTR("RAW:"));
    display.println((int)&gTreeArray, HEX);
    printRaw((char*)&gTreeArray, 2 * sizeof(const MenuTreeItem*), 0);
    display.display();
  */

  // pin change interrupt
  PCMSK2 |= 0xFF; // All pins from 0 to 7 (from PCINT16 to PCINT23)
  PCIFR  |= bit (PCIF2);    // clear any outstanding interrupts
  PCICR  |= bit (PCIE2);    // enable pin change interrupts for D0 to D7

  /*** Setup the WDT ***/

  /* Clear the reset flag. */
  MCUSR &= ~(1 << WDRF);

  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1 << WDP0 | 1 << WDP3; /* 8.0 seconds */

  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);

  // g_Sys.event.dirtyWidgets = ~0;
  // g_Sys.event.btnEvent = 0;

  g_menuStack.init((const char*) &gTreeArray);
  digitalWrite(PIN_LED_OUT, LOW);
}

void loop() {
  // blinkDebug(1);

  if (g_Sys.hasWidgets())
  {
    g_menuStack.paint();

    // printDebugMem();
    display.display();

    g_Sys.widgetsClear();
  }

  if (g_Sys.hasButtons())
  {
    g_menuStack.processEvents();

    // debounce
    if (g_Sys.event.btnEvent > 0x3)
      delay(100);

    g_Sys.buttonsClear();
  }

  if ((!g_Sys.hasButtons()) && (!g_Sys.hasWidgets()))
  {
    /* Don't forget to clear the flag. */
    f_wdt = 0;

    digitalWrite(PIN_LED_OUT, HIGH);

    /* Re-enter sleep mode. */
    enterSleep();

    digitalWrite(PIN_LED_OUT, LOW);
  }
}

