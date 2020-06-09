#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QDate>

#include "defines.h"
#include "modules/jsonprocessor.h"

enum LetterCase {
    NoModify,
    LowerCase,
    UpperCase
};

int filesCount(QString path);
QString fileCreated(QString path, QString format);
QString lastModified(QString path, QString format);
QString takeHumanReadableSize(int size);
QString toNativeSeparators(QString path);
QString toTranslit(QString str, LetterCase letterCase = NoModify);
QString toValidFileName(QString fn, LetterCase letterCase = NoModify);
QString toFileNameWithIndex(QString fn, QStringList paths);
QString takeFileExt(QString fn);
bool checkPath(QString path, bool mk = false);
bool readJson(QString path, QJsonObject& json, QJsonParseError &log);
bool writeJson(QString path, QJsonObject& json);
int fileSize(QString path);
int dirSize(QString path);
QString takeFileName(QString path);
QString takeDirPath(QString path);
QString takeValidSeparator(QString path);

#endif // FSPROCESSOR_H
