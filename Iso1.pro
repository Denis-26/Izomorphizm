QT += core
QT -= gui

CONFIG += c++11

TARGET = Iso1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    graph.cpp

HEADERS += \
    graph.h
