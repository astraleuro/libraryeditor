#include "mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent) : QMainWindow(parent)
{
    dataPath = path;

    QDir *dir = new QDir;
    if (!dir->exists(path))
        dir->mkpath(path);
    QString settingsPath = path + SETTINGS_FILE;
    if (dir->exists(settingsPath)) {
        QFile fl;
        fl.setFileName(settingsPath);
        if (fl.open(QIODevice::ReadOnly)) {
            QJsonDocument json;
            QJsonParseError jsonErrors;
            json = QJsonDocument::fromJson(fl.readAll(), &jsonErrors);
            fl.close();
            if (jsonErrors.error == QJsonParseError::NoError)
                settings = json.object();
        }
    }

    QString basePath = path + DATABASE_PATH;
    if (!dir->exists(basePath))
        dir->mkpath(basePath);
    basePath += DATABASE_FILE;
    if (dir->exists(settingsPath)) {
        QFile fl;
        fl.setFileName(settingsPath);
        if (fl.open(QIODevice::ReadOnly)) {
            QJsonDocument json;
            QJsonParseError jsonErrors;
            json = QJsonDocument::fromJson(fl.readAll(), &jsonErrors);
            fl.close();
            if (jsonErrors.error == QJsonParseError::NoError)
                settings = json.object();
        }
    }
    delete dir;

    mainLayout = new QVBoxLayout();
    setCentralWidget(new QWidget());
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);
    mainLayout->addWidget(new TableWidget());
}

MainWindow::~MainWindow()
{
    QFile fl;
    fl.setFileName(dataPath + SETTINGS_PATH + SETTINGS_FILE);
    if (fl.open(QIODevice::WriteOnly)) {
        QJsonDocument json(settings);
        fl.write(json.toJson());
        fl.close();
    }
    fl.setFileName(dataPath + DATABASE_PATH + DATABASE_FILE);
    if (fl.open(QIODevice::WriteOnly)) {
        QJsonDocument json(mainBase->toJson());
        fl.write(json.toJson());
        fl.close();
    }
    delete mainLayout;
    delete centralWidget();
    delete mainBase;
}

