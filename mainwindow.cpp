#include "mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent) : QMainWindow(parent)
{
    dataPath = path;
    QJsonParseError jsonLog;
    if (checkPath(dataPath + SETTINGS_PATH, true))
        readJson(dataPath + SETTINGS_PATH + SETTINGS_FILE, settings, jsonLog);
    if (checkPath(dataPath + DATABASE_PATH, true))
        readJson(dataPath + DATABASE_PATH + DATABASE_FILE, *mainBase, jsonLog);
    if (checkPath(dataPath + SCHEMA_PATH, true))
        readJson(dataPath + SCHEMA_PATH + SCHEMA_FILE, *mainSchema, jsonLog);

    mainLayout = new QVBoxLayout();
    setCentralWidget(new QWidget());
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);

    tableWidget = new TableWidget();
    tableDelegate = new TableDelegate();
    tableWidget->setItemDelegate(tableDelegate);

    tableWidget->connectBase(mainBase, mainSchema);
    tableWidget->showData(QStringList());

    mainLayout->addWidget(tableWidget);
}

MainWindow::~MainWindow()
{
    writeJson(dataPath + SETTINGS_PATH + SETTINGS_FILE, settings);
    writeJson(dataPath + DATABASE_PATH + DATABASE_FILE, mainBase->toJson());
    delete tableWidget;
    delete tableDelegate;
    delete mainLayout;
    delete centralWidget();
    delete mainBase;
}

