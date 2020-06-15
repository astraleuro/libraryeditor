#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);

    connect(ui->createBase, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(ui->openBase, SIGNAL(clicked()), this, SLOT(openData()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SIGNAL(closeApp()));

    ui->programName->setText(PROGRAM_NAME);
}

void WelcomeScreen::initData(QJsonObject &opt, QString defaultPath)
{
    settings = opt[getClassName(this)].toObject();
    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();
    settings[WELCOME_LAST_PATH_KEY] = settings[WELCOME_LAST_PATH_KEY].toString(defaultPath);
    settings[WELCOME_CREATE_BUTTON_KEY] = settings[WELCOME_CREATE_BUTTON_KEY].toString(WELCOME_CREATE_BUTTON);
    settings[WELCOME_OPEN_BUTTON_KEY] = settings[WELCOME_OPEN_BUTTON_KEY].toString(WELCOME_OPEN_BUTTON);
    settings[WELCOME_LAST_BUTTON_KEY] = settings[WELCOME_LAST_BUTTON_KEY].toString(WELCOME_LAST_BUTTON);
    settings[WELCOME_EXIT_BUTTON_KEY] = settings[WELCOME_EXIT_BUTTON_KEY].toString(WELCOME_EXIT_BUTTON);
    settings[WELCOME_OPENFILE_TITLE_KEY] = settings[WELCOME_OPENFILE_TITLE_KEY].toString(WELCOME_OPENFILE_TITLE);
    settings[WELCOME_SAVEFILE_TITLE_KEY] = settings[WELCOME_SAVEFILE_TITLE_KEY].toString(WELCOME_SAVEFILE_TITLE);


    ui->createBase->setText(settings[WELCOME_CREATE_BUTTON_KEY].toString());
    ui->openBase->setText(settings[WELCOME_OPEN_BUTTON_KEY].toString());
    ui->closeButton->setText(settings[WELCOME_EXIT_BUTTON_KEY].toString());

    QString lastFile = settings[WELCOME_LAST_FILE_KEY].toString();
    if (!lastFile.isEmpty() && checkPath(lastFile)) {
        ui->openLastBase->setText(settings[WELCOME_LAST_BUTTON_KEY].toString() + takeFileName(lastFile));
        ui->openLastBase->setVisible(true);
    } else {
        ui->openLastBase->setVisible(false);
        settings[WELCOME_LAST_FILE_KEY] = "";
    }

    if (!checkPath(settings[WELCOME_LAST_PATH_KEY].toString()))
        settings[WELCOME_LAST_PATH_KEY] = defaultPath;

}

void WelcomeScreen::openFile(QString fn)
{
    openData(fn);
}

WelcomeScreen::~WelcomeScreen()
{
    settingsChanged(getClassName(this), settings);
    delete ui;
}

void WelcomeScreen::showMsg(QMessageBox::Icon icon, QString text)
{
    QMessageBox msg(icon, errorsMsg[ERRORS_TITLE_KEY].toString(), text, QMessageBox::Close);
    msg.setModal(true);
    msg.exec();
}

void WelcomeScreen::saveData()
{
    QString dir;
    QJsonObject json;
    QFileDialog dialog(nullptr, settings[WELCOME_SAVEFILE_TITLE_KEY].toString(),
                       settings[WELCOME_LAST_PATH_KEY].toString(), BASE_EXTENSION_FILTER);
    dialog.setDefaultSuffix(BASE_EXTENSION);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        QString fn = dialog.selectedFiles()[0];
        if (!fn.isEmpty()) {
            dir = fn.left(fn.count() - QString(BASE_EXTENSION).count());
            if (checkPath(toNativeSeparators(dir + "/" + ARTS_KEY), true) &&
                checkPath(toNativeSeparators(dir + "/" + AUTHORS_KEY), true) &&
                checkPath(toNativeSeparators(dir + "/" + ERAS_KEY), true)) {
                json = initJsonObject();
                if (writeJson(fn, json)) {
                    settings[WELCOME_LAST_FILE_KEY] = fn;
                    settings[WELCOME_LAST_PATH_KEY] = takeDirPath(fn);
                    dataReady(fn, json);
                } else {
                    showMsg(QMessageBox::Critical, errorsMsg[ERRORS_DATA_UNSAVED_KEY].toString() + fn);
                }
            } else {
                showMsg(QMessageBox::Critical, errorsMsg[ERRORS_CHECK_PATH_KEY].toString());
            }
        }
    }
}

void WelcomeScreen::openData(QString fn)
{
    QJsonObject json;
    if (fn.isEmpty()) {
        QFileDialog dialog(nullptr, settings[WELCOME_OPENFILE_TITLE_KEY].toString(),
                           settings[WELCOME_LAST_PATH_KEY].toString(), BASE_EXTENSION_FILTER);;
        dialog.setDefaultSuffix(BASE_EXTENSION);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setModal(true);
        dialog.exec();
        if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty())
            fn = dialog.selectedFiles()[0];
    }
    if (!fn.isEmpty()) {
        QString dir = toNativeSeparators(fn.left(fn.count() - takeFileExt(fn).count() - 1) + "/");
        if (checkPath(fn) &&
                checkPath(dir + ARTS_KEY, true) &&
                checkPath(dir + AUTHORS_KEY, true) &&
                checkPath(dir + ERAS_KEY, true)) {
            QJsonParseError log;
            if (readJson(fn, json, log)) {
                if (log.error == QJsonParseError::NoError) {
                    QJsonObject schema;
                    readJson(RESOURCE_SCHEMA, schema, log);
                    if (isValidSchema(json, schema)) {
                        settings[WELCOME_LAST_FILE_KEY] = fn;
                        settings[WELCOME_LAST_PATH_KEY] = takeDirPath(fn);
                        dataReady(fn, json);
                    } else {
                        showMsg(QMessageBox::Critical, errorsMsg[ERRORS_INVALID_SCHEMA_KEY].toString());
                    }
                } else {
                    showMsg(QMessageBox::Critical, log.errorString());
                }
            } else {
                showMsg(QMessageBox::Critical, errorsMsg[ERRORS_READ_FILE_KEY].toString());
            }
        } else {
            showMsg(QMessageBox::Critical, errorsMsg[ERRORS_CHECK_PATH_KEY].toString());
        }
    }
}

void WelcomeScreen::on_openLastBase_clicked()
{
    openData(settings[WELCOME_LAST_FILE_KEY].toString());
}
