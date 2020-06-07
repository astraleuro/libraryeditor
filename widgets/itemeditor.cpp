#include "itemeditor.h"
#include "ui_itemeditor.h"

ItemEditor::ItemEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditor)
{
    ui->setupUi(this);
    saveTemplateA = new QAction;
    clearTemplateA = new QAction;

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
    itemIndex = index;
    currentItem = data;

    setWindowTitle(settings[EDITOR_EDIT_TITLE_KEY].toString());
    ui->addEditButton->setText(settings[EDITOR_EDIT_BUTTON_KEY].toString());
    ui->dontCloseCheck->setVisible(false);

    fillWidgets();
}

void ItemEditor::addData()
{
    itemIndex = -1;
    setWindowTitle(settings[EDITOR_ADD_TITLE_KEY].toString());
    ui->addEditButton->setText(settings[EDITOR_ADD_BUTTON_KEY].toString());
    ui->dontCloseCheck->setVisible(true);
    currentItem = QJsonObject();

    ui->dontCloseCheck->setChecked(false);

    fillWidgets();
}

ItemEditor::~ItemEditor()
{
    settingsChanged(getClassName(this), settings);
    delete ui;
}

void ItemEditor::recieveAuthors(QStringList &list)
{
    authors = list;
    authors.sort(Qt::CaseInsensitive);
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
        ui->rankCombo->setCurrentIndex(currentItem[ARTS_RANK_KEY].toInt(itemTemplate[ARTS_RANK_KEY].toInt(-1)));
        ui->eraCombo->setCurrentIndex(findEraIndex(currentItem[ARTS_ERA_KEY].toString(itemTemplate[ARTS_ERA_KEY].toString())));
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
        currentFilePath = toNativeSeparators(secFilesPath + "/" +
                currentItem[QString(FILE_SECTION_KEY).split(SEPARATOR)[section]].toString());
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
}

void ItemEditor::replaceAuthors(QStringList &list)
{
    tableFromList(ui->authorTable, list);
}

void ItemEditor::openNewImage()
{
    QString fn, translit;
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
            translit = toValidFileName(takeFileName(fn));
            if (checkPath(secFilesPath + translit)) {
                msg.setText(errorsMsg[ERRORS_FILE_ALREADY_EXIST_KEY].toString());
                isOk = false;
            }
        }
        if (isOk) {
            imageView->initData(fn);
            currentFilePath = fn;
        } else
            msg.exec();
    }
}

void ItemEditor::on_cancelButton_clicked()
{
    settingsChanged(getClassName(this), settings);
    ui->aaImageBox->setGeometry(ui->aaImageBox->x(), ui->aaImageBox->y(), 0, 0);
    close();
}

void ImageView::initData(QString path)
{
    if (checkPath(path))
        origImage.load(path);
    else
        origImage.load(RESOURCE_QUESTION);
    setPixmap(QPixmap::fromImage(origImage.scaled(width(), height(), Qt::KeepAspectRatio)));
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

/*void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton)
        clicked();
}*/

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
    QDate date;
    currentItem = QJsonObject();
    switch (section) {
    case ArtsSection:
        currentItem[ARTS_NAME_KEY] = ui->nameEdit->text();
        currentItem[ARTS_INFO_KEY] = ui->artInfoText->toPlainText();
        currentItem[ARTS_RANK_KEY] = ui->rankCombo->currentIndex();
        currentItem[ARTS_AUTHORS_KEY] = tableToArray(ui->authorTable);
        currentItem[ARTS_ERA_KEY] = ui->eraCombo->currentText();
        currentItem[ARTS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
        break;
    case AuthorsSection:
        currentItem[AUTHORS_NAME_KEY] = ui->nameEdit->text();
        currentItem[AUTHORS_INFO_KEY] = ui->artInfoText->toPlainText();
        currentItem[AUTHORS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
        break;
    case ErasSection:
        currentItem[ERAS_NAME_KEY] = ui->nameEdit->text();
        currentItem[ERAS_DATE_KEY] = date.currentDate().toString(settings[DATE_FORMAT_KEY].toString());
        break;
    }

    currentItem[QString(FILE_SECTION_KEY).split(SEPARATOR)[section]] = currentFilePath;

    if (!ui->dontCloseCheck->isChecked())
        close();
    else
        fillWidgets();
}
