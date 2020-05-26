#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QItemDelegate>

class TableDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TableDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:

};

#endif // TABLEDELEGATE_H
