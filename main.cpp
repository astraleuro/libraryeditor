#include <QCoreApplication>
#include <QString>
#include <QJsonDocument>
#include "modules/jsonbase.h"
#include "modules/fsprocessor.h"
#include "modules/filebase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileProcessor file;
    if (file.openFile("levels.json", QIODevice::ReadOnly)) {
        JsonBase base, schema;
        base.fromJson(QJsonDocument::fromJson(file.readAll()).object());
        file.close();
        if (file.openFile("schema.json", QIODevice::ReadOnly)) {
            schema.fromJson(QJsonDocument::fromJson(file.readAll()).object());
            file.close();
            if (base.isValid(schema)) {
                if (file.openFile("export.json", QIODevice::WriteOnly)) {
                    QJsonDocument jsonDocument(base.toJson());
                    file.write(jsonDocument.toJson());
                    file.close();
                }
            }
        }
        /*QJsonValue value = "Appended Value";
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
        path.clear();
        path << "obj1" << "arg3";
        base.move(0, base.indexOf(path), "arg3");
        if (file.openFile("levels_new.json", QIODevice::WriteOnly)) {
            QJsonDocument jsonDocument(base.toJson());
            file.write(jsonDocument.toJson());
            file.close();
        }
        DirProcessor files;
        files.openDir("load", "*.jpg|*,png", true);
        QStringList list = files.entryList();
        list.clear();*/
    }
    return a.exec();
}
