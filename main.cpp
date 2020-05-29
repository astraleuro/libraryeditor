#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QString dataPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/libraryeditor";
    for (QString arg : QApplication::arguments()) {
        if (arg == "--portable") {
            dataPath = QApplication::applicationDirPath();
            break;
        }
    }*/
    QString dataPath = QApplication::applicationDirPath();
    MainWindow w(dataPath);
    w.show();

    return a.exec();
}
