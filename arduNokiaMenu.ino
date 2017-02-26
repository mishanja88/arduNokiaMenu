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

/*
#define testMenu(x, y) const char catName2##x[] PROGMEM = "Test2" #x; \
  PROGMEM CategoryMenu const pmCat2##x (catName2##x, nullptr, &pmCat##y); \
  \
  const char catName##x[] PROGMEM = "Test" #x; \
  PROGMEM CategoryMenu const pmCat##x(catName##x, nullptr, &pmCat2##x);

//------------------------------------------------------------------------

const char catNameZ2[] PROGMEM = "TestZ2";
PROGMEM CategoryMenu const pmCatZ2(catNameZ2, nullptr, nullptr);

const char catNameZ[] PROGMEM = "TestZ";
PROGMEM CategoryMenu const pmCatZ(catNameZ, nullptr, &pmCatZ2);

testMenu(Y, Z)
testMenu(X, Y)
testMenu(W, X)
testMenu(V, W)
testMenu(U, V)
testMenu(T, U)
testMenu(S, T)
testMenu(R, S)
testMenu(Q, R)
testMenu(P, Q)
testMenu(O, P)
testMenu(N, O)
testMenu(M, N)
testMenu(L, M)
testMenu(K, L)
testMenu(J, K)
testMenu(I, J)
testMenu(H, I)
testMenu(G, H)
testMenu(F, G)
testMenu(E, F)
testMenu(D, E)
testMenu(C, D)
testMenu(B, C)
testMenu(A, B)
*/

PROGMEM MainMenu const pmMain(nullptr); // &pmCatA);

#define TI_TOP -1, -1

#define TI_BEGIN false, true
#define TI_O true, true
#define TI_END true, false

const TreeItem<int> PROGMEM gTreeArrayItem0((int*) 0xAB00, 0, TI_TOP, TI_BEGIN);
const TreeItem<int> PROGMEM gTreeArrayItem1((int*) 0xAB01, 1, TI_TOP, TI_O);
const TreeItem<int> PROGMEM gTreeArrayItem2((int*) 0xAB02, 2, TI_TOP, TI_O);
const TreeItem<int> PROGMEM gTreeArrayItem3((int*) 0xAB03, 3, TI_TOP, TI_O);
const TreeItem<int> PROGMEM gTreeArrayItem4((int*) 0xAB04, 4, TI_TOP, TI_O);
const TreeItem<int> PROGMEM gTreeArrayItem5((int*) 0xAB05, 5, TI_TOP, TI_O);
const TreeItem<int> PROGMEM gTreeArrayItem6((int*) 0xAB06, 6, TI_TOP, TI_END);

