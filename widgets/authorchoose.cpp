#include "authorchoose.h"
#include "ui_authorchoose.h"

AuthorChoose::AuthorChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorChoose)
{
    ui->setupUi(this);

    tableDelegate = new AuthorItemDelegate;
    connect(tableDelegate, SIGNAL(itemActivated(int)), this, SLOT(toggleRow(int)));
    delete ui->chooseTable->itemDelegate();
    ui->chooseTable->setItemDelegate(tableDelegate);
}

void AuthorChoose::initData(QJsonObject &opt, QStringList &list)
{
    tableFromList(ui->chooseTable, list, 1);
    settings = opt[getClassName(this)].toObject();
    errorsMsg = opt[ERRORS_SUBSECTION_KEY].toObject();

    settings[CHOOSER_TITLE_KEY] = settings[CHOOSER_TITLE_KEY].toString(CHOOSER_TITLE);
    settings[CHOOSER_SEARCH_BOX_KEY] = settings[CHOOSER_SEARCH_BOX_KEY].toString(CHOOSER_SEARCH_BOX);
    settings[CHOOSER_SEARCH_BUTTON_KEY] = settings[CHOOSER_SEARCH_BUTTON_KEY].toString(CHOOSER_SEARCH_BUTTON);
    settings[CHOOSER_DONE_BUTTON_KEY] = settings[CHOOSER_DONE_BUTTON_KEY].toString(CHOOSER_DONE_BUTTON);
    settings[CHOOSER_CANCEL_BUTTON_KEY] = settings[CHOOSER_CANCEL_BUTTON_KEY].toString(CHOOSER_CANCEL_BUTTON);

    setWindowTitle(settings[CHOOSER_TITLE_KEY].toString());
    ui->searchBox->setTitle(settings[CHOOSER_SEARCH_BOX_KEY].toString());
    ui->searchApply->setText(settings[CHOOSER_SEARCH_BUTTON_KEY].toString());
    ui->chooseButton->setText(settings[CHOOSER_DONE_BUTTON_KEY].toString());
    ui->cancelButton->setText(settings[CHOOSER_CANCEL_BUTTON_KEY].toString());

    settingsChanged(getClassName(this), settings);
}

void AuthorChoose::checkByList(QStringList list)
{
    ui->chooseTable->clearSelection();
    for (int i = 0; i < ui->chooseTable->rowCount(); i++)
        if (list.contains(ui->chooseTable->item(i, 1)->text()))
            checkRow(i);
        else
            uncheckRow(i);
}

AuthorChoose::~AuthorChoose()
{
    delete tableDelegate;
    delete ui;
}

int AuthorChoose::searchItem(const QString &phrase, int row)
{
    for (int i = row; i < ui->chooseTable->rowCount(); i++)
        if (ui->chooseTable->item(i, 1)->text().toLower().contains(phrase.toLower()))
            return i;
    return -1;
}

void AuthorChoose::checkRow(int row)
{
    ui->chooseTable->item(row, 0)->setText("+");
    ui->chooseTable->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void AuthorChoose::uncheckRow(int row)
{
    ui->chooseTable->item(row, 0)->setText(" ");
    ui->chooseTable->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void AuthorChoose::toggleRow(int row)
{
    if (ui->chooseTable->item(row, 0)->text() == "+")
        ui->chooseTable->item(row, 0)->setText(" ");
    else
        ui->chooseTable->item(row, 0)->setText("+");
}

void AuthorChoose::on_chooseButton_clicked()
{
    QStringList list;
    for (int i = 0; i < ui->chooseTable->rowCount(); i++)
        if (ui->chooseTable->item(i, 0)->text() == "+")
            list.append(ui->chooseTable->item(i, 1)->text());
    chooseIsDone(list);
    close();
}

void AuthorChoose::on_cancelButton_clicked()
{
    close();
}

void AuthorChoose::on_searchApply_clicked()
{
    QString phrase = ui->searchEdit->text();
    if (!phrase.isEmpty()) {
        int row = -1;
        QTableWidget *table = ui->chooseTable;
        if (table->selectedItems().count() > 0)
            row = searchItem(phrase, table->selectedItems().first()->row() + 1);
        if (row == -1)
            row = searchItem(phrase);
        if (row != -1)
            ui->chooseTable->selectRow(row);
    }
}
