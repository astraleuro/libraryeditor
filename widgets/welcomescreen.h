#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "defines.h"
#include "templates.h"
#include "modules/fsprocessor.h"
#include "modules/jsonprocessor.h"

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = nullptr);
    void initData(QJsonObject &opt, QString defaultPath);
    void openFile(QString fn);
    ~WelcomeScreen();

protected:
    void showMsg(QMessageBox::Icon icon, QString text);

signals:
    void settingsChanged(QString, QJsonObject);
    void dataReady(QString, QJsonObject&);
    void closeApp();

protected slots:
    void saveData();
    void openData(QString fn = "");

private slots:
    void on_openLastBase_clicked();

private:
    Ui::WelcomeScreen *ui;
    QJsonObject settings, errorsMsg;
};

#endif // WELCOMESCREEN_H
