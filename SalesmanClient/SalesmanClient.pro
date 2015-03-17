#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T20:45:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = SalesmanClient
TEMPLATE = app
#CONFIG += c++11

SOURCES += main.cpp\
    salesmanweightmatrixmodel.cpp \
    salesmanmainwidget.cpp \
    salesmancalculation.cpp

HEADERS  += \
    salesmanweightmatrixmodel.h \
    salesmanmainwidget.h \
    salesmancalculation.h

FORMS += \
    salesmanmainwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../salesmanLib/release/ -lsalesmanLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../salesmanLib/debug/ -lsalesmanLib
else:unix: LIBS += -L$$OUT_PWD/../salesmanLib/ -lsalesmanLib

INCLUDEPATH += $$PWD/../salesmanLib
DEPENDPATH += $$PWD/../salesmanLib

RESOURCES += \
    images.qrc

win32:RC_ICONS = img/evoluting256.ico
