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
