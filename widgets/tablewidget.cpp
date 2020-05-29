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
    if (baseIndex != 0) {
        if (pBase->typeOf(pBase->parentIndex(baseIndex)) == Array)
            schema = pSchema->toJson(pSchema->indexOf(pSchema->parentIndex(pSchema->parentIndex(schemaIndex)), "{" + path[path.count() - 2] + "}"));
        else if (pBase->typeOf(pBase->parentIndex(baseIndex)) == Object)
            schema = pSchema->toJson(pSchema->indexOf(pSchema->parentIndex(schemaIndex), "{" + path.last() + "}"));
        orderArgs(schema[ORDER_FLAG].toString().split(LIST_SEPARATOR));
    }

    QString label, modifier;
    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            modifier = toString(pSchema->value(pSchema->indexOf(schemaIndex, childKeys[i])));
            setItem(i, 0, new QTableWidgetItem(modifier.split(LIST_SEPARATOR)[LABEL_POS]));
            if (modifier.contains(BOOL_FLAG))
                setItem(i, 1, new QTableWidgetItem(modifier.split(LIST_SEPARATOR)[pBase->keyAt(baseIndex, childKeys[i]).toInt() + 2]));
            else
                setItem(i, 1, new QTableWidgetItem(toString(pBase->value(childIndexes[i]))));
            delegate->setRowType(i, ValueItem);
            delegate->setModifier(i, 1, modifier);
        } else {
            schema = pSchema->toJson(pSchema->indexOf(schemaIndex, "{" + childKeys[i] + "}"));
            label = schema[LABEL_FLAG].toString();
            if (label.isEmpty())
                label = childKeys[i];
            if (columnCount() == 1) {
                setItem(i, 0, new QTableWidgetItem(label + " (" + QString::number(pBase->keysCount(childIndexes[i])) + ")"));
            } else {
                setItem(i, 0, new QTableWidgetItem(label));
                setItem(i, 1, new QTableWidgetItem(pBase->keyAt(baseIndex, childKeys[i])));
            }
            delegate->setRowType(i, ChildItem);
        }
    }
}

void TableWidget::showArray()
{
    QString modifier;
    QStringList labels;
    QJsonValue childSchema;
    QJsonObject arraySchema = pSchema->toJson(pSchema->indexOf(pSchema->parentIndex(schemaIndex), "{" + path.last() + "}"));
    QStringList args = arraySchema[ORDER_FLAG].toString().split(LIST_SEPARATOR);
    if (pSchema->isChildExist(schemaIndex, Object))
        childSchema = pSchema->toJson(pSchema->indexOf(schemaIndex, "0"));
    else
        childSchema = pSchema->value(pSchema->indexOf(schemaIndex, "0"));

    appendRow(childIndexes.count());
    if (!childIndexes.isEmpty()) {
        if (childSchema.isObject()) {
            appendCol(pBase->keysCount(childIndexes[0]));
            for (QString key : args)
                if (!childSchema[key].isObject() && !childSchema[key].isArray())
                    labels.append(childSchema[key].toString().split(LIST_SEPARATOR)[LABEL_POS]);
                else
                    labels.append(childSchema["{" + key + "}"].toObject()[LABEL_FLAG].toString());
            setHorizontalHeaderLabels(labels);
        } else if (childSchema.toString() != "") {
            appendCol(1);
        }
    }

    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            delegate->setRowType(i, ValueItem);
            delegate->setModifier(i, 0, childSchema.toString());
            setItem(i, 0, new QTableWidgetItem(toString(pBase->value(pBase->indexOf(baseIndex, QString::number(i))))));
        } else {
            delegate->setRowType(i, ChildItem);
            for (int j = 0; j < args.count(); j++) {
                modifier = childSchema.toObject()[args[j]].toString();
                if (modifier.contains(BOOL_FLAG))
                    setItem(i, j, new QTableWidgetItem(modifier.split(LIST_SEPARATOR)[pBase->keyAt(childIndexes[i], args[j]).toInt() + 2]));
                else
                    setItem(i, j, new QTableWidgetItem(pBase->keyAt(childIndexes[i], args[j])));
            }
        }
        verticalHeaderItem(i)->setText(QString::number(i + 1));
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

void TableWidget::orderArgs(QStringList args)
{
    QStringList orderedChildKeys;
    QVector<int> orderedChildIndexes = childIndexes;

    orderedChildKeys = childKeys;
    orderedChildIndexes.resize(childIndexes.count());

    for (int i = 0; i < childKeys.count(); i++)
        for (int j = 0; j < args.count(); j++)
            if (childKeys[i] == args[j]) {
                orderedChildKeys[j] = childKeys[i];
                orderedChildIndexes[j] = childIndexes[i];
            }

    childKeys = orderedChildKeys;
    childIndexes = orderedChildIndexes;
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
