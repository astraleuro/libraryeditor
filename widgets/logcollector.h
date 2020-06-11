#ifndef LOGCOLLECTOR_H
#define LOGCOLLECTOR_H

#include <QDialog>

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

private:
    Ui::LogCollector *ui;
};

#endif // LOGCOLLECTOR_H
