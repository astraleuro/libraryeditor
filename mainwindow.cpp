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
    errorsMsg[ERRORS_JOBISDONOT_DIALOG_KEY] = errorsMsg[ERRORS_JOBISDONOT_DIALOG_KEY].toString(ERRORS_JOBISDONOT_DIALOG);
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
    errorsMsg[ERRORS_JOBISDON_DIALOG_KEY] = errorsMsg[ERRORS_JOBISDON_DIALOG_KEY].toString(ERRORS_JOBISDON_DIALOG);
    errorsMsg[ERRORS_SAVE_BEFORE_KEY] = errorsMsg[ERRORS_SAVE_BEFORE_KEY].toString(ERRORS_SAVE_BEFORE);
    errorsMsg[ERRORS_MERGE_SAME_FILE_KEY] = errorsMsg[ERRORS_MERGE_SAME_FILE_KEY].toString(ERRORS_MERGE_SAME_FILE);
    errorsMsg[ERRORS_MERGE_ITEM_ADDED_KEY] = errorsMsg[ERRORS_MERGE_ITEM_ADDED_KEY].toString(ERRORS_MERGE_ITEM_ADDED);
    errorsMsg[ERRORS_MERGE_ITEM_CHANGED_KEY] = errorsMsg[ERRORS_MERGE_ITEM_CHANGED_KEY].toString(ERRORS_MERGE_ITEM_CHANGED);
    errorsMsg[ERRORS_MERGE_FILE_ADDED_KEY] = errorsMsg[ERRORS_MERGE_FILE_ADDED_KEY].toString(ERRORS_MERGE_FILE_ADDED);
    errorsMsg[ERRORS_MERGE_FILE_ADD_FAIL_KEY] = errorsMsg[ERRORS_MERGE_FILE_ADD_FAIL_KEY].toString(ERRORS_MERGE_FILE_ADD_FAIL);
    errorsMsg[ERRORS_MERGE_SUCCESS_KEY] = errorsMsg[ERRORS_MERGE_SUCCESS_KEY].toString(ERRORS_MERGE_SUCCESS);
    errorsMsg[ERRORS_MERGE_FAIL_KEY] = errorsMsg[ERRORS_MERGE_FAIL_KEY].toString(ERRORS_MERGE_FAIL);
    errorsMsg[ERRORS_MERGE_ITEM_SKIPPED_KEY] = errorsMsg[ERRORS_MERGE_ITEM_SKIPPED_KEY].toString(ERRORS_MERGE_ITEM_SKIPPED);
    errorsMsg[ERRORS_MERGE_SECTION_KEY] = errorsMsg[ERRORS_MERGE_SECTION_KEY].toString(ERRORS_MERGE_SECTION);
    errorsMsg[ERRORS_INVALID_SCHEMA_KEY] = errorsMsg[ERRORS_INVALID_SCHEMA_KEY].toString(ERRORS_INVALID_SCHEMA);
    errorsMsg[ERRORS_READ_FILE_KEY] = errorsMsg[ERRORS_READ_FILE_KEY].toString(ERRORS_READ_FILE);
    errorsMsg[ERRORS_CHECK_PATH_KEY] = errorsMsg[ERRORS_CHECK_PATH_KEY].toString(ERRORS_CHECK_PATH);
    errorsMsg[ERRORS_WRITE_FILE_KEY] = errorsMsg[ERRORS_WRITE_FILE_KEY].toString(ERRORS_WRITE_FILE);
    errorsMsg[ERRORS_CHECK_FILES_BEGIN_KEY] = errorsMsg[ERRORS_CHECK_FILES_BEGIN_KEY].toString(ERRORS_CHECK_FILES_BEGIN);
    errorsMsg[ERRORS_CHECK_FILES_SECTION_BEGIN_KEY] = errorsMsg[ERRORS_CHECK_FILES_SECTION_BEGIN_KEY].toString(ERRORS_CHECK_FILES_SECTION_BEGIN);
    errorsMsg[ERRORS_FILE_NOT_FOUND_KEY] = errorsMsg[ERRORS_FILE_NOT_FOUND_KEY].toString(ERRORS_FILE_NOT_FOUND);
    errorsMsg[ERRORS_NOT_FOUND_KEY] = errorsMsg[ERRORS_NOT_FOUND_KEY].toString(ERRORS_NOT_FOUND);
    errorsMsg[ERRORS_CHECK_ARTS_BEGIN_KEY] = errorsMsg[ERRORS_CHECK_ARTS_BEGIN_KEY].toString(ERRORS_CHECK_ARTS_BEGIN);
    errorsMsg[ERRORS_CHECK_ARTS_ERA_EMPTY_KEY] = errorsMsg[ERRORS_CHECK_ARTS_ERA_EMPTY_KEY].toString(ERRORS_CHECK_ARTS_ERA_EMPTY);
    errorsMsg[ERRORS_CHECK_ARTS_ERA_NOT_FOUND_KEY] = errorsMsg[ERRORS_CHECK_ARTS_ERA_NOT_FOUND_KEY].toString(ERRORS_CHECK_ARTS_ERA_NOT_FOUND);
    errorsMsg[ERRORS_CHECK_ARTS_AUTHORS_EMPTY_KEY] = errorsMsg[ERRORS_CHECK_ARTS_AUTHORS_EMPTY_KEY].toString(ERRORS_CHECK_ARTS_AUTHORS_EMPTY);
    errorsMsg[ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND_KEY] = errorsMsg[ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND_KEY].toString(ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND);
    errorsMsg[ERRORS_CHECK_ARTS_INFO_EMPTY_KEY] = errorsMsg[ERRORS_CHECK_ARTS_INFO_EMPTY_KEY].toString(ERRORS_CHECK_ARTS_INFO_EMPTY);
    errorsMsg[ERRORS_CHECK_AUTHORS_BEGIN_KEY] = errorsMsg[ERRORS_CHECK_AUTHORS_BEGIN_KEY].toString(ERRORS_CHECK_AUTHORS_BEGIN);
    errorsMsg[ERRORS_CHECK_AUTHORS_INFO_EMPTY_KEY] = errorsMsg[ERRORS_CHECK_AUTHORS_INFO_EMPTY_KEY].toString(ERRORS_CHECK_AUTHORS_INFO_EMPTY);
    errorsMsg[ERRORS_FOUND_KEY] = errorsMsg[ERRORS_FOUND_KEY].toString(ERRORS_FOUND);
    errorsMsg[ERRORS_DETAILS_KEY] = errorsMsg[ERRORS_DETAILS_KEY].toString(ERRORS_DETAILS);
    allSettings[ERRORS_SUBSECTION_KEY] = errorsMsg;

    settings[MAIN_WIDTH_KEY] = settings[MAIN_WIDTH_KEY].toInt(MAIN_WIDTH);
    settings[MAIN_HEIGHT_KEY] = settings[MAIN_HEIGHT_KEY].toInt(MAIN_HEIGHT);
    setMinimumSize(MAIN_WIDTH, MAIN_HEIGHT);
    setGeometry(x(), y(),
                settings[MAIN_WIDTH_KEY].toInt(),
                settings[MAIN_HEIGHT_KEY].toInt());

    connect(&logCollector, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    logCollector.initData(allSettings);

    setCentralWidget(new QWidget);
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);
    setWindowTitle(APPLICATION_NAME);
    showWelcomeScreen();
}

