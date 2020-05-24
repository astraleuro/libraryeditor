#ifndef FILEBASE_H
#define FILEBASE_H

#include <QString>
#include <QVector>

#include "../fsprocessor.h"

#define FILE_EXTENSIONS "*.jpg|*.png";

class FileBase
{
public:
    FileBase();
    bool open(QString path, bool mk = false);
private:
    //FileProcessor file;
    //DirProcessor dir;
};

#endif // FILEBASE_H
