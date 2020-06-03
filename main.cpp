#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDir>

#include "defines.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir configPath;
    configPath.setPath(QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)));
    MainWindow w(QDir::toNativeSeparators(configPath.path() + "/" + CONFIG_FILE));
    w.show();
    return a.exec();
}
