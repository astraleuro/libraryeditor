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

bool JsonBase::isValid(JsonBase &schema)
{
    return isValid(baseRoot, schema.baseRoot);
}

bool JsonBase::merge(JsonBase &base, JsonBase &schema)
{
    if (isValid(base.baseRoot, schema.baseRoot)) {
        mergeObject(baseRoot, base.baseRoot, schema.baseRoot);
        return true;
    } else
        return false;
}

int JsonBase::countOf(JsonBaseItem *root, QRegExp regExp)
{
    if (root != NULL) {
        if (root->type == Object) {
            int count = 0;
            for (int i = 0; i < root->childKeys.count(); i++)
                if (regExp.exactMatch(root->childKeys[i]))
                    count++;
            return count;
        } else
            return 0;
    } else
        return 0;
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
                increase(newParent, false);
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

QString JsonBase::takeKey(JsonBaseItem *root, QString key)
{
    if (root != NULL && root->type == Object) {
        for (int i = 0; i < root->childKeys.count(); i++)
            if (root->childKeys[i] == key && root->childItems[i] != NULL && root->childItems[i]->type == Value)
                return root->childItems[i]->value.toString();
    }
    return "";
}

void JsonBase::increase(JsonBaseItem *root, bool alloc)
{
    root->childKeys.resize(root->childKeys.size() + 1);
    root->childItems.resize(root->childItems.size() + 1);
    if (alloc)
        root->childItems.last() = new JsonBaseItem;
    else
        root->childItems.last() = NULL;
}

void JsonBase::mergeObject(JsonBaseItem *toRoot, JsonBaseItem *fromRoot, JsonBaseItem *schema)
{
    QStringList *specList = NULL;
    int fromIndex, schemaIndex;
    for (int i = 0; i < toRoot->childKeys.count(); i++) {
        fromIndex = indexOf(fromRoot, toRoot->childKeys[i]);
        if (toRoot->childItems[i]->type == Array) {
            schemaIndex = indexOf(schema, "{" + toRoot->childKeys[i] + "}");
            if (schemaIndex >= 0) {
                specList = new QStringList;
                specList->append(takeKey(schema->childItems[schemaIndex], UNIQUEBY_FLAG));
                specList->append(takeKey(schema->childItems[schemaIndex], NEWESTBY_FLAG));
            }
            merge(toRoot->childItems[i], fromRoot->childItems[fromIndex],
                  schema->childItems[indexOf(schema, toRoot->childKeys[i])], specList);
            delete specList;
        } else if (toRoot->childItems[i]->type == Value)
            toRoot->childItems[i]->value = fromRoot->childItems[fromIndex]->value;
        else if (toRoot->childItems[i]->type == Object)
            merge(toRoot->childItems[i], fromRoot->childItems[fromIndex],
                  schema->childItems[indexOf(schema, toRoot->childKeys[i])]);
    }
}

void JsonBase::mergeArray(JsonBaseItem *toRoot, JsonBaseItem *fromRoot, JsonBaseItem *schema, QStringList *spec)
{
    int isExist, isEqual;
    QStringList uniqueby = spec->at(0).split(LIST_SEPARATOR, QString::SkipEmptyParts);
    QString newestby = spec->at(1);
    for (int i = 0; i < fromRoot->childKeys.count(); i++)
        if (fromRoot->childItems[i]->type == Value) {
            isExist = false;
            for (int j = 0; j < toRoot->childKeys.count(); j++)
                if (toRoot->childItems[j]->type == Value &&
                        toRoot->childItems[j]->value == fromRoot->childItems[i]->value) {
                    isExist = true;
                    break;
                }
            if (!isExist) {
                increase(toRoot, false);
                toRoot->childKeys.last() = QString(toRoot->childKeys.count() - 1);
                toRoot->childItems.last()->type = Value;
                toRoot->childItems.last()->value = fromRoot->childItems[i]->value;
            }
        } else if(fromRoot->childItems[i]->type == Object) {
            isExist = false;
            if (!uniqueby.isEmpty()) {
                for (int j = 0; j < toRoot->childKeys.count(); j++)
                    if (toRoot->childItems[j]->type == Object) {
                        isEqual = true;
                        for (QString key : uniqueby)
                            if (fromRoot->childItems[i]->type == Value &&
                                    takeKey(toRoot->childItems[j], key) != takeKey(fromRoot->childItems[i], key)) {
                                isEqual = false;
                                break;
                            }
                        if (isEqual && !newestby.isEmpty() &&
                                max(takeKey(toRoot->childItems[j], newestby), takeKey(fromRoot->childItems[i], newestby)) == 1) {
                            if (!isEqual) {
                                clear(toRoot->childItems[j]);
                                toRoot->childItems[j] = copy(fromRoot->childItems[i], toRoot->currentIndex);
                            }
                        } else
                            break;
                    }
            }
            if (!isExist) {
                increase(toRoot, false);
                toRoot->childKeys.last() = QString(toRoot->childKeys.count() - 1);
                toRoot->childItems.last() = copy(fromRoot->childItems[i], toRoot->currentIndex);
            }
        }
}

int JsonBase::max(QString left, QString right)
{

}

JsonBaseItem *JsonBase::copy(JsonBaseItem *root, int parentIndex)
{

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

bool JsonBase::isValid(JsonBaseItem *root, JsonBaseItem *schema)
{
    if (root != NULL && schema != NULL) {
        if (root->type == schema->type) {
            if (root->type == Object) {
                if (root->childKeys.count() == (schema->childKeys.count() - countOf(schema, QRegExp("[{][a-zA-Z0-9]*[}]$")) )) {
                    int keyIndex = -1;
                    for (int i = 0; i < root->childKeys.count(); i++) {
                        keyIndex = indexOf(schema, root->childKeys[i]);
                        if (keyIndex == -1)
                            return false;
                        if (root->childItems[i]->type == schema->childItems[keyIndex]->type) {
                            if (!isValid(root->childItems[i], schema->childItems[keyIndex]))
                                return false;
                        } else
                            return false;
                    }
                } else
                    return false;
                return true;
            } else if (root->type == Array) {
                bool isExist = true;
                for (int i = 0; i < root->childItems.count(); i++) {
                    if (root->childItems[i]->type == Value) {
                        isExist = false;
                        for (int j = 0; j < schema->childItems.count(); j++)
                            if (schema->childItems[j]->type == Value) {
                                isExist = true;
                                break;
                            }
                    } else {
                        isExist = false;
                        for (int j = 0; j < schema->childItems.count(); j++)
                            if (schema->childItems[j]->type == Object) {
                                isExist = isValid(root->childItems[i], schema->childItems[j]);
                                if (isExist)
                                    break;
                            }
                        if (!isExist)
                            return false;
                    }
                }
                return isExist;
            } else
                return true;
        } else
            return false;
    } else
        return false;
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
