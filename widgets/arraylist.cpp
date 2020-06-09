#include "arraylist.h"
#include "ui_arraylist.h"

ArrayList::ArrayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayList)
{
    ui->setupUi(this);
    delegate = new ArrayItemDelegate;

    ui->arrayTable->horizontalHeader()->setVisible(true);
    connect(ui->arrayTable->horizontalHeader(), SIGNAL(sectionResized(int , int, int)), this, SLOT(adoptItems(int, int, int)));
    connect(delegate, SIGNAL(itemActivated(int)), this, SLOT(openItemEditor(int)));
    connect(&itemEditor, SIGNAL(settingsChanged(QString, QJsonObject)), this, SIGNAL(settingsChanged(QString, QJsonObject)));
    connect(&itemEditor, SIGNAL(readyForEras(QString)), this, SIGNAL(readyForEras(QString)));
    connect(this, SIGNAL(sendEras(QStringList&)), &itemEditor, SLOT(recieveEras(QStringList&)));
    connect(&itemEditor, SIGNAL(readyForAuthors(QString)), this, SIGNAL(readyForAuthors(QString)));
    connect(this, SIGNAL(sendAuthors(QStringList&)), &itemEditor, SLOT(recieveAuthors(QStringList&)));
    connect(&itemEditor, SIGNAL(itemUniqueCheck(QJsonValue, QString, int)), this, SLOT(itemUniqueCheck(QJsonValue, QString, int)));

    delete ui->arrayTable->itemDelegate();
    ui->arrayTable->setItemDelegate(delegate);
    ui->filterBox->setVisible(false);
    ui->sortBox->setVisible(false);

    //void readyForEras();
    //void fillEras(QStringList &list);

    ui->disableFilter->setMaximumWidth(ui->disableFilter->height());
    ui->disableSort->setMaximumWidth(ui->disableSort->height());

}

