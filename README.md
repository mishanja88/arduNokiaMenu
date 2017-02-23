# arduNokiaMenu
Research on dynamic tree-like menu structure with low RAM footprint 

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
