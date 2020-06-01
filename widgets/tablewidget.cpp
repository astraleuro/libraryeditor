#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent)
    : QTableWidget(parent)
{
}

void TableWidget::connectBase(JsonBase *base, JsonBase *schema)
{
    pBase = base;
    pSchema = schema;
}

void TableWidget::showData()
{   
    clearDelegates();
    clear();
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

    adoptColsWidth();
    showImages();

    if (baseIndex > 0)
        backExist(true);
    else
        backExist(false);
}

void TableWidget::showObject()
{
    showedType = ObjectShow;
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
    StandardItemDelegate *newItemDelegate;
    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            modifier = toString(pSchema->value(pSchema->indexOf(schemaIndex, childKeys[i])));
            newItemDelegate = rowDelegate(i, modifier);
            newItemDelegate->setModifier(0, modifier);
            newItemDelegate->setData(0, toString(pBase->keyAt(baseIndex, childKeys[i])));
            setItem(i, 0, new QTableWidgetItem(modifier.split(LIST_SEPARATOR)[LABEL_POS]));
            setItem(i, 1, new QTableWidgetItem(newItemDelegate->takeModifiedData(0)));
            item(i, 0)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            item(i, 1)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
        } else {
            schema = pSchema->toJson(pSchema->indexOf(schemaIndex, "{" + childKeys[i] + "}"));
            newItemDelegate = rowDelegate(i);
            newItemDelegate->setModifier(0, schema[LABEL_FLAG].toString());
            newItemDelegate->setData(0, childKeys[i]);
            if (columnCount() == 1) {
                setItem(i, 0, new QTableWidgetItem(newItemDelegate->takeModifiedData(0) + " (" + QString::number(pBase->keysCount(childIndexes[i])) + ")"));
                item(i, 0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            } else {
                newItemDelegate->setData(1, pBase->keyAt(baseIndex, childKeys[i]));
                setItem(i, 0, new QTableWidgetItem(newItemDelegate->takeModifiedData(0)));
                setItem(i, 1, new QTableWidgetItem(pBase->keyAt(baseIndex, childKeys[i])));
                item(i, 0)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
                item(i, 1)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            }
            connect(newItemDelegate, SIGNAL(posActivated(int)), this, SLOT(activatePos(int)));
            connected.push_back(newItemDelegate);
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

    showedType = ArrayShow;
    appendRow(childIndexes.count());
    if (!childIndexes.isEmpty()) {
        if (childSchema.isObject()) {
            appendCol(pBase->keysCount(childIndexes[0]) + 1);
            for (QString key : args)
                if (!childSchema[key].isObject() && !childSchema[key].isArray())
                    labels.append(childSchema[key].toString().split(LIST_SEPARATOR)[LABEL_POS]);
                else
                    labels.append(childSchema["{" + key + "}"].toObject()[LABEL_FLAG].toString());

            labels.push_back("");
            setHorizontalHeaderLabels(labels);
        } else if (childSchema.toString() != "")
            appendCol(1);
    }

    StandardItemDelegate *newItemDelegate;
    for (int i = 0; i < childIndexes.count(); i++) {
        if (pBase->typeOf(childIndexes[i]) == Value) {
            newItemDelegate = colDelegate(i, "");
            newItemDelegate->setData(i, toString(pBase->value(pBase->indexOf(baseIndex, QString::number(i)))));
            setItem(i, 0, new QTableWidgetItem(newItemDelegate->takeData(i)));
            item(i, 0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        } else {
            for (int j = 0; j < args.count(); j++) {
                modifier = childSchema.toObject()[args[j]].toString();
                newItemDelegate = colDelegate(j, modifier);
                newItemDelegate->setModifier(i, modifier);
                newItemDelegate->setData(i, pBase->keyAt(childIndexes[i], args[j]));
                setItem(i, j, new QTableWidgetItem(newItemDelegate->takeModifiedData(i)));
                item(i, j)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
            }
            newItemDelegate = colDelegate(columnCount() - 1);
            setItem(i, columnCount() - 1, new QTableWidgetItem("..."));
            connect(newItemDelegate, SIGNAL(posActivated(int)), this, SLOT(activatePos(int)));
            connected.push_back(newItemDelegate);
            verticalHeaderItem(i)->setText(QString::number(i + 1));
        }
    }
}

void TableWidget::appendRow(int count)
{
    setRowCount(rowCount() + count);
    for (int i = count; i > 0; i--)
        setVerticalHeaderItem(rowCount() - i, new QTableWidgetItem(""));
}

void TableWidget::appendCol(int count)
{
    setColumnCount(columnCount() + count);
    for (int i = count; i > 0; i--)
        setHorizontalHeaderItem(columnCount() - i, new QTableWidgetItem(""));
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

void TableWidget::adoptColsWidth()
{
    disconnect(horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(showImages()));
    QFont font;
    QFontMetrics fontMetrics(font);
    if (columnCount() > 1) {
        int width;
        for (int j = 0; j < columnCount(); j++) {
            width = 0;
            if (showedType == ArrayShow) {
                if (j != columnCount() - 1)
                    width = settings[horizontalHeaderItem(j)->text()].toInt();
            } else
                width = settings["{" + QString::number(j) + "}"].toInt();
            if (width == 0) {
                for (int i = 0; i < rowCount(); i++)
                    if (item(i, j) != nullptr)
                        width = max(width, fontMetrics.horizontalAdvance(item(i, j)->text()), AUTO_MAX_WIDTH);
                if (showedType == ArrayShow)
                    width = max(width, fontMetrics.horizontalAdvance(horizontalHeaderItem(j)->text()), INT_MAX);
            }
            setColumnWidth(j, width + ADDITIONAL_WIDTH);
        }
    }
    connect(horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(showImages()));
}

void TableWidget::saveColsWidth()
{
    if (columnCount() > 1) {
        if (showedType == ArrayShow) {
            for (int i = 0; i < columnCount(); i++)
                settings[horizontalHeaderItem(i)->text()] = columnWidth(i);
        } else {
            settings["{0}"] = columnWidth(0);
            settings["{1}"] = columnWidth(1);
        }
    }
}

QVariant TableWidget::initImage(QString path, int width, int &height)
{
    path = QDir::toNativeSeparators(path);
    QImage image = QImage(path).scaledToWidth(width);
    height = image.height();
    return image;
}

void TableWidget::showImages()
{
    int height;
    StandardItemDelegate *itemPtr;
    for (int i = 0; i < rowCount(); i++)
        if (itemDelegateForRow(i) != nullptr) {
            itemPtr = (StandardItemDelegate*)itemDelegateForRow(i);
            if (itemPtr->itemType() == FileItem) {
                item(i, 1)->setData(Qt::DecorationRole, initImage(basePath + itemPtr->takeModifiedData(i), columnWidth(1), height));
                item(i, 1)->setToolTip(QDir::toNativeSeparators(itemPtr->takeModifiedData(i)));
                if (height > 0)
                    setRowHeight(i, height);
            }
        }
    for (int i = 0; i < rowCount(); i++)
        for (int j = 0; j < columnCount(); j++)
            if (itemDelegateForColumn(j) != nullptr) {
                itemPtr = (StandardItemDelegate*)itemDelegateForColumn(j);
                if (itemPtr->itemType() == FileItem) {
                    item(i, j)->setData(Qt::DecorationRole, initImage(basePath + itemPtr->takeModifiedData(i), columnWidth(j), height));
                    item(i, j)->setToolTip(QDir::toNativeSeparators(itemPtr->takeModifiedData(i)));
                if (height > 0)
                    setRowHeight(i, height);
                }
            }
}

StandardItemDelegate *TableWidget::initDelegate(QString &modifier)
{
    StandardItemDelegate *newDelegate;
    if (modifier == "complex")
        newDelegate = new ComplexItemDelegate(this);
    else if ((modifier.contains(FILE_FLAG)))
        newDelegate = new FileItemDelegate(this);
    else if (modifier.contains(BOOL_FLAG))
        newDelegate = new BoolItemDelegate(this);
    else
        newDelegate = new StandardItemDelegate(this);
    return newDelegate;
}

StandardItemDelegate *TableWidget::rowDelegate(int row, QString modifier)
{
    if (itemDelegateForRow(row) != nullptr)
        return (StandardItemDelegate*)(itemDelegateForRow(row));
    else {
        setItemDelegateForRow(row, initDelegate(modifier));
        return (StandardItemDelegate*)itemDelegateForRow(row);
    }
}

StandardItemDelegate *TableWidget::colDelegate(int col, QString modifier)
{
    if (itemDelegateForColumn(col) != nullptr)
        return (StandardItemDelegate*)(itemDelegateForColumn(col));
    else {
        setItemDelegateForColumn(col, initDelegate(modifier));
        return (StandardItemDelegate*)itemDelegateForColumn(col);
    }
}

void TableWidget::clearDelegates()
{
    for (int i = 0; i < connected.count(); i++)
        disconnect(connected[i], SIGNAL(posActivated(int)), this, SLOT(activateChild(int)));
    connected.clear();
    connected.resize(0);
    StandardItemDelegate *temp;
    for (int i = 0; i < rowCount(); i++)
        if (itemDelegateForRow(i) != nullptr) {
            temp = (StandardItemDelegate*)itemDelegateForRow(i);
            setItemDelegateForRow(i, nullptr);
            delete temp;
        }
    for (int i = 0; i < columnCount(); i++)
        if (itemDelegateForColumn(i) != nullptr) {
            temp = (StandardItemDelegate*)itemDelegateForColumn(i);
            setItemDelegateForColumn(i, nullptr);
            delete temp;
        }
}

void TableWidget::goBack()
{
    saveColsWidth();
    path.removeLast();
    showData();
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    if (columnCount() == 1)
        setColumnWidth(0, event->size().width());
    QTableWidget::resizeEvent(event);
}

void TableWidget::activatePos(int row)
{
    saveColsWidth();
    path.append(childKeys[row]);
    showData();
}
