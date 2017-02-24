#ifndef TYPEID_H
#define TYPEID_H

#include "Arduino.h"
#include "ForeachMacro.h"

// Each typeid capable class should declare first constructor by this macro
#define TYPEID_CLASS(x) constexpr x

//static const int cTypeSize = sizeof(x); constexpr x

// Each typeid capable class should call parent constructor by this macro
#define TYPEID_PARENT(x, parent) parent(sizeof(x),

/* Enumerator item
#define TYPEID_ITEM(X) id##X,
// Helper function
#define TYPEID_ENUM(FIRST, ...) id##FIRST = 1, FOR_EACH(TYPEID_ITEM,__VA_ARGS__)

// Enum with all typeid-capable classes
enum TypeId
{
  TYPEID_ENUM(CategoryMenu, MainMenu)
};
*/

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

template <typename T> T* copyToRam (const T * sce)
{
  void *dest = malloc(sizeof(T));
  memcpy_P (dest, sce, sizeof (T));
  return (T*)dest;
}

void* metaToRam (const char *sce);

#endif // TYPEID_H
