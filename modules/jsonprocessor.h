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
QString takeRank(int rank, const QStringList &ranks);

#endif // JSONPROCESSOR_H
