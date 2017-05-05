#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T14:46:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CDesigner
TEMPLATE = app


SOURCES += \
    ctabwidget.cpp \
    main.cpp \
    widget.cpp \
    cbutton.cpp \
    cdef.cpp \
    cstatement.cpp \
    cscope.cpp \
    cfunction.cpp \
    csentence.cpp \
    cif.cpp \
    clineedit.cpp \
    cifelse.cpp \
    cwhile.cpp \
    cdowhile.cpp \
    cfor.cpp \
    cbaffle.cpp \
    cfunctiondialog.cpp \
    ccase.cpp \
    cswitch.cpp \
    cbreaksentence.cpp \
    ccontinuesentence.cpp \
    creturnsentence.cpp

HEADERS  += \
    ctabwidget.h \
    widget.h \
    cbutton.h \
    cdef.h \
    cstatement.h \
    cscope.h \
    cfunction.h \
    csentence.h \
    cif.h \
    clineedit.h \
    cifelse.h \
    cwhile.h \
    cdowhile.h \
    cfor.h \
    cbaffle.h \
    cfunctiondialog.h \
    ccase.h \
    cswitch.h \
    cbreaksentence.h \
    ccontinuesentence.h \
    creturnsentence.h

DISTFILES +=

FORMS += \
    cfunctiondialog.ui

RESOURCES += \
    icons.qrc
