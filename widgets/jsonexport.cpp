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
    settings = opt[getClassName(this)].toObject();

    settings[EXPORT_TITLE_KEY] = settings[EXPORT_TITLE_KEY].toString(EXPORT_TITLE);
    settings[EXPORT_PREFIX_LABEL_KEY] = settings[EXPORT_PREFIX_LABEL_KEY].toString(EXPORT_PREFIX_LABEL);
    settings[EXPORT_PREFIX_KEY] = settings[EXPORT_PREFIX_KEY].toString(EXPORT_PREFIX);
    settings[EXPORT_SAVE_KEY] = settings[EXPORT_SAVE_KEY].toString(EXPORT_SAVE);
    settings[EXPORT_CANCEL_KEY] = settings[EXPORT_CANCEL_KEY].toString(EXPORT_CANCEL);

    setWindowTitle(settings[EXPORT_TITLE_KEY].toString());
    ui->prefixBox->setTitle(settings[EXPORT_PREFIX_LABEL_KEY].toString());
    ui->prefixEdit->setText(settings[EXPORT_PREFIX_KEY].toString());
    ui->exportButton->setText(settings[EXPORT_SAVE_KEY].toString());
    ui->cancelButton->setText(settings[EXPORT_CANCEL_KEY].toString());
    settingsChanged(getClassName(this), settings);
}

JsonExport::~JsonExport()
{
    delete ui;
}
