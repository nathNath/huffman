QT += core
QT -= gui

CONFIG += c++11

TARGET = Huffman
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += .

SOURCES += main.cpp \
    huffman.cpp \
    node.cpp

HEADERS += \
    huffman.h \
    node.h
