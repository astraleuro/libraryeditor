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

    switch (section) {
    case ArtsSection:
        settings[EDITOR_ARTS_NAME_BOX_KEY] = settings[EDITOR_ARTS_NAME_BOX_KEY].toString(EDITOR_ARTS_NAME_BOX);
        settings[EDITOR_ARTS_AUTHORS_BOX_KEY] = settings[EDITOR_ARTS_AUTHORS_BOX_KEY].toString(EDITOR_ARTS_AUTHORS_BOX);
        settings[EDITOR_ARTS_RANK_BOX_KEY] = settings[EDITOR_ARTS_RANK_BOX_KEY].toString(EDITOR_ARTS_RANK_BOX);
        settings[EDITOR_ARTS_ERA_BOX_KEY] = settings[EDITOR_ARTS_ERA_BOX_KEY].toString(EDITOR_ARTS_ERA_BOX);
        settings[EDITOR_ARTS_INFO_BOX_KEY] = settings[EDITOR_ARTS_INFO_BOX_KEY].toString(EDITOR_ARTS_INFO_BOX);
        settings[EDITOR_ARTS_TEMPLATE_KEY] = settings[EDITOR_ARTS_TEMPLATE_KEY].toObject();
        break;
    case AuthorsSection:
        settings[EDITOR_AUTHOR_NAME_BOX_KEY] = settings[EDITOR_AUTHOR_NAME_BOX_KEY].toString(EDITOR_AUTHOR_NAME_BOX);
        settings[EDITOR_AUTHOR_INFO_BOX_KEY] = settings[EDITOR_AUTHOR_INFO_BOX_KEY].toString(EDITOR_AUTHOR_INFO_BOX);
        settings[EDITOR_AUTHORS_TEMPLATE_KEY] = settings[EDITOR_AUTHORS_TEMPLATE_KEY].toObject();
        break;
    case ErasSection:
        settings[EDITOR_ERAS_NAME_BOX_KEY] = settings[EDITOR_ERAS_NAME_BOX_KEY].toString(EDITOR_ERAS_NAME_BOX);
        settings[EDITOR_ERAS_INFO_BOX_KEY] = settings[EDITOR_ERAS_INFO_BOX_KEY].toString(EDITOR_ERAS_INFO_BOX);
        settings[EDITOR_ERAS_TEMPLATE_KEY] = settings[EDITOR_ERAS_TEMPLATE_KEY].toObject();
        break;
    }

    adoptWidgets();
    settingsModified();
}

ItemEditor::~ItemEditor()
{
    delete ui;
}

void ItemEditor::adoptWidgets()
{
    if (section == ArtsSection) {
        ui->otherInfoBox->setVisible(false);
    } else {
        ui->artInfoBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->rankBox->setVisible(false);
    }

    switch (section) {
    case ArtsSection:
        break;
    case AuthorsSection:
        break;
    case ErasSection:
        break;
    }
}
