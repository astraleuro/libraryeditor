#include "mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent)
    : QMainWindow(parent)
{
    defaultPath = path;
    configPath = toNativeSeparators(defaultPath + "/" + CONFIG_FILE);

    QJsonParseError log;
    readJson(configPath, allSettings, log);
    if (log.error != QJsonParseError::NoError)
        allSettings = QJsonObject();

    settings = allSettings[getClassName(this)].toObject();

    errorsMsg = allSettings[ERRORS_SUBSECTION_KEY].toObject();
    errorsMsg[ERRORS_TITLE_KEY] = errorsMsg[ERRORS_TITLE_KEY].toString(ERRORS_TITLE);
    errorsMsg[ERRORS_SAVE_CONFIG_KEY] = errorsMsg[ERRORS_SAVE_CONFIG_KEY].toString(ERRORS_SAVE_CONFIG);
    errorsMsg[ERRORS_FILE_ON_BASESUBDIR_KEY] = errorsMsg[ERRORS_FILE_ON_BASESUBDIR_KEY].toString(ERRORS_FILE_ON_BASESUBDIR);
    allSettings[ERRORS_SUBSECTION_KEY] = errorsMsg;

    settings[MAIN_WIDTH_KEY] = settings[MAIN_WIDTH_KEY].toInt(MAIN_WIDTH);
    settings[MAIN_HEIGHT_KEY] = settings[MAIN_HEIGHT_KEY].toInt(MAIN_HEIGHT);
    setMinimumSize(MAIN_WIDTH, MAIN_HEIGHT);
    setGeometry(0, 0,
                settings[MAIN_WIDTH_KEY].toInt(),
                settings[MAIN_HEIGHT_KEY].toInt());

    setCentralWidget(new QWidget);
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);
    setWindowTitle(APPLICATION_NAME);
    showWelcomeScreen();
}

MainWindow::~MainWindow()
{
    allSettings[getClassName(this)] = settings;
    if (!writeJson(configPath, allSettings)) {
        QMessageBox msg(QMessageBox::Warning, errorsMsg[ERRORS_TITLE_KEY].toString(), errorsMsg[ERRORS_SAVE_CONFIG_KEY].toString() +
                        configPath, QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
    }
}

void MainWindow::showWelcomeScreen()
{
    clearMainLayout();
    welcomeScreen = new WelcomeScreen;
    connect(welcomeScreen, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    connect(welcomeScreen, SIGNAL(dataReady(QString, QJsonObject&)), this, SLOT(showMainList(QString, QJsonObject&)));
    connect(welcomeScreen, SIGNAL(closeApp()), this, SLOT(closeApp()));
    welcomeScreen->initData(allSettings, defaultPath);
    mainLayout->addWidget(welcomeScreen);
}

void MainWindow::showMainList(QString fn, QJsonObject &data)
{
    jsonPath = fn;
    if (&jsonData != &data)
        jsonData = data;

    clearMainLayout();
    mainList = new MainList;
    connect(mainList, SIGNAL(goBack()), this, SLOT(showWelcomeScreen()));
    connect(mainList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    connect(mainList, SIGNAL(showArrayList(JsonDataSections)), this, SLOT(showArrayList(JsonDataSections)));
    mainList->initData(jsonPath, jsonData, allSettings);
    mainLayout->addWidget(mainList);
}

void MainWindow::showArrayList(JsonDataSections sec)
{
    clearMainLayout();
    arrayList = new ArrayList;
    connect(arrayList, SIGNAL(goBack()), this, SLOT(backFromArrayList()));
    connect(arrayList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    connect(arrayList, SIGNAL(readyForEras(QString)), this, SLOT(sendEras(QString)));
    connect(arrayList, SIGNAL(readyForAuthors(QString)), this, SLOT(sendAuthors(QString)));
    arrayList->initData(jsonPath, jsonData, allSettings, sec);
    mainLayout->addWidget(arrayList);
}

void MainWindow::saveSettings(QString key, QJsonObject keySettings)
{
    allSettings[key] = keySettings;
}

void MainWindow::backFromArrayList()
{
    showMainList(jsonPath, jsonData);
}

void MainWindow::sendEras(QString key)
{
    QStringList eras = objectArrayToList(jsonData[ERAS_KEY].toArray(), key);
    arrayList->sendEras(eras);
}

void MainWindow::sendAuthors(QString key)
{
    QStringList authors = objectArrayToList(jsonData[AUTHORS_KEY].toArray(), key);
    arrayList->sendAuthors(authors);
}

void MainWindow::closeApp()
{
    close();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size()) {
        settings[MAIN_WIDTH_KEY] = width();
        settings[MAIN_HEIGHT_KEY] = height();
    }
}

void MainWindow::clearMainLayout()
{
    if (welcomeScreen != nullptr) {
        //disconnect(welcomeScreen, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
        //disconnect(welcomeScreen, SIGNAL(dataReady(QString, QJsonObject&)), this, SLOT(showMainList(QString, QJsonObject&)));
        //disconnect(welcomeScreen, SIGNAL(closeApp()), this, SLOT(closeApp()));
        mainLayout->removeWidget(welcomeScreen);
        delete welcomeScreen;
        welcomeScreen = nullptr;
    }
    if (mainList != nullptr) {
        //disconnect(mainList, SIGNAL(goBack()), this, SLOT(showWelcomeScreen()));
        //disconnect(mainList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
        //disconnect(mainList, SIGNAL(showArrayList(JsonDataSections)), this, SLOT(showArrayList(JsonDataSections)));
        mainLayout->removeWidget(mainList);
        delete mainList;
        mainList = nullptr;
    }
    if (arrayList != nullptr) {
        //disconnect(arrayList, SIGNAL(goBack()), this, SLOT(backFromArrayList()));
        //disconnect(arrayList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
        mainLayout->removeWidget(arrayList);
        delete arrayList;
        arrayList = nullptr;
    }
}

