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
