#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QItemDelegate>

#include "defines.h"
#include "templates.h"
#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"
#include "modules/txtprocessor.h"
#include "widgets/itemeditor.h"

class ListItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ListItemDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {};
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
class ItemList;
}

class ItemList : public QWidget
{
    Q_OBJECT

public:
    explicit ItemList(QWidget *parent = nullptr);
    void initData(QString fn, QJsonObject &data, QJsonObject &opt, JsonDataSections &sec);
    QJsonArray takeData();
    JsonDataSections takeSection();
    ~ItemList();

protected:
    void fillTable();
    void eraseTable();
    void addImageItem(int row, QJsonValue data);
    QJsonObject takeSettings();
    void changeItem(QJsonObject data, int row);
    QString jsonValueToText(QString key, QJsonValue value);
    void fillSortBox();
    void reorderItems(QVector<int> &order);

signals:
    void dataChanged();
    void settingsChanged(QString, QJsonObject);
    void goBack();
    void readyForEras(QString);
    void readyForAuthors(QString);
    void sendEras(QStringList&);
    void sendAuthors(QStringList&);
    void removeAuthorsInArts(QString, QString);
    void clearEraInArts(QString, QString);
    void changeKeyArgInArts(QString, QString, QString);

private slots:
    void applyFilter();
    void sortStateChanged(int state = 1);
    void itemUniqueCheck(QJsonValue value, QString key, int index);
    void adoptItems(int col, int oldSize, int newSize);
    void adoptText(int row);
    void openItemEditor(int index = -1);
    void on_filterButton_toggled(bool checked);
    void on_sortButton_toggled(bool checked);
    void on_backButton_clicked();
    void on_filterApplyButton_clicked();
    void on_sortOrderButton_clicked();
    void on_editButton_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_disableFilter_clicked();
    void on_disableSort_clicked();

private:
    Ui::ItemList *ui;
    QJsonObject allSettings, settings, jsonData, secOptions;
    QJsonArray jsonArray;
    QString allFilesPath;
    JsonDataSections section;
    QString secFilesPath, tmpFilesPath, imageKey, textColKeyF, filterStr;
    QStringList textColKeysH, textColLabels, ranks;
    bool sortOrder = true;
    ItemEditor itemEditor;
    ListItemDelegate *delegate;
};

#endif // ITEMLIST_H
