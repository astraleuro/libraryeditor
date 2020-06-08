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

    errorsMsg[ERRORS_SAVE_BEFORE_KEY] = errorsMsg[ERRORS_SAVE_BEFORE_KEY].toString(ERRORS_SAVE_BEFORE);
    errorsMsg[ERRORS_ALREADY_SAVED_KEY] = errorsMsg[ERRORS_ALREADY_SAVED_KEY].toString(ERRORS_ALREADY_SAVED);
    errorsMsg[ERRORS_SAVE_CONFIG_KEY] = errorsMsg[ERRORS_SAVE_CONFIG_KEY].toString(ERRORS_SAVE_CONFIG);
    errorsMsg[ERRORS_FILE_ON_BASESUBDIR_KEY] = errorsMsg[ERRORS_FILE_ON_BASESUBDIR_KEY].toString(ERRORS_FILE_ON_BASESUBDIR);
    errorsMsg[ERRORS_FILE_ALREADY_EXIST_KEY] = errorsMsg[ERRORS_FILE_ALREADY_EXIST_KEY].toString(ERRORS_FILE_ALREADY_EXIST);
    errorsMsg[ERRORS_CHECK_PREFIX_KEY] = errorsMsg[ERRORS_CHECK_PREFIX_KEY].toString(ERRORS_CHECK_PREFIX);
    errorsMsg[ERRORS_ITEM_ALREADY_EXIST_KEY] = errorsMsg[ERRORS_ITEM_ALREADY_EXIST_KEY].toString(ERRORS_ITEM_ALREADY_EXIST);
    errorsMsg[ERRORS_DATA_SAVED_KEY] = errorsMsg[ERRORS_DATA_SAVED_KEY].toString(ERRORS_DATA_SAVED);
    errorsMsg[ERRORS_DATA_UNSAVED_KEY] = errorsMsg[ERRORS_DATA_UNSAVED_KEY].toString(ERRORS_DATA_UNSAVED);
    errorsMsg[ERRORS_DATA_CHANGED_KEY] = errorsMsg[ERRORS_DATA_CHANGED_KEY].toString(ERRORS_DATA_CHANGED);
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
    if (isChanged) {
        if (arrayList != nullptr) {
            switch (arrayList->takeSection()) {
            case ArtsSection:
                jsonData[ARTS_KEY] = arrayList->takeData();
                break;
            case AuthorsSection:
                jsonData[AUTHORS_KEY] = arrayList->takeData();
                break;
            case ErasSection:
                jsonData[ERAS_KEY] = arrayList->takeData();
                break;
            }
        }
        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                            errorsMsg[ERRORS_DATA_CHANGED_KEY].toString(), QMessageBox::Save | QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
        if (msg.result() == QMessageBox::Save) {
            if (writeJson(jsonPath, jsonData)) {
                saveImages();
                QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                                errorsMsg[ERRORS_DATA_SAVED_KEY].toString(), QMessageBox::Close);
                msg.setModal(true);
                msg.exec();
            } else {
                QMessageBox msg(QMessageBox::Critical, errorsMsg[ERRORS_TITLE_KEY].toString(),
                                errorsMsg[ERRORS_DATA_UNSAVED_KEY].toString(), QMessageBox::Close);
                msg.setModal(true);
                msg.exec();
            }
        }
    }
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
    isChanged = false;
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
    connect(mainList, SIGNAL(dataSaved()), this, SLOT(setSaved()));
    connect(mainList, SIGNAL(saveImages()), this, SLOT(saveImages()));
    mainList->initData(jsonPath, jsonData, allSettings, isChanged);
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
    connect(arrayList, SIGNAL(dataChanged()), this, SLOT(setChanged()));
    connect(arrayList, SIGNAL(removeAuthorsInArts(QString, QString)), this, SLOT(removeAuthorsInArts(QString, QString)));
    connect(arrayList, SIGNAL(clearEraInArts(QString, QString)), this, SLOT(clearEraInArts(QString, QString)));
    arrayList->initData(jsonPath, jsonData, allSettings, sec);
    mainLayout->addWidget(arrayList);
}

void MainWindow::saveSettings(QString key, QJsonObject keySettings)
{
    allSettings[key] = keySettings;
}

void MainWindow::backFromArrayList()
{
    switch (arrayList->takeSection()) {
    case ArtsSection:
        jsonData[ARTS_KEY] = arrayList->takeData();
        break;
    case AuthorsSection:
        jsonData[AUTHORS_KEY] = arrayList->takeData();
        break;
    case ErasSection:
        jsonData[ERAS_KEY] = arrayList->takeData();
        break;
    }
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

void MainWindow::setSaved()
{
    isChanged = false;
}

void MainWindow::setChanged()
{
    isChanged = true;
}

void MainWindow::saveImages()
{
    QString imagesPath = toNativeSeparators(jsonPath.left(jsonPath.count() - takeFileExt(jsonPath).count() - 1) + "/");
    QDir dir;
    QFile file;
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks | QDir::Files);
    QStringList inPaths = {"." + QString(ARTS_KEY), "." + QString(AUTHORS_KEY), "." + QString(ERAS_KEY)};
    QStringList outPaths = {ARTS_KEY, AUTHORS_KEY, ERAS_KEY};
    for (int i = 0; i < inPaths.count(); i++) {
        dir.setPath(imagesPath + inPaths[i]);
        for (int j = 0; (uint)j < dir.count(); j++) {
            file.copy(toNativeSeparators(dir.path() + "/" + dir[j]), toNativeSeparators(imagesPath + outPaths[i] + "/" + dir[j]));
            file.remove(toNativeSeparators(dir.path() + "/" + dir[j]));
        }
    }

    dir.setPath(imagesPath);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden);
    for (QString sub : inPaths)
        dir.rmpath(imagesPath + sub);

    removeUnused(imagesPath);
}

void MainWindow::removeAuthorsInArts(QString subkey, QString key)
{
    jsonData[ARTS_KEY] = removeKeyInObjectArray(subkey, key, jsonData[ARTS_KEY].toArray());
}

void MainWindow::clearEraInArts(QString subkey, QString key)
{
    jsonData[ARTS_KEY] = clearKeyInObjectArray(subkey, key, jsonData[ARTS_KEY].toArray());
}

void MainWindow::removeUnused(QString path)
{
    QJsonArray items;
    QStringList subs = {ARTS_KEY, AUTHORS_KEY, ERAS_KEY};
    QStringList secs = QString(FILE_SECTION_KEY).split(SEPARATOR);
    QStringList subImages;
    QDir dir;
    QFile file;
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks | QDir::Files);
    for (int j = 0; j < subs.count(); j++) {
        dir.setPath(path + subs[j]);
        items = jsonData[subs[j]].toArray();
        subImages = takeListByObjectKey(secs[j], items);
        for (int i = 0; (uint)i < dir.count(); i++) {
            if (!subImages.contains(dir[i]))
                file.remove(toNativeSeparators(dir.path() + "/" + dir[i]));
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (event->oldSize() != event->size()) {
        settings[MAIN_WIDTH_KEY] = width();
        settings[MAIN_HEIGHT_KEY] = height();
    }
}

void MainWindow::clearMainLayout()
{
    if (welcomeScreen != nullptr) {
        mainLayout->removeWidget(welcomeScreen);
        delete welcomeScreen;
        welcomeScreen = nullptr;
    }
    if (mainList != nullptr) {
        mainLayout->removeWidget(mainList);
        delete mainList;
        mainList = nullptr;
    }
    if (arrayList != nullptr) {
        mainLayout->removeWidget(arrayList);
        delete arrayList;
        arrayList = nullptr;
    }
}