const TreeItem<int>* const gTreeArray[] PROGMEM = {
    &gTreeArrayItem0,
    &gTreeArrayItem1,
    &gTreeArrayItem2,
    &gTreeArrayItem3,
    &gTreeArrayItem4,
    &gTreeArrayItem5,
    &gTreeArrayItem6,
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

ISR (PCINT2_vect)
{
  static int g_btnPush = 0;
  static int g_encoderCheck = 0;
  static int g_curPORTD = 0;
  static int g_vol = 0;
  static int g_Sel = 0;

  g_curPORTD = PIND;
  g_btnPush = g_oldPORTD ^ g_curPORTD;

  // Checking hold on press
  if (cBtnHoldFlag & ~g_curPORTD)
  {
    if ((g_btnPush & cBtnHoldFlag))
    {
      g_btnEvent = cBtnHoldFlag;
    }
    return;
  }

  // Event set only on button release
  g_btnEvent |= (g_btnPush & ~g_curPORTD);
  g_btnEvent &= EVENT_BTN_MASK;


  // Checking encoder rotation
  if (g_btnPush & EVENT_VOL_MASK)
  {
    bool ta = !(g_btnPush & 0x1);
    bool a = g_curPORTD & 0x1;
    bool b = g_curPORTD & 0x2;

    if (ta ^ (a == b))
    {
      g_diffVol--;
    }
    else
    {
      g_diffVol++;
    }
  }

  if (g_btnPush & EVENT_SEL_MASK)
  {
    bool ta = !(g_btnPush & 0x4);
    bool a = g_curPORTD & 0x4;
    bool b = g_curPORTD & 0x8;

    if (ta ^ (a == b))
      g_diffSel--;
    else
      g_diffSel++;
  }

  if (g_diffVol < 0)
    g_btnEvent |= 1 << PIN_VOL_DOWN;
  else if (g_diffVol)
    g_btnEvent |= 1 << PIN_VOL_UP;

  if (g_diffSel < 0)
    g_btnEvent |= 1 << PIN_SEL_DOWN;
  else if (g_diffSel)
    g_btnEvent |= 1 << PIN_SEL_UP;

  g_oldPORTD = g_curPORTD;
}  // end of PCINT2_vect


void setup() {
  analogWrite(PIN_DISPLAY_BACKLIGHT, 0);

  pinMode(PIN_LED_OUT, OUTPUT);
  digitalWrite(PIN_LED_OUT, HIGH);

  // Initializing all ports 0 - 7
  // (serial is not used)
  for (int i = 0; i <= PIN_DISPLAY_DC; ++i)
    pinMode(i, INPUT_PULLUP);
  g_oldPORTD = PORTD;

  // Display init
  display.begin();
  display.setRotation(2);
  display.setContrast(60);

  display.clearDisplay();
  display.setCursor(0, 0);
  
  printProgmem(PSTR("RAW:"));
  display.println((int)&gTreeArray, HEX);
  printRaw((char*)&gTreeArray, sizeof(const TreeItem<int>), 0);
  display.display();

  delay(2000);

  const TreeItem<int>* it = (const TreeItem<int>*) pgm_read_word(gTreeArray);

  display.clearDisplay();

  for (int i = 0; i < 100; ++i)
  {
//    printProgmem(PSTR("it:"));
  //  display.print((int)it, HEX);
    //display.display();
    //delay(1000);

    const TreeItem<int>* unpackedIt = copyToRam< const TreeItem<int> >(it);

    printProgmem(PSTR(","));
    display.print((int)unpackedIt->data, HEX);
    display.display();
    delay(1500);

    if (unpackedIt->next((const TreeItem<int>**)&gTreeArray))
    {
      it = unpackedIt->next((const TreeItem<int>**)&gTreeArray);
      printProgmem(PSTR(">"));
      //display.print((int)&it, HEX);
      //display.display();
      //delay(1000);
    }
    else
    {
      printProgmem(PSTR("NO_NEXT:"));
      display.print((int)&it, HEX);
      display.display();
      delay(1000);

      delete unpackedIt;
      break;
    }

    delete unpackedIt;
  }

  delay(3000);

  display.clearDisplay();

  for (int i = 0; i < 100; ++i)
  {
//    printProgmem(PSTR("it:"));
  //  display.print((int)it, HEX);
    //display.display();
    //delay(1000);

    const TreeItem<int>* unpackedIt = copyToRam< const TreeItem<int> >(it);

    printProgmem(PSTR(","));
    display.print((int)unpackedIt->data, HEX);
    display.display();
    delay(1500);

    if (unpackedIt->prev((const TreeItem<int>**)&gTreeArray))
    {
      it = unpackedIt->prev((const TreeItem<int>**)&gTreeArray);
      printProgmem(PSTR(">"));
      //display.print((int)&it, HEX);
      //display.display();
      //delay(1000);
    }
    else
    {
      printProgmem(PSTR("NO_PREV:"));
      display.print((int)&it, HEX);
      display.display();
      delay(1000);

      delete unpackedIt;
      break;
    }

    delete unpackedIt;
  }
    delay(3000);
  // pin change interrupt
  PCMSK2 |= 0xFF; // All pins from 0 to 7 (from PCINT16 to PCINT23)
  PCIFR  |= bit (PCIF2);    // clear any outstanding interrupts
  PCICR  |= bit (PCIE2);    // enable pin change interrupts for D0 to D7

  g_dirtyWidgets = ~0;
  g_btnEvent = 0;

  g_menuStack.init(&pmMain);
  digitalWrite(PIN_LED_OUT, LOW);
}

void loop() {
  blinkDebug(1);

  if (g_dirtyWidgets)
  {
    g_menuStack.paint();

    printDebugMem();

    g_dirtyWidgets = 0;
  }

  if (g_btnEvent)
  {
    if (g_menuStack.processEvents())
      g_dirtyWidgets = ~0;

    // debounce
    if (g_btnEvent > 0x3)
      delay(100);

    g_btnEvent = 0;

    g_diffSel = 0;
    g_diffVol = 0;
  }
}

