#ifndef TYPEID_H
#define TYPEID_H

#define TYPEID_CLASS(x) static const TypeId cId = id##x; x

#define TEMP_BEGIN
#define TYPEID_PARENT(x) x(cId,
#undef TEMP_BEGIN

enum TypeId
{
  idCategoryMenu = 1,
  idMainMenu
};

#endif // TYPEID_H
