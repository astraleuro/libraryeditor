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

    filterTable->setVisible(false);
    connect(tableWidget, SIGNAL(showFilter(bool)), this, SLOT(showFilter(bool)));
    connect(tableWidget, SIGNAL(showIndex(bool)), this, SLOT(showIndex(bool)));
    connect(tableWidget, SIGNAL(initFilterHeader(QStringList)), this, SLOT(initFilterHeader(QStringList)));
    connect(tableWidget->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(colResize(int, int, int)));
    connect(filterTable->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), tableWidget, SLOT(colResize(int, int, int)));

    QFont font;
    QFontMetrics metrics(font);
    backButton->setMinimumWidth(metrics.horizontalAdvance(backButton->text()) + ADDITIONAL_WIDTH);
    backButton->setMaximumWidth(backButton->minimumWidth());

    doBarLayout->addWidget(backButton);
    doBarLayout->addWidget(saveButton);
    doBarLayout->addWidget(findText);
    doBarLayout->addWidget(findButton);

    //doBarLayout->addWidget(headerLabel);
    doBarLayout->addWidget(addButton);
    doBarLayout->addWidget(chgButton);
    doBarLayout->addWidget(delButton);
    doBarLayout->setStretch(0, 0);
    //doBarLayout->setStretch(2, 1);

    //filterLayout->addWidget(new QLabel("Фильтр:"));
    filterLayout->addWidget(filterTable);
    filterLayout->setStretch(0, 0);

    tableWidget->setSettings(settings[SETTINGS_TABLEWIDGET].toObject());
    tableWidget->setBasePath(dataPath + DATABASE_PATH + "/");
    tableWidget->connectBase(mainBase, mainSchema);
    tableWidget->showData();

    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(doBarLayout);
    mainLayout->setStretch(0, 0);
    mainLayout->setStretch(1, 1);
    mainLayout->setStretch(2, 0);

    //setStatusBar(statusBar);
    setMouseTracking(false);
}

MainWindow::~MainWindow()
{
    settings[SETTINGS_TABLEWIDGET] = tableWidget->takeSettings();

    writeJson(dataPath + SETTINGS_PATH + SETTINGS_FILE, settings);
    writeJson(dataPath + DATABASE_PATH + DATABASE_FILE, mainBase->toJson());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size()) {
        /*if (filterTable->horizontalScrollBar()->isHidden())
            filterTable->setMaximumHeight(filterTable->horizontalHeader()->height() +
                                              filterTable->rowHeight(0) + 40);*/
    }
    QMainWindow::resizeEvent(event);
}

void MainWindow::setStatusText(QString text)
{
    statusBar->showMessage(text, 5000);
}

void MainWindow::initFilterHeader(QStringList labels)
{
    filterTable->setRowCount(1);
    filterTable->setColumnCount(labels.count());
    filterTable->setHorizontalHeaderLabels(labels);
    filterTable->setMaximumHeight(filterTable->horizontalHeader()->height() +
                                          filterTable->rowHeight(0) + 25);
    filterTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void MainWindow::showFilter(bool what)
{
    filterTable->setVisible(what);
}

void MainWindow::showIndex(bool what)
{
    if (what) {
        if (filterTable->verticalHeaderItem(0) != nullptr)
            filterTable->verticalHeaderItem(0)->setText("*");
        else
            filterTable->setVerticalHeaderItem(0, new QTableWidgetItem(""));
    } else {
        if (filterTable->verticalHeaderItem(0) != nullptr)
            filterTable->verticalHeaderItem(0)->setText("");
        else
            filterTable->setVerticalHeaderItem(0, new QTableWidgetItem(""));
    }
}

void MainWindow::colResize(int col, int oldWidth, int newWidth)
{
    if (oldWidth != newWidth)
        filterTable->setColumnWidth(col, newWidth);
}

