#include "itemeditor.h"
#include "ui_itemeditor.h"

ItemEditor::ItemEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemEditor)
{
    ui->setupUi(this);

}

void ItemEditor::initData(QJsonObject &opt, JsonDataSections &sec)
{
    allSettings = opt;
    settings = allSettings[getClassName(this)].toObject();
    section = sec;

    settings[EDITOR_ADD_TITLE_KEY] = settings[EDITOR_ADD_TITLE_KEY].toString(EDITOR_ADD_TITLE);
    settings[EDITOR_EDIT_TITLE_KEY] = settings[EDITOR_EDIT_TITLE_KEY].toString(EDITOR_EDIT_TITLE);
    settings[EDITOR_ADD_BUTTON_KEY] = settings[EDITOR_ADD_BUTTON_KEY].toString(EDITOR_ADD_BUTTON);
    settings[EDITOR_EDIT_BUTTON_KEY] = settings[EDITOR_EDIT_BUTTON_KEY].toString(EDITOR_EDIT_BUTTON);
    settings[EDITOR_CANCEL_BUTTON_KEY] = settings[EDITOR_CANCEL_BUTTON_KEY].toString(EDITOR_CANCEL_BUTTON);
    settings[EDITOR_TEMPLATE_BUTTON_KEY] = settings[EDITOR_TEMPLATE_BUTTON_KEY].toString(EDITOR_TEMPLATE_BUTTON);

    ui->templateButton->setText(settings[EDITOR_TEMPLATE_BUTTON_KEY].toString());
    ui->cancelButton->setText(settings[EDITOR_CANCEL_BUTTON_KEY].toString());

    switch (section) {
    case ArtsSection:
        settings[EDITOR_ARTS_NAME_BOX_KEY] = settings[EDITOR_ARTS_NAME_BOX_KEY].toString(EDITOR_ARTS_NAME_BOX);
        settings[EDITOR_ARTS_AUTHORS_BOX_KEY] = settings[EDITOR_ARTS_AUTHORS_BOX_KEY].toString(EDITOR_ARTS_AUTHORS_BOX);
        settings[EDITOR_ARTS_RANK_BOX_KEY] = settings[EDITOR_ARTS_RANK_BOX_KEY].toString(EDITOR_ARTS_RANK_BOX);
        settings[EDITOR_ARTS_ERA_BOX_KEY] = settings[EDITOR_ARTS_ERA_BOX_KEY].toString(EDITOR_ARTS_ERA_BOX);
        settings[EDITOR_ARTS_INFO_BOX_KEY] = settings[EDITOR_ARTS_INFO_BOX_KEY].toString(EDITOR_ARTS_INFO_BOX);
        settings[EDITOR_ARTS_IMAGE_BOX_KEY] = settings[EDITOR_ARTS_IMAGE_BOX_KEY].toString(EDITOR_ARTS_IMAGE_BOX);
        settings[EDITOR_ARTS_TEMPLATE_KEY] = settings[EDITOR_ARTS_TEMPLATE_KEY].toObject();
        settings[EDITOR_ARTS_WIDTH_KEY] = settings[EDITOR_ARTS_WIDTH_KEY].toInt(EDITOR_ARTS_WIDTH);
        settings[EDITOR_ARTS_HEIGHT_KEY] = settings[EDITOR_ARTS_HEIGHT_KEY].toInt(EDITOR_ARTS_HEIGHT);
        setMinimumSize(EDITOR_ARTS_WIDTH, EDITOR_ARTS_HEIGHT);
        setGeometry(0, 0,
                    settings[EDITOR_ARTS_WIDTH_KEY].toInt(),
                    settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt());
        ui->nameBox->setTitle(settings[EDITOR_ARTS_NAME_BOX_KEY].toString());
        ui->authorsBox->setTitle(settings[EDITOR_ARTS_AUTHORS_BOX_KEY].toString());
        ui->rankBox->setTitle(settings[EDITOR_ARTS_RANK_BOX_KEY].toString());
        ui->eraBox->setTitle(settings[EDITOR_ARTS_ERA_BOX_KEY].toString());
        ui->artInfoBox->setTitle(settings[EDITOR_ARTS_INFO_BOX_KEY].toString());
        ui->imageBox->setTitle(settings[EDITOR_ARTS_IMAGE_BOX_KEY].toString());
        ui->authorInfoBox->setVisible(false);
        ui->eraImageBox->setVisible(false);
        break;
    case AuthorsSection:
        settings[EDITOR_AUTHORS_NAME_BOX_KEY] = settings[EDITOR_AUTHORS_NAME_BOX_KEY].toString(EDITOR_AUTHORS_NAME_BOX);
        settings[EDITOR_AUTHORS_INFO_BOX_KEY] = settings[EDITOR_AUTHORS_INFO_BOX_KEY].toString(EDITOR_AUTHORS_INFO_BOX);
        settings[EDITOR_AUTHORS_IMAGE_BOX_KEY] = settings[EDITOR_AUTHORS_IMAGE_BOX_KEY].toString(EDITOR_AUTHORS_IMAGE_BOX);
        settings[EDITOR_AUTHORS_TEMPLATE_KEY] = settings[EDITOR_AUTHORS_TEMPLATE_KEY].toObject();
        settings[EDITOR_AUTHORS_WIDTH_KEY] = settings[EDITOR_AUTHORS_WIDTH_KEY].toInt(EDITOR_AUTHORS_WIDTH);
        settings[EDITOR_AUTHORS_HEIGHT_KEY] = settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt(EDITOR_AUTHORS_HEIGHT);
        setMinimumSize(EDITOR_AUTHORS_WIDTH, EDITOR_AUTHORS_HEIGHT);
        setGeometry(0, 0,
                    settings[EDITOR_AUTHORS_WIDTH_KEY].toInt(),
                    settings[EDITOR_AUTHORS_HEIGHT_KEY].toInt());
        ui->nameBox->setTitle(settings[EDITOR_AUTHORS_NAME_BOX_KEY].toString());
        ui->authorInfoBox->setTitle(settings[EDITOR_AUTHORS_INFO_BOX_KEY].toString());
        ui->imageBox->setTitle(settings[EDITOR_AUTHORS_IMAGE_BOX_KEY].toString());
        ui->artInfoBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->rankBox->setVisible(false);
        ui->eraImageBox->setVisible(false);
        break;
    case ErasSection:
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
        ui->imageBox->setVisible(false);
        ui->artInfoBox->setVisible(false);
        ui->authorInfoBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->rankBox->setVisible(false);
        break;
    }

    settingsChanged(getClassName(this), settings);
}

ItemEditor::~ItemEditor()
{
    delete ui;
}

void ItemEditor::resizeEvent(QResizeEvent *event)
{
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
        settingsChanged(getClassName(this), settings);
    }
}

void ItemEditor::on_cancelButton_clicked()
{
    close();
}
