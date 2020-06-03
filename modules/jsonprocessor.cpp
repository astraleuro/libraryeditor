#include "modules/jsonprocessor.h"

QJsonObject initObject()
{
    QJsonObject json;
    json[ARTS_KEY] = QJsonArray();
    json[AUTHORS_KEY] = QJsonArray();
    json[ERAS_KEY] = QJsonArray();
    return json;
}
