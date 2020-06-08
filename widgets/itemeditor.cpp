#include "itemeditor.h"
#include "ui_itemeditor.h"

ItemEditor::ItemEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditor)
{
    ui->setupUi(this);
    //saveTemplateA = new QAction;
    //clearTemplateA = new QAction;

    dialog.setNameFilters(QString(IMAGE_EXTENSION_FILTER).split(SEPARATOR));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setModal(true);

    connect(ui->aaImage, SIGNAL(clicked()), this, SLOT(openNewImage()));
    connect(ui->eraImage, SIGNAL(clicked()), this, SLOT(openNewImage()));

    connect(&authorsList, SIGNAL(chooseIsDone(QStringList&)), this, SLOT(replaceAuthors(QStringList&)));
    connect(&authorsList, SIGNAL(settingsChanged(QString, QJsonObject)), this, SIGNAL(settingsChanged(QString, QJsonObject)));
    authorsList.setModal(true);
}

void ItemEditor::initData(QJsonObject &opt, JsonDataSections &sec, QString path, QStringList ranks)
{
    allSettings = opt;
    settings = allSettings[getClassName(this)].toObject();
    section = sec;
    allFilesPath = path;

    settings[EDITOR_ARTS_RANK_TYPE_KEY] = settings[EDITOR_ARTS_RANK_TYPE_KEY].toString(EDITOR_ARTS_RANK_TYPE);
    rankType = settings[EDITOR_ARTS_RANK_TYPE_KEY].toString();
    if (rankType != "bool" && rankType != "int") {
        rankType = EDITOR_ARTS_RANK_TYPE;
        settings[EDITOR_ARTS_RANK_TYPE_KEY] = EDITOR_ARTS_RANK_TYPE;
    }

    settings[EDITOR_ARTS_UNIQUE_KEY] = settings[EDITOR_ARTS_UNIQUE_KEY].toString(EDITOR_ARTS_UNIQUE);
    settings[EDITOR_AUTHORS_UNIQUE_KEY] = settings[EDITOR_AUTHORS_UNIQUE_KEY].toString(EDITOR_AUTHORS_UNIQUE);
    settings[EDITOR_ERAS_UNIQUE_KEY] = settings[EDITOR_ERAS_UNIQUE_KEY].toString(EDITOR_ERAS_UNIQUE);
    settings[EDITOR_ADD_TITLE_KEY] = settings[EDITOR_ADD_TITLE_KEY].toString(EDITOR_ADD_TITLE);
    settings[EDITOR_EDIT_TITLE_KEY] = settings[EDITOR_EDIT_TITLE_KEY].toString(EDITOR_EDIT_TITLE);
    settings[EDITOR_TEMPLATE_SAVE_KEY] = settings[EDITOR_TEMPLATE_SAVE_KEY].toString(EDITOR_TEMPLATE_SAVE);
    settings[EDITOR_TEMPLATE_CLEAR_KEY] = settings[EDITOR_TEMPLATE_CLEAR_KEY].toString(EDITOR_TEMPLATE_CLEAR);
    settings[EDITOR_IMAGE_STYLE_KEY] = settings[EDITOR_IMAGE_STYLE_KEY].toString(EDITOR_IMAGE_STYLE);
    settings[EDITOR_ADD_TITLE_KEY] = settings[EDITOR_ADD_TITLE_KEY].toString(EDITOR_ADD_TITLE);
    settings[EDITOR_EDIT_TITLE_KEY] = settings[EDITOR_EDIT_TITLE_KEY].toString(EDITOR_EDIT_TITLE);
    settings[EDITOR_ADD_BUTTON_KEY] = settings[EDITOR_ADD_BUTTON_KEY].toString(EDITOR_ADD_BUTTON);
    settings[EDITOR_EDIT_BUTTON_KEY] = settings[EDITOR_EDIT_BUTTON_KEY].toString(EDITOR_EDIT_BUTTON);
    settings[EDITOR_CANCEL_BUTTON_KEY] = settings[EDITOR_CANCEL_BUTTON_KEY].toString(EDITOR_CANCEL_BUTTON);
    settings[EDITOR_TEMPLATE_BUTTON_KEY] = settings[EDITOR_TEMPLATE_BUTTON_KEY].toString(EDITOR_TEMPLATE_BUTTON);
    settings[EDITOR_OPENFILE_TITLE_KEY] = settings[EDITOR_OPENFILE_TITLE_KEY].toString(EDITOR_OPENFILE_TITLE);
    settings[DATE_FORMAT_KEY] = settings[DATE_FORMAT_KEY].toString(DATE_FORMAT);
    if (!isValidDateFormat(settings[DATE_FORMAT_KEY].toString()))
        settings[DATE_FORMAT_KEY] = DATE_FORMAT;

    ui->templateButton->setText(settings[EDITOR_TEMPLATE_BUTTON_KEY].toString());
    ui->cancelButton->setText(settings[EDITOR_CANCEL_BUTTON_KEY].toString());

    errorsMsg = allSettings[ERRORS_SUBSECTION_KEY].toObject();

    switch (section) {
    case ArtsSection:
        artRanks = takeRanksList(ranks);
        secFilesPath = toNativeSeparators(allFilesPath  + "/" + QString(ARTS_KEY) + "/");
        tmpFilePath = toNativeSeparators(allFilesPath  + "/." + QString(ARTS_KEY) + "/");
        settings[EDITOR_ERAS_KEY_FOR_ARTS_LIST_KEY] = settings[EDITOR_ERAS_KEY_FOR_ARTS_LIST_KEY].toString(EDITOR_ERAS_KEY_FOR_ARTS_LIST);
        settings[EDITOR_AUTHORS_KEY_FOR_ARTS_LIST_KEY] = settings[EDITOR_AUTHORS_KEY_FOR_ARTS_LIST_KEY].toString(EDITOR_AUTHORS_KEY_FOR_ARTS_LIST);
        settings[EDITOR_ARTS_NAME_BOX_KEY] = settings[EDITOR_ARTS_NAME_BOX_KEY].toString(EDITOR_ARTS_NAME_BOX);
        settings[EDITOR_ARTS_AUTHORS_BOX_KEY] = settings[EDITOR_ARTS_AUTHORS_BOX_KEY].toString(EDITOR_ARTS_AUTHORS_BOX);
        settings[EDITOR_ARTS_RANK_BOX_KEY] = settings[EDITOR_ARTS_RANK_BOX_KEY].toString(EDITOR_ARTS_RANK_BOX);
        settings[EDITOR_ARTS_ERA_BOX_KEY] = settings[EDITOR_ARTS_ERA_BOX_KEY].toString(EDITOR_ARTS_ERA_BOX);
        settings[EDITOR_ARTS_INFO_BOX_KEY] = settings[EDITOR_ARTS_INFO_BOX_KEY].toString(EDITOR_ARTS_INFO_BOX);
        settings[EDITOR_ARTS_IMAGE_BOX_KEY] = settings[EDITOR_ARTS_IMAGE_BOX_KEY].toString(EDITOR_ARTS_IMAGE_BOX);
        settings[EDITOR_ARTS_TEMPLATE_KEY] = settings[EDITOR_ARTS_TEMPLATE_KEY].toObject();
        settings[EDITOR_ARTS_WIDTH_KEY] = settings[EDITOR_ARTS_WIDTH_KEY].toInt(EDITOR_ARTS_WIDTH);
        settings[EDITOR_ARTS_HEIGHT_KEY] = settings[EDITOR_ARTS_HEIGHT_KEY].toInt(EDITOR_ARTS_HEIGHT);
        itemTemplate = settings[EDITOR_ARTS_TEMPLATE_KEY].toObject();
        setMinimumSize(EDITOR_ARTS_WIDTH, EDITOR_ARTS_HEIGHT);
        setGeometry(0, 0,
                    settings[EDITOR_ARTS_WIDTH_KEY].toInt(),
                    settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt());
        ui->nameBox->setTitle(settings[EDITOR_ARTS_NAME_BOX_KEY].toString());
        ui->authorsBox->setTitle(settings[EDITOR_ARTS_AUTHORS_BOX_KEY].toString());
        ui->rankBox->setTitle(settings[EDITOR_ARTS_RANK_BOX_KEY].toString());
        ui->eraBox->setTitle(settings[EDITOR_ARTS_ERA_BOX_KEY].toString());
        ui->artInfoBox->setTitle(settings[EDITOR_ARTS_INFO_BOX_KEY].toString());
        ui->aaImageBox->setTitle(settings[EDITOR_ARTS_IMAGE_BOX_KEY].toString());
        ui->authorInfoBox->setVisible(false);
        ui->eraImageBox->setVisible(false);
        imageView = ui->aaImage;
        ui->templateButton->setEnabled(true);
        readyForEras(settings[EDITOR_ERAS_KEY_FOR_ARTS_LIST_KEY].toString());
        readyForAuthors(settings[EDITOR_AUTHORS_KEY_FOR_ARTS_LIST_KEY].toString());
        authorsList.initData(allSettings, authors);
        break;
    case AuthorsSection:
        secFilesPath = toNativeSeparators(allFilesPath  + "/" + QString(AUTHORS_KEY) + "/");
        tmpFilePath = toNativeSeparators(allFilesPath  + "/." + QString(AUTHORS_KEY) + "/");
        settings[EDITOR_AUTHORS_NAME_BOX_KEY] = settings[EDITOR_AUTHORS_NAME_BOX_KEY].toString(EDITOR_AUTHORS_NAME_BOX);
        settings[EDITOR_AUTHORS_INFO_BOX_KEY] = settings[EDITOR_AUTHORS_INFO_BOX_KEY].toString(EDITOR_AUTHORS_INFO_BOX);
        settings[EDITOR_AUTHORS_IMAGE_BOX_KEY] = settings[EDITOR_AUTHORS_IMAGE_BOX_KEY].toString(EDITOR_AUTHORS_IMAGE_BOX);
        settings[EDITOR_AUTHORS_TEMPLATE_KEY] = settings[EDITOR_AUTHORS_TEMPLATE_KEY].toObject();
        settings[EDITOR_AUTHORS_WIDTH_KEY] = settings[EDITOR_AUTHORS_WIDTH_KEY].toInt(EDITOR_AUTHORS_WIDTH);
        settings[EDITOR_AUTHORS_HEIGHT_KEY] = settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt(EDITOR_AUTHORS_HEIGHT);
        itemTemplate = settings[EDITOR_AUTHORS_TEMPLATE_KEY].toObject();
        setMinimumSize(EDITOR_AUTHORS_WIDTH, EDITOR_AUTHORS_HEIGHT);
        setGeometry(0, 0,
                    settings[EDITOR_AUTHORS_WIDTH_KEY].toInt(),
                    settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt());
        ui->nameBox->setTitle(settings[EDITOR_AUTHORS_NAME_BOX_KEY].toString());
        ui->authorInfoBox->setTitle(settings[EDITOR_AUTHORS_INFO_BOX_KEY].toString());
        ui->aaImageBox->setTitle(settings[EDITOR_AUTHORS_IMAGE_BOX_KEY].toString());
        ui->artInfoBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->rankBox->setVisible(false);
        ui->eraImageBox->setVisible(false);
        imageView = ui->aaImage;
        ui->templateButton->setEnabled(true);
        break;
    case ErasSection:
        secFilesPath = toNativeSeparators(allFilesPath  + "/" + QString(ERAS_KEY) + "/");
        tmpFilePath = toNativeSeparators(allFilesPath  + "/." + QString(ERAS_KEY) + "/");
        settings[EDITOR_ERAS_NAME_BOX_KEY] = settings[EDITOR_ERAS_NAME_BOX_KEY].toString(EDITOR_ERAS_NAME_BOX);
        settings[EDITOR_ERAS_IMAGE_BOX_KEY] = settings[EDITOR_ERAS_IMAGE_BOX_KEY].toString(EDITOR_ERAS_IMAGE_BOX);
        settings[EDITOR_ERAS_WIDTH_KEY] = settings[EDITOR_ERAS_WIDTH_KEY].toInt(EDITOR_ERAS_WIDTH);
        settings[EDITOR_ERAS_HEIGHT_KEY] = settings[EDITOR_ERAS_HEIGHT_KEY].toInt(EDITOR_ERAS_HEIGHT);
        setMinimumSize(EDITOR_ERAS_WIDTH, EDITOR_ERAS_HEIGHT);
        setGeometry(0, 0,
                    settings[EDITOR_ERAS_WIDTH_KEY].toInt(),
                    settings[EDITOR_ERAS_HEIGHT_KEY].toInt());
        ui->nameBox->setTitle(settings[EDITOR_ERAS_NAME_BOX_KEY].toString());
        ui->eraImageBox->setTitle(settings[EDITOR_ERAS_IMAGE_BOX_KEY].toString());
        ui->aaImageBox->setVisible(false);
        ui->artInfoBox->setVisible(false);
        ui->authorInfoBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->rankBox->setVisible(false);
        imageView = ui->eraImage;
        ui->templateButton->setEnabled(false);
        break;
    }

    checkPath(tmpFilePath, true);

    ui->dontCloseCheck->setChecked(false);

    saveTemplateA = templateMenu.addAction(settings[EDITOR_TEMPLATE_SAVE_KEY].toString(), this, SLOT(saveTemplate()));
    clearTemplateA = templateMenu.addAction(settings[EDITOR_TEMPLATE_CLEAR_KEY].toString(), this, SLOT(clearTemplate()));
    ui->templateButton->setMenu(&templateMenu);

    dialog.setWindowTitle(settings[EDITOR_OPENFILE_TITLE_KEY].toString());

    imageView->initData();

    settingsChanged(getClassName(this), settings);
}

