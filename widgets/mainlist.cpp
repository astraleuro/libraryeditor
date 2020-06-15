#include "mainlist.h"
#include "ui_mainlist.h"

MainList::MainList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainList)
{
    ui->setupUi(this);
    ui->saveButton->setHiddenMenu(&exportMenu);

    connect(&exportDialog, SIGNAL(settingsChanged(QString, QJsonObject)), this, SIGNAL(settingsChanged(QString, QJsonObject)));

}

void MainList::initData(LogCollector *logDialog, QString fn, QJsonObject &data, QJsonObject &opt, bool changed)
{
    jsonPath = fn;
    allSettings = opt;
    jsonData = data;
    settings = opt[getClassName(this)].toObject();
    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();
    isChanged = changed;
    jsonFile = fn;
    logCollector = logDialog;

    settings[ML_EXPORT_TO_JSON_KEY] = settings[ML_EXPORT_TO_JSON_KEY].toString(ML_EXPORT_TO_JSON);
    settings[ML_SAVE_BUTTON_KEY] = settings[ML_SAVE_BUTTON_KEY].toString(ML_SAVE_BUTTON);
    settings[ML_MERGE_BUTTON_KEY] = settings[ML_MERGE_BUTTON_KEY].toString(ML_MERGE_BUTTON);
    settings[MERGE_OPENFILE_TITLE_KEY] = settings[MERGE_OPENFILE_TITLE_KEY].toString(MERGE_OPENFILE_TITLE);
    settings[ML_FILE_LABEL_KEY] = settings[ML_FILE_LABEL_KEY].toString(ML_FILE_LABEL);
    settings[ML_FILE_CREATED_LABEL_KEY] = settings[ML_FILE_CREATED_LABEL_KEY].toString(ML_FILE_CREATED_LABEL);
    settings[ML_FILE_MODIFIED_LABEL_KEY] = settings[ML_FILE_MODIFIED_LABEL_KEY].toString(ML_FILE_MODIFIED_LABEL);
    settings[ML_FILE_SIZE_LABEL_KEY] = settings[ML_FILE_SIZE_LABEL_KEY].toString(ML_FILE_SIZE_LABEL);
    settings[ML_FILES_LABEL_KEY] = settings[ML_FILES_LABEL_KEY].toString(ML_FILES_LABEL);
    settings[ML_FILE_DATE_FORMAT_KEY] = settings[ML_FILE_DATE_FORMAT_KEY].toString(ML_FILE_DATE_FORMAT);
    settings[ARTS_KEY] = settings[ARTS_KEY].toString(ARTS_LABEL);
    settings[AUTHORS_KEY] = settings[AUTHORS_KEY].toString(AUTHORS_LABEL);
    settings[ERAS_KEY] = settings[ERAS_KEY].toString(ERAS_LABEL);
    if (!isValidDateFormat(settings[ML_FILE_DATE_FORMAT_KEY].toString()))
        settings[ML_FILE_DATE_FORMAT_KEY] = ML_FILE_DATE_FORMAT;


    ui->saveButton->setText(settings[ML_SAVE_BUTTON_KEY].toString());
    ui->mergeButton->setText(settings[ML_MERGE_BUTTON_KEY].toString());

    updateInfo();

    exportAction = exportMenu.addAction(settings[ML_EXPORT_TO_JSON_KEY].toString(), this, SLOT(exportToJson()));

    exportDialog.initData(fn, data, opt);

    settingsChanged(getClassName(this), settings);
}

QJsonObject MainList::takeData()
{
    return jsonData;
}

MainList::~MainList()
{
    settingsChanged(getClassName(this), settings);
    delete exportAction;
    delete ui;
}

