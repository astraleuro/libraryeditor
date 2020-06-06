#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QItemDelegate>

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

protected:
    void fillTable();
    void eraseTable();
    void addImageItem(int row, QJsonValue data);
    void addTextItem(int row, QJsonValue data);
    QString jsonValueToText(QString key, QJsonValue value);
    QJsonObject takeSettings();


signals:
    void settingsChanged(QString, QJsonObject);
    void saveData();
    void goBack();
    void readyForEras(QString);
    void readyForAuthors(QString);
    void sendEras(QStringList &list);
    void sendAuthors(QStringList &list);

private slots:
    void adoptItems(int col, int oldSize, int newSize);
    void adoptText(int row);
    void openItemEditor(int index = -1);
    void on_filterButton_toggled(bool checked);
    void on_sortButton_toggled(bool checked);
    void on_backButton_clicked();
    void on_filterApplyButton_clicked();
    void on_sortApplyButton_clicked();
    void on_sortOrderButton_clicked();
    void on_editButton_clicked();
    void on_addButton_clicked();

private:
    Ui::ArrayList *ui;
    QJsonObject allSettings, settings, jsonData, secOptions;
    QJsonArray jsonArray;
    QString allFilesPath;
    JsonDataSections section;
    QString secFilesPath, imageKey, textColKeyF;
    QStringList textColKeysH, textColLabels, ranks;
    bool sortOrder = true;
    ItemEditor itemEditor;
    ArrayItemDelegate *delegate;
};

#endif // ARRAYLIST_H