void ItemEditor::editData(int index, QJsonObject data)
{
    ui->dontCloseCheck->setCheckState(Qt::Unchecked);
    isImageChanged = false;
    itemIndex = index;
    currentItem = data;

    setWindowTitle(settings[EDITOR_EDIT_TITLE_KEY].toString());
    ui->addEditButton->setText(settings[EDITOR_EDIT_BUTTON_KEY].toString());
    ui->dontCloseCheck->setVisible(false);

    fillWidgets();
}

void ItemEditor::addData()
{
    isImageChanged = true;
    itemIndex = -1;
    setWindowTitle(settings[EDITOR_ADD_TITLE_KEY].toString());
    ui->addEditButton->setText(settings[EDITOR_ADD_BUTTON_KEY].toString());
    ui->dontCloseCheck->setVisible(true);
    currentItem = QJsonObject();

    ui->dontCloseCheck->setChecked(false);

    fillWidgets();
}

void ItemEditor::itemUniqueCheckFail()
{
    QMessageBox msg(QMessageBox::Warning, errorsMsg[ERRORS_TITLE_KEY].toString(),
                    errorsMsg[ERRORS_ITEM_ALREADY_EXIST_KEY].toString(), QMessageBox::Close);
    msg.setModal(true);
    msg.exec();
}

