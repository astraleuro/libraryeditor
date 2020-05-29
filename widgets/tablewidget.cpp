#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    delegate = new TableDelegate;
    setItemDelegate(delegate);
    connect(delegate, SIGNAL(childActivated(int)), this, SLOT(activateChild(int)));
}

void TableWidget::connectBase(JsonBase *base, JsonBase *schema)
{
    pBase = base;
    pSchema = schema;
}

void TableWidget::showData()
{
    clear();
    delegate->clear();

    setColumnCount(0);
    setRowCount(0);

    baseIndex = pBase->indexOf(path);
    schemaIndex = pSchema->indexOf(path);

    childIndexes = pBase->indexesOf(baseIndex);
    childKeys = pBase->keysOf(baseIndex);

    verticalHeader()->setVisible(true);
    horizontalHeader()->setVisible(true);

    switch (pBase->typeOf(baseIndex)) {
    case Object:
        showObject();
        break;
    case Array:
        showArray();
        break;
    default:
        break;
    }

    if (baseIndex > 0)
        backExist(true);
    else
        backExist(false);
}

void TableWidget::showObject()
{
    appendRow(childIndexes.count());
    if (pBase->isChildExist(baseIndex, Value)) {
        appendCol(2);
    } else
        appendCol(1);

    QJsonObject schema;
    QString label, modifyer;
    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            delegate->setRowType(i, ValueItem);
            delegate->setModifyer(i, 1, modifyer);
            modifyer = toString(pSchema->value(pSchema->indexOf(schemaIndex, childKeys[i])));
            schema = pSchema->toJson(pSchema->indexOf(schemaIndex, childKeys[i]));
            setItem(i, 0, new QTableWidgetItem(modifyer.split(LIST_SEPARATOR)[LABEL_POS]));
            setItem(i, 1, new QTableWidgetItem(toString(pBase->value(childIndexes[i]))));
        } else {
            delegate->setRowType(i, ChildItem);
            schema = pSchema->toJson(pSchema->indexOf(schemaIndex, "{" + childKeys[i] + "}"));
            label = schema[LABEL_FLAG].toString();
            if (label.isEmpty())
                label = childKeys[i];
            setItem(i, 0, new QTableWidgetItem(label));
        }
    }
}

void TableWidget::showArray()
{
    QString modifyer;
    QStringList labels;
    QJsonObject arraySchema = pSchema->toJson(pSchema->indexOf(pSchema->parentIndex(schemaIndex), "{" + path.last() + "}"));
    QJsonValue childSchema = pSchema->toJson(pSchema->indexOf(schemaIndex, "0"));
    QStringList args = arraySchema[ORDER_FLAG].toString().split(LIST_SEPARATOR);

    appendRow(childIndexes.count());
    if (!childIndexes.isEmpty())
        appendCol(pBase->keysCount(childIndexes[0]));

    if (childSchema.isObject()) {
        for (QString key : args)
            if (!childSchema[key].isObject() && !childSchema[key].isArray())
                labels.append(childSchema[key].toString().split(LIST_SEPARATOR)[LABEL_POS]);
            else
                labels.append(childSchema["{" + key + "}"].toObject()[LABEL_FLAG].toString());
        setHorizontalHeaderLabels(labels);
    }

    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            delegate->setRowType(i, ValueItem);
            delegate->setModifyer(i, 1, childSchema.toString());
            setItem(i, 0, new QTableWidgetItem(pBase->keyAt(baseIndex, i)));
        } else {
            delegate->setRowType(i, ChildItem);
            for (int j = 0; j < args.count(); j++) {
                modifyer = childSchema.toObject()[args[j]].toString();
                if (modifyer.contains(BOOL_FLAG))
                    setItem(i, j, new QTableWidgetItem(modifyer.split(LIST_SEPARATOR)[pBase->keyAt(childIndexes[i], args[j]).toInt() + 2]));
                else
                    setItem(i, j, new QTableWidgetItem(pBase->keyAt(childIndexes[i], args[j])));
            }
        }
    }
}

void TableWidget::appendRow(int count)
{
    setRowCount(rowCount() + count);
    for (int i = count; i > 0; i--)
        setVerticalHeaderItem(rowCount() - i, new QTableWidgetItem(""));
    delegate->appendRow(count);
}

void TableWidget::appendCol(int count)
{
    setColumnCount(columnCount() + count);
    for (int i = count; i > 0; i--)
        setHorizontalHeaderItem(columnCount() - i, new QTableWidgetItem(""));
    delegate->appendCol(count);
}

QString TableWidget::toString(QJsonValue value)
{
    if (value.isString())
        return value.toString();
    else if (value.isBool())
        return QString::number(value.toBool());
    else if (value.isDouble())
        return QString::number(value.toDouble());
    else
        return "";
}

TableWidget::~TableWidget()
{
    delete delegate;
}

void TableWidget::goBack()
{
    path.removeLast();
    showData();
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    if (columnCount() == 1)
        setColumnWidth(0, event->size().width() );
    QTableWidget::resizeEvent(event);
}

void TableWidget::activateChild(int row)
{
    path.append(childKeys[row]);
    showData();
}
