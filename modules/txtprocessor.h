#ifndef TXTPROCESSOR_H
#define TXTPROCESSOR_H

#include <QFont>
#include <QFontMetrics>
#include <QDate>

int rowsCountInHeight(int height);
QString truncateByWidth(QString str,int width);
QString takeRank(int rank, const QStringList &ranks);
QStringList takeRanksList(QStringList &ranks);
int ranksCount(QStringList &ranks);
QStringList reserveList(int count);
QString takeValidSeparator(QString str);
bool isValidDateFormat(QString format);

#endif // TXTPROCESSOR_H
