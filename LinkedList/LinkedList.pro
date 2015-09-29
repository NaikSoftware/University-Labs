TEMPLATE = app
CONFIG += C++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    apartament.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    util/linkedlist.h \
    util/list.h \
    apartament.h

DISTFILES += \
    java.astylerc

