#include "modules/fsprocessor.h"

QString toValidFileName(QString fn, LetterCase letterCase)
{
    QString ext = fn.right(fn.length() - fn.lastIndexOf('.') - 1);
    fn = fn.left(fn.length() - ext.length() - 1);
    fn = toTranslit(fn, letterCase).
            replace(' ', '_').
            remove(QRegExp("[^a-zA-Z0-9\\_\\-]"));
    ext = toTranslit(ext, letterCase).
            replace(' ', '_').
            remove(QRegExp("[^a-zA-Z0-9\\_\\-]"));
    fn += "." + ext;
    return fn;
}

QString toTranslit(QString str, LetterCase letterCase)
{
    QString tr;
    if (LowerCase == letterCase)
        str = str.toLower();
    else if (UpperCase == letterCase)
        str = str.toUpper();
    for (int i = 0; i < str.length(); i++) {
        switch (str[i].unicode()) {
        case 1072: /*а*/ tr += "a"; break;
        case 1073: /*б*/ tr += "b"; break;
        case 1074: /*в*/ tr += "v"; break;
        case 1075: /*г*/ tr += "g"; break;
        case 1076: /*д*/ tr += "d"; break;
        case 1077: /*е*/ tr += "e"; break;
        case 1105: /*ё*/ tr += "e"; break;
        case 1078: /*ж*/ tr += "zh"; break;
        case 1079: /*з*/ tr += "z"; break;
        case 1080: /*и*/ tr += "i"; break;
        case 1082: /*к*/ tr += "k"; break;
        case 1083: /*л*/ tr += "l"; break;
        case 1084: /*м*/ tr += "m"; break;
        case 1085: /*н*/ tr += "n"; break;
        case 1086: /*о*/ tr += "o"; break;
        case 1087: /*п*/ tr += "p"; break;
        case 1088: /*р*/ tr += "r"; break;
        case 1089: /*с*/ tr += "s"; break;
        case 1090: /*т*/ tr += "t"; break;
        case 1091: /*у*/ tr += "u"; break;
        case 1092: /*ф*/ tr += "f"; break;
        case 1093: /*х*/ tr += "kh"; break;
        case 1094: /*ц*/ tr += "c"; break;
        case 1095: /*ч*/ tr += "ch"; break;
        case 1096: /*ш*/ tr += "sh"; break;
        case 1097: /*щ*/ tr += "shch"; break;
        case 1098: /*ъ*/ tr += ""; break;
        case 1099: /*ы*/ tr += "y"; break;
        case 1100: /*ь*/ tr += ""; break;
        case 1101: /*э*/ tr += "e"; break;
        case 1102: /*ю*/ tr += "iu"; break;
        case 1103: /*я*/ tr += "ia"; break;
        case 1040: /*А*/ tr += "A"; break;
        case 1041: /*Б*/ tr += "B"; break;
        case 1042: /*В*/ tr += "V"; break;
        case 1043: /*Г*/ tr += "G"; break;
        case 1044: /*Д*/ tr += "D"; break;
        case 1045: /*Е*/ tr += "E"; break;
        case 1025: /*Ё*/ tr += "E"; break;
        case 1046: /*Ж*/ tr += "ZH"; break;
        case 1047: /*З*/ tr += "Z"; break;
        case 1048: /*И*/ tr += "I"; break;
        case 1050: /*К*/ tr += "K"; break;
        case 1051: /*Л*/ tr += "L"; break;
        case 1052: /*М*/ tr += "M"; break;
        case 1053: /*Н*/ tr += "N"; break;
        case 1054: /*О*/ tr += "O"; break;
        case 1055: /*П*/ tr += "P"; break;
        case 1056: /*Р*/ tr += "R"; break;
        case 1057: /*С*/ tr += "S"; break;
        case 1058: /*Т*/ tr += "T"; break;
        case 1059: /*У*/ tr += "U"; break;
        case 1060: /*Ф*/ tr += "F"; break;
        case 1061: /*Х*/ tr += "KH"; break;
        case 1062: /*Ц*/ tr += "C"; break;
        case 1063: /*Ч*/ tr += "CH"; break;
        case 1064: /*Ш*/ tr += "SH"; break;
        case 1065: /*Щ*/ tr += "SHCH"; break;
        case 1066: /*Ъ*/ tr += ""; break;
        case 1067: /*Ы*/ tr += "Y"; break;
        case 1068: /*Ь*/ tr += ""; break;
        case 1069: /*Э*/ tr += "E"; break;
        case 1070: /*Ю*/ tr += "IU"; break;
        case 1071: /*Я*/ tr += "IA"; break;
        default: tr += str[i]; break;
        }
    }
    return tr;
}

