#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

#include "defines.h"

enum LetterCase {
    NoModify,
    LowerCase,
    UpperCase
};

QString toNativeSeparators(QString path);
QString toTranslit(QString str, LetterCase letterCase = NoModify);
QString toValidFileName(QString fn, LetterCase letterCase = NoModify);
bool checkPath(QString path, bool mk = false);
bool readJson(QString path, QJsonObject& json, QJsonParseError &log);
bool writeJson(QString path, QJsonObject& json);
QString fileInfo(QString path);

#endif // FSPROCESSOR_H
