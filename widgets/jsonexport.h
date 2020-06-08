#ifndef JSONEXPORT_H
#define JSONEXPORT_H

#include <QDialog>

#include "defines.h"
#include "templates.h"
#include "modules/jsonprocessor.h"
#include "modules/fsprocessor.h"

namespace Ui {
class JsonExport;
}

class JsonExport : public QDialog
{
    Q_OBJECT

public:
    explicit JsonExport(QWidget *parent = nullptr);
    void initData(QString fn, QJsonObject &data, QJsonObject &opt);
    ~JsonExport();

signals:
    void settingsChanged(QString, QJsonObject);

private:
    Ui::JsonExport *ui;
    QJsonObject settings, errorsMsg;
};

#endif // JSONEXPORT_H
