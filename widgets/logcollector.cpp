#include "logcollector.h"
#include "ui_logcollector.h"

LogCollector::LogCollector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogCollector)
{
    ui->setupUi(this);
}

LogCollector::~LogCollector()
{
    delete ui;
}
