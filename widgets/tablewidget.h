#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QResizeEvent>
#include <QHeaderView>

#include "modules/database/jsonbase.h"
#include "widgets/tabledelegate.h"

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    void connectBase(JsonBase *base, JsonBase *schema);
    void showData();
    ~TableWidget();
signals:
    void backExist(bool);

public slots:
    void goBack();

protected:
    void resizeEvent(QResizeEvent *event);
    void showObject();
    void showArray();
    void appendRow(int count = 1);
    void appendCol(int count = 1);
    int lastRow() {return rowCount() - 1;};
    int lastCol() {return columnCount() - 1;};
    QString toString(QJsonValue value);

protected slots:
    void activateChild(int row);

private:
    JsonBase *pBase, *pSchema;
    int baseIndex = 0;
    int schemaIndex = 0;
    QStringList path, childKeys;
    QVector<int> childIndexes;
    TableDelegate *delegate;
};

#endif // TABLEWIDGET_H
