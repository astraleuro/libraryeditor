#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}
