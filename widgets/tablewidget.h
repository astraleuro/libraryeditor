#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QResizeEvent>
#include <QHeaderView>

#include "modules/database/jsonbase.h"

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr) : QTableWidget(parent) {};
    void connectBase(JsonBase *base, JsonBase *schema);
    void showData(QStringList path);
    ~TableWidget();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    JsonBase *mainBase, *mainSchema;
    int currentBaseIndex = -1;
    int currentSchemaIndex = -1;
};

#endif // TABLEWIDGET_H