bool MainList::checkFiles(QStringList &list)
{
    bool isOk, isAllOk = true;
    QString path = toNativeSeparators(jsonFile.left(jsonFile.count() - takeFileExt(jsonFile).count() - 1) + "/");
    QStringList files;
    QStringList flSections = QString(FILE_SECTION_KEY).split(SEPARATOR);
    QStringList arrSections = QString(ARRAY_SECTION_KEY).split(SEPARATOR);
    list.append(errorsMsg[ERRORS_CHECK_FILES_BEGIN_KEY].toString());
    QString sub;
    for (int i = 0; i < 3; i++) {
        list.append("");
        isOk = true;
        switch (i) {
        case 0:
            list.append(errorsMsg[ERRORS_CHECK_FILES_SECTION_BEGIN_KEY].toString() + " \"" + settings[ARTS_KEY].toString() + "\":");
            sub = toNativeSeparators(QString(ARTS_KEY) + "/");
            break;
        case 1:
            list.append(errorsMsg[ERRORS_CHECK_FILES_SECTION_BEGIN_KEY].toString() + " \"" + settings[AUTHORS_KEY].toString() + "\":");
            sub = toNativeSeparators(QString(AUTHORS_KEY) + "/");
            break;
        case 2:
            list.append(errorsMsg[ERRORS_CHECK_FILES_SECTION_BEGIN_KEY].toString() + " \"" + settings[ERAS_KEY].toString() + "\":");
            sub = toNativeSeparators(QString(ERAS_KEY) + "/");
            break;
        }
        files = takeListByObjectKey(flSections[i], jsonData[arrSections[i]].toArray());
        for (int j = 0; j < files.count(); j++)
            if (!checkPath(path + sub + files[j])) {
                list.append(errorsMsg[ERRORS_FILE_NOT_FOUND_KEY].toString() + " - " + files[j]);
                isOk = false;
                isAllOk = false;
            }
        if (isOk)
            list.append(errorsMsg[ERRORS_NOT_FOUND_KEY].toString());
    }
    list.append("");
    return isAllOk;
}

bool MainList::checkAuthors(QStringList &list)
{
    bool isOk = true;
    QJsonArray authors = jsonData[AUTHORS_KEY].toArray();
    QJsonObject author;
    list.append(errorsMsg[ERRORS_CHECK_AUTHORS_BEGIN_KEY].toString());
    for (int i = 0; i < authors.count(); i++) {
        author = authors[i].toObject();
        if (author[AUTHORS_INFO_KEY].toString().isEmpty()) {
            list.append("\"" + author[AUTHORS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_AUTHORS_INFO_EMPTY_KEY].toString());
            isOk = false;
        }
    }
    if (isOk) {
        list.append(errorsMsg[ERRORS_NOT_FOUND_KEY].toString());
    }
    list.append("");
    return isOk;
}

bool MainList::checkArts(QStringList &list)
{
    bool isOk = true;
    QJsonArray arts = jsonData[ARTS_KEY].toArray();
    QStringList eras = takeListByObjectKey(ERAS_NAME_KEY, jsonData[ERAS_KEY].toArray());
    QStringList authors = takeListByObjectKey(AUTHORS_NAME_KEY, jsonData[AUTHORS_KEY].toArray());
    QString artEra;
    QStringList artAuthors;
    QJsonObject art;
    list.append(errorsMsg[ERRORS_CHECK_ARTS_BEGIN_KEY].toString());
    for (int i = 0; i < arts.count(); i++) {
        art = arts[i].toObject();
        artEra = art[ARTS_ERA_KEY].toString();
        artAuthors = stringArrayToList(art[ARTS_AUTHORS_KEY].toArray());
        if (artEra.isEmpty()) {
            list.append("\"" + art[ARTS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_ARTS_ERA_EMPTY_KEY].toString());
            isOk = false;
        } else {
            if (!eras.contains(artEra)) {
                list.append("\"" + art[ARTS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_ARTS_ERA_NOT_FOUND_KEY].toString() +
                            " \"" + artEra + "\"");
                isOk = false;
            }
        }
        if (artAuthors.isEmpty()) {
            list.append("\"" + art[ARTS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_ARTS_AUTHORS_EMPTY_KEY].toString());
            isOk = false;
        } else {
            for (int j = 0; j < artAuthors.count(); j++) {
                if (!authors.contains(artAuthors[j])) {
                    list.append("\"" + art[ARTS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_ARTS_AUTHOR_NOT_FOUND_KEY].toString() +
                                " \"" + artAuthors[j] + "\"");
                    isOk = false;
                }
            }
        }
        if (art[ARTS_INFO_KEY].toString().isEmpty()) {
            list.append("\"" + art[ARTS_NAME_KEY].toString() + "\" - " + errorsMsg[ERRORS_CHECK_ARTS_INFO_EMPTY_KEY].toString());
            isOk = false;
        }
    }
    if (isOk)
        list.append(errorsMsg[ERRORS_NOT_FOUND_KEY].toString());
    list.append("");
    return isOk;
}

