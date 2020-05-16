#include "jsonbase.h"

void JsonBase::fromJson(QJsonObject json)
{
    if (!json.isEmpty()) {
        baseRoot.type = Object;
        append(baseRoot, json, baseCache.append(&baseRoot));
    }
}

QJsonObject JsonBase::toJson()
{
    return toJson(baseRoot).toObject();
}

void JsonBase::remove(QStringList path)
{
    if (!path.isEmpty()) {
        JsonBaseItem *root = find(baseRoot, path);
        if (root != NULL) {
            int index = indexOf(*root, path.last());
            root->childKeys.remove(index);
            root->childItems.remove(index);
            if (root->type == Array)
                for (int i = index; i < root->childKeys.count(); i++)
                    root->childKeys[i] = QString::number(i);
        }
    }
}

void JsonBase::append(QJsonValue json, QStringList path)
{
    if (!json.isUndefined() && !path.isEmpty()) {
        JsonBaseItem *root = find(baseRoot, path);
        if (root != NULL) {
            int index = indexOf(*root, path.last());
            if (index < 0) {
                increase(*root);
                root->childKeys.last() = path.last();
                root = &root->childItems.last();
            } else
                root = &root->childItems[index];
            if (json.isObject())
                append(*root, json.toObject(), root->parentIndex);
            else if (!json.isArray())
                append(*root, json, root->parentIndex);
            else if (root->type != Array)
                append(*root, json.toArray(), root->parentIndex);
        }
    }
}

void JsonBase::append(JsonBaseItem &root, QJsonObject json, int parentIndex)
{
    int currentIndex = baseCache.append(&root);
    root.parentIndex = parentIndex;
    root.type = Object;
    for (QString key : json.keys()) {
        if (!json[key].isUndefined()) {
            increase(root);
            root.childKeys.last() = key;
            if (json[key].isObject())
                append(root.childItems.last(), json[key].toObject(), currentIndex);
            else if (json[key].isArray())
                append(root.childItems.last(), json[key].toArray(), currentIndex);
            else
                append(root.childItems.last(), json[key], currentIndex);
        }
    }
}

void JsonBase::append(JsonBaseItem &root, QJsonArray json, int parentIndex)
{
    int currentIndex = baseCache.append(&root);
    root.parentIndex = parentIndex;
    root.type = Array;
    for (int key = 0; key < json.count(); key++)
        if (!json[key].isUndefined()) {
            increase(root);
            root.childKeys.last() = QString::number(key);
            if (json[key].isObject())
                append(root.childItems.last(), json[key].toObject(), currentIndex);
            else
                append(root.childItems.last(), json[key], currentIndex);
        }
}

void JsonBase::append(JsonBaseItem  &root, QJsonValue json, int parentIndex)
{
    root.parentIndex = parentIndex;
    root.type = Value;
    root.value = json;
}

JsonBaseItem *JsonBase::find(JsonBaseItem &root, QStringList path)
{
    if (!path.isEmpty()) {
        int nextHop;
        nextHop = indexOf(root, path.first());
        if (path.count() > 1) {
            if (nextHop >= 0) {
                path.removeFirst();
                return find(*takeAt(root, nextHop), path);
            } else
                return NULL;
        } else
            return &root;
    }
    return NULL;
}

int JsonBase::indexOf(JsonBaseItem &root, QString key)
{
    if (root.type == Object || root.type == Array) {
        int index = -1;
        for (int key_i = 0; key_i < root.childKeys.count(); key_i++)
            if (root.childKeys[key_i] == key) {
                index = key_i;
                break;
            }
        return index;
    } else
        return -1;
}

JsonBaseItem *JsonBase::takeAt(JsonBaseItem &root, int key)
{
    if (root.childItems.count() > key)
        return &root.childItems[key];
    else
        return NULL;
}

void JsonBase::increase(JsonBaseItem &root)
{
    root.childKeys.resize(root.childKeys.size() + 1);
    root.childItems.resize(root.childItems.size() + 1);
}

QJsonValue JsonBase::toJson(JsonBaseItem &root)
{
    QJsonObject object;
    QJsonArray array;

    switch (root.type) {
    case Object:
        for (int key = 0; key < root.childKeys.count(); key++)
            object[root.childKeys[key]] = toJson(root.childItems[key]);
        return object;
        break;
    case Array:
        for (int key = 0; key < root.childItems.count(); key++) {
            if (root.childItems[key].type == Object)
                array.append(toJson(root.childItems[key]));
            else
                array.append(root.childItems[key].value);
        }
        return array;
        break;
    case Value:
        return root.value;
        break;
    case Undefined:
        break;
    }
    return QJsonValue();
}
