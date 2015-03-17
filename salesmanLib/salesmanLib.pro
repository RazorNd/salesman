#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T18:33:42
#
#-------------------------------------------------

QT       -= core gui

TARGET = salesmanLib
TEMPLATE = lib

DEFINES += SALESMANLIB_LIBRARY

SOURCES += salesman.cpp \
    substitution.cpp \
    objectivefunction.cpp

HEADERS += salesman.h \
    substitution.h \
    objectivefunction.h

#CONFIG += c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}