void ArrayList::initData(QString fn, QJsonObject &data, QJsonObject &opt, JsonDataSections &sec)
{
    allSettings = opt;
    settings = allSettings[getClassName(this)].toObject();
    jsonData = data;
    allFilesPath = toNativeSeparators(fn.left(fn.count() - QString(BASE_EXTENSION).count()));
    section = sec;
    imageKey = QString(FILE_SECTION_KEY).split(SEPARATOR)[sec];

    settings[ARTS_KEY] = settings[ARTS_KEY].toString(ARTS_LABEL);
    settings[AUTHORS_KEY] = settings[AUTHORS_KEY].toString(AUTHORS_LABEL);
    settings[ERAS_KEY] = settings[ERAS_KEY].toString(ERAS_LABEL);
    settings[AL_FILTER_BUTTON_KEY] = settings[AL_FILTER_BUTTON_KEY].toString(AL_FILTER_BUTTON);
    settings[AL_FILTER_APPLY_KEY] = settings[AL_FILTER_APPLY_KEY].toString(AL_FILTER_APPLY);
    settings[AL_SORT_BUTTON_KEY] = settings[AL_SORT_BUTTON_KEY].toString(AL_SORT_BUTTON);
    settings[AL_ADD_BUTTON] = settings[AL_ADD_BUTTON].toString(AL_ADD_BUTTON);
    settings[AL_EDIT_BUTTON] = settings[AL_EDIT_BUTTON].toString(AL_EDIT_BUTTON);
    settings[AL_DEL_BUTTON] = settings[AL_DEL_BUTTON].toString(AL_DEL_BUTTON);
    settings[AL_SORT_ORDER_ASC_KEY] = settings[AL_SORT_ORDER_ASC_KEY].toString(AL_SORT_ORDER_ASC);
    settings[AL_SORT_ORDER_DSC_KEY] = settings[AL_SORT_ORDER_DSC_KEY].toString(AL_SORT_ORDER_DSC);
    settings[AL_SORT_ENABLE_TITLE_KEY] = settings[AL_SORT_ENABLE_TITLE_KEY].toString(AL_SORT_ENABLE_TITLE);

    ui->sortEnable->setText(settings[AL_SORT_ENABLE_TITLE_KEY].toString());
    ui->addButton->setText(settings[AL_ADD_BUTTON].toString());
    ui->editButton->setText(settings[AL_EDIT_BUTTON].toString());
    ui->removeButton->setText(settings[AL_DEL_BUTTON].toString());
    ui->filterButton->setText(settings[AL_FILTER_BUTTON_KEY].toString());
    ui->filterBox->setTitle(settings[AL_FILTER_BUTTON_KEY].toString());
    ui->filterApplyButton->setText(settings[AL_FILTER_APPLY_KEY].toString());
    ui->sortButton->setText(settings[AL_SORT_BUTTON_KEY].toString());
    ui->sortBox->setTitle(settings[AL_SORT_BUTTON_KEY].toString());

    switch (section) {
    case ArtsSection:
        ui->arrayBox->setTitle(settings[ARTS_KEY].toString());
        jsonArray = jsonData[ARTS_KEY].toArray();
        secFilesPath = toNativeSeparators(allFilesPath + "/" + QString(ARTS_KEY) + "/");
        tmpFilesPath = toNativeSeparators(allFilesPath + "/." + QString(ARTS_KEY) + "/");
        secOptions = settings[ARTS_OPTIONS_KEY].toObject();
        secOptions[TEXT_COLS_LABELS_KEY] = secOptions[TEXT_COLS_LABELS_KEY].toString(ARTS_TEXT_COLS_LABELS);
        secOptions[TEXT_COLS_H_KEY] = secOptions[TEXT_COLS_H_KEY].toString(ARTS_TEXT_COLS_H);
        secOptions[TEXT_COLS_F_KEY] = secOptions[TEXT_COLS_F_KEY].toString(ARTS_TEXT_COLS_F);
        secOptions[ARTS_RANKS_KEY] = secOptions[ARTS_RANKS_KEY].toString(ARTS_RANKS);
        ranks = secOptions[ARTS_RANKS_KEY].toString().split(SEPARATOR);
        break;
    case AuthorsSection:
        ui->arrayBox->setTitle(settings[AUTHORS_KEY].toString());
        jsonArray = jsonData[AUTHORS_KEY].toArray();
        secFilesPath = toNativeSeparators(allFilesPath + "/" + QString(AUTHORS_KEY) + "/");
        tmpFilesPath = toNativeSeparators(allFilesPath + "/." + QString(AUTHORS_KEY) + "/");
        secOptions = settings[AUTHORS_OPTIONS_KEY].toObject();
        secOptions[TEXT_COLS_LABELS_KEY] = secOptions[TEXT_COLS_LABELS_KEY].toString(AUTHORS_TEXT_COLS_LABELS);
        secOptions[TEXT_COLS_H_KEY] = secOptions[TEXT_COLS_H_KEY].toString(AUTHORS_TEXT_COLS_H);
        secOptions[TEXT_COLS_F_KEY] = secOptions[TEXT_COLS_F_KEY].toString(AUTHORS_TEXT_COLS_F);
        settings[AL_AUTHORS_KEY_FOR_ARTS_LIST_KEY] = settings[AL_AUTHORS_KEY_FOR_ARTS_LIST_KEY].toString(AL_AUTHORS_KEY_FOR_ARTS_LIST);
        break;
    case ErasSection:
        ui->arrayBox->setTitle(settings[ERAS_KEY].toString());
        jsonArray = jsonData[ERAS_KEY].toArray();
        secFilesPath = toNativeSeparators(allFilesPath + "/" + QString(ERAS_KEY) + "/");
        tmpFilesPath = toNativeSeparators(allFilesPath + "/." + QString(ERAS_KEY) + "/");
        secOptions = settings[ERAS_OPTIONS_KEY].toObject();
        secOptions[TEXT_COLS_LABELS_KEY] = secOptions[TEXT_COLS_LABELS_KEY].toString(ERAS_TEXT_COLS_LABELS);
        secOptions[TEXT_COLS_H_KEY] = secOptions[TEXT_COLS_H_KEY].toString(ERAS_TEXT_COLS_H);
        secOptions[TEXT_COLS_F_KEY] = secOptions[TEXT_COLS_F_KEY].toString(ERAS_TEXT_COLS_F);
        settings[AL_ERAS_KEY_FOR_ARTS_LIST_KEY] = settings[AL_ERAS_KEY_FOR_ARTS_LIST_KEY].toString(AL_ERAS_KEY_FOR_ARTS_LIST);
        break;
    }

    secOptions[SORT_ORDER_KEY] = secOptions[SORT_ORDER_KEY].toBool(1);

    textColKeyF = secOptions[TEXT_COLS_F_KEY].toString();
    textColKeysH = secOptions[TEXT_COLS_H_KEY].toString().split(SEPARATOR);
    textColLabels = secOptions[TEXT_COLS_LABELS_KEY].toString().split(SEPARATOR);
    fillSortBox();

    if (secOptions[FILTER_VISIBLE_KEY].toBool(false))
        ui->filterButton->toggle();
    else
        secOptions[FILTER_VISIBLE_KEY] = false;

    if (secOptions[FILTER_TEXT_KEY].isUndefined())
        secOptions[FILTER_TEXT_KEY] = "";
    ui->filterEdit->setText(secOptions[FILTER_TEXT_KEY].toString());
    filterStr = ui->filterEdit->text();

    if (secOptions[SORT_VISIBLE_KEY].toBool(false))
        ui->sortButton->toggle();
    else
        secOptions[SORT_VISIBLE_KEY] = false;

    if (!secOptions[SORT_ORDER_KEY].isBool())
        secOptions[SORT_ORDER_KEY] = true;

    if (secOptions[SORT_ORDER_KEY].toBool()) {
        sortOrder = true;
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_ASC_KEY].toString());
    } else {
        sortOrder = false;
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_DSC_KEY].toString());
    }

    itemEditor.initData(allSettings, section, allFilesPath, ranks);
    itemEditor.setModal(true);
    fillTable();

    connect(ui->sortEnable, SIGNAL(stateChanged(int)), this, SLOT(sortStateChanged(int)));
    connect(ui->sortCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(sortStateChanged()));

    secOptions[AL_SORT_ENABLE_CHECK_KEY] = secOptions[AL_SORT_ENABLE_CHECK_KEY].toBool(AL_SORT_ENABLE_CHECK);
    if (secOptions[AL_SORT_ENABLE_CHECK_KEY].toBool())
        ui->sortEnable->setCheckState(Qt::Checked);
    else
        ui->sortEnable->setCheckState(Qt::Unchecked);

    sortStateChanged(ui->sortEnable->isChecked());
}

