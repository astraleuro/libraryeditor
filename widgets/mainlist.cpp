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

void MainList::initData(QString fn, QJsonObject &data, QJsonObject &opt, bool changed)
{
    jsonPath = fn;
    allSettings = opt;
    jsonData = data;
    settings = opt[getClassName(this)].toObject();
    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();
    isChanged = changed;
    jsonFile = fn;

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
    if (!isValidDateFormat(settings[ML_FILE_DATE_FORMAT_KEY].toString()))
        settings[ML_FILE_DATE_FORMAT_KEY] = ML_FILE_DATE_FORMAT;


    ui->saveButton->setText(settings[ML_SAVE_BUTTON_KEY].toString());
    ui->mergeButton->setText(settings[ML_MERGE_BUTTON_KEY].toString());

    if (settings[ARTS_KEY].toString().isEmpty()) {
        settings[ARTS_KEY] = ARTS_LABEL;
        ui->artsButton->setText(QString(ARTS_LABEL) +
                                " (" + QString::number(data[ARTS_KEY].toArray().count()) + ")");
    } else
        ui->artsButton->setText(settings[ARTS_KEY].toString() +
                                " (" + QString::number(data[ARTS_KEY].toArray().count()) + ")");

    if (settings[AUTHORS_KEY].toString().isEmpty()) {
        settings[AUTHORS_KEY] = AUTHORS_LABEL;
        ui->authorsButton->setText(QString(AUTHORS_LABEL) +
                                   " (" + QString::number(data[AUTHORS_KEY].toArray().count()) + ")");
    } else
        ui->authorsButton->setText(settings[AUTHORS_KEY].toString() +
                                   " (" + QString::number(data[AUTHORS_KEY].toArray().count()) + ")");

    if (settings[ERAS_KEY].toString().isEmpty()) {
        settings[ERAS_KEY] = ERAS_LABEL;
        ui->erasButton->setText(QString(ERAS_LABEL) +
                                " (" + QString::number(data[ERAS_KEY].toArray().count()) + ")");
    } else
        ui->erasButton->setText(settings[ERAS_KEY].toString() +
                                " (" + QString::number(data[ERAS_KEY].toArray().count()) + ")");

    updateInfo();

    exportAction = exportMenu.addAction(settings[ML_EXPORT_TO_JSON_KEY].toString(), this, SLOT(exportToJson()));

    exportDialog.initData(fn, data, opt);

    settingsChanged(getClassName(this), settings);
}

MainList::~MainList()
{
    settingsChanged(getClassName(this), settings);
    delete exportAction;
    delete ui;
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
}

void MainList::mergeFiles()
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
                QJsonParseError log;
                if (readJson(fn, json, log))
                    if (log.error == QJsonParseError::NoError) {
                        settings[WELCOME_LAST_FILE_KEY] = fn;
                        settings[WELCOME_LAST_PATH_KEY] = takeDirPath(fn);
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
            saveImages();
            QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                            errorsMsg[ERRORS_DATA_SAVED_KEY].toString(), QMessageBox::Close);
            msg.setModal(true);
            msg.exec();
            isChanged = false;
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
        mergeFiles();
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
            mergeFiles();
        }
    }
}
