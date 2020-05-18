#include "jsonbase.h"

void JsonBase::fromJson(QJsonObject json)
{
    if (!json.isEmpty()) {
        clear(baseRoot);
        baseRoot = new JsonBaseItem;
        append(baseRoot, json, baseCache.append(baseRoot));
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
            int index = indexOf(root, path.last());
            clear(root->childItems[index]);
            root->childKeys.remove(index);
            root->childItems.remove(index);
            if (root->type == Array)
                for (int i = index; i < root->childKeys.count(); i++)
                    root->childKeys[i] = QString::number(i);
        }
    }
}

void JsonBase::remove(int index)
{
    JsonBaseItem *item = baseCache[index];
    if (item != NULL) {
        JsonBaseItem *root = baseCache[item->parentIndex];
        if (root->type == Object || root->type == Array)
            for (int key = 0; key < root->childItems.count(); key++)
                if (root->childItems[key]->currentIndex == index) {
                    clear(root->childItems[index]);
                    root->childKeys.remove(index);
                    root->childItems.remove(index);
                    if (root->type == Array)
                        for (int i = index; i < root->childKeys.count(); i++)
                            root->childKeys[i] = QString::number(i);
                    break;
                }
    }
}

QJsonValue JsonBase::takeAt(int index)
{
    JsonBaseItem *root = baseCache[index];
    if (root != NULL) {
        QJsonObject object;
        QJsonArray array;
        switch (root->type) {
        case Object:
            for (int key = 0; key < root->childKeys.count(); key++)
                object[root->childKeys[key]] = QString::number(root->childItems[key]->type);
            return object;
            break;
        case Array:
            for (int key = 0; key < root->childKeys.count(); key++)
                array.append(QJsonValue(QString::number(root->childItems[key]->type)));
            return array;
            break;
        case Value:
            return root->value;
            break;
        case Undefined:
            break;
        }
    }
    return QJsonValue();
}

void JsonBase::move(int parentIndex, int index, QString key)
{
    JsonBaseItem *newParent = baseCache[parentIndex];
    JsonBaseItem *child = baseCache[index];
    if (newParent != NULL && child != NULL) {
        JsonBaseItem *oldParent = baseCache[child->parentIndex];
        if (oldParent != NULL && newParent->type == oldParent->type) {
            for (int i = 0; i < oldParent->childItems.count(); i++)
                if (oldParent->childItems[i] == child) {
                    oldParent->childKeys.remove(i);
                    oldParent->childItems.remove(i);
                    if (oldParent->type == Array)
                        for (int j = i; i < oldParent->childKeys.count(); j++)
                            oldParent->childKeys[j] = QString::number(j);
                    break;
                }
            int index = indexOf(newParent, key);
            if (index >= 0 && newParent->type == Object) {
                clear(newParent->childItems[index]);
                newParent->childItems[index] = child;
            } else {
                index = newParent->childKeys.count();
                newParent->childKeys.resize(index + 1);
                newParent->childItems.resize(index + 1);
                if (newParent->type == Object)
                    newParent->childKeys.last() = key;
                else
                    newParent->childKeys.last() = QString::number(index);
                newParent->childItems.last() = child;
            }
        }
    }
}

int JsonBase::append(QJsonValue json, QStringList path)
{
    if (!json.isUndefined() && !path.isEmpty()) {
        JsonBaseItem *root = find(baseRoot, path);
        if (root != NULL) {
            if (root->type != Value && !(root->type == Array && json.isArray())) {
                int index = indexOf(root, path.last());
                if (index < 0) {
                    increase(root);
                    root->childKeys.last() = path.last();
                    root = root->childItems.last();
                } else {
                    clear(root->childItems[index]);
                    root->childItems[index] = new JsonBaseItem;
                    root = root->childItems[index];
                }
                if (json.isObject())
                    append(root, json.toObject(), root->parentIndex);
                else if (!json.isArray())
                    append(root, json, root->parentIndex);
                else
                    append(root, json.toArray(), root->parentIndex);
                return root->currentIndex;
            }
        }
    }
    return -1;
}

int JsonBase::append(QJsonValue json, QString key, int index)
{
    if (!key.isEmpty()) {
        JsonBaseItem *root = baseCache[index];
        if (root != NULL) {
            if (root->type != Value && !(root->type == Array && json.isArray())) {
                int index = indexOf(root, key);
                if (index < 0) {
                    increase(root);
                    root->childKeys.last() = key;
                    root = root->childItems.last();
                } else {
                    clear(root->childItems[index]);
                    root->childItems[index] = new JsonBaseItem;
                    root = root->childItems[index];
                }
                if (root->type == Object)
                    append(root, json.toObject(), root->currentIndex);
                else
                    append(root, json.toArray(), root->currentIndex);
                return root->currentIndex;
            }
        }
    }
    return -1;
}

