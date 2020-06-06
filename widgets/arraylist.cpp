#include "arraylist.h"
#include "ui_arraylist.h"

ArrayList::ArrayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayList)
{
    ui->setupUi(this);
    delegate = new ArrayItemDelegate;

    connect(ui->saveButton, SIGNAL(clicked()), this, SIGNAL(saveData()));
    connect(ui->arrayTable->horizontalHeader(), SIGNAL(sectionResized(int , int, int)), this, SLOT(adoptItems(int, int, int)));
    connect(delegate, SIGNAL(itemActivated(int)), this, SLOT(openItemEditor(int)));
    connect(&itemEditor, SIGNAL(settingsChanged(QString, QJsonObject)), this, SIGNAL(settingsChanged(QString, QJsonObject)));

    connect(&itemEditor, SIGNAL(readyForEras(QString)), this, SIGNAL(readyForEras(QString)));
    connect(this, SIGNAL(sendEras(QStringList&)), &itemEditor, SLOT(recieveEras(QStringList&)));

    connect(&itemEditor, SIGNAL(readyForAuthors(QString)), this, SIGNAL(readyForAuthors(QString)));
    connect(this, SIGNAL(sendAuthors(QStringList&)), &itemEditor, SLOT(recieveAuthors(QStringList&)));

    delete ui->arrayTable->itemDelegate();
    ui->arrayTable->setItemDelegate(delegate);
    ui->filterBox->setVisible(false);
    ui->sortBox->setVisible(false);

    void readyForEras();
    void fillEras(QStringList &list);
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
    settings[AL_SORT_APPLY_KEY] = settings[AL_SORT_APPLY_KEY].toString(AL_SORT_APPLY);

    settings[AL_ADD_BUTTON] = settings[AL_ADD_BUTTON].toString(AL_ADD_BUTTON);
    settings[AL_SAVE_BUTTON] = settings[AL_SAVE_BUTTON].toString(AL_SAVE_BUTTON);
    settings[AL_EDIT_BUTTON] = settings[AL_EDIT_BUTTON].toString(AL_EDIT_BUTTON);
    settings[AL_DEL_BUTTON] = settings[AL_DEL_BUTTON].toString(AL_DEL_BUTTON);

    settings[AL_SORT_ORDER_ASC_KEY] = settings[AL_SORT_ORDER_ASC_KEY].toString(AL_SORT_ORDER_ASC);
    settings[AL_SORT_ORDER_DSC_KEY] = settings[AL_SORT_ORDER_DSC_KEY].toString(AL_SORT_ORDER_DSC);

    ui->addButton->setText(settings[AL_ADD_BUTTON].toString());
    ui->saveButton->setText(settings[AL_SAVE_BUTTON].toString());
    ui->editButton->setText(settings[AL_EDIT_BUTTON].toString());
    ui->removeButton->setText(settings[AL_DEL_BUTTON].toString());

    ui->filterButton->setText(settings[AL_FILTER_BUTTON_KEY].toString());
    ui->filterBox->setTitle(settings[AL_FILTER_BUTTON_KEY].toString());
    ui->filterApplyButton->setText(settings[AL_SORT_APPLY_KEY].toString());
    ui->sortButton->setText(settings[AL_SORT_BUTTON_KEY].toString());
    ui->sortBox->setTitle(settings[AL_SORT_BUTTON_KEY].toString());
    ui->sortApplyButton->setText(settings[AL_FILTER_APPLY_KEY].toString());

    switch (section) {
    case ArtsSection:
        ui->arrayBox->setTitle(settings[ARTS_KEY].toString());
        jsonArray = jsonData[ARTS_KEY].toArray();
        secFilesPath = toNativeSeparators(allFilesPath + "/" + QString(ARTS_KEY) + "/");
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
        secOptions = settings[AUTHORS_OPTIONS_KEY].toObject();
        secOptions[TEXT_COLS_LABELS_KEY] = secOptions[TEXT_COLS_LABELS_KEY].toString(AUTHORS_TEXT_COLS_LABELS);
        secOptions[TEXT_COLS_H_KEY] = secOptions[TEXT_COLS_H_KEY].toString(AUTHORS_TEXT_COLS_H);
        secOptions[TEXT_COLS_F_KEY] = secOptions[TEXT_COLS_F_KEY].toString(AUTHORS_TEXT_COLS_F);
        break;
    case ErasSection:
        ui->arrayBox->setTitle(settings[ERAS_KEY].toString());
        jsonArray = jsonData[ERAS_KEY].toArray();
        secFilesPath = toNativeSeparators(allFilesPath + "/" + QString(ERAS_KEY) + "/");
        secOptions = settings[ERAS_OPTIONS_KEY].toObject();
        secOptions[TEXT_COLS_LABELS_KEY] = secOptions[TEXT_COLS_LABELS_KEY].toString(ERAS_TEXT_COLS_LABELS);
        secOptions[TEXT_COLS_H_KEY] = secOptions[TEXT_COLS_H_KEY].toString(ERAS_TEXT_COLS_H);
        secOptions[TEXT_COLS_F_KEY] = secOptions[TEXT_COLS_F_KEY].toString(ERAS_TEXT_COLS_F);
        break;
    }

    textColKeyF = secOptions[TEXT_COLS_F_KEY].toString();
    textColKeysH = secOptions[TEXT_COLS_H_KEY].toString().split(SEPARATOR);
    textColLabels = secOptions[TEXT_COLS_LABELS_KEY].toString().split(SEPARATOR);

    if (secOptions[FILTER_VISIBLE_KEY].toBool(false))
        ui->filterButton->toggle();
    else
        secOptions[FILTER_VISIBLE_KEY] = false;

    if (secOptions[FILTER_TEXT_KEY].isUndefined())
        secOptions[FILTER_TEXT_KEY] = "";
    ui->filterEdit->setText(secOptions[FILTER_TEXT_KEY].toString());

    if (secOptions[SORT_VISIBLE_KEY].toBool(false))
        ui->sortButton->toggle();
    else
        secOptions[SORT_VISIBLE_KEY] = false;

    if (secOptions[SORT_TEXT_KEY].isUndefined())
        secOptions[SORT_TEXT_KEY] = "";
    ui->sortCombo->setCurrentText(secOptions[SORT_TEXT_KEY].toString());

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
}

