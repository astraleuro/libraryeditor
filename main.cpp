#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>

#include "defines.h"
#include "modules/fsprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString configPath;
    if (!QApplication::arguments().contains("--portable"))
        configPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    else
        configPath = QDir::toNativeSeparators(QApplication::applicationDirPath());

    checkPath(configPath, true);
    MainWindow w(QDir::toNativeSeparators(configPath + "/" + CONFIG_FILE));
    w.show();

    return a.exec();
}
