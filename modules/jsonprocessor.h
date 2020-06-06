#ifndef JSONPROCESSOR_H
#define JSONPROCESSOR_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QStringList>

#include "defines.h"

QJsonObject initJsonObject();
QString stringArrayToString(QJsonArray data);
QStringList stringArrayToList(QJsonArray data);
QStringList objectArrayToList(QJsonArray data, QString key);

#endif // JSONPROCESSOR_H
