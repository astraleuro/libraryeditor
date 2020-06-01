#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>

#include <QFont>
#include <QFontMetrics>

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
#define SCHEMA_FILE "/schema.json"
#define SCHEMA_PATH "/database"

#define SETTINGS_TABLEWIDGET "maintable"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString path, QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void setBackButtonState(bool state) {backButton->setEnabled(state);};
    void setStatusText(QString text);

private:
    QString dataPath;
    JsonBase *mainBase = new JsonBase;
    JsonBase *mainSchema = new JsonBase;
    QJsonObject settings;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topBarLayout = new QHBoxLayout;
    TableWidget *tableWidget = new TableWidget();
    QPushButton *backButton = new QPushButton("<");
    QLabel *headerLabel = new QLabel();
    QStatusBar *statusBar = new QStatusBar;
};
#endif // MAINWINDOW_H
