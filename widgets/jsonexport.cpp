#include "jsonexport.h"
#include "ui_jsonexport.h"

JsonExport::JsonExport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JsonExport)
{
    ui->setupUi(this);
}

JsonExport::~JsonExport()
{
    delete ui;
}
