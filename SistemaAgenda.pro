QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = SistemaAgenda
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    contato.cpp \
    gerenciadorcsv.cpp

HEADERS += \
    mainwindow.h \
    contato.h \
    gerenciadorcsv.h
