#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QDialog>
#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QResizeEvent>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDate>

#include "defines.h"
#include "templates.h"
#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"
#include "modules/txtprocessor.h"
#include "modules/tableprocessor.h"

#include "widgets/chooselist.h"

class ItemEditor;

class ImageView : public QLabel
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = nullptr) : QLabel(parent) {editor = (ItemEditor*)parent;};
    void initData(QString path = "");

protected:
    void resizeEvent(QResizeEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void clicked();

private:
    QImage origImage;
    ItemEditor *editor;
};

namespace Ui {
class ItemEditor;
}

class ItemEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ItemEditor(QWidget *parent = nullptr);
    void initData(QJsonObject &opt, JsonDataSections &sec, QString path, QStringList ranks = QStringList());
    void editData(int index, QJsonObject data);
    void addData();
    ~ItemEditor();

public slots:
    void recieveEras(QStringList &list);
    void recieveAuthors(QStringList &list);

protected:
    bool isValidDateFormat(QString format);
    int findEraIndex(QString key);
    void fillWidgets();
    void fillRanks();
    void fillAuthors();
    void clearWidgets();
    void resizeEvent(QResizeEvent *event);

signals:
    void settingsChanged(QString, QJsonObject);
    void readyForEras(QString);
    void readyForAuthors(QString);

private slots:
    void openNewImage();
    void saveTemplate();
    void clearTemplate();
    void replaceAuthors(QStringList &list);
    void on_cancelButton_clicked();
    void on_authorDelButton_clicked();
    void on_authorAddButton_clicked();
    void on_addEditButton_clicked();

private:
    Ui::ItemEditor *ui;
    JsonDataSections section;
    QJsonObject allSettings, settings, itemTemplate, currentItem, errorsMsg;
    QImage image;
    ImageView *imageView;
    QStringList artRanks;
    int itemIndex = -1;
    QString allFilesPath, secFilesPath, currentFilePath;
    QMenu templateMenu;
    QAction *saveTemplateA, *clearTemplateA;
    QFileDialog dialog;
    QStringList eras, authors;
    ChooseList authorsList;
};

#endif // ITEMEDITOR_H
