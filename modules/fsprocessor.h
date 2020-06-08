#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QRegExp>
#include <QFile>
#include <QDir>

#include "defines.h"
#include "modules/jsonprocessor.h"

enum LetterCase {
    NoModify,
    LowerCase,
    UpperCase
};

QString toNativeSeparators(QString path);
QString toTranslit(QString str, LetterCase letterCase = NoModify);
QString toValidFileName(QString fn, LetterCase letterCase = NoModify);
QString toFileNameWithIndex(QString fn, QStringList paths);
QString takeFileExt(QString fn);
bool checkPath(QString path, bool mk = false);
bool readJson(QString path, QJsonObject& json, QJsonParseError &log);
bool writeJson(QString path, QJsonObject& json);
QString fileInfo(QString path);
QString takeFileName(QString path);
QString takeDirPath(QString path);

#endif // FSPROCESSOR_H