bool MainList::isCheck()
{
    check.clear();
    if (checkArts(check) & checkAuthors(check) & checkFiles(check))
        return true;
    else
        return false;
}

void MainList::updateInfo()
{
    ui->pathInfo->setText(takeDirPath(jsonFile));
    QString path = toNativeSeparators(takeDirPath(jsonFile) + "/" +
                                      takeFileName(jsonFile.left(jsonFile.count() - takeFileExt(jsonFile).count() - 1)) + "/");
    QString info = settings[ML_FILE_LABEL_KEY].toString() + ": " + takeFileName(jsonFile) + "\n" +
        settings[ML_FILE_SIZE_LABEL_KEY].toString() + ": " + takeHumanReadableSize(fileSize(jsonFile)) + "\n" +
        settings[ML_FILE_CREATED_LABEL_KEY].toString() + ": " + fileCreated(jsonFile, ML_FILE_DATE_FORMAT) + "\n" +
        settings[ML_FILE_MODIFIED_LABEL_KEY].toString() + ": " + lastModified(jsonFile, ML_FILE_DATE_FORMAT) + "\n" +
        settings[ARTS_KEY].toString() + ": " + QString::number(filesCount(path + ARTS_KEY)) + " " + settings[ML_FILES_LABEL_KEY].toString() + ", " +
        takeHumanReadableSize(dirSize(path + ARTS_KEY)) + "\n" +
        settings[AUTHORS_KEY].toString() + ": " + QString::number(filesCount(path + AUTHORS_KEY)) + " " + settings[ML_FILES_LABEL_KEY].toString() + ", " +
        takeHumanReadableSize(dirSize(path + AUTHORS_KEY)) + "\n" +
        settings[ERAS_KEY].toString() + ": " + QString::number(filesCount(path + ERAS_KEY)) + " " + settings[ML_FILES_LABEL_KEY].toString() + ", " +
        takeHumanReadableSize(dirSize(path + ERAS_KEY));

    ui->filesInfo->setText(info);
    ui->artsButton->setText(settings[ARTS_KEY].toString() +
                                " (" + QString::number(jsonData[ARTS_KEY].toArray().count()) + ")");
    ui->authorsButton->setText(settings[AUTHORS_KEY].toString() +
                                " (" + QString::number(jsonData[AUTHORS_KEY].toArray().count()) + ")");
    ui->erasButton->setText(settings[ERAS_KEY].toString() +
                                " (" + QString::number(jsonData[ERAS_KEY].toArray().count()) + ")");

    if (isCheck()) {
        ui->checkInfo->setText(errorsMsg[ERRORS_NOT_FOUND_KEY].toString());
    } else {
        ui->checkInfo->setText(errorsMsg[ERRORS_FOUND_KEY].toString() + " <a href=\"details\">" + errorsMsg[ERRORS_DETAILS_KEY].toString() + "</a>");
    }
}

