#ifndef LOGCOLLECTOR_H
#define LOGCOLLECTOR_H

#include <QDialog>

#include "defines.h"
#include "templates.h"
#include "modules/jsonprocessor.h"

namespace Ui {
class LogCollector;
}

class LogCollector : public QDialog
{
    Q_OBJECT

public:
    explicit LogCollector(QWidget *parent = nullptr);
    void initData(QJsonObject &opt);
    void fillLog(QStringList list);
    ~LogCollector();

signals:
    void settingsChanged(QString, QJsonObject);

private slots:
    void on_closeButton_clicked();

private:
    Ui::LogCollector *ui;
    QJsonObject settings;
};

#endif // LOGCOLLECTOR_H
