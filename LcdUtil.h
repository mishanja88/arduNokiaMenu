#ifndef LCD_UTIL_H
#define LCD_UTIL_H

void printProgmem(const char *data);

void printRaw(const char* mem, int len, const char* title);

void printDebugMem(const char *label = 0);

#endif
