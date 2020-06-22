#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMessageBox>
#include <QResizeEvent>

#include "defines.h"
#include "widgets/welcomescreen.h"
#include "widgets/mainmenu.h"
#include "widgets/itemlist.h"
#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"
#include "widgets/logcollector.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {};
    MainWindow(QString config, QWidget *parent = nullptr);
    void openFile(QString fn);
    ~MainWindow();

protected slots:
    void showWelcomeScreen();
    void showMainMenu(QString fn, QJsonObject &data);
    void showItemList(JsonDataSections sec);
    void saveSettings(QString key, QJsonObject keySettings);
    void backFromItemList();
    void sendEras(QString key);
    void sendAuthors(QString key);
    void closeApp();
    void setSaved();
    void setChanged();
    void saveImages();
    void removeAuthorsInArts(QString subkey, QString key);
    void clearEraInArts(QString subkey, QString key);
    void changeKeyArgInArts(QString prevArg, QString newArg, QString key);
    void updateData();

protected:
    void removeUnused(QString path);
    void resizeEvent(QResizeEvent *event);
    void clearMainLayout();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    WelcomeScreen *welcomeScreen = nullptr;
    MainMenu *mainMenu = nullptr;
    ItemList *itemList = nullptr;
    QString configPath, jsonPath, defaultPath;
    QJsonObject allSettings, settings, jsonData, errorsMsg;
    bool isChanged = false;
    LogCollector logCollector;
};

#endif // MAINWINDOW_H