QJsonArray ArrayList::takeData()
{
    return jsonArray;
}

JsonDataSections ArrayList::takeSection()
{
    return section;
}

ArrayList::~ArrayList()
{
    secOptions[SORT_TEXT_KEY] = ui->sortCombo->currentIndex();
    secOptions[SORT_ORDER_KEY] = sortOrder;

    settingsChanged(getClassName(this), takeSettings());
    delete delegate;
    delete ui;
}

QJsonObject ArrayList::takeSettings()
{
    switch (section) {
    case ArtsSection:
        settings[ARTS_OPTIONS_KEY] = secOptions;
        break;
    case AuthorsSection:
        settings[AUTHORS_OPTIONS_KEY] = secOptions;
        break;
    case ErasSection:
        settings[ERAS_OPTIONS_KEY] = secOptions;
        break;
    }

    return settings;
}

void ArrayList::changeItem(QJsonObject data, int row)
{
    if (row == -1) {
        jsonArray.append(data);
        ui->arrayTable->insertRow(ui->arrayTable->rowCount());
        addImageItem(ui->arrayTable->rowCount() - 1, data);
        adoptText(ui->arrayTable->rowCount() - 1);
    } else {
        jsonArray[row] = data;
        addImageItem(row, data);
        adoptText(row);
    }

    sortStateChanged(ui->sortEnable->isChecked());
}

