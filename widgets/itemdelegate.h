#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QWidget>
#include <QItemDelegate>
#include <QString>
#include <QEvent>

#include "modules/templates.h"

enum ItemType {
    TextItem,
    FileItem,
    BoolItem,
    ComplexItem
};

enum Orientation {
    ColOriented,
    RowOriented
};

class StandardItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    StandardItemDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual ItemType itemType() {return TextItem;};
    virtual void setData(int pos, QString text);
    virtual void setModifier(int pos, QString text);
    virtual QString takeData(int pos) {return d[pos];};
    virtual QString takeModifier(int pos) {return m[pos];};
    virtual QString takeModifiedData(int pos) {return d[pos];};
    void setOrientation(Orientation type) {orientation = type;};

signals:
    void posActivated(int) const;

protected:
    QVector<QString> d, m;
    Orientation orientation;
};

class ComplexItemDelegate : public StandardItemDelegate
{
    Q_OBJECT

public:
    ComplexItemDelegate(QObject *parent = nullptr) : StandardItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    ItemType itemType() {return ComplexItem;};
    QString takeModifiedData(int pos);
};

class BoolItemDelegate : public StandardItemDelegate
{
    Q_OBJECT

public:
    BoolItemDelegate(QObject *parent = nullptr) : StandardItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    ItemType itemType() {return BoolItem;};
    QString takeModifiedData(int pos);
};

class FileItemDelegate : public StandardItemDelegate
{
    Q_OBJECT

public:
    FileItemDelegate(QObject *parent = nullptr) : StandardItemDelegate(parent) {};
    ItemType itemType() {return FileItem;};
    QString takeModifiedData(int pos);
};

#endif // ITEMDELEGATE_H
