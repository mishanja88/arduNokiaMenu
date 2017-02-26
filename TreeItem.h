#ifndef TREEITEM_H
#define TREEITEM_H

#include "Arduino.h"

enum TreeItemType
{
  TI_ROOT = 0x0,
  TI_BEGIN = 0x1,
  TI_END = 0x2,
  TI_MID = 0x3,
};

template <typename T>
class TreeItem
{
  public:
    const PROGMEM T* data;

    constexpr TreeItem(const T* _data, unsigned int _id,
                       unsigned int _iParent,
                       unsigned int _iChild,
                       TreeItemType _iType
                      )
      : data(_data),
        iParent(_iParent),
        iChild(_iChild),
        iType(_iType),
        id(_id)
    {
    }

    inline const TreeItem<T>* parent(const char* arr) const {
      return ((iParent != ~0) ? (const TreeItem<T>*)pgm_read_word(arr + iParent * sizeof(const TreeItem<T>*)) : nullptr);
    }
    inline const TreeItem<T>* child(const char* arr) const {
      return ((iChild != ~0) ? (const TreeItem<T>*)pgm_read_word(arr + iChild * sizeof(const TreeItem<T>*)) : nullptr);
    }
    inline const TreeItem<T>* prev(const char* arr) const {
      return ((iType & TI_END) ? (const TreeItem<T>*)pgm_read_word( arr + (id - 1) * sizeof(const TreeItem<T>*)) : nullptr);
    }
    inline const TreeItem<T>* next(const char* arr) const {
      return ((iType & TI_BEGIN) ? (const TreeItem<T>*)pgm_read_word( arr + (id + 1) * sizeof(const TreeItem<T>*)) : nullptr);
    }

  protected:
    const PROGMEM unsigned int iParent;
    const PROGMEM unsigned int iChild;
    const PROGMEM unsigned int id;
    const PROGMEM unsigned char iType;
 
} __attribute__((packed));

#endif // TREEITEM_H

