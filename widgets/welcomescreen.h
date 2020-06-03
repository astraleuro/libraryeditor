#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>
#include <QFileDialog>

#include "defines.h"
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
    ~WelcomeScreen();

signals:
    void dataReady(QString, QJsonObject&);
    void closeApp();

protected slots:
    void saveData();
    void openData();

private:
    Ui::WelcomeScreen *ui;
};

#endif // WELCOMESCREEN_H
