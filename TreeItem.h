#ifndef TREEITEM_H
#define TREEITEM_H

#include "Arduino.h"

template <typename T>
class TreeItem
{
  public:
    const PROGMEM T* data;

    constexpr TreeItem(const T* _data, int _id,
                       int _iParent,
                       int _iChild,
                       bool _hasPrev,
                       bool _hasNext
                      )
      : data(_data),
        id(_id),
        iParent(_iParent),
        iChild(_iChild),
        hasPrev(_hasPrev),
        hasNext(_hasNext)
    {
    }
    inline const TreeItem<T>* parent(const TreeItem<T>** arr) const {
      return ((iParent >= 0) ? (const TreeItem<T>*)pgm_read_word(arr + iParent) : nullptr);
    }
    inline const TreeItem<T>* child(const TreeItem<T>** arr) const {
      return ((iChild >= 0) ? (const TreeItem<T>*)pgm_read_word(arr + iChild) : nullptr);
    }
    inline const TreeItem<T>* prev(const TreeItem<T>** arr) const {
      return (hasPrev ? (const TreeItem<T>*)pgm_read_word( arr + (id - 1)) : nullptr);
    }
    inline const TreeItem<T>* next(const TreeItem<T>** arr) const {
      return (hasNext ? (const TreeItem<T>*)pgm_read_word( arr + (id + 1)) : nullptr);
    }

  protected:
    const PROGMEM int id;
    const PROGMEM int iParent;
    const PROGMEM int iChild;
    const PROGMEM bool hasPrev;
    const PROGMEM bool hasNext;
};

#endif // TREEITEM_H

