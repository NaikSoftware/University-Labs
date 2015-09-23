TEMPLATE = app
CONFIG += C++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    util/linkedlist.h \
    util/list.h

DISTFILES += \
    java.astylerc

