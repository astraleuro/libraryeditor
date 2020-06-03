#include "mainwindow.h"

MainWindow::MainWindow(QString config, QWidget *parent)
    : QMainWindow(parent)
{
    configPath = config;

    QJsonParseError log;
    readJson(configPath, allSettings, log);
    if (log.error != QJsonParseError::NoError)
        allSettings = QJsonObject();
    setCentralWidget(new QWidget);
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);
    setWindowTitle(MAINWINDOW_TITLE);
    showWelcomeScreen();
}

MainWindow::~MainWindow()
{
    if (!writeJson(configPath, allSettings)) {
        QMessageBox msg(QMessageBox::Warning, MSGBOX_TITLE, MSG_SETTINGS_WRITE_ERROR +
                        configPath, QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
    }
}

void MainWindow::showWelcomeScreen()
{
    clearMainLayout();
    welcomeScreen = new WelcomeScreen;
    mainLayout->addWidget(welcomeScreen);
    connect(welcomeScreen, SIGNAL(dataReady(QString, QJsonObject&)), this, SLOT(showMainList(QString, QJsonObject&)));
    connect(welcomeScreen, SIGNAL(closeApp()), this, SLOT(closeApp()));
}

void MainWindow::showMainList(QString fn, QJsonObject &data)
{
    jsonPath = fn;
    if (&jsonData != &data)
        jsonData = data;

    clearMainLayout();
    mainList = new MainList;
    mainLayout->addWidget(mainList);
    connect(mainList, SIGNAL(settingsModified()), this, SLOT(takeMainListSettings()));
    connect(mainList, SIGNAL(goBack()), this, SLOT(showWelcomeScreen()));
    connect(mainList, SIGNAL(showArrayList(JsonDataSections)), this, SLOT(showArrayList(JsonDataSections)));
    mainList->initData(jsonPath, jsonData, allSettings);
}

void MainWindow::showArrayList(JsonDataSections sec)
{
    clearMainLayout();
    arrayList = new ArrayList;
    mainLayout->addWidget(arrayList);
    connect(arrayList, SIGNAL(goBack()), this, SLOT(backFromArrayList()));
    connect(arrayList, SIGNAL(settingsModified()), this, SLOT(takeArrayListSettings()));
    arrayList->initData(jsonPath, jsonData, allSettings, sec);
}

void MainWindow::takeMainListSettings()
{
    allSettings[getClassName(mainList)] = mainList->takeSettings();
}

void MainWindow::takeArrayListSettings()
{
    allSettings[getClassName(arrayList)] = arrayList->takeSettings();
}

void MainWindow::backFromArrayList()
{
    showMainList(jsonPath, jsonData);
}

void MainWindow::closeApp()
{
    close();
}

void MainWindow::clearMainLayout()
{
    if (welcomeScreen != nullptr) {
        disconnect(welcomeScreen, SIGNAL(dataReady(QString, QJsonObject&)), this, SLOT(showMainList(QString, QJsonObject&)));
        disconnect(welcomeScreen, SIGNAL(closeApp()), this, SLOT(closeApp()));
        mainLayout->removeWidget(welcomeScreen);
        delete welcomeScreen;
        welcomeScreen = nullptr;
    }
    if (mainList != nullptr) {
        disconnect(mainList, SIGNAL(settingsModified()), this, SLOT(takeMainListSettings()));
        disconnect(mainList, SIGNAL(goBack()), this, SLOT(showWelcomeScreen()));
        disconnect(mainList, SIGNAL(showArrayList(JsonDataSections)), this, SLOT(showArrayList(JsonDataSections)));
        mainLayout->removeWidget(mainList);
        delete mainList;
        mainList = nullptr;
    }
    if (arrayList != nullptr) {
        disconnect(arrayList, SIGNAL(goBack()), this, SLOT(backFromArrayList()));
        disconnect(arrayList, SIGNAL(settingsModified()), this, SLOT(takeArrayListSettings()));
        mainLayout->removeWidget(arrayList);
        delete arrayList;
        arrayList = nullptr;
    }
}