void MainWindow::openFile(QString fn)
{
    welcomeScreen->openFile(fn);
}

MainWindow::~MainWindow()
{
    if (isChanged) {
        if (itemList != nullptr) {
            switch (itemList->takeSection()) {
            case ArtsSection:
                jsonData[ARTS_KEY] = itemList->takeData();
                break;
            case AuthorsSection:
                jsonData[AUTHORS_KEY] = itemList->takeData();
                break;
            case ErasSection:
                jsonData[ERAS_KEY] = itemList->takeData();
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
                                errorsMsg[ERRORS_DATA_UNSAVED_KEY].toString() + jsonPath, QMessageBox::Close);
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
    connect(welcomeScreen, SIGNAL(dataReady(QString, QJsonObject&)), this, SLOT(showMainMenu(QString, QJsonObject&)));
    connect(welcomeScreen, SIGNAL(closeApp()), this, SLOT(closeApp()));
    welcomeScreen->initData(allSettings, defaultPath);
    mainLayout->addWidget(welcomeScreen);
}

void MainWindow::showMainMenu(QString fn, QJsonObject &data)
{
    jsonPath = fn;
    if (&jsonData != &data)
        jsonData = data;

    clearMainLayout();
    mainMenu = new MainMenu;
    connect(mainMenu, SIGNAL(goBack()), this, SLOT(showWelcomeScreen()));
    connect(mainMenu, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    connect(mainMenu, SIGNAL(showItemList(JsonDataSections)), this, SLOT(showItemList(JsonDataSections)));
    connect(mainMenu, SIGNAL(dataSaved()), this, SLOT(setSaved()));
    connect(mainMenu, SIGNAL(saveImages()), this, SLOT(saveImages()));
    connect(mainMenu, SIGNAL(dataMerged()), this, SLOT(updateData()));
    connect(mainMenu, SIGNAL(dataNotMerged()), this, SLOT(saveImages()));
    mainMenu->initData(&logCollector, jsonPath, jsonData, allSettings, isChanged);
    mainLayout->addWidget(mainMenu);
}

void MainWindow::showItemList(JsonDataSections sec)
{
    clearMainLayout();
    itemList = new ItemList;
    connect(itemList, SIGNAL(goBack()), this, SLOT(backFromItemList()));
    connect(itemList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SLOT(saveSettings(QString, QJsonObject)));
    connect(itemList, SIGNAL(readyForEras(QString)), this, SLOT(sendEras(QString)));
    connect(itemList, SIGNAL(readyForAuthors(QString)), this, SLOT(sendAuthors(QString)));
    connect(itemList, SIGNAL(dataChanged()), this, SLOT(setChanged()));
    connect(itemList, SIGNAL(removeAuthorsInArts(QString, QString)), this, SLOT(removeAuthorsInArts(QString, QString)));
    connect(itemList, SIGNAL(clearEraInArts(QString, QString)), this, SLOT(clearEraInArts(QString, QString)));
    connect(itemList, SIGNAL(changeKeyArgInArts(QString, QString, QString)), this, SLOT(changeKeyArgInArts(QString, QString, QString)));
    itemList->initData(jsonPath, jsonData, allSettings, sec);
    mainLayout->addWidget(itemList);
}

void MainWindow::saveSettings(QString key, QJsonObject keySettings)
{
    allSettings[key] = keySettings;
}

void MainWindow::backFromItemList()
{
    switch (itemList->takeSection()) {
    case ArtsSection:
        jsonData[ARTS_KEY] = itemList->takeData();
        break;
    case AuthorsSection:
        jsonData[AUTHORS_KEY] = itemList->takeData();
        break;
    case ErasSection:
        jsonData[ERAS_KEY] = itemList->takeData();
        break;
    }
    showMainMenu(jsonPath, jsonData);
}

void MainWindow::sendEras(QString key)
{
    QStringList eras = objectArrayToList(jsonData[ERAS_KEY].toArray(), key);
    itemList->sendEras(eras);
}

void MainWindow::sendAuthors(QString key)
{
    QStringList authors = objectArrayToList(jsonData[AUTHORS_KEY].toArray(), key);
    itemList->sendAuthors(authors);
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

void MainWindow::changeKeyArgInArts(QString prevArg, QString newArg, QString key)
{
    jsonData[ARTS_KEY] = changeKeyInObjectArray(prevArg, newArg, key, jsonData[ARTS_KEY].toArray());
}

void MainWindow::updateData()
{
    jsonData = mainMenu->takeData();
    saveImages();
    isChanged = true;
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
    if (mainMenu != nullptr) {
        mainLayout->removeWidget(mainMenu);
        delete mainMenu;
        mainMenu = nullptr;
    }
    if (itemList != nullptr) {
        mainLayout->removeWidget(itemList);
        delete itemList;
        itemList = nullptr;
    }
}

