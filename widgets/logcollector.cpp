#include "logcollector.h"
#include "ui_logcollector.h"

LogCollector::LogCollector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogCollector)
{
    ui->setupUi(this);
}

void LogCollector::initData(QJsonObject &opt)
{
    settings = opt[getClassName(this)].toObject();

    settings[LOG_TITLE_KEY] = settings[LOG_TITLE_KEY].toString(LOG_TITLE);
    settings[LOG_CLOSE_KEY] = settings[LOG_CLOSE_KEY].toString(LOG_CLOSE);

    setWindowTitle(settings[LOG_TITLE_KEY].toString());
    ui->closeButton->setText(settings[LOG_CLOSE_KEY].toString());

    settingsChanged(getClassName(this), settings);
}

void LogCollector::fillLog(QStringList list)
{
    ui->logList->clear();
    ui->logList->addItems(list);
}

LogCollector::~LogCollector()
{
    delete ui;
}

void LogCollector::on_closeButton_clicked()
{
    close();
}
