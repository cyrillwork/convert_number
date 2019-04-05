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

SOURCES += main.cpp \
    bignumber.cpp
HEADERS += bignumber.h
