#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QItemDelegate>
#include <QVector>

enum RowTypes {
    ChildItem,
    ValueItem
};

class TableDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TableDelegate(QObject *parent = nullptr);
    ~TableDelegate() {clear();};
    void setRowType(int row, RowTypes type);
    void setModifyer(int row, int col, QString modifyer);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void clear();
    void appendRow(int count = 1);
    void appendCol(int count = 1);

signals:
    void childActivated(int) const;
    void valueActivated(int) const;

private:
    QVector<RowTypes> types;
    QVector<QVector<QString>> modifyers;
};

#endif // TABLEDELEGATE_H