void MainList::merge()
{
    QString fn;
    QJsonObject json;
    QFileDialog dialog(nullptr, settings[MERGE_OPENFILE_TITLE_KEY].toString(),
                       settings[WELCOME_LAST_PATH_KEY].toString(), BASE_EXTENSION_FILTER);
    dialog.setDefaultSuffix(BASE_EXTENSION);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty())
        fn = dialog.selectedFiles()[0];
    if (!fn.isEmpty()) {
        if (fn != jsonFile) {
            if (checkPath(fn) && checkPath(takeDirPath(fn))) {
                QJsonParseError jsonLog;
                if (readJson(fn, json, jsonLog))
                    if (jsonLog.error == QJsonParseError::NoError) {
                        log.clear();
                        QStringList filePathKeys = QString(FILE_SECTION_KEY).split(SEPARATOR);
                        QStringList uniqueByKey = QString(UNIQUE_SECTION_KEY).split(SEPARATOR);
                        QString newestByKey = NEWESTBY_SECTION_KEY;
                        QString out = jsonFile.left(jsonFile.count() - takeFileExt(jsonFile).count() - 1);
                        fn = fn.left(fn.count() - takeFileExt(fn).count() - 1);
                        QJsonObject mergeData;
                        log.clear();
                        log.append(errorsMsg[ERRORS_MERGE_SECTION_KEY].toString() + " \"" + settings[ARTS_KEY].toString() + "\":");
                        mergeData[ARTS_KEY] = mergeArrays(
                                    toNativeSeparators(fn + "/" + ARTS_KEY + "/"),
                                    toNativeSeparators(out + "/"),
                                    ARTS_KEY,
                                    filePathKeys[0], uniqueByKey[0], newestByKey,
                                    json[ARTS_KEY].toArray(), jsonData[ARTS_KEY].toArray());
                        log.append("");
                        log.append(errorsMsg[ERRORS_MERGE_SECTION_KEY].toString() + " \"" + settings[AUTHORS_KEY].toString() + "\":");
                        mergeData[AUTHORS_KEY] = mergeArrays(
                                    toNativeSeparators(fn + "/" + AUTHORS_KEY + "/"),
                                    toNativeSeparators(out + "/"),
                                    AUTHORS_KEY,
                                    filePathKeys[1], uniqueByKey[1], newestByKey,
                                    json[AUTHORS_KEY].toArray(), jsonData[AUTHORS_KEY].toArray());
                        log.append("");
                        log.append(errorsMsg[ERRORS_MERGE_SECTION_KEY].toString() + " \"" + settings[AUTHORS_KEY].toString() + "\":");
                        mergeData[ERAS_KEY] = mergeArrays(
                                    toNativeSeparators(fn + "/" + ERAS_KEY + "/"),
                                    toNativeSeparators(out + "/"),
                                    ERAS_KEY,
                                    filePathKeys[2], uniqueByKey[2], newestByKey,
                                    json[ERAS_KEY].toArray(), jsonData[ERAS_KEY].toArray());
                        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(), "",
                                        QMessageBox::Yes | QMessageBox::Close);
                        msg.setModal(true);
                        if (isMergeOk) {
                            isMerged = true;
                            jsonData = mergeData;
                            dataMerged();
                            updateInfo();
                            msg.setText(errorsMsg[ERRORS_MERGE_SUCCESS_KEY].toString());
                            msg.exec();
                            isChanged = true;
                        } else {
                            msg.setIcon(QMessageBox::Critical);
                            msg.setText(errorsMsg[ERRORS_MERGE_FAIL_KEY].toString());
                            msg.exec();
                            dataNotMerged();
                        }
                        if (msg.result() == QMessageBox::Yes) {
                            logCollector->fillLog(log);
                            logCollector->setModal(false);
                            if (!logCollector->isVisible())
                                logCollector->show();
                        }

                    }
            }
        } else {
            QMessageBox msg(QMessageBox::Critical, errorsMsg[ERRORS_TITLE_KEY].toString(),
                            errorsMsg[ERRORS_MERGE_SAME_FILE_KEY].toString(), QMessageBox::Close);
            msg.setModal(true);
            msg.exec();
        }
    }
}

