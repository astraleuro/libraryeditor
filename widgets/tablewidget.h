#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QResizeEvent>
#include <QHeaderView>
#include <QImage>
#include <QDir>

#include "widgets/itemdelegate.h"
#include "modules/database/jsonbase.h"
#include "modules/templates.h"

#define ADDITIONAL_WIDTH 20
#define AUTO_MAX_WIDTH 180

enum ShowType {
    ObjectShow,
    ArrayShow,
};

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    void connectBase(JsonBase *base, JsonBase *schema);
    void showData();
    ~TableWidget() {};
    QJsonObject takeSettings() {return settings;};
    void setSettings(QJsonObject data) {settings = data;};
    void setBasePath(QString path) {basePath = path;};

signals:
    void backExist(bool);
    void statusText(QString);

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
    void orderArgs(QStringList args);
    void adoptColsWidth();
    void saveColsWidth();
    QVariant initImage(QString path, int width, int &height);
    StandardItemDelegate *initDelegate(QString &modifier);
    StandardItemDelegate *rowDelegate(int row, QString modifier = "complex");
    StandardItemDelegate *colDelegate(int col, QString modifier = "complex");
    void clearDelegates();

public slots:
    void activatePos(int row);
    void showImages();

private:
    JsonBase *pBase, *pSchema;
    int baseIndex = 0;
    int schemaIndex = 0;
    QStringList path, childKeys;
    QVector<int> childIndexes;
    QJsonObject settings;
    ShowType showedType = ObjectShow;
    QString basePath;
    QVector<StandardItemDelegate*> connected;
};

#endif // TABLEWIDGET_H
