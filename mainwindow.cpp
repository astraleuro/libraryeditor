#include "mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent) : QMainWindow(parent)
{
    setGeometry(0,0,700,500);

    dataPath = path;
    QJsonParseError jsonLog;
    if (checkPath(dataPath + SETTINGS_PATH, true))
        readJson(dataPath + SETTINGS_PATH + SETTINGS_FILE, settings, jsonLog);
    if (checkPath(dataPath + DATABASE_PATH, true))
        readJson(dataPath + DATABASE_PATH + DATABASE_FILE, *mainBase, jsonLog);
    if (checkPath(dataPath + SCHEMA_PATH, true))
        readJson(dataPath + SCHEMA_PATH + SCHEMA_FILE, *mainSchema, jsonLog);

    setCentralWidget(new QWidget());
    delete centralWidget()->layout();
    centralWidget()->setLayout(mainLayout);

    backButton->setEnabled(false);
    connect(tableWidget, SIGNAL(backExist(bool)), this, SLOT(setBackButtonState(bool)));
    connect(backButton, SIGNAL(released()), tableWidget, SLOT(goBack()));

    QFont font;
    QFontMetrics metrics(font);
    backButton->setMinimumWidth(metrics.horizontalAdvance(backButton->text()) + ADDITIONAL_WIDTH);
    backButton->setMaximumWidth(backButton->minimumWidth());

    topBarLayout->addWidget(backButton);
    topBarLayout->addWidget(headerLabel);
    topBarLayout->setStretch(0, 0);
    topBarLayout->setStretch(1, 1);

    tableWidget->setSettings(settings[SETTINGS_TABLEWIDGET].toObject());
    tableWidget->setBasePath(dataPath + DATABASE_PATH + "/");
    tableWidget->connectBase(mainBase, mainSchema);
    tableWidget->showData();

    mainLayout->addLayout(topBarLayout);
    mainLayout->addWidget(tableWidget);

    //setStatusBar(statusBar);
    setMouseTracking(false);
}

MainWindow::~MainWindow()
{
    settings[SETTINGS_TABLEWIDGET] = tableWidget->takeSettings();

    writeJson(dataPath + SETTINGS_PATH + SETTINGS_FILE, settings);
    writeJson(dataPath + DATABASE_PATH + DATABASE_FILE, mainBase->toJson());
}

void MainWindow::setStatusText(QString text)
{
    statusBar->showMessage(text, 5000);
}