QString ArrayList::jsonValueToText(QString key, QJsonValue value)
{
    if (key == ARTS_AUTHORS_KEY)
        return stringArrayToString(value.toArray());
    else if (key == ARTS_RANK_KEY) {
        if (value.isBool()) {
            if (value.toBool())
                return takeRank(1, ranks);
            else
                return takeRank(0, ranks);
        } else
            return takeRank(value.toInt(-1), ranks);
    } else
        return value.toString();
}

void ArrayList::fillSortBox()
{
    ui->sortCombo->clear();
    for (int i = 0; i < textColLabels.count(); i += 2)
        ui->sortCombo->addItem(textColLabels[i], textColLabels[i + 1]);

    if (secOptions[SORT_TEXT_KEY].isUndefined())
        secOptions[SORT_TEXT_KEY] = 0;

    if (secOptions[SORT_TEXT_KEY].toInt() >= 0 && secOptions[SORT_TEXT_KEY].toInt() < ui->sortCombo->count())
        ui->sortCombo->setCurrentIndex(secOptions[SORT_TEXT_KEY].toInt());
}

void ArrayList::reorderItems(QVector<int> &order)
{
    QTableWidget *table = ui->arrayTable;
    QVector<QVariant> images;
    QVector<QString> texts;
    QVector<int> heights;

    images.resize(table->rowCount());
    texts.resize(table->rowCount());
    heights.resize(table->rowCount());

    for (int i = 0; i < table->rowCount(); i++) {
        images[i] = table->item(i, 0)->data(Qt::DecorationRole);
        texts[i] = table->item(i, 0)->text();
    }

    for (int i = 0; i < order.count(); i++)
        heights[i] = table->rowHeight(order[i]);

    for (int i = 0; i < order.count(); i++) {
        table->item(i, 0)->setData(Qt::DecorationRole, images[order[i]]);
        table->item(i, 0)->setText(texts[i]);
        table->setRowHeight(i, heights[i]);
        adoptText(i);
    }
}

void ArrayList::applyFilter()
{
    QFont font = ui->filterButton->font();
    QTableWidget *table = ui->arrayTable;
    QJsonObject object;

    for (int i = 0; i < table->rowCount(); i++)
        table->showRow(i);

    bool isHide;
    for (int i = 0; i < table->rowCount(); i++) {
        isHide = true;
        object = jsonArray[i].toObject();
        for (QString key : object.keys()) {
            if (jsonValueToText(key, object[key]).contains(filterStr)) {
                isHide = false;
                break;
            }
        }
        if (isHide)
            table->hideRow(i);
    }

    if (!filterStr.isEmpty()) {
        ui->filterButton->setIcon(QIcon(RESOURCE_CHECK));
        font.setBold(true);
    } else {
        ui->filterButton->setIcon(QIcon());
        font.setBold(false);
    }
    ui->filterButton->setFont(font);
}

void ArrayList::sortStateChanged(int state)
{
    QFont font = ui->sortButton->font();

    secOptions[SORT_TEXT_KEY] = ui->sortCombo->currentIndex();
    secOptions[SORT_ORDER_KEY] = sortOrder;
    secOptions[AL_SORT_ENABLE_CHECK_KEY] = ui->sortEnable->isChecked();

    if (state > 0) {
        font.setBold(true);
        ui->sortButton->setIcon(QIcon(RESOURCE_CHECK));
        QVector<int> swaps;
        jsonArray = bubbleSortByKey(jsonArray, ui->sortCombo->itemData(ui->sortCombo->currentIndex()).toString(), sortOrder, swaps);
        for (int i = 0; i < ui->arrayTable->rowCount(); i++)
            ui->arrayTable->showRow(i);
        reorderItems(swaps);
        ui->sortCombo->setEnabled(true);
        ui->sortOrderButton->setEnabled(true);
    } else {
        font.setBold(false);
        ui->sortButton->setIcon(QIcon());
        ui->sortCombo->setEnabled(false);
        ui->sortOrderButton->setEnabled(false);
    }
    ui->sortButton->setFont(font);
    applyFilter();
}