void ItemEditor::itemUniqueCheckOk()
{
    if (!ui->dontCloseCheck->isChecked()) {
        close();
    } else {
        currentItem = QJsonObject();
        fillWidgets();
    }
}

QJsonObject ItemEditor::takeItem()
{
    return currentItem;
}

ItemEditor::~ItemEditor()
{
    settingsChanged(getClassName(this), settings);
    delete saveTemplateA;
    delete clearTemplateA;
    delete ui;
}

void ItemEditor::recieveAuthors(QStringList &list)
{
    authors = list;
    authors.sort(Qt::CaseInsensitive);
}

bool ItemEditor::isFirstStageCheckOk()
{
    isImageOk = false;
    isNameOk = false;
    isRankOk = false;
    isEraOk = false;
    isAuthorsOk = false;
    isInfoOk = false;

    if (isImageChanged) {
        if (imageView->isValid())
            isImageOk = true;
    } else
        isImageOk = true;

    if (ui->nameEdit->text().count() > 0)
        isNameOk = true;

    if (section == ArtsSection) {
        if (ui->rankCombo->currentIndex() != -1)
            isRankOk = true;

        if (ui->eraCombo->currentIndex() != -1)
            isEraOk = true;

        if (ui->authorTable->rowCount() > 0)
            isAuthorsOk = true;

        if (ui->artInfoText->toPlainText().count() > 0)
            isInfoOk = true;
    } else {
        isRankOk = true;
        isEraOk = true;
        isAuthorsOk = true;
        if (section == AuthorsSection) {
            if (ui->authorInfoText->toPlainText().count() > 0)
                isInfoOk = true;
        } else
            isInfoOk = true;
    }

    //if (isImageOk && isNameOk && isRankOk && isEraOk && isAuthorsOk && isInfoOk)
    if (isImageOk && isNameOk && isRankOk)
        return true;
    else
        return false;
}

