#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr) : QTableWidget(parent) {};
    ~TableWidget();
};

#endif // TABLEWIDGET_H
