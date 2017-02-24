#ifndef TYPEID_H
#define TYPEID_H

#include "Arduino.h"
#include "ForeachMacro.h"

// Each typeid capable class should declare first constructor by this macro
#define TYPEID_CLASS(x) static const TypeId cId = id##x; constexpr x

// Each typeid capable class should call parent constructor by this macro
#define TYPEID_PARENT(x) x(cId,

// Enumerator item
#define TYPEID_ITEM(X) id##X,
// Helper function
#define TYPEID_ENUM(FIRST, ...) id##FIRST = 1, FOR_EACH(TYPEID_ITEM,__VA_ARGS__)

// Enum with all typeid-capable classes
enum TypeId
{
  TYPEID_ENUM(CategoryMenu, MainMenu)
};

class TypeIdClass
{
  public:
    const PROGMEM TypeId typeId;

  protected:
    constexpr TypeIdClass(const TypeId _typeId)
      : typeId(_typeId)
    {
    }
};

template <typename T> T* copyToRam (const T * sce)
{
  void *dest = malloc(sizeof(T));
  memcpy_P (dest, sce, sizeof (T));
  return (T*)dest;
}

#endif // TYPEID_H
