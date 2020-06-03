#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QString>

#define UNUSED(T) (void)(T)

template<typename T>
const QString getClassName(T) {
    return typeid(T).name();
}

#endif // TEMPLATES_H
