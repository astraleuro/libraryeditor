#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include "widgets/tablewidget.h"
#include "widgets/tabledelegate.h"

#include "modules/database/jsonbase.h"
#include "modules/fsprocessor.h"

#define SETTINGS_FILE "/settings.json"
#define SETTINGS_PATH ""
#define DATABASE_FILE "/database.json"
#define DATABASE_PATH "/database"
#define SCHEMA_FILE "/schema.json"
#define SCHEMA_PATH "/database"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString path, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString dataPath;
    JsonBase *mainBase = new JsonBase;
    JsonBase *mainSchema = new JsonBase;
    QJsonObject settings;
    QLayout *mainLayout = NULL;
    TableWidget *tableWidget;
    TableDelegate *tableDelegate;
};
#endif // MAINWINDOW_H
