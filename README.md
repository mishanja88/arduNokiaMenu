# arduNokiaMenu
Research on dynamic tree-like menu structure with low RAM footprint 

Uses:
- Adafruit graphics library ( https://github.com/adafruit/Adafruit-GFX-Library )
- Adafruit-PCD8544-Nokia-5110-LCD-library ( https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library )
- Revised MemoryFree Library ( https://github.com/McNeight/MemoryFree )

Project also contains encoder and button handling by interrupts.

Setup for project:
- Arduino uno (Atmega 328)
- Nokia 5110 screen board through 5V to 3.3V level convertor
- 2 encoders with embedded pushbuttons
- up to 2 extra pushbuttons/switches

Menu should consist of different screens, with tree-like pointer connections.

Also menu should provide event handling logic.

Main idea is to make classes that store as much as possible in PROGMEM.

It's only beginning of research (and maybe I'm inventing a bicycle).

----------------

As of 2017.02.24:

All menu objects are stored in PROGMEM. Dynamic memory is used only for operating on them. Thus, the main goal is accomplished. 

Also dynamic memory is required for parent pointers' stack, when moving deeper into each menu level. Still, it is `O(log(n))` instead of `O(n)`.

Key features:
- Dynamic PROGMEM read: first data byte of each class contains `sizeof`.
- Extensive use of `constexpr` constructors.
- Stack for backward movements.
