#include "jsonexport.h"
#include "ui_jsonexport.h"

JsonExport::JsonExport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JsonExport)
{
    ui->setupUi(this);
}

void JsonExport::initData(QString fn, QJsonObject &data, QJsonObject &opt)
{
    fileName = fn;
    jsonData = data;
    settings = opt[getClassName(this)].toObject();

    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();

    settings[EXPORT_TITLE_KEY] = settings[EXPORT_TITLE_KEY].toString(EXPORT_TITLE);
    settings[EXPORT_PREFIX_LABEL_KEY] = settings[EXPORT_PREFIX_LABEL_KEY].toString(EXPORT_PREFIX_LABEL);
    settings[EXPORT_PREFIX_KEY] = settings[EXPORT_PREFIX_KEY].toString(EXPORT_PREFIX);
    settings[EXPORT_SAVE_KEY] = settings[EXPORT_SAVE_KEY].toString(EXPORT_SAVE);
    settings[EXPORT_CANCEL_KEY] = settings[EXPORT_CANCEL_KEY].toString(EXPORT_CANCEL);
    settings[EXPORT_ANNOTATION_KEY] = settings[EXPORT_ANNOTATION_KEY].toString(EXPORT_ANNOTATION);
    settings[EXPORT_FILE_DIALOG_TITLE_KEY] = settings[EXPORT_FILE_DIALOG_TITLE_KEY].toString(EXPORT_FILE_DIALOG_TITLE);
    settings[EXPORT_ANNOTATION_KEY] = settings[EXPORT_ANNOTATION_KEY].toString(EXPORT_ANNOTATION);
    settings[EXPORT_WIDTH_KEY] = settings[EXPORT_WIDTH_KEY].toInt(EXPORT_WIDTH);
    settings[EXPORT_HEIGHT_KEY] = settings[EXPORT_HEIGHT_KEY].toInt(EXPORT_HEIGHT);

    setWindowTitle(settings[EXPORT_TITLE_KEY].toString());
    ui->prefixBox->setTitle(settings[EXPORT_PREFIX_LABEL_KEY].toString());
    ui->prefixEdit->setText(settings[EXPORT_PREFIX_KEY].toString());
    ui->exportButton->setText(settings[EXPORT_SAVE_KEY].toString());
    ui->cancelButton->setText(settings[EXPORT_CANCEL_KEY].toString());
    ui->label->setText(settings[EXPORT_ANNOTATION_KEY].toString());

    setGeometry(x(), y(),
                settings[EXPORT_WIDTH_KEY].toInt(),
                settings[EXPORT_HEIGHT_KEY].toInt());

    settingsChanged(getClassName(this), settings);
}

JsonExport::~JsonExport()
{
    delete ui;
}

void JsonExport::on_exportButton_clicked()
{
    bool isNotOk = true;
    QString dir;
    QJsonObject json;
    QFileDialog dialog(nullptr, settings[EXPORT_FILE_DIALOG_TITLE_KEY].toString(),
                       "", "*" + QString(JSON_EXTENSION));
    if (checkPath(settings[EXPORT_LAST_PATH_KEY].toString()))
        dialog.setDirectory(settings[EXPORT_LAST_PATH_KEY].toString());
    dialog.setDefaultSuffix(JSON_EXTENSION);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        QString fn = dialog.selectedFiles()[0];
        if (!fn.isEmpty()) {
            dir = takeDirPath(fn);
            if (checkPath(toNativeSeparators(dir + "/" + ARTS_KEY), true) &&
                checkPath(toNativeSeparators(dir + "/" + AUTHORS_KEY), true) &&
                checkPath(toNativeSeparators(dir + "/" + ERAS_KEY), true)) {
                QString pathPrefix = ui->prefixEdit->text();
                QString separator = takeValidSeparator(ui->prefixEdit->text());
                jsonData[ARTS_KEY] = modifyObjectsKeyInArray(pathPrefix + separator + ARTS_KEY + separator,
                            QString(FILE_SECTION_KEY).split(SEPARATOR)[0],
                            jsonData[ARTS_KEY].toArray());
                jsonData[AUTHORS_KEY] = modifyObjectsKeyInArray(pathPrefix + separator + AUTHORS_KEY + separator,
                            QString(FILE_SECTION_KEY).split(SEPARATOR)[1],
                            jsonData[AUTHORS_KEY].toArray());
                jsonData[ERAS_KEY] = modifyObjectsKeyInArray(pathPrefix + separator + ERAS_KEY + separator,
                            QString(FILE_SECTION_KEY).split(SEPARATOR)[2],
                            jsonData[ERAS_KEY].toArray());

                saveImage(fileName, fn);

                if (writeJson(fn, jsonData)) {
                    isNotOk = false;
                    QMessageBox msg(QMessageBox::Information, errorsMsg[ERRORS_TITLE_KEY].toString(),
                                    errorsMsg[ERRORS_JOBISDON_DIALOG_KEY].toString(), QMessageBox::Close);
                    msg.setModal(true);
                    msg.exec();
                    close();
                }
            }
        }
    }
    if (isNotOk) {
        QMessageBox msg(QMessageBox::Critical, errorsMsg[ERRORS_TITLE_KEY].toString(),
                        errorsMsg[ERRORS_JOBISDONOT_DIALOG_KEY].toString(), QMessageBox::Close);
        msg.setModal(true);
        msg.exec();
        close();
    }
}

void JsonExport::on_cancelButton_clicked()
{
    settingsChanged(getClassName(this), settings);
    close();
}

void JsonExport::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    if (event->oldSize() != event->size()) {
        settings[EXPORT_WIDTH_KEY] = width();
        settings[EXPORT_HEIGHT_KEY] = height();
    }
}

void JsonExport::saveImage(QString inPath, QString outPath)
{
    inPath = takeDirPath(inPath) + "/" + takeFileName(inPath);
    inPath = toNativeSeparators(inPath.left(inPath.count() - takeFileExt(inPath).count() - 1) + "/");
    outPath = toNativeSeparators(takeDirPath(outPath) + "/");
    QDir dir;
    QFile file;
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks | QDir::Files);
    QStringList secs = {ARTS_KEY, AUTHORS_KEY, ERAS_KEY};
    QString inFile, outFile;
    for (int i = 0; i < secs.count(); i++) {
        dir.setPath(inPath + secs[i]);
        inFile = toNativeSeparators(inPath + secs[i] + "/");
        outFile = toNativeSeparators(outPath + secs[i] + "/");
        checkPath(outFile, true);
        for (int j = 0; (uint)j < dir.count(); j++)
            file.copy(inFile + dir[j], outFile + dir[j]);
    }
}
