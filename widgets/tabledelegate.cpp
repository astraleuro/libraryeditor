#include "tabledelegate.h"

TableDelegate::TableDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void TableDelegate::setRowType(int row, RowTypes type)
{
    types[row] = type;
}

void TableDelegate::setModifier(int row, int col, QString modifyer)
{
    modifiers[row][col] = modifyer;
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (types[index.row()] == ChildItem) {
        if (modifiers[index.row()][index.column()] == "")
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
    modifiers.resize(0);
}

void TableDelegate::appendRow(int count)
{
    types.resize(types.size() + count);
    modifiers.resize(modifiers.size() + count);
    if (modifiers.count() > 0) {
        int size = modifiers[0].size();
        for (int i = 1; i < modifiers.count(); i++)
            modifiers[i].resize(size);
    }
}

void TableDelegate::appendCol(int count)
{
    for (int i = 0; i < modifiers.count(); i++)
        modifiers[i].resize(modifiers[i].size() + count);
}
