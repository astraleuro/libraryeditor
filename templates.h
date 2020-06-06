#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QString>

#define UNUSED(T) (void)(T)

template<typename T>
const QString getClassName(T) {
    return typeid(T).name();
}

template<typename T>
const T min(T one, T two) {
    if (one < two)
        return one;
    else
        return two;
}

#endif // TEMPLATES_H
