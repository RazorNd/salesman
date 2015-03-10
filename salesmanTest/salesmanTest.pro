TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../salesmanLib/release/ -lsalesmanLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../salesmanLib/debug/ -lsalesmanLib
else:unix: LIBS += -L$$OUT_PWD/../salesmanLib/ -lsalesmanLib

INCLUDEPATH += $$PWD/../salesmanLib
DEPENDPATH += $$PWD/../salesmanLib

OTHER_FILES += \
    input.txt