bool ItemEditor::isValidDateFormat(QString format)
{
    QDate date;
    date = QDate::fromString(format);
    if (date.isValid())
        return true;
    else
        return false;
}

void ItemEditor::recieveEras(QStringList &list)
{
    eras = list;
    eras.sort(Qt::CaseInsensitive);
    ui->eraCombo->addItems(eras);
}

int ItemEditor::findEraIndex(QString key)
{
    QComboBox *eras = ui->eraCombo;
    int index = -1;
    for (int i = 0; i < eras->count(); i++)
        if (eras->itemText(i) == key) {
            index = i;
            break;
        }
    return index;
}

void ItemEditor::fillWidgets()
{
    clearWidgets();
    switch (section) {
    case ArtsSection:
        fillRanks();
        fillAuthors();
        ui->nameEdit->setText(currentItem[ARTS_NAME_KEY].toString(itemTemplate[ARTS_NAME_KEY].toString()));
        ui->artInfoText->setPlainText(currentItem[ARTS_INFO_KEY].toString(itemTemplate[ARTS_INFO_KEY].toString()));
        ui->eraCombo->setCurrentIndex(findEraIndex(currentItem[ARTS_ERA_KEY].toString(itemTemplate[ARTS_ERA_KEY].toString())));
        if (currentItem[ARTS_RANK_KEY].isBool()) {
            bool rank = currentItem[ARTS_RANK_KEY].toBool();
            if (rank)
                ui->rankCombo->setCurrentIndex(1);
            else
                ui->rankCombo->setCurrentIndex(0);
        } else
            ui->rankCombo->setCurrentIndex(currentItem[ARTS_RANK_KEY].toInt(itemTemplate[ARTS_RANK_KEY].toInt(-1)));
        break;
    case AuthorsSection:
        ui->nameEdit->setText(currentItem[AUTHORS_NAME_KEY].toString(itemTemplate[AUTHORS_NAME_KEY].toString()));
        ui->authorInfoText->setPlainText(currentItem[AUTHORS_INFO_KEY].toString(itemTemplate[AUTHORS_INFO_KEY].toString()));
        break;
    case ErasSection:
        ui->nameEdit->setText(currentItem[ERAS_NAME_KEY].toString(itemTemplate[ERAS_NAME_KEY].toString()));
        break;
    }

    if (itemIndex != -1) {
        currentFilePath = currentItem[QString(FILE_SECTION_KEY).split(SEPARATOR)[section]].toString();
        if (checkPath(secFilesPath + currentFilePath))
            currentFilePath = toNativeSeparators(secFilesPath + currentFilePath);
        else if (checkPath(tmpFilePath + currentFilePath))
                 currentFilePath = toNativeSeparators(tmpFilePath + currentFilePath);
        imageView->initData(currentFilePath);
    } else
        currentFilePath = "";
}

