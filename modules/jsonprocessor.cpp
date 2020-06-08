#include "modules/jsonprocessor.h"

QJsonObject initJsonObject()
{
    QJsonObject json;
    json[ARTS_KEY] = QJsonArray();
    json[AUTHORS_KEY] = QJsonArray();
    json[ERAS_KEY] = QJsonArray();
    return json;
}

QString stringArrayToString(QJsonArray data)
{
    QString str;
    for (int i = 0; i < data.count(); i++)
        str += data[i].toString() + ", ";
    str.remove(str.count() - 2, 2);
    return str;
}


QStringList stringArrayToList(QJsonArray data)
{
    QStringList list;
    for (int i = 0; i < data.count(); i++)
        list.append(data[i].toString());
    return list;
}

QStringList objectArrayToList(QJsonArray data, QString key)
{
    QStringList list;
    QJsonObject object;
    for (int i = 0; i < data.count(); i++) {
        object = data[i].toObject();
        if (object.contains(key))
            list.append(object[key].toString());
    }
    return list;
}

void removeArraySelectedItems(QJsonArray &array, QList<QTableWidgetItem *> range)
{
    for (int i = range.count() - 1; i >= 0; i--)
        if (0 == range[i]->column())
            array.removeAt(range[i]->row());
}

QStringList takeListByObjectKey(QString key, QJsonArray array)
{
    QStringList list;
    QString item;
    for (int i = 0; i < array.count(); i++) {
        item = array[i].toObject()[key].toString();
        if (!item.isEmpty())
            list.append(item);
    }
    return list;
}


QJsonArray removeKeyInObjectArray(QString subkey, QString key, QJsonArray array)
{
    QJsonArray subArray;
    QJsonObject object;
    for (int i = 0; i < array.count(); i++) {
        object = array[i].toObject();
        subArray = object[key].toArray();
        if (subArray.contains(subkey)) {
            for (int j = 0; j < subArray.count(); j++)
                if (subArray[j].toString() == subkey) {
                    subArray.removeAt(j);
                    object[key] = subArray;
                    array[i] = object;
                    break;
                }
        }
    }
    return array;
}

QJsonArray clearKeyInObjectArray(QString subkey, QString key, QJsonArray array)
{
    QJsonObject object;
    for (int i = 0; i < array.count(); i++) {
        object = array[i].toObject();
        if (object[key] == subkey) {
            object[key] = "";
            array[i] = object;
        }
    }
    return array;
}