void ArrayList::itemUniqueCheck(QJsonValue value, QString key, int index)
{
    bool isUnique = true;
    for (int i = 0; i < jsonArray.count(); i++)
        if (jsonArray[i].toObject()[key] == value && index != i) {
            isUnique = false;
            break;
        }
    if (isUnique) {
        changeItem(itemEditor.takeItem(), index);
        itemEditor.itemUniqueCheckOk();
        dataChanged();
    } else {
        itemEditor.itemUniqueCheckFail();
    }
}

void ArrayList::fillTable()
{
    if (!jsonData.isEmpty()) {
        eraseTable();
        QTableWidget *table = ui->arrayTable;
        table->setColumnCount(2);
        table->setHorizontalHeaderLabels(QStringList({"", ""}));
        table->setColumnWidth(0, secOptions[IMAGE_WIDTH_KEY].toInt(table->columnWidth(0)));
        for(int i = 0; i < jsonArray.count(); i++) {
            table->setRowCount(table->rowCount() + 1);
            addImageItem(i, jsonArray[i]);
            adoptText(i);
        }
        secOptions[IMAGE_WIDTH_KEY] = table->columnWidth(0);
    }
}

void ArrayList::eraseTable()
{
    ui->arrayTable->clear();
    ui->arrayTable->setColumnCount(0);
    ui->arrayTable->setRowCount(0);
}

void ArrayList::addImageItem(int row, QJsonValue data)
{
    QImage image;
    QTableWidget *table = ui->arrayTable;
    QTableWidgetItem *item;
    int size = table->columnWidth(0);
    if (table->item(row, 0) == nullptr)
        item = new QTableWidgetItem;
    else
        item = table->item(row, 0);
    if (checkPath(secFilesPath + data[imageKey].toString())) {
        image = QImage(secFilesPath + data[imageKey].toString()).scaledToWidth(size);
        item->setText(secFilesPath + data[imageKey].toString());
    } else if (checkPath(tmpFilesPath + data[imageKey].toString())) {
        image = QImage(tmpFilesPath + data[imageKey].toString()).scaledToWidth(size);
        item->setText(tmpFilesPath + data[imageKey].toString());
    } else {
        image = QImage(RESOURCE_QUESTION).scaledToWidth(size);
        item->setText(RESOURCE_QUESTION);
    }
    item->setData(Qt::DecorationRole, image);
    table->setItem(row, 0, item);
    table->setRowHeight(row, image.height());
}

void ArrayList::adoptItems(int col, int oldSize, int newSize)
{
    UNUSED(oldSize);
    QTableWidget *table = ui->arrayTable;
    if (col == 0) {
        QImage image;
        for (int i = 0; i < table->rowCount(); i++) {
            image = QImage(table->item(i, 0)->text()).scaledToWidth(newSize);
            if (table->item(i, 0) != nullptr)
                table->item(i, 0)->setData(Qt::DecorationRole, image);
            if (image.height() != table->rowHeight(i)) {
                table->setRowHeight(i, image.height());
                adoptText(i);
            }
        }
        int savedColWidth = secOptions[IMAGE_WIDTH_KEY].toInt(-1);
        if (savedColWidth == -1 || savedColWidth != table->columnWidth(0)) {
            secOptions[IMAGE_WIDTH_KEY] = table->columnWidth(0);
        }
    }
}

