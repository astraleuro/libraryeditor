#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QDialog>
#include <QResizeEvent>

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
    void resizeEvent(QResizeEvent *event);

signals:
    void settingsChanged(QString, QJsonObject);

private slots:
    void on_cancelButton_clicked();

private:
    Ui::ItemEditor *ui;
    bool isAddDialog = true;
    JsonDataSections section;
    QJsonObject allSettings, settings, itemTemplate;
};

#endif // ITEMEDITOR_H
