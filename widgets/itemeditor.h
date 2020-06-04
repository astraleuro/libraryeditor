#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QDialog>

#include "defines.h"
#include "templates.h"

#include "modules/jsonprocessor.h"

namespace Ui {
class ItemEditor;
}

class ItemEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ItemEditor(QWidget *parent = nullptr);
    void initData(QJsonObject &opt, JsonDataSections &sec);
    void setData(QJsonObject &data);
    void getData();
    ~ItemEditor();

protected:
    void hideWidgets(bool isArtsSection);

private:
    Ui::ItemEditor *ui;
    bool isSectionValid = false;
    JsonDataSections section;
};

#endif // ITEMEDITOR_H
