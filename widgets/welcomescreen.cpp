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
    settings[WELCOME_LAST_PATH_KEY] = settings[WELCOME_LAST_PATH_KEY].toString(defaultPath);
    settings[WELCOME_CREATE_BUTTON_KEY] = settings[WELCOME_CREATE_BUTTON_KEY].toString(WELCOME_CREATE_BUTTON);
    settings[WELCOME_OPEN_BUTTON_KEY] = settings[WELCOME_OPEN_BUTTON_KEY].toString(WELCOME_OPEN_BUTTON);
    settings[WELCOME_LAST_BUTTON_KEY] = settings[WELCOME_LAST_BUTTON_KEY].toString(WELCOME_LAST_BUTTON);
    settings[WELCOME_EXIT_BUTTON_KEY] = settings[WELCOME_EXIT_BUTTON_KEY].toString(WELCOME_EXIT_BUTTON);

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

    settingsChanged(getClassName(this), settings);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::saveData()
{
    QJsonObject json;
    QFileDialog dialog(nullptr, SAVEFILE_TITLE, "", BASE_EXTENSION_FILTER);
    dialog.setDefaultSuffix(BASE_EXTENSION);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        QString fn = dialog.selectedFiles()[0];
        if (!fn.isEmpty())
            if (checkPath(fn.left(fn.count() - QString(BASE_EXTENSION).count()), true)) {
                json = initJsonObject();
                if (writeJson(fn, json)) {
                    settings[WELCOME_LAST_FILE_KEY] = fn;
                    settings[WELCOME_LAST_PATH_KEY] = takeDirPath(fn);
                    settingsChanged(getClassName(this), settings);
                    dataReady(fn, json);
                }
            }
    }
}

void WelcomeScreen::openData(QString fn)
{
    QJsonObject json;
    if (fn.isEmpty()) {
        QFileDialog dialog(nullptr, OPENFILE_TITLE, settings[WELCOME_LAST_PATH_KEY].toString(), BASE_EXTENSION_FILTER);;
        dialog.setDefaultSuffix(BASE_EXTENSION);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setModal(true);
        dialog.exec();
        if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
            fn = dialog.selectedFiles()[0];
            settings[WELCOME_LAST_PATH_KEY] = takeDirPath(fn);
        }
    }
    if (!fn.isEmpty())
        if (checkPath(fn) && checkPath(takeDirPath(fn))) {
            QJsonParseError log;
            if (readJson(fn, json, log))
                if (log.error == QJsonParseError::NoError) {
                    settings[WELCOME_LAST_FILE_KEY] = fn;
                    settingsChanged(getClassName(this), settings);
                    dataReady(fn, json);
                }
        }
}

void WelcomeScreen::on_openLastBase_clicked()
{
    openData(settings[WELCOME_LAST_FILE_KEY].toString());
}
