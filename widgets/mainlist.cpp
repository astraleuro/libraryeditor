#include "mainlist.h"
#include "ui_mainlist.h"

MainList::MainList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainList)
{
    ui->setupUi(this);

    connect(ui->goBackButton, SIGNAL(clicked()), this, SIGNAL(goBack()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SIGNAL(saveData()));
}

void MainList::initData(QString fn, QJsonObject &data, QJsonObject &opt)
{
    jsonPath = fn;
    allSettings = opt;
    settings = allSettings[getClassName(this)].toObject();

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

}

MainList::~MainList()
{
    settingsChanged(getClassName(this), settings);
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
