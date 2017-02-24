#include "TypeId.h"

void* metaToRam (const char *sce)
{
  TypeIdClass *typeId = copyToRam<TypeIdClass>((const TypeIdClass*)sce);
    
  void *dest = malloc(typeId->typeSize);
  memcpy_P (dest, sce, typeId->typeSize);

  delete typeId;
  
  return dest;
}


