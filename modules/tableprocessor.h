#ifndef TABLEPROCESSOR_H
#define TABLEPROCESSOR_H

#include <QTableView>
#include <QTableWidgetItem>
#include <QList>
#include <QJsonArray>

#include "defines.h"
#include "templates.h"

void tableFromList(QTableWidget *table, QStringList &list, int col = 0);
void removeTableSelectedItems(QTableWidget* table, QList<QTableWidgetItem*> range);
QJsonArray tableToArray(QTableWidget *table);
QStringList tableToList(QTableWidget *table, int col = 0);

#endif // TABLEPROCESSOR_H
