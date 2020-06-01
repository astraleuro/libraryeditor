#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QVector>

#define LIST_SEPARATOR '|'
#define UNIQUEBY_FLAG "{uniqueby}"
#define NEWESTBY_FLAG "{newestby}"
#define LABEL_FLAG "{label}"
#define EDIT_FLAG "{edit}"
#define DATE_FLAG "{date}"
#define FILE_FLAG "{file}"
#define ORDER_FLAG "{order}"
#define BOOL_FLAG "{bool}"
#define BOOL_POS 2
#define LABEL_POS 1
#define FILE_POS 2
#define TYPE_POS 0

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
        if (index >= 0 && index < lastIndex)
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

template<typename T>
int compare(T left, T right) {
    if (left < right)
        return 1;
    else if (left > right)
        return -1;
    else
        return 0;
};

template<typename T>
T min(T left, T right) {
    if (left < right)
        return left;
    else
        return right;
};

template<typename T>
T max(T left, T right, T limit) {
    if (left < right)
        return min(right, limit);
    else
        return min(left, limit);
};

#endif // TEMPLATES_H
