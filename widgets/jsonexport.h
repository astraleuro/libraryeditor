#ifndef JSONEXPORT_H
#define JSONEXPORT_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>

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

private slots:
    void on_exportButton_clicked();
    void on_cancelButton_clicked();

protected:
    void resizeEvent(QResizeEvent *event);
    void saveImage(QString inPath, QString outPath);

private:
    Ui::JsonExport *ui;
    QJsonObject jsonData, settings, errorsMsg;
    QString fileName;
};

#endif // JSONEXPORT_H
