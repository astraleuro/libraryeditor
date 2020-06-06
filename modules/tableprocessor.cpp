#include "tableprocessor.h"


void removeTableSelectedItems(QTableWidget *table, QList<QTableWidgetItem *> range)
{
    for (int i = range.count() - 1; i >= 0; i--)
        table->removeRow(table->row(range[i]));
}

void tableFromList(QTableWidget *table, QStringList &list, int col)
{
    table->clear();
    table->setColumnCount(col + 1);
    table->setRowCount(list.count());
    for (int i = 0; i < list.count(); i++) {
        for (int j = 0; j < table->columnCount(); j++)
            if (table->item(i, j) == nullptr)
                table->setItem(i, j, new QTableWidgetItem);
        table->item(i, table->columnCount() - 1)->setText(list[i]);
    }
}

QJsonArray tableToArray(QTableWidget *table)
{
    QJsonArray array;
    for (int i = 0; i < table->rowCount(); i++)
        array.append(QJsonValue(table->item(i, 0)->text()));
    return array;
}

QStringList tableToList(QTableWidget *table, int col)
{
    QStringList list;
    for (int i = 0; i < table->rowCount(); i++)
        list.append(table->item(i, col)->text());
    return list;
}
