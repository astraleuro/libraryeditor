#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QItemDelegate>
#include <QJsonObject>
#include <QJsonArray>
#include <QWindow>

#include "defines.h"
#include "templates.h"

#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"
#include "modules/txtprocessor.h"

#include "widgets/itemeditor.h"

class ArrayItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ArrayItemDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {};
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        UNUSED(parent);
        UNUSED(option);
        itemActivated(index.row());
        return nullptr;
    };

signals:
    void itemActivated(int) const;

};

class ArrayListWidget : public QTableWidget
{
    Q_OBJECT

public:
    ArrayListWidget(QWidget *parent = nullptr) : QTableWidget(parent) {};
    ~ArrayListWidget() {};

protected:
    void resizeEvent(QResizeEvent *event);

};

namespace Ui {
class ArrayList;
}

class ArrayList : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayList(QWidget *parent = nullptr);
    void initData(QString fn, QJsonObject &data, QJsonObject &opt, JsonDataSections &sec);
    ~ArrayList();
    QJsonObject takeSettings();

protected:
    void fillTable();
    void eraseTable();
    void addImageItem(int row, QJsonValue data);
    void addTextItem(int row, QJsonValue data);

protected slots:
    void adoptItems(int col, int oldSize, int newSize);
    //void adoptText();
    void openItemEditor();

signals:
    void settingsModified();
    void saveData();
    void goBack();

private slots:
    void on_filterButton_toggled(bool checked);
    void on_sortButton_toggled(bool checked);
    void on_backButton_clicked();
    void on_filterApplyButton_clicked();
    void on_sortApplyButton_clicked();
    void on_sortOrderButton_clicked();

    void on_editButton_clicked();

private:
    Ui::ArrayList *ui;
    QJsonObject allSettings, settings, jsonData, secOptions;
    QJsonArray jsonArray;
    QString allFilesPath;
    JsonDataSections section;
    QString secFilesPath, imageKey, textColKeyF;
    QStringList textColKeysH, textColLabels;
};

#endif // ARRAYLIST_H
