#-------------------------------------------------
#
# Project created by QtCreator 2019-10-27T20:41:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(GifImage/src/gifimage/qtgifimage.pri)

TARGET = Constructor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    drawingtools.cpp \
    editortools.cpp \
    gifexport.cpp \
    load.cpp \
    main.cpp \
    mainwindow.cpp \
    editor.cpp \
    editorview.cpp \
    animatedpreview.cpp \
    frame.cpp \
    framecontainer.cpp \
    framepreview.cpp \
    framepreviewscroll.cpp \
    framelabel.cpp \
    save.cpp \
    editortoolsspinbox.cpp

HEADERS += \
    drawingtools.h \
    editortools.h \
    gifexport.h \
    load.h \
    mainwindow.h \
    editor.h \
    editorview.h \
    animatedpreview.h \
    frame.h \
    framecontainer.h \
    framepreview.h \
    framepreviewscroll.h \
    framelabel.h \
    save.h \
    editortoolsspinbox.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Editor/background.png \
    ../AnimatedPreview/sprite_0.png \
    ../AnimatedPreview/sprite_1.png \
    ../AnimatedPreview/sprite_2.png \
    ../AnimatedPreview/sprite_3.png \
    ../AnimatedPreview/sprite_4.png \
    ../AnimatedPreview/sprite_5.png

RESOURCES += \
    images.qrc