void ItemEditor::fillRanks()
{
    ui->rankCombo->clear();
    QComboBox *rankWgt = ui->rankCombo;
    for (int i = 0; i < artRanks.count(); i++) {
        rankWgt->addItem(artRanks[i]);
    }
}

void ItemEditor::fillAuthors()
{
    QStringList list;
    if (currentItem[ARTS_AUTHORS_KEY].isArray())
        list = stringArrayToList(currentItem[ARTS_AUTHORS_KEY].toArray());
    else
        list = stringArrayToList(itemTemplate[ARTS_AUTHORS_KEY].toArray());
    list.sort(Qt::CaseInsensitive);
    tableFromList(ui->authorTable, list);
}

void ItemEditor::clearWidgets()
{
    ui->nameEdit->setText("");
    ui->artInfoText->setPlainText("");
    ui->rankCombo->setCurrentIndex(-1);
    ui->eraCombo->setCurrentIndex(-1);
    ui->authorInfoText->setPlainText("");
    ui->authorTable->clear();
    ui->authorTable->setRowCount(0);
    currentFilePath = "";
    imageView->initData();
}

void ItemEditor::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    if (event->oldSize() != event->size()) {
        switch (section) {
        case ArtsSection:
            settings[EDITOR_ARTS_WIDTH_KEY] = width();
            settings[EDITOR_ARTS_HEIGHT_KEY] = height();
            break;
        case AuthorsSection:
            settings[EDITOR_AUTHORS_WIDTH_KEY] = width();
            settings[EDITOR_AUTHORS_HEIGHT_KEY] = height();
            break;
        case ErasSection:
            settings[EDITOR_ERAS_WIDTH_KEY] = width();
            settings[EDITOR_ERAS_HEIGHT_KEY] = height();
            break;
        }
    }
}

