#ifndef CACHEBASE_H
#define TEMPLATES_H

#include <QVector>

template<class T>
struct CacheItem {
    int index = -1;
    T* item;
};

template<class T>
class CacheBase {
public:
    int append(T* item)
    {
        items.resize(lastIndex + 1);
        items[lastIndex].item = item;
        items[lastIndex].index = lastIndex;
        return lastIndex++;
    };
    int indexOf(T* item)
    {
        for (int i = 0; i < items.count(); i++)
            if (items[i].item == item)
                return items[i].index;
        return -1;
    };
    T* operator[](int index)
    {
        if (index >= 0 && index <= lastIndex)
            return items[index].item;
        else
            return NULL;
    };
    void clear() {
        lastIndex = 0;
        items.clear();
    };
protected:
    int lastIndex = 0;
    QVector<CacheItem<T>> items;
};


#endif // CACHEBASE_H
