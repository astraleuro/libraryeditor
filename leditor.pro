QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 -Wunused-parameter

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    modules/fsprocessor.cpp \
    modules/jsonprocessor.cpp \
    modules/txtprocessor.cpp \
    widgets/arraylist.cpp \
    widgets/itemeditor.cpp \
    widgets/mainlist.cpp \
    widgets/welcomescreen.cpp

HEADERS += \
    defines.h \
    mainwindow.h \
    modules/fsprocessor.h \
    modules/jsonprocessor.h \
    modules/txtprocessor.h \
    templates.h \
    widgets/arraylist.h \
    widgets/itemeditor.h \
    widgets/mainlist.h \
    widgets/welcomescreen.h

FORMS += \
    widgets/arraylist.ui \
    widgets/itemeditor.ui \
    widgets/mainlist.ui \
    widgets/welcomescreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
