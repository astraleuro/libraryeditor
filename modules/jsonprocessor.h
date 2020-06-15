#ifndef JSONPROCESSOR_H
#define JSONPROCESSOR_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QStringList>
#include <QTableWidgetItem>
#include <QList>

#include "defines.h"

QJsonObject initJsonObject();
QString stringArrayToString(QJsonArray data);
QStringList stringArrayToList(QJsonArray data);
QStringList objectArrayToList(QJsonArray data, QString key);
void removeArraySelectedItems(QJsonArray &array, QList<QTableWidgetItem*> range);
QStringList takeListByObjectKey(QString key, QJsonArray array);
QJsonArray clearKeyInObjectArray(QString subkey, QString key, QJsonArray array);
QJsonArray removeKeyInObjectArray(QString subkey, QString key, QJsonArray array);
QJsonArray modifyObjectsKeyInArray(QString prefix, QString key, QJsonArray array);
QJsonArray bubbleSortByKey(QJsonArray array, QString key, bool order, QVector<int> &swaps);
int indexOfObjectByKey(QString uniqueKey, QString data, QJsonArray array);
bool isValidSchema(QJsonValue file, QJsonValue schema);

#endif // JSONPROCESSOR_H