int JsonBase::indexOf(QStringList path)
{
    return indexOf(baseRoot, path);
}

void JsonBase::append(JsonBaseItem *root, QJsonObject json, int parentIndex)
{
    if (root->type == Undefined) {
        root->type = Object;
        root->currentIndex = baseCache.append(root);
        root->parentIndex = parentIndex;
    }
    for (QString key : json.keys()) {
        if (!json[key].isUndefined()) {
            increase(root);
            root->childKeys.last() = key;
            if (json[key].isObject())
                append(root->childItems.last(), json[key].toObject(), root->currentIndex);
            else if (json[key].isArray())
                append(root->childItems.last(), json[key].toArray(), root->currentIndex);
            else
                append(root->childItems.last(), json[key], root->currentIndex);
        }
    }
}

void JsonBase::append(JsonBaseItem *root, QJsonArray json, int parentIndex)
{
    if (root->type == Undefined) {
        root->type = Array;
        root->currentIndex = baseCache.append(root);
        root->parentIndex = parentIndex;
    }
    for (int key = 0; key < json.count(); key++)
        if (!json[key].isUndefined()) {
            increase(root);
            root->childKeys.last() = QString::number(key);
            if (json[key].isObject())
                append(root->childItems.last(), json[key].toObject(), root->currentIndex);
            else
                append(root->childItems.last(), json[key], root->currentIndex);
        }
}

void JsonBase::append(JsonBaseItem  *root, QJsonValue json, int parentIndex)
{
    if (root->type == Undefined) {
        root->type = Value;
        root->currentIndex = baseCache.append(root);
        root->parentIndex = parentIndex;
    }
    root->value = json;
}

JsonBaseItem *JsonBase::find(JsonBaseItem *root, QStringList path)
{
    if (!path.isEmpty()) {
        int nextHop;
        nextHop = indexOf(root, path.first());
        if (path.count() > 1) {
            if (nextHop >= 0) {
                path.removeFirst();
                return find(takeAt(root, nextHop), path);
            } else
                return NULL;
        } else
            return root;
    }
    return NULL;
}

int JsonBase::indexOf(JsonBaseItem *root, QString key)
{
    if (root != NULL) {
        if (root->type == Object || root->type == Array) {
            int index = -1;
            for (int key_i = 0; key_i < root->childKeys.count(); key_i++)
                if (root->childKeys[key_i] == key) {
                    index = key_i;
                    break;
                }
            return index;
        }
    }
    return -1;
}

int JsonBase::indexOf(JsonBaseItem *root, QStringList path)
{
    if (!path.isEmpty()) {
        int index = indexOf(root, path.first());
        if (index >= 0) {
            if (path.count() > 1) {
                path.removeFirst();
                return indexOf(root->childItems[index], path);
            } else
                return root->childItems[index]->currentIndex;
        }
    }
    return -1;
}

JsonBaseItem *JsonBase::takeAt(JsonBaseItem *root, int key)
{
    if (root->childItems.count() > key)
        return root->childItems[key];
    else
        return NULL;
}

void JsonBase::increase(JsonBaseItem *root)
{
    root->childKeys.resize(root->childKeys.size() + 1);
    root->childItems.resize(root->childItems.size() + 1);
    root->childItems.last() = new JsonBaseItem;
}

QJsonValue JsonBase::toJson(JsonBaseItem *root)
{
    QJsonObject object;
    QJsonArray array;

    switch (root->type) {
    case Object:
        for (int key = 0; key < root->childKeys.count(); key++)
            object[root->childKeys[key]] = toJson(root->childItems[key]);
        return object;
        break;
    case Array:
        for (int key = 0; key < root->childItems.count(); key++) {
            if (root->childItems[key]->type == Object)
                array.append(toJson(root->childItems[key]));
            else
                array.append(root->childItems[key]->value);
        }
        return array;
        break;
    case Value:
        return root->value;
        break;
    case Undefined:
        break;
    }
    return QJsonValue();
}

void JsonBase::clear(JsonBaseItem *root)
{
    if (root != NULL) {
        for (int i = 0; i < root->childItems.count(); i++)
            if (root->childItems[i] != NULL) {
                if (root->childItems[i]->type == Object || root->childItems[i]->type == Array)
                    clear(root->childItems[i]);
                delete root->childItems[i];
            }
    }
}
