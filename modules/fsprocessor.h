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

#endif // FSPROCESSOR_H
