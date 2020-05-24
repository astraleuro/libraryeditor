#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include "widgets/tablewidget.h"
#include "modules/database/jsonbase.h"
#include "modules/fsprocessor.h"

#define SETTINGS_FILE "/settings.json"
#define SETTINGS_PATH ""
#define DATABASE_FILE "/database.json"
#define DATABASE_PATH "/database"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString path, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString dataPath;
    JsonBase *mainBase = new JsonBase;
    QJsonObject settings;
    QLayout *mainLayout = NULL;
};
#endif // MAINWINDOW_H
