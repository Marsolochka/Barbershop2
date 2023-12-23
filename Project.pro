#-------------------------------------------------
#
# Project created by QtCreator 2023-12-15T15:07:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Project
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client_service.cpp \
    administrator.cpp \
    user.cpp \
    main_screen.cpp \
    client.cpp

HEADERS += \
    main_screen.h \
    user.h \
    client_service.h \
    administrator.h \
    client.h \
    service.h
