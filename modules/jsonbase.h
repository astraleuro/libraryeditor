#ifndef JSONBASE_H
#define JSONBASE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QVector>

#include "cachebase.h"

enum JsonBaseItemType {
    Undefined = 0,
    Object = 1,
    Array = 2,
    Value = 3
};

struct JsonBaseItem
{
    QJsonValue value;
    QVector<QString> childKeys;
    QVector<JsonBaseItem> childItems;
    JsonBaseItemType type = Undefined;
    int parentIndex = -1;
    int currentIndex = -1;
};

class JsonBase
{
public:
    JsonBase() {};
    void fromJson(QJsonObject json);
    QJsonObject toJson();
    int append(QJsonValue json, QStringList path);
    int append(QJsonValue json, int index);
    void remove(QStringList path);
    void remove(int index);
    QJsonValue takeAt(int index);
protected:
    void append(JsonBaseItem &root, QJsonObject json, int parentIndex);
    void append(JsonBaseItem &root, QJsonArray json, int parentIndex);
    void append(JsonBaseItem &root, QJsonValue json, int parentIndex);
    void increase(JsonBaseItem &root);
    int indexOf(JsonBaseItem &root, QString key);
    JsonBaseItem *find(JsonBaseItem &root, QStringList path);
    JsonBaseItem *takeAt(JsonBaseItem &root, int key);
    QJsonValue toJson(JsonBaseItem &root);
protected:
    JsonBaseItem baseRoot;
    CacheBase<JsonBaseItem> baseCache;
};

#endif // JSONBASE_H
