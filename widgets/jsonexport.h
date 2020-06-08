#ifndef JSONEXPORT_H
#define JSONEXPORT_H

#include <QDialog>

namespace Ui {
class JsonExport;
}

class JsonExport : public QDialog
{
    Q_OBJECT

public:
    explicit JsonExport(QWidget *parent = nullptr);
    ~JsonExport();

private:
    Ui::JsonExport *ui;
};

#endif // JSONEXPORT_H
