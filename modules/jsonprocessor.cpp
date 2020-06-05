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

QString takeRank(int rank, const QStringList &ranks)
{
    bool isOk;
    int current;
    for (int i = 0; i < ranks.count(); i++) {
        current = ranks[i].toInt(&isOk);
        if (isOk && current == rank && i > 0)
            return ranks[i - 1];
    }
    return "";
}
