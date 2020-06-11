#ifndef MAINLIST_H
#define MAINLIST_H

#include <QWidget>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QMouseEvent>

#include "templates.h"
#include "defines.h"
#include "modules/fsprocessor.h"
#include "widgets/jsonexport.h"
#include "modules/txtprocessor.h"
#include "modules/jsonprocessor.h"

class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MenuButton(QWidget *parent = nullptr) : QPushButton(parent) {};
    void setHiddenMenu(QMenu *m);

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QMenu *menu = nullptr;
};

namespace Ui {
class MainList;
}

class MainList : public QWidget
{
    Q_OBJECT

public:
    explicit MainList(QWidget *parent = nullptr);
    void initData(QString fn, QJsonObject &data, QJsonObject &opt, bool changed = false);
    QJsonObject takeData();
    ~MainList();

signals:
    void saveImages();
    void dataSaved();
    void settingsChanged(QString, QJsonObject);
    void goBack();
    void showArrayList(JsonDataSections section);
    void dataMerged();
    void dataNotMerged();

protected:
    void updateInfo();
    void merge();
    QJsonArray mergeArrays(QString inPath, QString outPath, QString secSuffix,
                           QString filePathKey, QString uniqueByKey, QString newestByKey,
                           QJsonArray inArr, QJsonArray outArr);

private slots:
    void on_artsButton_clicked();
    void on_authorsButton_clicked();
    void on_erasButton_clicked();
    void on_saveButton_clicked();
    void on_goBackButton_clicked();
    void exportToJson();
    void on_mergeButton_clicked();

private:
    Ui::MainList *ui;
    QString jsonFile;
    QJsonObject allSettings, settings, jsonData, errorsMsg;
    QString jsonPath;
    bool isChanged = false;
    bool isMergeOk = true;
    bool isMerged = false;
    QAction *exportAction;
    QMenu exportMenu;
    JsonExport exportDialog;
    QStringList log;
};

#endif // MAINLIST_H
