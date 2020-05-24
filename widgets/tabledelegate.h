#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QItemDelegate>

class TableDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TableDelegate(QObject *parent = nullptr);

signals:

};

#endif // TABLEDELEGATE_H
