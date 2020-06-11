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

QJsonArray modifyObjectsKeyInArray(QString prefix, QString key, QJsonArray array)
{
    QJsonObject item;
    for (int i = 0; i < array.count(); i++) {
        item = array[i].toObject();
        if (item.contains(key)) {
            item[key] = prefix + item[key].toString();
            array[i] = item;
        }
    }
    return array;
}

QJsonArray bubbleSortByKey(QJsonArray array, QString key, bool order, QVector<int> &swaps)
{
    bool isSwap;
    int index;
    QJsonObject object;
    swaps.resize(array.count());
    for (int i = 0; i < swaps.count(); i++)
        swaps[i] = i;
    for (int i = 0; i < array.count() - 1; i++) {
        for (int j = 0; j < array.count() - i - 1; j++) {
            isSwap = false;
            switch (array[j].toObject()[key].type()) {
            case QJsonValue::Bool:
                if ((order && array[j].toObject()[key].toBool() > array[j + 1].toObject()[key].toBool()) ||
                        (!order && array[j].toObject()[key].toBool() < array[j + 1].toObject()[key].toBool()))
                    isSwap = true;
                break;
            case QJsonValue::Double:
                if ((order && array[j].toObject()[key].toDouble() > array[j + 1].toObject()[key].toDouble()) ||
                        (!order && array[j].toObject()[key].toDouble() < array[j + 1].toObject()[key].toDouble()))
                    isSwap = true;
                break;
            case QJsonValue::Array:
                if ((order && stringArrayToString(array[j].toObject()[key].toArray()) > stringArrayToString(array[j + 1].toObject()[key].toArray())) ||
                        (!order && stringArrayToString(array[j].toObject()[key].toArray()) < stringArrayToString(array[j + 1].toObject()[key].toArray())))
                    isSwap = true;
                break;
            default:
                if ((order && array[j].toObject()[key].toString() > array[j + 1].toObject()[key].toString()) ||
                        (!order && array[j].toObject()[key].toString() < array[j + 1].toObject()[key].toString()))
                    isSwap = true;
                break;
            }
            if (isSwap) {
                index = swaps[j];
                swaps[j] = swaps[j + 1];
                swaps[j + 1] = index;
                object = array[j].toObject();
                array[j] = array[j + 1];
                array[j + 1] = object;

            }
        }
    }
    return array;
}

int indexOfObjectByKey(QString uniqueKey, QString data, const QJsonArray &array)
{
    int index = -1;
    for (int i = 0; i < array.count(); i++)
        if (array[i].toObject()[uniqueKey] == data) {
            index = i;
            break;
        }
    return index;
}
