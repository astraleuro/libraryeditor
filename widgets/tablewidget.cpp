#include "tablewidget.h"

void TableWidget::connectBase(JsonBase *base, JsonBase *schema)
{
    mainBase = base;
    mainSchema = schema;
}

void TableWidget::showData(QStringList path)
{
    currentBaseIndex = mainBase->indexOf(path);
    currentSchemaIndex = mainBase->indexOf(path);
    if (mainBase->typeOf(currentBaseIndex) == Object) {
        verticalHeader()->setVisible(false);
        horizontalHeader()->setVisible(false);
        setColumnCount(1);
        QString keyPrintableName;
        QJsonObject keySchema;
        for (QString key : mainBase->keysOf(currentBaseIndex)) {
            setRowCount(rowCount() + 1);
            keySchema = mainSchema->toJson(mainSchema->indexOf(currentSchemaIndex, "{" + key + "}"));
            keyPrintableName = keySchema[NAME_FLAG].toString();
            if (keyPrintableName.isEmpty())
                keyPrintableName = key;
            if (item(rowCount() - 1, 0) != nullptr)
                item(rowCount() - 1, 0)->setText(keyPrintableName);
            else
                setItem(rowCount() - 1, 0, new QTableWidgetItem(keyPrintableName));
        }
    }
}

TableWidget::~TableWidget()
{

}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    if (columnCount() > 0 && event->size().width() > 0) {
        int colWidth = event->size().width() / columnCount();
        for (int i = 0; i < rowCount(); i++)
            setColumnWidth(i, colWidth);
    }
}
