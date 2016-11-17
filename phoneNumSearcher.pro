QT += core
QT -= gui

CONFIG += c++11

TARGET = phoneNumSearcher
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    hash.cpp

HEADERS += \
    hash.h