ArrayList::~ArrayList()
{
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
            addTextItem(i, QJsonValue());
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
    QTableWidget *table = ui->arrayTable;
    QTableWidgetItem *item;
    if (table->item(row, 0) == nullptr)
        item = new QTableWidgetItem;
    else
        item = table->item(row, 0);
    int size = table->columnWidth(0);
    QImage image = QImage(secFilesPath + data[imageKey].toString()).scaledToWidth(size);
    item->setData(Qt::DecorationRole, image);
    item->setText(secFilesPath + data[imageKey].toString());
    table->setItem(row, 0, item);
    table->setRowHeight(row, image.height());
}

void ArrayList::addTextItem(int row, QJsonValue data)
{
    if (!data.isObject()) {
        adoptText(row);
    }
}

QString ArrayList::jsonValueToText(QString key, QJsonValue value)
{
    if (key == ARTS_AUTHORS_KEY)
        return stringArrayToString(value.toArray());
    else if (key == ARTS_RANK_KEY)
        return takeRank(value.toInt(-1), ranks);
    else
        return value.toString();
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
    secOptions[FILTER_TEXT_KEY] = ui->filterEdit->text();
}

void ArrayList::on_sortApplyButton_clicked()
{
    secOptions[SORT_TEXT_KEY] = ui->sortCombo->currentIndex();
    secOptions[SORT_ORDER_KEY] = sortOrder;
}

void ArrayList::on_sortOrderButton_clicked()
{
    if (sortOrder)
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_DSC_KEY].toString());
    else
        ui->sortOrderButton->setText(settings[AL_SORT_ORDER_ASC_KEY].toString());
    sortOrder = !sortOrder;
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
