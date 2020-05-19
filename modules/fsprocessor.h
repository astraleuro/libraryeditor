#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QString>
#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QStringList>

enum LetterCase {
    NoModify,
    LowerCase,
    UpperCase
};

QString toTranslit(QString str, LetterCase letterCase = NoModify);
QString toValidFileName(QString fn, LetterCase letterCase = NoModify);

class FileProcessor : public QFile
{
public:
    bool openFile(QString path, OpenMode mode);
};

class DirProcessor : public QDir
{
public:
    bool openDir(QString path, QString extensions, bool mk = false);
};

#endif // FSPROCESSOR_H
