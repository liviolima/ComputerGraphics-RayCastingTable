#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T19:56:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Table
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    ray.cpp \
    camera.cpp \
    object.cpp \
    triangle.cpp \
    numbervector.cpp \
    color.cpp \
    cube.cpp

HEADERS  += mainwindow.h \
    scene.h \
    ray.h \
    camera.h \
    object.h \
    triangle.h \
    numbervector.h \
    color.h \
    cube.h

FORMS    += mainwindow.ui

CONFIG += console
