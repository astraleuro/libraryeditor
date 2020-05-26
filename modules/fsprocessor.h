#ifndef FSPROCESSOR_H
#define FSPROCESSOR_H

#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

#include "modules/database/jsonbase.h"

enum LetterCase {
    NoModify,
    LowerCase,
    UpperCase
};

QString toTranslit(QString str, LetterCase letterCase = NoModify);
QString toValidFileName(QString fn, LetterCase letterCase = NoModify);
bool checkPath(QString path, bool mk = false);
bool readJson(QString path, QJsonObject& json, QJsonParseError &log);
bool readJson(QString path, JsonBase& base, QJsonParseError &log);
bool writeJson(QString path, QJsonObject json);

#endif // FSPROCESSOR_H