QJsonArray MainList::mergeArrays(QString inPath, QString outPath, QString secSuffix,
                                 QString filePathKey, QString uniqueByKey, QString newestByKey,
                                 QJsonArray inArr, QJsonArray outArr)
{
    QString tmpPath = toNativeSeparators(outPath + "." + secSuffix + "/");
    outPath = toNativeSeparators(outPath + secSuffix + "/");
    QStringList outPaths({outPath, tmpPath});
    QString outFn;
    QJsonObject obj;

    checkPath(tmpPath, true);

    isMergeOk = true;
    bool isFileAdd;
    int existIndex;
    for (int i = 0; i < inArr.count(); i++) {
        isFileAdd = true;
        existIndex = indexOfObjectByKey(uniqueByKey,inArr[i].toObject()[uniqueByKey].toString(), outArr);
        obj = inArr[i].toObject();
        outFn = toFileNameWithIndex(obj[filePathKey].toString(), outPaths);
        obj[filePathKey] = outFn;
        if (existIndex == -1) {
            log.append(errorsMsg[ERRORS_MERGE_ITEM_ADDED_KEY].toString() + " - " + obj[uniqueByKey].toString());
            outArr.append(obj);
        } else if (obj[newestByKey].toString() > outArr[existIndex].toObject()[newestByKey].toString()) {
            log.append(errorsMsg[ERRORS_MERGE_ITEM_CHANGED_KEY].toString() + " - " + obj[uniqueByKey].toString());
            outArr[existIndex] = obj;
        } else {
            log.append(errorsMsg[ERRORS_MERGE_ITEM_SKIPPED_KEY].toString() + " - " + obj[uniqueByKey].toString());
            isFileAdd = false;
        }
        if (isFileAdd) {
            if (copyFile(inPath + inArr[i].toObject()[filePathKey].toString(), tmpPath + outFn))
                log.append(errorsMsg[ERRORS_MERGE_FILE_ADDED_KEY].toString() + " - " + outFn);
            else {
                log.append(errorsMsg[ERRORS_MERGE_FILE_ADD_FAIL_KEY].toString() + " - " + outFn);
                isMergeOk = false;
            }
        }
    }
    return outArr;
}


void MainList::on_artsButton_clicked()
{
    showArrayList(ArtsSection);
}

void MainList::on_authorsButton_clicked()
{
    showArrayList(AuthorsSection);
}

void MainList::on_erasButton_clicked()
{
    showArrayList(ErasSection);
}

void MainList::on_saveButton_clicked()
{
    if (isChanged) {
        if (writeJson(jsonPath, jsonData)) {
            saveImages();            if (isMerged)
                dataMerged();
            QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                            errorsMsg[ERRORS_DATA_SAVED_KEY].toString(), QMessageBox::Close);
            msg.setModal(true);
            msg.exec();
            isChanged = false;
            isMerged = false;
            dataSaved();
            updateInfo();
        } else {
            QMessageBox msg(QMessageBox::Critical, errorsMsg[ERRORS_TITLE_KEY].toString(),
                            errorsMsg[ERRORS_DATA_UNSAVED_KEY].toString(), QMessageBox::Close);
            msg.setModal(true);
            msg.exec();
        }
    } else {
        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                        errorsMsg[ERRORS_ALREADY_SAVED_KEY].toString(), QMessageBox::Close);
        msg.setModal(true);
        msg.exec();
    }
}

void MainList::on_goBackButton_clicked()
{
    if (isChanged) {
        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                        errorsMsg[ERRORS_DATA_CHANGED_KEY].toString(), QMessageBox::Save | QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
        if (msg.result() == QMessageBox::Save)
            on_saveButton_clicked();
    }
    goBack();
}

void MainList::exportToJson()
{
    if (!isChanged) {
        exportDialog.setModal(true);
        exportDialog.exec();
    } else {
        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                        errorsMsg[ERRORS_SAVE_BEFORE_KEY].toString(), QMessageBox::Save | QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
        if (msg.result() == QMessageBox::Save) {
            saveImages();
            isChanged = false;
            dataSaved();
            updateInfo();
            exportDialog.setModal(true);
            exportDialog.exec();
        }
    }
}

void MenuButton::setHiddenMenu(QMenu *m)
{
    menu = m;
}

void MenuButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if (e->button() == Qt::RightButton && menu != nullptr)
        menu->popup(e->globalPos());
}

void MainList::on_mergeButton_clicked()
{
    if (!isChanged) {
        merge();
    } else {
        QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                        errorsMsg[ERRORS_SAVE_BEFORE_KEY].toString(), QMessageBox::Save | QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
        if (msg.result() == QMessageBox::Save) {
            saveImages();
            isChanged = false;
            dataSaved();
            updateInfo();
            merge();
        }
    }
}

void MainList::on_checkInfo_linkActivated(const QString &link)
{
    UNUSED(link);
    logCollector->fillLog(check);
    if (!logCollector->isVisible())
        logCollector->show();
}
