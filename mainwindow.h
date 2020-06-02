#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>

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

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void setBackButtonState(bool state) {backButton->setEnabled(state);};
    void setStatusText(QString text);
    void initFilterHeader(QStringList labels);
    void showFilter(bool what);
    void showIndex(bool what);
    void colResize(int col, int oldWidth, int newWidth);

private:
    QString dataPath;
    JsonBase *mainBase = new JsonBase;
    JsonBase *mainSchema = new JsonBase;
    QJsonObject settings;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *doBarLayout = new QHBoxLayout;
    QVBoxLayout *filterLayout = new QVBoxLayout;
    TableWidget *tableWidget = new TableWidget();
    QPushButton *backButton = new QPushButton("<");
    QTableWidget *filterTable = new QTableWidget;
    QLabel *headerLabel = new QLabel();
    QStatusBar *statusBar = new QStatusBar;
    QPushButton *addButton = new QPushButton("&Добавить");
    QPushButton *delButton = new QPushButton("&Удалить");
    QPushButton *chgButton = new QPushButton("&Изменить");
    QPushButton *findButton = new QPushButton("&Поиск");
    QPushButton *saveButton = new QPushButton("&Сохранить");
    QLineEdit *findText = new QLineEdit();
};
#endif // MAINWINDOW_H
