# -------------------------------------------------
# Project created by QtCreator 2017-10-07T22:51:01
# -------------------------------------------------
QT -= gui
TARGET = convertor

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG += console

CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $${_PRO_FILE_PWD_}/depends/BigNumber

SOURCES += main.cpp
HEADERS +=

LIBS += depends/BigNumber/bignumber.o