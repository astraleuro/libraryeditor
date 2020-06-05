#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMessageBox>
#include <QResizeEvent>

#include "defines.h"
#include "widgets/welcomescreen.h"
#include "widgets/mainlist.h"
#include "widgets/arraylist.h"
#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {};
    MainWindow(QString config, QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void showWelcomeScreen();
    void showMainList(QString fn, QJsonObject &data);
    void showArrayList(JsonDataSections sec);
    void saveSettings(QString key, QJsonObject keySettings);
    void backFromArrayList();
    void closeApp();

protected:
    void resizeEvent(QResizeEvent *event);
    void clearMainLayout();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    WelcomeScreen *welcomeScreen = nullptr;
    MainList *mainList = nullptr;
    ArrayList *arrayList = nullptr;
    QString configPath, jsonPath, defaultPath;
    QJsonObject allSettings, settings, jsonData;
};

#endif // MAINWINDOW_H
