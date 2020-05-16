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
    Undefined,
    Object,
    Array,
    Value
};

struct JsonBaseItem
{
    QJsonValue value;
    QVector<QString> childKeys;
    QVector<JsonBaseItem> childItems;
    JsonBaseItemType type = Undefined;
    int parentIndex = -1;
};

class JsonBase
{
public:
    JsonBase() {};
    void fromJson(QJsonObject json);
    QJsonObject toJson();
    void append(QJsonValue json, QStringList path);
    void remove(QStringList path);
protected:
    void append(JsonBaseItem &root, QJsonObject json, int parentIndex);
    void append(JsonBaseItem &root, QJsonArray json, int parentIndex);
    void append(JsonBaseItem &root, QJsonValue json, int parentIndex);
    JsonBaseItem *find(JsonBaseItem &root, QStringList path);
    int indexOf(JsonBaseItem &root, QString key);
    JsonBaseItem *takeAt(JsonBaseItem &root, int key);
    void increase(JsonBaseItem &root);
    QJsonValue toJson(JsonBaseItem &root);
protected:
    JsonBaseItem baseRoot;
    CacheBase<JsonBaseItem> baseCache;
};

#endif // JSONBASE_H
