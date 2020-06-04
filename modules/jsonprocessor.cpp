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
    if (ranks.count() > rank + 1) {
        if (rank == 0)
            return ranks[0];
        else if (rank == 1)
            return ranks[2];
        else
            return ranks[rank + 2];
    }
    return "";
}
