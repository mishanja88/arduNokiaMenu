#ifndef TYPEID_H
#define TYPEID_H

#include "Arduino.h"

// Each typeid capable class should declare constructor by this macro
// #define TYPEID_CONSTRUCTOR(x, parent, ...) constexpr x(__VA_ARGS__) : parent(sizeof(x),

class TypeIdClass
{
  public:
    const PROGMEM int typeSize;
    virtual ~TypeIdClass() {}
    
  protected:
    constexpr TypeIdClass(const int _typeSize)
      : typeSize(_typeSize)
    {
    }
};

// See PROGMEM_getAnything, http://www.gammon.com.au/progmem
template <typename T> T* copyToRam (const T * sce)
{
  void *dest = malloc(sizeof(T));
  memcpy_P (dest, sce, sizeof (T));
  return (T*)dest;
}

void* metaToRam (const char *sce);

#endif // TYPEID_H
