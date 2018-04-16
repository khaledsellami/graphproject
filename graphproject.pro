TEMPLATE = app
TARGET = graphproject

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp \
    mainwindow.cpp \
    button.cpp

HEADERS += \
    mainwindow.h \
    button.h

RESOURCES += \
    graphprojectresource.qrc
