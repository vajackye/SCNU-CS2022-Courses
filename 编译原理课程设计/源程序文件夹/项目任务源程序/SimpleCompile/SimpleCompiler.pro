QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common.cpp \
    grammerdo.cpp \
    gramtable.cpp \
    lexsource.cpp \
    main.cpp \
    mainwindow.cpp \
    minidfa.cpp \
    nfatodfa.cpp \
    nodetable.cpp \
    predore.cpp \
    retonfa.cpp \
    taskonewindow.cpp \
    tasktwowindow.cpp

HEADERS += \
    common.h \
    grammerdo.h \
    gramtable.h \
    lexsource.h \
    lexsource.h \
    mainwindow.h \
    minidfa.h \
    nfatodfa.h \
    nodetable.h \
    predore.h \
    retonfa.h \
    taskonewindow.h \
    tasktwowindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
