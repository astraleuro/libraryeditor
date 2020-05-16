#include <QCoreApplication>
#include <QString>
#include <QJsonDocument>
#include "modules/jsonbase.h"
#include "modules/fsprocessor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileProcessor file;
    if (file.open("levels.json", QIODevice::ReadOnly)) {
        JsonBase base;
        base.fromJson(QJsonDocument::fromJson(file.readAll()).object());
        file.close();
        QJsonValue value = "Appended Value";
        QStringList path;
        path << "obj1" << "array2" << "1";
        base.append(value, path);
        path.clear();
        path << "obj1" << "array2" << "0";
        base.remove(path);
        path.clear();
        path << "obj1" << "arg1";
        base.remove(path);
        path.clear();
        path << "array2";
        base.append(value, path);
        path.clear();
        path << "arg1";
        base.remove(path);
        if (file.open("levels_new.json", QIODevice::WriteOnly)) {
            QJsonDocument jsonDocument(base.toJson());
            file.write(jsonDocument.toJson());
            file.close();
        }
    }
    return a.exec();
}