void ArrayList::adoptText(int row)
{
    QString str;
    bool enableFooter = false;
    int rowsCountH;
    QTableWidget *table = ui->arrayTable;
    QJsonObject item = jsonArray[row].toObject();

    rowsCountH = rowsCountInHeight(table->rowHeight(row));
    if (!textColKeyF.isEmpty() && rowsCountH > 1) {
        rowsCountH--;
        enableFooter = true;
    }
    for (int i = 0; i < textColKeysH.count() ; i++) {
        if (rowsCountH > 0) {
            str += textColLabels[textColLabels.indexOf(textColKeysH[i]) - 1] + ": " +
                    jsonValueToText(textColKeysH[i], item[QString(textColKeysH[i])]) + "\n";
            rowsCountH--;
        }
    }

    if (enableFooter)
        str += textColLabels[textColLabels.indexOf(textColKeyF) - 1] + ": " +
                jsonValueToText(textColKeyF, item[QString(textColKeyF)]);

    if (table->item(row, 1) == nullptr)
        table->setItem(row, 1, new QTableWidgetItem(str));
    else
        table->item(row, 1)->setText(str);
    table->item(row, 1)->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void ArrayList::openItemEditor(int index)
{
    if (index != -1) {
        itemEditor.editData(index, jsonArray[index].toObject());
    } else {
        itemEditor.addData();
    }
    itemEditor.exec();
}

void ArrayList::on_filterButton_toggled(bool checked)
{
    secOptions[FILTER_VISIBLE_KEY] = checked;
    ui->filterBox->setVisible(checked);
}

void ArrayList::on_sortButton_toggled(bool checked)
{
    secOptions[SORT_VISIBLE_KEY] = checked;
    ui->sortBox->setVisible(checked);
}

void ArrayList::on_backButton_clicked()
{
    goBack();
}

void ArrayList::on_filterApplyButton_clicked()
{
    QFont font = ui->filterButton->font();
    filterStr = ui->filterEdit->text();
    secOptions[FILTER_TEXT_KEY] = filterStr;
    applyFilter();
}

void ArrayList::on_sortOrderButton_clicked()
{
    if (sortOrder)
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_DSC_KEY].toString());
    else
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_ASC_KEY].toString());
    sortOrder = !sortOrder;
    sortStateChanged(ui->sortEnable->isChecked());
}

void ArrayList::on_editButton_clicked()
{
    if (ui->arrayTable->selectedItems().count() > 0)
        openItemEditor(ui->arrayTable->selectedItems().first()->row());
}

void ArrayList::on_addButton_clicked()
{
    openItemEditor();
}

void ArrayList::on_removeButton_clicked()
{
    QString key;
    int index = -1;
    switch (section) {
    case ArtsSection:
        break;
    case AuthorsSection:
        key = settings[AL_AUTHORS_KEY_FOR_ARTS_LIST_KEY].toString();
        for (int i = 0; i < ui->arrayTable->selectedItems().count(); i++)
            if (index < ui->arrayTable->selectedItems()[i]->row()) {
                index = ui->arrayTable->selectedItems()[i]->row();
                removeAuthorsInArts(jsonArray[ui->arrayTable->selectedItems()[i]->row()].toObject()[AUTHORS_NAME_KEY].toString(), key);
            }
        break;
    case ErasSection:
        key = settings[AL_ERAS_KEY_FOR_ARTS_LIST_KEY].toString();
        for (int i = 0; i < ui->arrayTable->selectedItems().count(); i++)
            if (index < ui->arrayTable->selectedItems()[i]->row()) {
                index = ui->arrayTable->selectedItems()[i]->row();
                clearEraInArts(jsonArray[ui->arrayTable->selectedItems()[i]->row()].toObject()[ERAS_NAME_KEY].toString(), key);
            }
        break;
    }
    removeArraySelectedItems(jsonArray, ui->arrayTable->selectedItems());
    removeTableSelectedItems(ui->arrayTable, ui->arrayTable->selectedItems());
    dataChanged();
}

void ArrayList::on_disableFilter_clicked()
{
    ui->filterEdit->setText("");
    on_filterApplyButton_clicked();
}

void ArrayList::on_disableSort_clicked()
{
    ui->sortEnable->setCheckState(Qt::Unchecked);
    sortStateChanged(0);
}