bool checkPath(QString path, bool mk)
{
    QDir dir;
    if (!dir.exists(path)) {
        if (mk) {
            if (dir.mkpath(path))
                return true;
            else
                return false;
        } else
            return false;
    } else
        return true;
    return false;
}

bool readJson(QString path, QJsonObject &json, QJsonParseError &log)
{
    QFile file;
    file.setFileName(QDir::toNativeSeparators(path));
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDoc;
        jsonDoc = QJsonDocument::fromJson(file.readAll(), &log);
        file.close();
        if (log.error == QJsonParseError::NoError) {
            json = jsonDoc.object();
            return true;
        }
    }
    return false;
}

bool writeJson(QString path, QJsonObject &json)
{
    QFile file;
    file.setFileName(QDir::toNativeSeparators(path));
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument jsonDoc(json);
        if (file.write(jsonDoc.toJson()) != -1) {
            file.close();
            return true;
        }
    }
    return false;
}

QString toNativeSeparators(QString path)
{
    return QDir::toNativeSeparators(path);
}

QString takeFileName(QString path)
{
    path = toNativeSeparators(path);
    QString separator = QDir::toNativeSeparators("/");
    int sepIndex = path.lastIndexOf(separator);
    if (sepIndex != -1)
        return path.right(path.count() - sepIndex - 1);
    else
        return path;
}

QString takeDirPath(QString path)
{
    path = toNativeSeparators(path);
    QString separator = QDir::toNativeSeparators("/");
    int sepIndex = path.lastIndexOf(separator);
    if (sepIndex != -1)
        return path.left(sepIndex);
    else
        return path;
}

QString toFileNameWithIndex(QString fn, QStringList paths)
{
    QFile test;
    QString result;
    QString ext = takeFileExt(fn);
    QString name = fn.left(fn.count() - ext.count() - 1);

    QString sep = toNativeSeparators("/");
    for (int i = 0; i < paths.count(); i++) {
        paths[i] = toNativeSeparators(paths[i]);
        if (paths[i][paths[i].count() - 1] != sep)
            paths[i] += sep;
    }

    int index = 0;
    QString suffix = "";
    bool isOk;
    do {
        if (index != 0)
            suffix = QString::number(index);
        isOk = true;
        for (int i = 0; i < paths.count(); i++)
            if (test.exists(paths[i] + name + suffix + "." + ext)) {
                isOk = false;
                break;
            }
        if (isOk)
            return name + suffix + "." + ext;
        index++;
    } while (!isOk);

    return "";
}

QString takeFileExt(QString fn)
{
    int dot = fn.lastIndexOf('.');
    return fn.right(fn.count() - dot - 1);
}

QString takeValidSeparator(QString path)
{
    if (path.contains("/"))
        return "/";
    else if (path.contains("\\"))
        return "\\";
    else
        return toNativeSeparators("/");
}

QString takeHumanReadableSize(int size)
{
    QString textSize = QString::number(size);
    QStringList mults = QString(FILE_SIZE_MULT).split(SEPARATOR);
    QStringList units = QString(FILE_SIZE_UNIT).split(SEPARATOR);
    if (mults.count() == units.count()) {
        for (int i = 0; i < mults.count(); i++) {
            size /= mults[i].toInt();
            textSize = QString::number(size);
            if (textSize.count() <= 4) {
                textSize += units[i];
                break;
            }
        }
    }
    return textSize;
}

int fileSize(QString path)
{
    QFileInfo file(path);
    if (file.isFile() && !file.isSymLink())
        return file.size();
    return 0;
}

int dirSize(QString path)
{
    int size = 0;
    QDir dir(path);
    QFileInfoList file = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Dirs | QDir::Files);
    for (int i = 0; i < file.count(); i++)
        if (file[i].isFile())
            size += file[i].size();
        else if (file[i].isDir())
            size += dirSize(file[i].absoluteFilePath());

    return size;
}

QString lastModified(QString path, QString format)
{
    QFileInfo file(path);
    return file.lastModified().toString(format);
}

QString fileCreated(QString path, QString format)
{
    QFileInfo file(path);
    return file.birthTime().toString(format);
}

int filesCount(QString path)
{
    int size = 0;
    QDir dir(path);
    QFileInfoList file = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Dirs | QDir::Files);
    for (int i = 0; i < file.count(); i++)
        if (file[i].isFile())
            size++;
        else if (file[i].isDir())
            size += filesCount(file[i].absoluteFilePath());

    return size;
}

bool removeFile(QString path)
{
    QFile file(path);
    return file.remove();
}

bool copyFile(QString in, QString out)
{
    QFile file;
    return file.copy(in, out);
}
