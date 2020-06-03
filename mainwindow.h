#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMessageBox>

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
    void takeMainListSettings();
    void takeArrayListSettings();
    void backFromArrayList();
    void closeApp();

protected:
    void clearMainLayout();

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    WelcomeScreen *welcomeScreen = nullptr;
    MainList *mainList = nullptr;
    ArrayList *arrayList = nullptr;
    QString configPath, jsonPath;
    QJsonObject allSettings, jsonData;
};

#endif // MAINWINDOW_H
