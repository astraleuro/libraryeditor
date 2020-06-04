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
    section = sec;
    switch (section) {
    case ArtsSection:
        hideWidgets(true);
        break;
    case AuthorsSection:
        hideWidgets(false);
        break;
    case ErasSection:

        break;
    }
}

ItemEditor::~ItemEditor()
{
    delete ui;
}

void ItemEditor::hideWidgets(bool isArtsSection)
{
    if (isArtsSection) {
        ui->otherInfoBox->setVisible(false);
    } else {
        ui->artInfoBox->setVisible(false);
        ui->authorsBox->setVisible(false);
        ui->eraBox->setVisible(false);
        ui->rankBox->setVisible(false);
    }
}
