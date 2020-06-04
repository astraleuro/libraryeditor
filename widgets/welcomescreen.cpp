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
                if (writeJson(fn, json))
                    dataReady(fn, json);
            }
    }
}

void WelcomeScreen::openData()
{
    QJsonObject json;
    QFileDialog dialog(nullptr, OPENFILE_TITLE, "", BASE_EXTENSION_FILTER);
    dialog.setDefaultSuffix(BASE_EXTENSION);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setModal(true);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        QString fn = dialog.selectedFiles()[0];
        if (!fn.isEmpty())
            if (checkPath(fn) && checkPath(fn.left(fn.count() - QString(BASE_EXTENSION).count()))) {
                QJsonParseError log;
                if (readJson(fn, json, log))
                    if (log.error == QJsonParseError::NoError)
                        dataReady(fn, json);
            }
    }
}
