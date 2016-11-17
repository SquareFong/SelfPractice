QT += core
QT -= gui

CONFIG += c++11

TARGET = myFileManager
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    item.h \
    filemanage.h