void ItemEditor::saveTemplate()
{
    switch (section) {
    case ArtsSection:
        itemTemplate[ARTS_NAME_KEY] = ui->nameEdit->text();
        itemTemplate[ARTS_INFO_KEY] = ui->artInfoText->toPlainText();
        itemTemplate[ARTS_RANK_KEY] = ui->rankCombo->currentIndex();
        itemTemplate[ARTS_AUTHORS_KEY] = tableToArray(ui->authorTable);
        itemTemplate[ARTS_ERA_KEY] = ui->eraCombo->currentText();
        settings[EDITOR_ARTS_TEMPLATE_KEY] = itemTemplate;
        settingsChanged(getClassName(this), settings);
        break;
    case AuthorsSection:
        itemTemplate[AUTHORS_NAME_KEY] = ui->nameEdit->text();
        itemTemplate[AUTHORS_INFO_KEY] = ui->artInfoText->toPlainText();
        settings[EDITOR_AUTHORS_TEMPLATE_KEY] = itemTemplate;
        settingsChanged(getClassName(this), settings);
        break;
    case ErasSection:
        break;
    }
}

void ItemEditor::clearTemplate()
{
    itemTemplate = QJsonObject();
    switch (section) {
    case ArtsSection:
        settings[EDITOR_ARTS_TEMPLATE_KEY] = itemTemplate;
        settingsChanged(getClassName(this), settings);
        break;
    case AuthorsSection:
        settings[EDITOR_AUTHORS_TEMPLATE_KEY] = itemTemplate;
        settingsChanged(getClassName(this), settings);
        settingsChanged(getClassName(this), settings);
        break;
    case ErasSection:
        break;
    }
}

void ItemEditor::replaceAuthors(QStringList &list)
{
    tableFromList(ui->authorTable, list);
}

void ItemEditor::openNewImage()
{
    QString fn, valid;
    QMessageBox msg(QMessageBox::Warning, errorsMsg[ERRORS_TITLE_KEY].toString(), "", QMessageBox::Close);
    msg.setModal(true);
    bool isOk = true;
    dialog.exec();
    if (dialog.result() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        fn = dialog.selectedFiles()[0];
        if (fn.contains(allFilesPath)) {
            msg.setText(errorsMsg[ERRORS_FILE_ON_BASESUBDIR_KEY].toString());
            isOk = false;
        } else {
            valid = toFileNameWithIndex(toValidFileName(takeFileName(fn), LowerCase), QStringList({secFilesPath, tmpFilePath}));
            QFile file;
            file.copy(fn, tmpFilePath + valid);
        }
        if (isOk) {
            imageView->initData(tmpFilePath + valid);
            currentFilePath = tmpFilePath + valid;
        } else
            msg.exec();
    }
}

void ItemEditor::on_cancelButton_clicked()
{
    currentItem = QJsonObject();
    itemIndex = -1;
    ui->dontCloseCheck->setCheckState(Qt::Unchecked);
    settingsChanged(getClassName(this), settings);
    //ui->aaImageBox->setGeometry(ui->aaImageBox->x(), ui->aaImageBox->y(), 0, 0);
    close();
}

void ImageView::initData(QString path)
{
    fn = path;
    if (checkPath(path))
        origImage.load(path);
    else
        origImage.load(RESOURCE_QUESTION);
    setPixmap(QPixmap::fromImage(origImage.scaled(width(), height(), Qt::KeepAspectRatio)));
}

