#ifndef MAINMENU_H
#define MAINMENU_H

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
#include "widgets/logcollector.h"

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
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    void initData(LogCollector *logDialog, QString fn, QJsonObject &data, QJsonObject &opt, bool changed = false);
    QJsonObject takeData();
    ~MainMenu();

signals:
    void saveImages();
    void dataSaved();
    void settingsChanged(QString, QJsonObject);
    void goBack();
    void showItemList(JsonDataSections section);
    void dataMerged();
    void dataNotMerged();

protected:
    bool checkFiles(QStringList &list);
    bool checkAuthors(QStringList &list);
    bool checkArts(QStringList &list);
    bool isCheck();
    bool isValidData(QStringList &list);
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

    void on_checkInfo_linkActivated(const QString &link);

private:
    Ui::MainMenu *ui;
    QString jsonFile;
    QJsonObject allSettings, settings, jsonData, errorsMsg;
    QString jsonPath;
    bool isChanged = false;
    bool isMergeOk = true;
    bool isMerged = false;
    QAction *exportAction;
    QMenu exportMenu;
    JsonExport exportDialog;
    QStringList log, check;
    LogCollector *logCollector;
};

#endif // MAINMENU_H
