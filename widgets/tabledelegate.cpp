#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void TableDelegate::setRowType(int row, RowTypes type)
{
    types[row] = type;
}

void TableDelegate::setModifyer(int row, int col, QString modifyer)
{
    modifyers[row][col] = modifyer;
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (types[index.row()] == ChildItem) {
        if (modifyers[index.row()][index.column()] == "")
            childActivated(index.row());
        else {

        }
    } else if (types[index.row()] == ValueItem)
        valueActivated(index.row());
    return nullptr;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void TableDelegate::clear()
{
    types.resize(0);
    modifyers.resize(0);
}

void TableDelegate::appendRow(int count)
{
    types.resize(types.size() + count);
    modifyers.resize(modifyers.size() + count);
    if (modifyers.count() > 0) {
        int size = modifyers[0].size();
        for (int i = 1; i < modifyers.count(); i++)
            modifyers[i].resize(size);
    }
}

void TableDelegate::appendCol(int count)
{
    for (int i = 0; i < modifyers.count(); i++)
        modifyers[i].resize(modifyers[i].size() + count);
}
