#ifndef JSONBASE_H
#define JSONBASE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QRegExp>
#include <QDate>

#include "../templates.h"

#define LIST_SEPARATOR '|'
#define UNIQUEBY_FLAG "{uniqueby}"
#define NEWESTBY_FLAG "{newestby}"
#define LABEL_FLAG "{label}"
#define EDIT_FLAG "{edit}"
#define DATE_FLAG "{date}"
#define FILE_FLAG "{file}"
#define ORDER_FLAG "{order}"
#define BOOL_FLAG "{bool}"
#define LABEL_POS 1

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
    JsonBase();
    JsonBase(QJsonObject json) {fromJson(json);};
    ~JsonBase() {clear(baseRoot);};
    void fromJson(QJsonObject json);
    QJsonObject toJson();
    int append(QJsonValue json, QStringList path);
    int append(QJsonValue json, QString key, int index);
    int indexOf(QStringList path);
    int indexOf(int index, QString key);
    QJsonValue takeAt(int index);
    void move(int parentIndex, int index, QString key);
    void remove(QStringList path);
    void remove(int index);
    bool isValid(JsonBase &schema);
    bool merge(JsonBase &base, JsonBase &schema);
    JsonBaseItemType typeOf(int index);
    QStringList keysOf(int index);
    QVector<int> indexesOf(int index);
    int keysCount(int index);
    QString keyAt(int index, int key);
    QString keyAt(int index, QString key);
    int parentIndex(int index);
    bool isChildExist(int index, JsonBaseItemType type);
    QJsonObject toJson(int index);
    QJsonValue value(int index);
protected:
    int countOf(JsonBaseItem *root, QRegExp *regExp);
    void append(JsonBaseItem *root, QJsonObject json, int parentIndex);
    void append(JsonBaseItem *root, QJsonArray json, int parentIndex);
    void append(JsonBaseItem *root, QJsonValue json, int parentIndex);
    void increase(JsonBaseItem *root, bool alloc = true);
    void mergeObject(JsonBaseItem *toRoot, JsonBaseItem *fromRoot, JsonBaseItem *schema);
    void mergeArray(JsonBaseItem *toRoot, JsonBaseItem *fromRoot, JsonBaseItem *schema, QStringList *spec = NULL);
    int max(QString left, QString right);
    JsonBaseItem *copy(JsonBaseItem *root, int parentIndex);
    int indexOf(JsonBaseItem *root, QString key);
    int indexOf(JsonBaseItem *root, QStringList path);
    JsonBaseItem *find(JsonBaseItem *root, QStringList path);
    JsonBaseItem *takeAt(JsonBaseItem *root, int key);
    QString takeKey(JsonBaseItem *root, QString key);
    QJsonValue toJson(JsonBaseItem *root);
    bool isValid(JsonBaseItem *root, JsonBaseItem *schema);
    void clear(JsonBaseItem *root);
    QString keyOf(JsonBaseItem *root, int index);
protected:
    JsonBaseItem *baseRoot = NULL;
    CacheBase<JsonBaseItem> baseCache;
    QRegExp flagsRegExp = QRegExp("[{][a-zA-Z0-9]*[}]$");
};

#endif // JSONBASE_H
