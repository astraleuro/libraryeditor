#include "mainlist.h"
#include "ui_mainlist.h"

MainList::MainList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainList)
{
    ui->setupUi(this);
    ui->saveButton->setHiddenMenu(&exportMenu);

    connect(&exportDialog, SIGNAL(settingsChanged(QString, QJsonObject)), this, SIGNAL(saveSettings(QString, QJsonObject)));
}

void MainList::initData(QString fn, QJsonObject &data, QJsonObject &opt, bool changed)
{
    jsonPath = fn;
    allSettings = opt;
    jsonData = data;
    settings = opt[getClassName(this)].toObject();
    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();
    isChanged = changed;

    settings[ML_EXPORT_TO_JSON_KEY] = settings[ML_EXPORT_TO_JSON_KEY].toString(ML_EXPORT_TO_JSON);

    ui->filesInfo->setText(QString(DATAFILE_TITLE) + ": " + fileInfo(jsonPath));

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
                        errorsMsg[ERRORS_SAVE_BEFORE].toString(), QMessageBox::Save | QMessageBox::Ignore);
        msg.setModal(true);
        msg.exec();
        if (msg.result() == QMessageBox::Save) {
            saveImages();
            isChanged = false;
            dataSaved();
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
