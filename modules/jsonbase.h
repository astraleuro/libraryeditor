#ifndef JSONBASE_H
#define JSONBASE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QVector>

#include "templates.h"

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
    QVector<JsonBaseItem*> childItems;
    JsonBaseItemType type = Undefined;
    int parentIndex = -1;
    int currentIndex = -1;
};

class JsonBase
{
public:
    JsonBase() {};
    JsonBase(QJsonObject json) {fromJson(json);};
    ~JsonBase() {clear(baseRoot);};
    void fromJson(QJsonObject json);
    QJsonObject toJson();
    int append(QJsonValue json, QStringList path);
    int append(QJsonValue json, QString key, int index);
    int indexOf(QStringList path);
    QJsonValue takeAt(int index);
    void move(int parentIndex, int index, QString key);
    void remove(QStringList path);
    void remove(int index);
    bool isValid(JsonBase &schema);
protected:
    void append(JsonBaseItem *root, QJsonObject json, int parentIndex);
    void append(JsonBaseItem *root, QJsonArray json, int parentIndex);
    void append(JsonBaseItem *root, QJsonValue json, int parentIndex);
    void increase(JsonBaseItem *root);
    int indexOf(JsonBaseItem *root, QString key);
    int indexOf(JsonBaseItem *root, QStringList path);
    JsonBaseItem *find(JsonBaseItem *root, QStringList path);
    JsonBaseItem *takeAt(JsonBaseItem *root, int key);
    QJsonValue toJson(JsonBaseItem *root);
    bool isValid(JsonBaseItem *root, JsonBaseItem *schema);
    void clear(JsonBaseItem *root);
protected:
    JsonBaseItem *baseRoot = NULL;
    CacheBase<JsonBaseItem> baseCache;
};

#endif // JSONBASE_H
