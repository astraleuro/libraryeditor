#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>

#include "defines.h"
#include "modules/fsprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool isPortable = false;
    QString assocFile = "";
    QStringList args = QApplication::arguments();
    for (int i = 1; i < args.count(); i++) {
        if (args[i].toLower() == "--portable")
            isPortable = true;
        else if (checkPath(args[i]))
            assocFile = args[i];
    }

    QString configPath;
    if (isPortable || takeFileName(QApplication::applicationFilePath()).toLower().contains("portable"))
        configPath = toNativeSeparators(QApplication::applicationDirPath());
    else
        configPath = toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));


    checkPath(configPath, true);
    MainWindow w(configPath);
    w.show();

    if (!assocFile.isEmpty())
        w.openFile(assocFile);

    return a.exec();
}