bool ImageView::isValid()
{
    if (checkPath(fn))
        return true;
    else
        return false;
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    if (event->oldSize() != event->size()) {
        clear();
        setPixmap(QPixmap::fromImage(origImage.scaled(width(), height(), Qt::KeepAspectRatio)));
    }
}

void ImageView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QLabel::mouseDoubleClickEvent(event);
    if (event->button() == Qt::LeftButton)
        clicked();
}

void ItemEditor::on_authorDelButton_clicked()
{
    removeTableSelectedItems(ui->authorTable, ui->authorTable->selectedItems());
}

void ItemEditor::on_authorAddButton_clicked()
{
    authorsList.checkByList(tableToList(ui->authorTable));
    authorsList.exec();
}

void ItemEditor::on_addEditButton_clicked()
{
    if (isFirstStageCheckOk()) {
        QDate date;
        QJsonValue value;
        QString uniqueKey;
        currentItem = QJsonObject();
        switch (section) {
        case ArtsSection:
            currentItem[ARTS_NAME_KEY] = ui->nameEdit->text();
            currentItem[ARTS_INFO_KEY] = ui->artInfoText->toPlainText();
            if (rankType == "int")
                currentItem[ARTS_RANK_KEY] = ui->rankCombo->currentIndex();
            else {
                if (ui->rankCombo->currentIndex() == 0)
                    currentItem[ARTS_RANK_KEY] = false;
                else
                    currentItem[ARTS_RANK_KEY] = true;
            }
            currentItem[ARTS_AUTHORS_KEY] = tableToArray(ui->authorTable);
            currentItem[ARTS_ERA_KEY] = ui->eraCombo->currentText();
            currentItem[ARTS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
            uniqueKey = settings[EDITOR_ARTS_UNIQUE_KEY].toString();
            break;
        case AuthorsSection:
            currentItem[AUTHORS_NAME_KEY] = ui->nameEdit->text();
            currentItem[AUTHORS_INFO_KEY] = ui->authorInfoText->toPlainText();
            currentItem[AUTHORS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
            uniqueKey = settings[EDITOR_AUTHORS_UNIQUE_KEY].toString();
            break;
        case ErasSection:
            currentItem[ERAS_NAME_KEY] = ui->nameEdit->text();
            currentItem[ERAS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
            uniqueKey = settings[EDITOR_ERAS_UNIQUE_KEY].toString();
            break;
        }

        currentItem[QString(FILE_SECTION_KEY).split(SEPARATOR)[section]] = takeFileName(currentFilePath);

        value = currentItem.value(uniqueKey).toString();
        itemUniqueCheck(value, uniqueKey, itemIndex);
    } else {
        QString text, prefix;
        prefix = errorsMsg[ERRORS_CHECK_PREFIX_KEY].toString();
        switch (section) {
        case ArtsSection:
            if (!isImageOk)
                text += prefix + ": \"" + ui->aaImageBox->title() + "\"\n";
            if (!isNameOk)
                text += prefix + ": \"" + ui->nameBox->title() + "\"\n";
            if (!isRankOk)
                text += prefix + ": \"" + ui->rankBox->title() + "\"\n";
            /*if (!isEraOk)
                text += prefix + ": \"" + ui->eraBox->title() + "\"\n";
            if (!isAuthorsOk)
                text += prefix + ": \"" + ui->authorsBox->title() + "\"\n";
            if (!isInfoOk)
                text += prefix + ": \"" + ui->artInfoBox->title() + "\"\n";*/
            break;
        case AuthorsSection:
            if (!isImageOk)
                text += prefix + ": \"" + ui->aaImageBox->title() + "\"\n";
            if (!isNameOk)
                text += prefix + ": \"" + ui->nameBox->title() + "\"\n";
            /*if (!isInfoOk)
                text += prefix + ": \"" + ui->authorInfoBox->title() + "\"\n";*/
            break;
        case ErasSection:
            if (!isImageOk)
                text += prefix + ": \"" + ui->eraImageBox->title() + "\"\n";
            if (!isNameOk)
                text += prefix + ": \"" + ui->nameBox->title() + "\"\n";
            break;
        }
        QMessageBox msg(QMessageBox::Warning, errorsMsg[ERRORS_TITLE_KEY].toString(), text, QMessageBox::Close);
        msg.setModal(true);
        msg.exec();
    }

}
