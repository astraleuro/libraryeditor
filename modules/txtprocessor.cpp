#include "txtprocessor.h"


int rowsCountInHeight(int height)
{
    QFont font;
    QFontMetrics fontMetrics(font);
    return height / (fontMetrics.height());
}

QString truncateByWidth(QString str, int width)
{
    QFont font;
    QFontMetrics fontMetrics(font);
    QString newStr;
    if (fontMetrics.horizontalAdvance(str) > width) {
        for (int i = str.count(); i > 0; i--) {
            newStr = str.left(i) + "...";
            if (fontMetrics.horizontalAdvance(newStr) <= width)
                return newStr;
        }
        return "";
    } else
        return str;
}

QString takeRank(int rank, const QStringList &ranks)
{
    bool isOk;
    int current;
    for (int i = 0; i < ranks.count(); i++) {
        current = ranks[i].toInt(&isOk);
        if (isOk && current == rank && i > 0)
            return ranks[i - 1];
    }
    return "";
}

QStringList takeRanksList(QStringList &ranks)
{
    bool isOk;
    int current;
    QStringList sorted = reserveList(ranksCount(ranks));
    for (int i = 0; i < ranks.count(); i++) {
        current = ranks[i].toInt(&isOk);
        if (isOk && i > 0) {
            sorted[current] = ranks[i - 1];
        }
    }
    return QStringList(sorted);
}

int ranksCount(QStringList &ranks)
{
    bool isOk;
    int current = 0;
    int biggest = 0;
    for (int i = 0; i < ranks.count(); i++) {
        current = ranks[i].toInt(&isOk);
        if (isOk && biggest < current)
            biggest = current;
    }
    return biggest + 1;
}

QStringList reserveList(int count)
{
    QStringList newList;
    for (int i = 0; i < count; i++)
        newList.append("");
    return newList;

}

bool isValidDateFormat(QString format)
{
    QString date = QDate::currentDate().toString(format);
    if (!date.isEmpty())
        return true;
    else
        return false;
}
