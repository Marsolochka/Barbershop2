#-------------------------------------------------
#
# Project created by QtCreator 2023-12-15T15:07:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = Project
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client_service.cpp \
    administrator.cpp \
    user.cpp \
    main_screen.cpp

HEADERS += \
    main_screen.h \
    user.h \
    client_service.h \
    administrator.h \
    client.h \
    service.h \
    main_screen.h
