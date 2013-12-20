#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T22:52:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addpersondialog.cpp \
    person.cpp \
    people.cpp \
    bag_of_words.cpp

HEADERS  += mainwindow.h \
    addpersondialog.h \
    person.h \
    people.h \
    bag_of_words.h

FORMS    += mainwindow.ui \
    addpersondialog.ui

LIBS += `pkg-config --libs opencv`

