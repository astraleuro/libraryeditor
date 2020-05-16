#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QString>
#include <QRegExp>
#include <QFile>
#include <QDir>

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
    bool open(QString path, OpenMode mode);
};

class DirProcessor : public QDir
{

};

#endif // FSPROCESSOR_H
