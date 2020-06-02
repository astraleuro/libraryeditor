#include "itemdelegate.h"

QWidget *StandardItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int pos = 0;
    if (orientation == ColOriented)
        pos = index.row();
    if (m.size() > 0)
        if (m[pos].split(LIST_SEPARATOR)[TYPE_POS] == EDIT_FLAG || m[pos].split(LIST_SEPARATOR)[TYPE_POS] == PLAIN_FLAG)
            if ((orientation == ColOriented && !m[pos].contains(PLAIN_FLAG)) || (orientation == RowOriented && index.column() == 1))
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
        if (orientation == ColOriented || (orientation == RowOriented && index.column() == 1)) {
            if (d[pos] == "0")
                d[pos] = "1";
            else
                d[pos] = "0";
            model->setData(index, QVariant(takeModifiedData(pos)));
        }
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

bool FileItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (orientation == RowOriented) {
            if (index.column() == 1) {
                QFileDialog dialog(nullptr,
                                   "Выберите файл...",
                                   QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                   FILE_EXTENSIONS);
                dialog.setFileMode(QFileDialog::ExistingFile);
                dialog.setViewMode(QFileDialog::Detail);
                dialog.setModal(true);
                dialog.exec();
                if (dialog.selectedFiles().count() == 1)
                    fileChanged(index.row(), dialog.selectedFiles()[0]);
            }
        } else
            posActivated(index.row());
    }
}

QString FileItemDelegate::takeModifiedData(int pos)
{
    return m[pos].split(LIST_SEPARATOR)[FILE_POS] + d[pos];
}
