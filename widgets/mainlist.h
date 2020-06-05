#ifndef MAINLIST_H
#define MAINLIST_H

#include <QWidget>
#include "templates.h"
#include "defines.h"

#include "modules/fsprocessor.h"

namespace Ui {
class MainList;
}

class MainList : public QWidget
{
    Q_OBJECT

public:
    explicit MainList(QWidget *parent = nullptr);
    void initData(QString fn, QJsonObject &data, QJsonObject &opt);
    ~MainList();

protected:
    QJsonObject takeSettings();

signals:
    void settingsChanged(QString, QJsonObject);
    void goBack();
    void showArrayList(JsonDataSections section);
    void saveData();

private slots:
    void on_artsButton_clicked();
    void on_authorsButton_clicked();
    void on_erasButton_clicked();

private:
    Ui::MainList *ui;
    QJsonObject allSettings, settings;
    QString jsonPath;
};

#endif // MAINLIST_H
