#ifndef CHOOSELIST_H
#define CHOOSELIST_H

#include <QDialog>
#include <QItemDelegate>

#include "defines.h"
#include "templates.h"

#include "modules/jsonprocessor.h"
#include "modules/tableprocessor.h"

class ChooseItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ChooseItemDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        UNUSED(parent);
        UNUSED(option);
        itemActivated(index.row());
        return nullptr;
    };

signals:
    void itemActivated(int) const;

};

namespace Ui {
class ChooseList;
}

class ChooseList : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseList(QWidget *parent = nullptr);
    void initData(QJsonObject &opt, QStringList &list);
    void checkByList(QStringList list);
    ~ChooseList();

protected:
    int searchItem(const QString &phrase, int row = 0);

signals:
    void settingsChanged(QString, QJsonObject);
    void chooseIsDone(QStringList &list);

private slots:
    void checkRow(int row);
    void uncheckRow(int row);
    void toggleRow(int row);
    void on_chooseButton_clicked();
    void on_cancelButton_clicked();
    void on_searchApply_clicked();

private:
    Ui::ChooseList *ui;
    QJsonObject settings;
    ChooseItemDelegate *tableDelegate;
};

#endif // CHOOSELIST_H
