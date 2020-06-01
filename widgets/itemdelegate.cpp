#include "itemdelegate.h"

QWidget *StandardItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int pos = 0;
    if (orientation == RowOriented)
        pos = index.row();
    if (m.size() > 0)
        if (m[pos].split(LIST_SEPARATOR)[TYPE_POS] == EDIT_FLAG)
            return QItemDelegate::createEditor(parent, option, index);
    return nullptr;
}

void StandardItemDelegate::setData(int pos, QString text)
{
    if (d.size() <= pos)
        d.resize(pos + 1);
    d[pos] = text;
}

void StandardItemDelegate::setModifier(int pos, QString text)
{
    if (m.size() <= pos)
        m.resize(pos + 1);
    m[pos] = text;
}

QWidget *BoolItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr;
}

bool BoolItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        int pos = 0;
        if (orientation == ColOriented)
            pos = index.row();
        if (d[pos] == "0")
            d[pos] = "1";
        else
            d[pos] = "0";
        model->setData(index, QVariant(takeModifiedData(pos)));
    }
}

QString BoolItemDelegate::takeModifiedData(int pos)
{
    return m[pos].split(LIST_SEPARATOR)[BOOL_POS + d[pos].toInt()];
}

QWidget *ComplexItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    posActivated(index.row());
    return nullptr;
}

QString ComplexItemDelegate::takeModifiedData(int pos)
{
    return m[pos];
}

QString FileItemDelegate::takeModifiedData(int pos)
{
    return m[pos].split(LIST_SEPARATOR)[FILE_POS] + d[pos];
}
